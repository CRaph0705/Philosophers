/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:56:06 by rcochran          #+#    #+#             */
/*   Updated: 2025/08/27 17:06:28 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		do_eat(t_philo *philo);
int		do_sleep(t_philo *philo);
int		do_think(t_philo *philo);
void	*routine(void *p_philo);
void	meal_check(t_philo *philo);

/* void	meal_check(t_philo *philo)
{
	if (check_death(philo))
		return ;
	pthread_mutex_lock(&philo->data->m_meals);
	philo->nb_meal++;
	if (philo->data->max_meal > 0 && philo->nb_meal >= philo->data->max_meal)
		philo->data->nb_meals++;
	pthread_mutex_unlock(&philo->data->m_meals);
	if (philo->data->max_meal > 0
		&& philo->data->nb_meals >= philo->data->nb_philo)
		philo->data->simulation_stop = 1;
} */

int	do_eat(t_philo *philo)
{
	if (get_forks(philo))
		return (1);
	if (!safe_mutex_lock(&philo->data->m_print, philo->data))
		return (1);
	printf("%ld %d is eating\n",
		get_time_in_ms() - philo->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->m_print);
	if (!safe_mutex_lock(&philo->data->m_meals, philo->data))
		return (put_forks(philo, 2), 1);
	pthread_mutex_lock(&philo->m_status);
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->m_status);
	pthread_mutex_unlock(&philo->data->m_meals);
	if (custom_usleep(philo, philo->time_to_eat))
		return (put_forks(philo, 2), 1);
	philo->nb_meal++;
	put_forks(philo, 2);
	return (do_sleep(philo));
}

int	do_sleep(t_philo *philo)
{
	if (!safe_mutex_lock(&philo->data->m_print, philo->data))
		return (1);
	printf("%ld %d is sleeping\n",
		get_time_in_ms() - philo->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->m_print);
	if (custom_usleep(philo, philo->time_to_sleep))
		return (1);
	return (do_think(philo));
}

int	do_think(t_philo *philo)
{
	long	time_to_think;

	if (!safe_mutex_lock(&philo->data->m_print, philo->data))
		return (1);
	printf("%ld %d is thinking\n",
		get_time_in_ms() - philo->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->m_print);
	time_to_think = (philo->time_to_die - (get_time_in_ms() - philo->last_meal)
			- philo->time_to_eat);
	if (time_to_think < 0)
		time_to_think = 0;
	if (custom_usleep(philo, time_to_think))
		return (1);
	return (0);
}

void	*routine(void *p_philo)
{
	t_philo	*philo;
	bool	stop;

	philo = (t_philo *)p_philo;
	// wait_for_start(philo);

	if (!safe_mutex_lock(&philo->data->m_stop, philo->data))
		return (NULL);
	stop = philo->data->simulation_stop;
	pthread_mutex_unlock(&philo->data->m_stop);
	while (stop == 0)
	{

		if (do_eat(philo))
			break ;
		if (!safe_mutex_lock(&philo->data->m_stop, philo->data))
			return (NULL);
		stop = philo->data->simulation_stop;
		pthread_mutex_unlock(&philo->data->m_stop);
	}
	return (NULL);
}

/* void	*routine(void *p_philo)
{
	t_philo	*philo;
	bool	start;

	start = 1;
	philo = (t_philo *)p_philo;
	// wait_for_start(philo);
	while (1)
	{
		if (philo->data->max_meal >= 0
			&& philo->nb_meal >= philo->data->max_meal)
			break ;
		if (start && philo->id % 2 == 1)
		{
			start = 0;
			custom_usleep(philo, philo->time_to_eat - 10);
		}
		if (do_eat(philo))
			break ;
	}
	return (NULL);
} */