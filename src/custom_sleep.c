/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_sleep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 00:52:59 by rcochran          #+#    #+#             */
/*   Updated: 2025/08/26 16:22:14 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	custom_usleep(t_philo *philo, long duration_ms)
{
	long	start;

	start = get_time_in_ms();
	while (get_time_in_ms() - start < duration_ms)
	{
		if (check_death(philo))
			return (1);
		// printf("timestamp = %ld, id = %d\n", start, philo->id);
		usleep(100);
	}
	return (0);
}
