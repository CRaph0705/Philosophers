/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:56:06 by rcochran          #+#    #+#             */
/*   Updated: 2025/08/25 16:54:02 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		do_eat(t_philo *philo);
int		do_sleep(t_philo *philo);
int		do_think(t_philo *philo);
void	*routine(void *p_philo);
void	meal_check(t_philo *philo);

void	meal_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mtx);
	if (philo->nb_meal == philo->data->max_meal)
		philo->data->nb_meals++;
	if (philo->data->nb_meals == philo->data->max_meal)
		philo->data->has_stopped = 1;
	pthread_mutex_unlock(&philo->data->mtx);
}

int	do_eat(t_philo *philo)
{
	time_t	actual;

	if (check_if_death(philo))
		return (1);
	actual = get_time_in_ms() - philo->start_time;
	if (am_i_dead(philo))
		return (do_die(philo));
	if (philo->m_left == philo->m_right)
		(usleep(philo->time_to_die * 1000), do_die(philo));
	if (get_forks(philo))
		return (0);
	actual = get_time_in_ms() - philo->start_time;
	if (actual - philo->last_meal > philo->time_to_die)
		return (put_forks(philo), do_die(philo));
	actual = get_time_in_ms() - philo->start_time;
	pthread_mutex_lock(&philo->data->mtx);
	if (philo->data->has_stopped == 0)
		printf("%ld %d is eating\n", actual, philo->id);
	pthread_mutex_unlock(&philo->data->mtx);
	usleep(philo->time_to_eat * 1000);
	philo->last_meal = get_time_in_ms() - philo->start_time;
	philo->nb_meal += 1;
	put_forks(philo);
	meal_check(philo);
	return (do_sleep(philo));
}

int	do_sleep(t_philo *philo)
{
	long long	actual;
	long long	wake_up;

	if (am_i_dead(philo))
		return (do_die(philo), 1);
	if (check_if_death(philo))
		return (1);
	actual = get_time_in_ms() - philo->start_time;
	pthread_mutex_lock(&philo->data->mtx);
	actual = get_time_in_ms() - philo->start_time;
	printf("%lld %d is sleeping\n", actual, philo->id);
	pthread_mutex_unlock(&philo->data->mtx);
	wake_up = get_time_in_ms() + philo->time_to_sleep;
	while (get_time_in_ms() < wake_up)
	{
		pthread_mutex_lock(&philo->data->mtx);
		if (philo->is_dead || philo->data->has_stopped)
		{
			pthread_mutex_unlock(&philo->data->mtx);
			return (1);
		}
		pthread_mutex_unlock(&philo->data->mtx);
		usleep(100);
	}
	return (do_think(philo));
}

int	do_think(t_philo *philo)
{
	long		actual;
	long		time_to_think;
	long long	wake_up;

	pthread_mutex_lock(&philo->data->mtx);
	if (philo->is_dead == true || philo->data->has_stopped)
	{
		pthread_mutex_unlock(&philo->data->mtx);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->mtx);
	actual = get_time_in_ms() - philo->start_time;
	time_to_think = (philo->time_to_die
			- (actual - philo->last_meal) - philo->time_to_eat) / 2;

	// printf("time to think = [%ld]\n", time_to_think);
	if (time_to_think < 0)
		time_to_think = 0;
	pthread_mutex_lock(&philo->data->mtx);
	actual = get_time_in_ms() - philo->start_time;
	printf("%ld %d is thinking\n", actual, philo->id);
	pthread_mutex_unlock(&philo->data->mtx);
	// usleep(time_to_think * 1000);
	wake_up = get_time_in_ms() + time_to_think;
	while (get_time_in_ms() < wake_up)
	{
		pthread_mutex_lock(&philo->data->mtx);
		if (philo->is_dead || philo->data->has_stopped)
		{
			pthread_mutex_unlock(&philo->data->mtx);
			return (1);
		}
		pthread_mutex_unlock(&philo->data->mtx);
		usleep(100);
	}
	return (0);
}

void	*routine(void *p_philo)
{
	t_philo	*philo;
	int		do_stop;

	philo = (void *)(p_philo);
	wait_for_start(philo);
	pthread_mutex_lock(&philo->data->mtx);
	do_stop = philo->data->has_stopped;
	pthread_mutex_unlock(&philo->data->mtx);
	if (do_stop != 0)
		return (NULL);
	while ((do_stop == 0
			&& ((philo->data->max_meal < 0)
				|| philo->nb_meal < philo->data->max_meal)))
	{
		do_eat(philo);
		pthread_mutex_lock(&philo->data->mtx);
		do_stop = philo->data->has_stopped;
		pthread_mutex_unlock(&philo->data->mtx);
	}
	return (NULL);
}
