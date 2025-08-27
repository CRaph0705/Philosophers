/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:32:32 by rcochran          #+#    #+#             */
/*   Updated: 2025/08/27 19:19:44 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_for_start(t_philo *philo);
int		do_die(t_philo *philo);
int		get_forks(t_philo *philo);
void	put_forks(t_philo *philo, int nb_forks);
int		get_target_fork(t_philo *philo, int hand);

void	wait_for_start(t_philo *philo)
{
	bool	ready;

	pthread_mutex_lock(&philo->data->m_ready);
	philo->data->ready_count++;
	pthread_mutex_unlock(&philo->data->m_ready);
	while (1)
	{
		pthread_mutex_lock(&philo->data->m_ready);
		ready = (philo->data->ready_count == philo->data->nb_philo);
		pthread_mutex_unlock(&philo->data->m_ready);
		if (ready)
			break ;
		usleep(100);
	}
}

int	do_die(t_philo *philo)
{
	time_t	actual;

	actual = get_time_in_ms() - philo->start_time;
	if (!safe_mutex_lock(&philo->data->m_print, philo->data))
		return (1);
	printf("%ld %d died\n", actual, philo->id);
	pthread_mutex_unlock(&philo->data->m_print);
	philo->is_dead = 1;
	philo->data->simulation_stop = 1;
	pthread_mutex_unlock(&philo->data->m_death);
	return (0);
}

int	get_target_fork(t_philo *philo, int hand)
{
	if (hand == 0)
	{
		if (!safe_mutex_lock(&philo->data->forks[philo->m_left], philo->data))
			return (1);
	}
	else
	{
		if (!safe_mutex_lock(&philo->data->forks[philo->m_right], philo->data))
			return (1);
	}
	if (!safe_mutex_lock(&philo->data->m_print, philo->data))
		return (1);
	printf("%ld %d has taken a fork\n",
		get_time_in_ms() - philo->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->m_print);
	return (0);
}

int	lonely_routine(t_philo *philo)
{
	get_target_fork(philo, 0);
	put_forks(philo, 1);
	custom_usleep(philo, philo->time_to_die);
	return (do_die(philo), 1);
}

int	get_forks(t_philo *philo)
{
	if (philo->m_left == philo->m_right)
		return (lonely_routine(philo));
	if (philo->id % 2 == 1)
	{
		if (get_target_fork(philo, 1))
			return (1);
		if (get_target_fork(philo, 0))
			return (put_forks(philo, 1), 1);
	}
	else
	{
		if (get_target_fork(philo, 0))
			return (1);
		if (get_target_fork(philo, 1))
			return (put_forks(philo, 1), 1);
	}
	return (0);
}

void	put_forks(t_philo *philo, int nb_forks)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->m_right]);
		if (nb_forks > 1)
			pthread_mutex_unlock(&philo->data->forks[philo->m_left]);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->forks[philo->m_left]);
		if (nb_forks > 1)
			pthread_mutex_unlock(&philo->data->forks[philo->m_right]);
	}
	return ;
}
