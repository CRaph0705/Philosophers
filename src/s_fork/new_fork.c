/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_fork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:48:43 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/17 14:57:56 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_fork	*create_t_fork(void);
void	add_to_list(t_fork *new, t_fork *list);
void	delete_fork(t_fork *tfork);
void	free_forks(t_fork *tfork);

t_fork	*create_t_fork(void)
{
	t_fork	*new;

	new = malloc(sizeof(t_fork));
	if (!new)
		return (NULL);
	new->is_used = false;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	add_to_list(t_fork *new, t_fork *list)
{
	t_fork	*old_prev;

	old_prev = NULL;
	if (!list)
	{
		list = new;
		list->head = new;
		return ;
	}
	old_prev = list->head->prev;
	if (old_prev)
	{
		list->head->prev = new;
		new->next = list->head;
		new->prev = old_prev;
		old_prev->next = new;
	}
	else
	{
		list->head->prev = new;
		list->head->next = new;
		new->next = list->head;
		new->prev = list->head;
	}
}

void	delete_fork(t_fork *tfork)
{
	t_fork	*prev;
	t_fork	*next;

	prev = NULL;
	next = NULL;
	if (!tfork)
		return ;
	prev = tfork->prev;
	next = tfork->next;
	prev->next = next;
	next->prev = prev;
	tfork->next = NULL;
	tfork->prev = NULL;
	tfork->head = NULL;
	free(tfork);
}

void	free_forks(t_fork *tfork)
{
	t_fork	*cursor;
	t_fork	*tmp;

	if (!tfork)
		return ;
	cursor = tfork->head;
	while (cursor->next)
	{
		tmp = cursor;
		delete_fork(tmp);
		cursor = cursor->next;
	}
}
