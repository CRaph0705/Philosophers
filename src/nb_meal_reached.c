/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nb_meal_reached.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:16:00 by rcochran          #+#    #+#             */
/*   Updated: 2025/08/27 18:25:42 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	nb_meal_reached(t_data *data);

int	nb_meal_reached(t_data *data)
{
	int		i;
	t_philo	*philo;

	if (data->max_meal == -1)
		return (0);
	i = 0;
	while (i < data->nb_philo)
	{
		philo = data->philos[i];
		if (!safe_mutex_lock(&(philo->m_status), philo->data))
			return (0);
		if (philo->nb_meal < data->max_meal)
			return (pthread_mutex_unlock(&(philo->m_status)), 0);
		pthread_mutex_unlock(&(philo->m_status));
		i++;
	}
	return (1);
}
