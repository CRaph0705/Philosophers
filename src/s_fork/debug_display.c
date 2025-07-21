/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:58:18 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/17 15:20:30 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	debug_display_fork_list(t_fork *tfork);
void	display_fork(t_fork *tfork);

void	debug_display_fork_list(t_fork *tfork)
{
	t_fork	*head;
	t_fork	*cursor;
	int		i;

	cursor = NULL;
	i = 0;
	if (!tfork)
		return ;
	head = tfork;
	while (cursor->next && cursor != head && i > 0)
	{
		display_fork(cursor);
		cursor = cursor->next;
		i++;
	}
}

void	display_fork(t_fork *tfork)
{
	if (!tfork)
		return ;
	printf("tfork->head ptr = %p\ntfork->next ptr = %p\ntfork->prev ptr = %p\n",
		tfork->head, tfork->next, tfork->prev);
}
