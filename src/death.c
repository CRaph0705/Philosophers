/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 16:16:20 by rcochran          #+#    #+#             */
/*   Updated: 2025/08/26 01:09:51 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_death(t_philo *philo);

int check_death(t_philo *philo)
{
    long now;

    pthread_mutex_lock(&philo->data->mtx);
    if (philo->is_dead || philo->data->has_stopped)
    {
        pthread_mutex_unlock(&philo->data->mtx);
        return (1);
    }

    now = get_time_in_ms() - philo->start_time;
    if (now - philo->last_meal >= philo->time_to_die)
    {
        if (!philo->is_dead && !philo->data->has_stopped)
        {
            printf("%ld %d died\n", now, philo->id);
            philo->is_dead = true;
            philo->data->has_stopped = 1;
        }
        pthread_mutex_unlock(&philo->data->mtx);
        return (1);
    }
    pthread_mutex_unlock(&philo->data->mtx);
    return (0);
}
