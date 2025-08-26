/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 23:33:53 by rcochran          #+#    #+#             */
/*   Updated: 2025/08/27 00:11:17 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void	*monitor(void *arg);

static int all_meals_done(t_data *data)
{
	int done;
	
	done = 0;
	pthread_mutex_lock(&data->m_meals);
	if (data->max_meal > 0 && data->nb_meals >= data->nb_philo)
		done = 1;
	pthread_mutex_unlock(&data->m_meals);
	return (done);
}

void	*monitor(void *arg)//TODO à redécouper
{
	t_data *data = (t_data *)arg;

	while (1)
	{
		pthread_mutex_lock(&data->m_death);
		if (data->has_stopped)
		{
			pthread_mutex_unlock(&data->m_death);
			break;
		}
		pthread_mutex_unlock(&data->m_death);
		if (all_meals_done(data))
		{
			pthread_mutex_lock(&data->m_death);
			data->has_stopped = 1;
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
				if (!data->has_stopped)
				{
					data->has_stopped = 1;
					pthread_mutex_lock(&data->m_print);
					printf("%ld %d died\n",
							now - data->start_time, data->philos[i]->id);
					pthread_mutex_unlock(&data->m_print);
				}
				pthread_mutex_unlock(&data->m_death);
				return NULL;
			}
		}
		usleep(1000);
	}
	return NULL;
	}
