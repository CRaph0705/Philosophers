/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 16:16:20 by rcochran          #+#    #+#             */
/*   Updated: 2025/08/25 16:13:13 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_data_hasstopped(t_philo *philo);
int	am_i_dead(t_philo *philo);
int	check_if_death(t_philo *philo);

int	get_data_hasstopped(t_philo *philo)
{
	int	ret;

	pthread_mutex_lock(&philo->data->mtx);
	ret = philo->data->has_stopped;
	pthread_mutex_unlock(&philo->data->mtx);
	return (ret);
}

int	am_i_dead(t_philo *philo)
{
	time_t	actual;

	if (philo->is_dead == 1)
		return (1);
	actual = get_time_in_ms() - philo->start_time;
	if (actual - philo->last_meal >= philo->time_to_die)
		return (1);
	return (0);
}

int	check_if_death(t_philo *philo)
{
	if (get_data_hasstopped(philo) == 1)
		return (1);
	if (am_i_dead(philo) == 1)
	{
		do_die(philo);
		return (1);
	}
	return (0);
}
