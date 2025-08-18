/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:56:06 by rcochran          #+#    #+#             */
/*   Updated: 2025/08/18 16:42:59 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	do_eat(int t_eat);
void	do_sleep(int t_sleep);
void	do_think(void);
void	*routine(void *data);

void	do_eat(int t_eat)
{
	printf("eating...\n");
	usleep(t_eat);
}

void	do_sleep(int t_sleep)
{
	printf("sleeping...\n");
	usleep(t_sleep);
}

void	do_think(void)
{
	printf("thinking...\n");
	usleep(300);
}

void	*routine(void *p_data)
{
	t_data	*data;
	int		i;

	i = 0;
	data = (void *)(p_data);
	while (data->has_stopped == 0 && i < 10)
	{	
		do_eat(data->time_to_eat);
		do_sleep(data->time_to_sleep);
		do_think();
		i++;
	}
	return (NULL);
}
