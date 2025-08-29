/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 10:20:07 by rcochran          #+#    #+#             */
/*   Updated: 2025/08/29 10:26:52 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	launch_monitor(t_data *data);
int	launch_philos(t_data *data);

int	launch_monitor(t_data *data)
{
	if (pthread_create(&data->monitor, NULL, &monitor, data) != 0)
	{
		pthread_mutex_lock(&data->m_stop);
		data->simulation_stop = 1;
		pthread_mutex_unlock(&data->m_stop);
		return (ft_putstr_fd("Monitor thread error\n", 2), 1);
	}
	return (0);
}

int	launch_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philos[i]->thread, NULL,
				&routine, (void *)data->philos[i]) != 0)
		{
			pthread_mutex_lock(&data->m_stop);
			data->simulation_stop = 1;
			pthread_mutex_unlock(&data->m_stop);
			return (ft_putstr_fd("Thread error\n", 2), i);
		}
		i++;
		pthread_mutex_lock(&data->m_meals);
		data->ready_count++;
		pthread_mutex_unlock(&data->m_meals);
	}
	return (i);
}
