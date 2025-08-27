/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 23:33:53 by rcochran          #+#    #+#             */
/*   Updated: 2025/08/27 18:23:03 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void	*monitor(void *arg);

/* static int all_meals_done(t_data *data)
{
	int done;
	
	done = 0;
	pthread_mutex_lock(&data->m_meals);
	if (data->max_meal > 0 && data->nb_meals >= data->nb_philo)
		done = 1;
	pthread_mutex_unlock(&data->m_meals);
	return (done);
} */

void	*monitor(void *arg)//TODO à redécouper
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!data->simulation_stop)
	{
		i = 0;
		while (i < data->nb_philo)
		{
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


/* 		pthread_mutex_lock(&data->m_death);
		if (data->simulation_stop)
		{
			pthread_mutex_unlock(&data->m_death);
			break;
		}
		pthread_mutex_unlock(&data->m_death);
		if (all_meals_done(data))
		{
			pthread_mutex_lock(&data->m_death);
			data->simulation_stop = 1;
			pthread_mutex_unlock(&data->m_death);
			break;
		}
		long now = get_time_in_ms();
		for (int i = 0; i < data->nb_philo; i++)
		{
			long last;
			pthread_mutex_lock(&data->m_time);
			last = data->philos[i]->last_meal;
			pthread_mutex_unlock(&data->m_time);
			if (now - last >= data->time_to_die)
			{
				pthread_mutex_lock(&data->m_death);
				if (!data->simulation_stop)
				{
					data->simulation_stop = 1;
					pthread_mutex_lock(&data->m_print);
					printf("%ld %d died\n",
							now - data->start_time, data->philos[i]->id);
					pthread_mutex_unlock(&data->m_print);
				}
				pthread_mutex_unlock(&data->m_death);
				return NULL;
			}
		}
		usleep(1000); */