/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:56:06 by rcochran          #+#    #+#             */
/*   Updated: 2025/08/20 17:45:45 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		do_eat(t_philo *philo);
int		do_sleep(t_philo *philo);
int		do_think(t_philo *philo);
void	*routine(void *p_philo);

int	do_eat(t_philo *philo)
{
	time_t	actual;

	actual = get_time_in_ms() - philo->start_time;
	pthread_mutex_lock(&philo->data->mtx);
	if (philo->is_dead == true || philo->data->has_stopped)
		return (pthread_mutex_unlock(&philo->data->mtx));
	if (actual - philo->last_meal > philo->time_to_die)
		return (pthread_mutex_unlock(&philo->data->mtx), do_die(philo));
	pthread_mutex_unlock(&philo->data->mtx);
	get_forks(philo);
	pthread_mutex_lock(&philo->data->mtx);
	printf("%ld %d is eating\n", actual, philo->id);
	pthread_mutex_unlock(&philo->data->mtx);
	usleep(philo->time_to_eat * 1000);
	philo->last_meal = get_time_in_ms() - philo->start_time;
	philo->nb_meal += 1;
	put_forks(philo);
	pthread_mutex_lock(&philo->data->mtx);
	if (philo->nb_meal == philo->data->max_meal)
		philo->data->nb_meals++;
	if (philo->data->nb_meals == philo->data->max_meal)
		philo->data->has_stopped = 1;
	pthread_mutex_unlock(&philo->data->mtx);
	return (do_sleep(philo));
}


void	philo_sleep(time_t sleep_time)
{
	time_t	wake_up;

	wake_up = get_time_in_ms() + sleep_time;
	while (get_time_in_ms() < wake_up)
	{
		usleep(100);
	}
}

int	do_sleep(t_philo *philo)
{
	long long	actual;
	long long	wake_up;

	pthread_mutex_lock(&philo->data->mtx);
	if (philo->is_dead == true || philo->data->has_stopped)
		return (pthread_mutex_unlock(&philo->data->mtx), 1);
	pthread_mutex_unlock(&philo->data->mtx);
	actual = get_time_in_ms() - philo->start_time;
	pthread_mutex_lock(&philo->data->mtx);
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
		usleep(1000);
	}
/* 	if (actual - philo->last_meal + philo->time_to_sleep > philo->time_to_die)
	{
		usleep((philo->time_to_die - (actual - philo->last_meal))* 1000);
		return (do_die(philo));
	} */
/* 	usleep(philo->time_to_sleep * 1000);*/
	return (do_think(philo));
}

int	do_think(t_philo *philo)
{
	long	actual;
	long	time_to_think;

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
	if (time_to_think < 0)
		time_to_think = 0;
	printf("time to think = [%ld]\n", time_to_think);
	pthread_mutex_lock(&philo->data->mtx);
	printf("%ld %d is thinking\n", actual, philo->id);
	pthread_mutex_unlock(&philo->data->mtx);
	usleep(time_to_think * 1000);
	return (0);
}

void	*routine(void *p_philo)
{
	t_philo	*philo;
	int		i;
	time_t	actual;
	int		do_stop;

	philo = (void *)(p_philo);
	actual = get_time_in_ms() - philo->start_time;
	wait_for_start(philo);
	i = 0;
	pthread_mutex_lock(&philo->data->mtx);
	do_stop = philo->data->has_stopped;
	pthread_mutex_unlock(&philo->data->mtx);
	while ((do_stop == 0
			&& ((philo->data->max_meal < 0)
				|| philo->nb_meal < philo->data->max_meal)))
	{	
		do_eat(philo);
		i++;
		pthread_mutex_lock(&philo->data->mtx);
		do_stop = philo->data->has_stopped;
		pthread_mutex_unlock(&philo->data->mtx);
	}
	return (NULL);
}
