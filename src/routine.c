/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:56:06 by rcochran          #+#    #+#             */
/*   Updated: 2025/08/20 16:19:58 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		do_eat(t_philo *philo);
int		do_sleep(t_philo *philo);
int		do_think(t_philo *philo);
void	*routine(void *p_philo);
int		do_die(t_philo *philo);
void	get_forks(t_philo *philo);
void	put_forks(t_philo *philo);

int	do_die(t_philo *philo)
{
	time_t	actual;

	actual = get_time_in_ms() - philo->start_time;
	pthread_mutex_lock(&philo->data->mtx);
	if (philo->data->has_stopped == 1)
		return (pthread_mutex_unlock(&philo->data->mtx));
	printf("%ld %d died\n", actual,philo->id);
	philo->is_dead = 1;
	philo->data->has_stopped = 1;
	pthread_mutex_unlock(&philo->data->mtx);
	return (0);
}

void	get_forks(t_philo *philo)
{
	time_t	actual;

	pthread_mutex_lock(&philo->data->mtx);
	if (philo->data->has_stopped == 1)
	{
		pthread_mutex_unlock(&philo->data->mtx);
		return ;
	}
	actual = get_time_in_ms() - philo->start_time;
	if (philo->id % 2 == 0)
	{
		//prio main droite
		// pthread_mutex_lock(&philo->m_right);
		pthread_mutex_lock(&philo->data->forks[philo->m_right]);
		printf("%ld %d has taken a fork\n", actual,philo->id);
		// pthread_mutex_lock(&philo->m_left);
		pthread_mutex_lock(&philo->data->forks[philo->m_left]);
		printf("%ld %d has taken a fork\n", actual,philo->id);
	}
	else
	{
		// prio main gauche
		// pthread_mutex_lock(&philo->m_left);
		pthread_mutex_lock(&philo->data->forks[philo->m_left]);
		printf("%ld %d has taken a fork\n", actual,philo->id);
		// pthread_mutex_lock(&philo->m_right);
		pthread_mutex_lock(&philo->data->forks[philo->m_right]);
		printf("%ld %d has taken a fork\n", actual,philo->id);
	}
	pthread_mutex_unlock(&philo->data->mtx);
	return ;
}

void	put_forks(t_philo *philo)
{
	time_t	actual;

	actual = get_time_in_ms() - philo->start_time;
	if (philo->id % 2 == 0)
	{
		//prio main droite
		// pthread_mutex_unlock(&philo->m_right);
		pthread_mutex_unlock(&philo->data->forks[philo->m_right]);
		// printf("[%ld] %d has put right fork\n", actual,philo->id);
		// pthread_mutex_unlock(&philo->m_left);
		pthread_mutex_unlock(&philo->data->forks[philo->m_left]);
		// printf("[%ld] %d has put left fork\n", actual,philo->id);
	}
	else
	{
		// prio main gauche
		// pthread_mutex_unlock(&philo->m_left);
		pthread_mutex_unlock(&philo->data->forks[philo->m_left]);
		// printf("%ld %d has put left fork\n", actual,philo->id);
		// pthread_mutex_unlock(&philo->m_right);
		pthread_mutex_unlock(&philo->data->forks[philo->m_right]);
		// printf("%ld %d has put right fork\n", actual,philo->id);
	}
	return ;
}

int	do_eat(t_philo *philo)
{
	time_t	actual;
	// printf("debug\n");

	actual = get_time_in_ms() - philo->start_time;
	pthread_mutex_lock(&philo->data->mtx);
	if (philo->is_dead == true || philo->data->has_stopped)
		return 	(pthread_mutex_unlock(&philo->data->mtx));
	if (actual - philo->last_meal > philo->time_to_die)
		return (pthread_mutex_unlock(&philo->data->mtx), do_die(philo));
	pthread_mutex_unlock(&philo->data->mtx);
	get_forks(philo);
	pthread_mutex_lock(&philo->data->mtx);// mutex de data pour proteger le printf
	printf("%ld %d is eating\n", actual, philo->id);
	pthread_mutex_unlock(&philo->data->mtx);
	usleep(philo->time_to_eat);
	philo->nb_meal += 1;
	philo->last_meal = actual;
	put_forks(philo);
	pthread_mutex_lock(&philo->data->mtx);
	if (philo->nb_meal == philo->data->max_meal)
		philo->data->nb_meals++;
	if (philo->data->nb_meals == philo->data->max_meal)
		philo->data->has_stopped = 1;
	pthread_mutex_unlock(&philo->data->mtx);
	return (do_sleep(philo));
}


/* 

	pthread_mutex_lock(&philo->data->mtx);
	pthread_mutex_unlock(&philo->data->mtx);
*/


int	do_sleep(t_philo *philo)
{
	time_t	actual;

	pthread_mutex_lock(&philo->data->mtx);
	if (philo->is_dead == true || philo->data->has_stopped)
		return 	(pthread_mutex_unlock(&philo->data->mtx));
	pthread_mutex_unlock(&philo->data->mtx);
	actual = get_time_in_ms() - philo->start_time;
	pthread_mutex_lock(&philo->data->mtx);
	printf("%ld %d is sleeping\n", actual, philo->id);
	pthread_mutex_unlock(&philo->data->mtx);
	// if die during sleep

	if (actual - philo->last_meal + philo->time_to_sleep > philo->time_to_die)
	{
		usleep(philo->time_to_die - (actual - philo->last_meal));
		return (do_die(philo));
	}
	usleep(philo->time_to_sleep);
	return (do_think(philo));
}

int	do_think(t_philo *philo)
{
	time_t	actual;
	time_t	time_to_think;

	time_to_think = (philo->time_to_die - (get_time_in_ms() - philo->last_meal) - philo->time_to_eat) / 2;
	pthread_mutex_lock(&philo->data->mtx);
	if (philo->is_dead == true || philo->data->has_stopped)
		return 	(pthread_mutex_unlock(&philo->data->mtx));
	pthread_mutex_unlock(&philo->data->mtx);
	actual = get_time_in_ms() - philo->start_time;
	pthread_mutex_lock(&philo->data->mtx);
	printf("%ld %d is thinking\n", actual, philo->id);
	pthread_mutex_unlock(&philo->data->mtx);
	usleep(time_to_think);
	return (0);
}

void	*routine(void *p_philo)
{
	t_philo	*philo;
	int		i;
	time_t	actual;
	int do_stop;

	philo = (void *)(p_philo);

	actual = get_time_in_ms() - philo->start_time;
	while (1)
	{
		actual = get_time_in_ms() - philo->start_time;
		if(actual == 0)
			break ;
	}
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
