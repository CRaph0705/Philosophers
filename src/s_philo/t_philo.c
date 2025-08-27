/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_philo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:49:42 by rcochran          #+#    #+#             */
/*   Updated: 2025/08/27 15:15:55 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			init_philo(t_data *data);
t_philo		*new_philo(int index, t_data *data);
void		free_philo(t_philo *philo);
void		free_philos(t_data *data);

t_philo	*new_philo(int index, t_data *data)
{
	t_philo	*new;
	t_mutex	status;

	new = NULL;
	if (data)
	{
		new = malloc(sizeof(t_philo));
		if (!new)
			return (NULL);
		new->id = index + 1;
		new->is_dead = 0;
		new->nb_meal = 0;
		new->time_to_die = data->time_to_die;
		new->time_to_eat = data->time_to_eat;
		new->time_to_sleep = data->time_to_sleep;
		new->data = data;
		new->m_left = index;
		new->m_right = (index + 1) % data->nb_philo;
		if (pthread_mutex_init(&status, NULL) != 0)
			return (ft_putstr_fd("Error : mutex error\n", 2), free(new), NULL);
		new->m_status = status;
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

void	free_philo(t_philo *philo)
{
	if (!philo)
		return ;
	free(philo);
}

void	free_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		free_philo(data->philos[i]);
		i++;
	}
	free(data->philos);
	data->philos = NULL;
	return ;
}
