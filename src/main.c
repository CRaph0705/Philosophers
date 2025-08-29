/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:55:24 by rcochran          #+#    #+#             */
/*   Updated: 2025/08/29 10:12:28 by rcochran         ###   ########.fr       */
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
