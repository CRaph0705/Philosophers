/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:55:24 by rcochran          #+#    #+#             */
/*   Updated: 2025/08/27 16:13:57 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>
/**
 *  Mandatory part
 * • Each philosopher must be represented as a separate thread.
 * • There is one fork between each pair of philosophers.
 * Therefore, if there are several philosophers, 
 * each philosopher has a fork on their left side and a fork on their right side.
 * If there is only one philosopher, they will have access to just one fork.
 * • To prevent philosophers from duplicating forks,
 * you should protect each fork’s state with a mutex.
*/

int	set_last_meal(t_data *data)
{
	int		i;
	time_t	time;

	i = 0;
	if (!data->nb_philo)
		return (1);
	if (!data || !data->philos)
		return (1);
	time = get_time_in_ms();
	data->start_time = time;
	while (i < data->nb_philo && data->philos[i])
	{
		pthread_mutex_lock(&data->philos[i]->m_status);
		data->philos[i]->last_meal = time;
		data->philos[i]->start_time = time;
		pthread_mutex_unlock(&data->philos[i]->m_status);
		i++;
	}
	return (0);
}
/* void	*routine(void	*p_philo)
{
	t_philo	*philo;

	philo = (t_philo *)p_philo;
	safe_mutex_lock(&philo->data->m_print, philo->data);
	printf("routine\n");
	pthread_mutex_unlock(&philo->data->m_print);
	return (NULL);
} */

/* void	*monitor(void *p_data)
{
	t_data	*data;

	data = (t_data *)p_data;
	safe_mutex_lock(&data->m_print, data);
	printf("monitor\n");
	pthread_mutex_unlock(&data->m_print);
	return (NULL);
} */

int	start_sim(t_data *data)
{
	int	i;

	i = 0;
	if (!data)
		return (1);
	if (!data->philos)
		return (ft_putstr_fd("Error : no philos\n", 2), 1);
	set_last_meal(data);
	if (pthread_create(&data->monitor, NULL, &monitor, data) != 0)
	{
		pthread_mutex_lock(&data->m_stop);
		data->simulation_stop = 1;
		pthread_mutex_unlock(&data->m_stop);
		return (ft_putstr_fd("Monitor thread error\n", 2), i);
	}
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

int	stop_sim(t_data *data, int stop)
{
	int		i;

	i = 0;
	if (pthread_join(data->monitor, NULL) != 0)
	{
		pthread_mutex_lock(&data->m_print);
		ft_putstr_fd("Thread join error\n", 2);
		pthread_mutex_unlock(&data->m_print);
	}
	while (i < stop)
	{
		if (pthread_join(data->philos[i]->thread, NULL) != 0)
		{
			pthread_mutex_lock(&data->m_print);
			ft_putstr_fd("Thread join error\n", 2);
			pthread_mutex_unlock(&data->m_print);
			return (1);
		}
		i++;
	}
	return (free_data(data), 0);
}

int	main(int ac, char **av)
{
	t_data			*data;
	int				stop;

	stop = 0;
	if (invalid_args(ac, av))
		return (1);
	data = init_data(ac, av);
	if (!data)
		return (42);
	stop = start_sim(data);
	stop_sim(data, stop);
	return (0);
}
