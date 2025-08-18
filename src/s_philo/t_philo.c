/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_philo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:49:42 by rcochran          #+#    #+#             */
/*   Updated: 2025/08/18 18:09:29 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			init_philo(t_data *data);
t_philo		*new_philo(int index, t_data *data);

t_philo	*new_philo(int index, t_data *data)
{
	t_philo	*new;

	new = NULL;
	if (data)
	{
		new = malloc(sizeof(t_philo));
		if (!new)
			return (NULL);
		new->id = index;
		new->is_dead = 0;
		new->time_to_die = data->time_to_die;
		new->time_to_eat = data->time_to_eat;
		new->time_to_sleep = data->time_to_sleep;
		
		new->data = data;
	}
	return (new);
}

int	init_philo(t_data *data)
{
	int		i;
	t_philo	**philos;

	if (!data)
		return (1);
	philos = malloc(sizeof(t_philo *) * data->nb_philo);
	if (!philos)
		return (1);
	i = 0;
	while (i < data->nb_philo)
	{
		philos[i] = new_philo(i, data);
		if (!philos[i])
			return (free_data(data), 1);
		i++;
	}
	data->philos = philos;
	return (0);
}

void	free_philos(t_philo **philo)
{
	(void)philo;
	return ;
}
