/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_fork.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 14:03:35 by rcochran          #+#    #+#             */
/*   Updated: 2025/08/22 18:40:34 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		init_forks(t_data *data);
void	free_forks(t_data *data);

/**
 * @brief init_forks
 * 
 * @param *data the main struct
 * 
 */
int	init_forks(t_data *data)
{
	int		i;
	t_mutex	*mtx_array;

	i = 0;
	mtx_array = malloc(sizeof(t_mutex) * data->nb_philo);
	if (!mtx_array)
		return (ft_putstr_fd("Error : malloc failed\n", 2), 1);
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&mtx_array[i], 0) != 0)
			return (ft_putstr_fd("Error : mutex init failed\n", 2), 1);
		i++;
	}
	data->forks = mtx_array;
	return (0);
}

void	free_forks(t_data *data)
{
	int	i;

	i = 0;
	if (!data->forks || !data->forks)
		return ;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
	return ;
}
