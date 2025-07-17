/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:48:43 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/17 14:28:14 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_fork	*create_t_fork(void);

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
