/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_mutex_lock.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:44:58 by rcochran          #+#    #+#             */
/*   Updated: 2025/08/27 13:47:20 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	safe_mutex_lock(pthread_mutex_t *m, t_data *data)
{
	int	simulation_stopped;

	pthread_mutex_lock(&(data->m_stop));
	simulation_stopped = data->simulation_stop;
	pthread_mutex_unlock(&(data->m_stop));
	if (simulation_stopped)
		return (0);
	if (pthread_mutex_lock(m) != 0)
		return (0);
	return (1);
}
