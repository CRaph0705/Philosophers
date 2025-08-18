/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_fork.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 14:03:35 by rcochran          #+#    #+#             */
/*   Updated: 2025/08/18 17:26:31 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		init_forks(t_data *data);
void	free_forks(t_mutex *forks);
t_fork	*new_fork();

/**
 * @brief init_forks
 * 
 * @param *data the main struct
 * 
 */
int	init_forks(t_data *data)
{
	int		i;
	t_mutex	*mtx;

	i = 0;
	mtx = malloc(sizeof(t_mutex) * data->nb_philo);
	if (!mtx)
		return (perror("Error : malloc failed\n"), 1);
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&mtx[i], 0) != 0)
			return (perror("Error : mutex init failed\n"), 1);
		i++;
	}
	data->forks = mtx;
	return (0);
}

void	free_forks(t_mutex *forks)
{
	(void)forks;
	return ;
}
