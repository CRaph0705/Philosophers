/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 16:16:20 by rcochran          #+#    #+#             */
/*   Updated: 2025/08/27 00:00:46 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo);

int	check_death(t_philo *philo)
{
	long	now;
	long	last;

	pthread_mutex_lock(&philo->data->m_death);
	if (philo->is_dead || philo->data->has_stopped)
	{
		pthread_mutex_unlock(&philo->data->m_death);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->m_death);
	now = get_time_in_ms();
	pthread_mutex_lock(&philo->data->m_time);
	last = philo->last_meal;
	pthread_mutex_unlock(&philo->data->m_time);
	if (now - last >= philo->time_to_die)
	{
		pthread_mutex_lock(&philo->data->m_death);
		if (!philo->is_dead && !philo->data->has_stopped)
		{
			philo->is_dead = 1;
			philo->data->has_stopped = 1;
			pthread_mutex_lock(&philo->data->m_print);
			printf("now = [%ld], philo->last_meal = [%ld], (now - philo->last_meal) = [%ld], philo->time_to_die = [%d]\n", now, philo->last_meal, (now - philo->last_meal), philo->time_to_die);
			printf("%ld %d died\n", now - philo->start_time, philo->id);
			pthread_mutex_unlock(&philo->data->m_print);
		}
		pthread_mutex_unlock(&philo->data->m_death);
		return (1);
	}
	return (0);
}
