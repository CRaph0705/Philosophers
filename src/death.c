/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 16:16:20 by rcochran          #+#    #+#             */
/*   Updated: 2025/08/28 17:21:30 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_philo_dead(t_data *data, long now, int i)
{
	t_philo	*philo;

	philo = data->philos[i];
	if ((now - philo->last_meal) > data->time_to_die)
	{
		if (!safe_mutex_lock(&(data->m_print), data))
			return (1);
		pthread_mutex_lock(&(data->m_stop));
		printf("%ld %d died\n", now - data->start_time, philo->id);
		data->simulation_stop = 1;
		pthread_mutex_unlock(&(data->m_stop));
		pthread_mutex_unlock(&(data->m_print));
		pthread_mutex_unlock(&(philo->m_status));
		return (1);
	}
	return (0);
}
