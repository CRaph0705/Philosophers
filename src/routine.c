/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:56:06 by rcochran          #+#    #+#             */
/*   Updated: 2025/08/26 01:30:09 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		do_eat(t_philo *philo);
int		do_sleep(t_philo *philo);
int		do_think(t_philo *philo);
void	*routine(void *p_philo);
void	meal_check(t_philo *philo);

void meal_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mtx);
	philo->nb_meal++;
	if (philo->data->max_meal > 0 && philo->nb_meal >= philo->data->max_meal)
		philo->data->nb_meals++;
	if (philo->data->max_meal > 0 && philo->data->nb_meals >= philo->data->nb_philo)
		philo->data->has_stopped = 1;
	pthread_mutex_unlock(&philo->data->mtx);
}
int do_eat(t_philo *philo)
{
	long actual;

	if (check_death(philo))
		return (1);
	if (philo->m_left == philo->m_right)
	{
		custom_usleep(philo, philo->time_to_die);
		return (check_death(philo), 1);
	}
	if (get_forks(philo))
		return (0);
	// if (get_forks(philo))
	// 	return (0);
	actual = get_time_in_ms() - philo->start_time;
	pthread_mutex_lock(&philo->data->mtx);
	if (philo->data->has_stopped == 0 && !philo->is_dead)
		printf("%ld %d is eating\n", actual, philo->id);
	pthread_mutex_unlock(&philo->data->mtx);
	philo->last_meal = get_time_in_ms() - philo->start_time;
	if (custom_usleep(philo, philo->time_to_eat))
	{
		put_forks(philo);
		return (1);
	}
	philo->nb_meal += 1;
	put_forks(philo);
	meal_check(philo);
	return (do_sleep(philo));
}

int do_sleep(t_philo *philo)
{
    long actual;

    if (check_death(philo))
        return (1);
    actual = get_time_in_ms() - philo->start_time;
    pthread_mutex_lock(&philo->data->mtx);
    if (!philo->is_dead && !philo->data->has_stopped)
        printf("%ld %d is sleeping\n", actual, philo->id);
    pthread_mutex_unlock(&philo->data->mtx);
    if (custom_usleep(philo, philo->time_to_sleep))
        return (1);
    return do_think(philo);
}






int do_think(t_philo *philo)
{
    long actual;
    long time_to_think;


    if (check_death(philo))
        return (1);

    actual = get_time_in_ms() - philo->start_time;
    time_to_think = (philo->time_to_die - (actual - philo->last_meal) - philo->time_to_eat) / 2;
    if (time_to_think < 0)
        time_to_think = 0;
    pthread_mutex_lock(&philo->data->mtx);
    if (!philo->is_dead && !philo->data->has_stopped)
        printf("%ld %d is thinking\n", actual, philo->id);
    pthread_mutex_unlock(&philo->data->mtx);
    if (custom_usleep(philo, time_to_think))
        return (1);
    return (0);
}

void	*routine(void *p_philo)
{
	t_philo	*philo;

	philo = (t_philo *)p_philo;
	wait_for_start(philo);
	while (1)
	{
		if (check_death(philo))
			break;
		if (philo->data->max_meal >= 0 && philo->nb_meal >= philo->data->max_meal)
			break;
		if (do_eat(philo))
			break;
	}
	return (NULL);
}
