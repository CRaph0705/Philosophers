/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_sleep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 00:52:59 by rcochran          #+#    #+#             */
/*   Updated: 2025/08/26 00:54:13 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	custom_usleep(t_philo *philo, long duration_ms)
{
    long start = get_time_in_ms();
    while (get_time_in_ms() - start < duration_ms)
    {
        pthread_mutex_lock(&philo->data->mtx);
        if (philo->is_dead || philo->data->has_stopped)
        {
            pthread_mutex_unlock(&philo->data->mtx);
            return (1);
        }
        pthread_mutex_unlock(&philo->data->mtx);

        usleep(200);
    }
    return (0);
}
