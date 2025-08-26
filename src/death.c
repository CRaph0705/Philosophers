/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 16:16:20 by rcochran          #+#    #+#             */
/*   Updated: 2025/08/26 14:44:53 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo);

int	check_death(t_philo *philo)
{
	long	now;

	pthread_mutex_lock(&philo->data->m_death);
	if (philo->is_dead || philo->data->has_stopped)
	{
		pthread_mutex_unlock(&philo->data->m_death);
		return (1);
	}
	now = get_time_in_ms() - philo->start_time;
	if (now - philo->last_meal >= philo->time_to_die)
	{
		if (!philo->is_dead && !philo->data->has_stopped)
		{

			printf("now = [%ld], philo->last_meal = [%ld], (now - philo->last_meal) = [%ld], philo->time_to_die = [%d]\n", now, philo->last_meal, (now - philo->last_meal), philo->time_to_die);
			printf("%ld %d died\n", now, philo->id);
			philo->is_dead = 1;
			philo->data->has_stopped = 1;
		}
		pthread_mutex_unlock(&philo->data->m_death);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->m_death);
	return (0);
}
