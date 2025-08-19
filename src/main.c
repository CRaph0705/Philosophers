/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:55:24 by rcochran          #+#    #+#             */
/*   Updated: 2025/08/19 15:38:56 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
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
//TODO valeur de offset a ajuster avec les tests
int	set_last_meal(t_data *data)
{
	int		i;
	time_t	time;
	time_t	offset;

	i = 0;
	offset = data->nb_philo * 20;
	if (!data || !data->philos)
		return (1);
	time = get_time_in_ms();
	data->start = time + offset;
	printf("time = %ld\n", time);
	while (data->philos[i] && i < data->nb_philo)
	{
		data->philos[i]->last_meal = time + offset;
		i++;
	}
	return (0);
}

int	start_sim(t_data *data)
{
	int	i;

	printf("start\n");
	i = 0;
	if (!data)
		return (1);
	if (!data->philos)
		return (perror("Error : no philos\n"), 1);
	set_last_meal(data);
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philos[i]->thread, NULL,
				&routine, (void *)data->philos[i]) != 0)
			return (perror("Thread error\n"), 1);
		i++;
	}
	return (0);
}

int	stop_sim(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_join(data->philos[i]->thread, NULL) != 0)
			return (perror("Thread join error\n"), 1);
		i++;
	}
	free_data(data);
	return (0);
}

int	main(int ac, char **av)
{
	t_data			*data;
	pthread_mutex_t	mutex;

	pthread_mutex_init(&mutex, NULL);
	data = init_data(ac, av);
	if (!data)
		return (42);
	start_sim(data);
	stop_sim(data);
	return (0);
}
