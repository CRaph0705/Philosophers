/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 23:33:53 by rcochran          #+#    #+#             */
/*   Updated: 2025/08/28 15:10:33 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void			*monitor(void *arg);

void	*monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!data->simulation_stop)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			// if (!safe_mutex_lock(&(data->philos[i]->m_status), data))
			// 	return (NULL);
			safe_mutex_lock(&(data->philos[i]->m_status), data);
			if (is_philo_dead(data, get_time_in_ms(), i))
				return (NULL);
			pthread_mutex_unlock(&(data->philos[i]->m_status));
			i++;
		}
		if (nb_meal_reached(data))
		{
			safe_mutex_lock(&(data->m_stop), data);
			data->simulation_stop = 1;
			pthread_mutex_unlock(&(data->m_stop));
			return (NULL);
		}
	}
	return (NULL);
}
