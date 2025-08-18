/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:56:06 by rcochran          #+#    #+#             */
/*   Updated: 2025/08/18 17:58:46 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	do_eat(t_philo *philo);
void	do_sleep(t_philo *philo);
void	do_think(t_philo *philo);
void	*routine(void *p_philo);

void	do_eat(t_philo *philo)
{
	printf("[TIMESTAMP_IN_MS] %d is eating\n", philo->id);
	usleep(philo->time_to_eat);
}

void	do_sleep(t_philo *philo)
{
	printf("[TIMESTAMP_IN_MS] %d is sleeping\n", philo->id);
	usleep(philo->time_to_sleep);
}

void	do_think(t_philo *philo)
{
	printf("[TIMESTAMP_IN_MS] %d is thinking\n", philo->id);
	usleep(300);
}

void	*routine(void *p_philo)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (void *)(p_philo);
	while (philo->data->has_stopped == 0 && i < 10)
	{	
		do_eat(philo);
		do_sleep(philo);
		do_think(philo);
		i++;
	}
	return (NULL);
}
