/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:55:24 by rcochran          #+#    #+#             */
/*   Updated: 2025/08/26 00:45:39 by rcochran         ###   ########.fr       */
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
	time_t	offset;

	i = 0;
	if (!data->nb_philo)
		return (1);
	offset = data->nb_philo * 20;
	if (!data || !data->philos)
		return (1);
	time = get_time_in_ms();
	data->start_time = time + offset;
	while (i < data->nb_philo && data->philos[i])
	{
		data->philos[i]->last_meal = time + offset;
		data->philos[i]->start_time = time + offset;
		i++;
	}
	return (0);
}

int	start_sim(t_data *data)
{
	int	i;

	i = 0;
	if (!data)
		return (1);
	if (!data->philos)
		return (ft_putstr_fd("Error : no philos\n", 2), 1);
	set_last_meal(data);
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philos[i]->thread, NULL,
				&routine, (void *)data->philos[i]) != 0)
		{
			pthread_mutex_lock(&data->mtx);
			data->has_stopped = 1;
			pthread_mutex_unlock(&data->mtx);
			return (printf("i = %d\n", i), ft_putstr_fd("Thread error\n", 2), i);
		}
		i++;
	}
	return (i);
}

int	stop_sim(t_data *data, int stop)
{
	int		i;

	i = 0;
	// if (stop != data->nb_philo)
	// {
	// 	while (i < stop)
	// 	{
	// 		if (pthread_detach(data->philos[i]->thread) != 0)
	// 			return (ft_putstr_fd("Thread detach error\n", 2), 1);
	// 		i++;
	// 	}
	// 	return (free_data(data), 0);
	// }
	while (i < stop)
	{
		if (pthread_join(data->philos[i]->thread, NULL) != 0)
			return (ft_putstr_fd("Thread join error\n", 2), 1);
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
