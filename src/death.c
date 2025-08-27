/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 16:16:20 by rcochran          #+#    #+#             */
/*   Updated: 2025/08/27 15:19:06 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo);

int	check_death(t_philo *philo)
{

	(void)philo;
	// long	now;
	// long	last;

	// now = get_time_in_ms();

	// safe_mutex_lock(&philo->data->m_death, philo->data);
	// if (now - last >= philo->time_to_die)
	// {
	// 	pthread_mutex_lock(&philo->data->m_death);
	// 	if (!philo->is_dead && !philo->data->simulation_stop)
	// 	{
	// 		philo->is_dead = 1;
	// 		philo->data->simulation_stop = 1;
	// 		pthread_mutex_lock(&philo->data->m_print);
	// 		printf("now = [%ld], philo->last_meal = [%ld], (now - philo->last_meal) = [%ld], philo->time_to_die = [%d]\n", now, philo->last_meal, (now - philo->last_meal), philo->time_to_die);
	// 		printf("%ld %d died\n", now - philo->start_time, philo->id);
	// 		pthread_mutex_unlock(&philo->data->m_print);
	// 	}
	// 	pthread_mutex_unlock(&philo->data->m_death);
	// 	return (1);
	// }
	return (0);
}

int	is_philo_dead(t_data *data, long now, int i)
{
	t_philo	*philo;

	philo = data->philos[i];
	if ((now - philo->last_meal) > data->time_to_die)
	{
		if (!safe_mutex_lock(&(data->m_print), data))
			return (TRUE);
		printf("%ld %d died\n", now - data->start_time, philo->id);
		pthread_mutex_unlock(&(data->m_print));
		pthread_mutex_lock(&(data->m_stop));
		data->simulation_stop = 1;
		pthread_mutex_unlock(&(data->m_stop));
		pthread_mutex_unlock(&(philo->m_status));
		return (TRUE);
	}
	return (FALSE);
}
