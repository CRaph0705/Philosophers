/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:32:32 by rcochran          #+#    #+#             */
/*   Updated: 2025/08/26 14:57:28 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_for_start(t_philo *philo);
int		do_die(t_philo *philo);
int		get_forks(t_philo *philo);
void	put_forks(t_philo *philo);
int		get_target_fork(t_philo *philo, int hand);

void	wait_for_start(t_philo *philo)
{
	time_t	actual;

	actual = get_time_in_ms() - philo->start_time;
	while (1)
	{
		actual = get_time_in_ms() - philo->start_time;
		if (actual == 0)
		{
			if ((philo->id) % 2 == 0)
				break ;
			else
			{
				usleep(1000);
				break ;
			}
		}
	}
}

int	do_die(t_philo *philo)
{
	time_t	actual;

	actual = get_time_in_ms() - philo->start_time;
	pthread_mutex_lock(&philo->data->m_death);
	if (philo->data->has_stopped == 1)
	{
		pthread_mutex_unlock(&philo->data->m_death);
		return (0);
	}
	pthread_mutex_lock(&philo->data->m_print);
	printf("%ld %d died\n", actual, philo->id);
	pthread_mutex_unlock(&philo->data->m_print);
	philo->is_dead = 1;
	philo->data->has_stopped = 1;
	pthread_mutex_unlock(&philo->data->m_death);
	return (0);
}

int	get_target_fork(t_philo *philo, int hand)
{
	if (check_death(philo))
		return (1);
	if (hand == 0)
		pthread_mutex_lock(&philo->data->forks[philo->m_left]);
	else
		pthread_mutex_lock(&philo->data->forks[philo->m_right]);
	pthread_mutex_lock(&philo->data->mtx);
	if (!philo->is_dead && !philo->data->has_stopped)
	{
		pthread_mutex_lock(&philo->data->m_print);
		printf("%ld %d has taken a fork\n",
			get_time_in_ms() - philo->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->m_print);
	}
	pthread_mutex_unlock(&philo->data->mtx);
	return (0);
}

int	get_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		get_target_fork(philo, 1);
		if (check_death(philo))
			return (put_forks(philo), 1);
		get_target_fork(philo, 0);
		if (check_death(philo))
			return (put_forks(philo), 1);
	}
	else
	{
		get_target_fork(philo, 0);
		if (check_death(philo))
			return (put_forks(philo), 1);
		get_target_fork(philo, 1);
		if (check_death(philo))
			return (put_forks(philo), 1);
	}
	return (0);
}

void	put_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->m_right]);
		pthread_mutex_unlock(&philo->data->forks[philo->m_left]);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->forks[philo->m_left]);
		pthread_mutex_unlock(&philo->data->forks[philo->m_right]);
	}
	return ;
}
