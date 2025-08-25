/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:32:32 by rcochran          #+#    #+#             */
/*   Updated: 2025/08/26 01:18:25 by rcochran         ###   ########.fr       */
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
			break ;
	}
}

int	do_die(t_philo *philo)
{
	time_t	actual;

	actual = get_time_in_ms() - philo->start_time;
	pthread_mutex_lock(&philo->data->mtx);
	if (philo->data->has_stopped == 1)
	{
		pthread_mutex_unlock(&philo->data->mtx);
		return (0);
	}
	printf("%ld %d died\n", actual, philo->id);
	philo->is_dead = 1;
	philo->data->has_stopped = 1;
	pthread_mutex_unlock(&philo->data->mtx);
	return (0);
}

int	get_target_fork(t_philo *philo, int hand)
{
	time_t	actual;

	if (check_death(philo))
		return (1);
	if (hand == 0)
		pthread_mutex_lock(&philo->data->forks[philo->m_left]);
	else
		pthread_mutex_lock(&philo->data->forks[philo->m_right]);
	pthread_mutex_lock(&philo->data->mtx);
	if (check_death(philo))
		return (pthread_mutex_unlock(&philo->data->mtx), do_die(philo), 1);
	actual = get_time_in_ms() - philo->start_time;
	printf("%ld %d has taken a fork\n", actual, philo->id);
	pthread_mutex_unlock(&philo->data->mtx);
	return (0);
}

int	get_forks(t_philo *philo)
{
	long long	wake_up;

	if (check_death(philo))
		return (1);
	if (philo->id % 2 == 0)
	{
		if (get_target_fork(philo, 1))
			return (put_forks(philo), 1);
		if (get_target_fork(philo, 0))
			return (put_forks(philo), 1);
	}
	else
	{
		wake_up = get_time_in_ms() + philo->time_to_eat - 1;
		// usleep((philo->time_to_eat - 1) * 1000);
		while (get_time_in_ms() < wake_up)
		{
			pthread_mutex_lock(&philo->data->mtx);
			if (philo->is_dead || philo->data->has_stopped)
			{
				pthread_mutex_unlock(&philo->data->mtx);
				return (1);
			}
			pthread_mutex_unlock(&philo->data->mtx);
			usleep(10);
		}
		if (get_target_fork(philo, 0))
			return (put_forks(philo), 1);
		if (get_target_fork(philo, 1))
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
