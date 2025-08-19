/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:56:06 by rcochran          #+#    #+#             */
/*   Updated: 2025/08/19 15:41:12 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	do_eat(t_philo *philo);
void	do_sleep(t_philo *philo);
void	do_think(t_philo *philo);
void	*routine(void *p_philo);
void	die(t_philo *philo);

void	die(t_philo *philo)
{
	if (philo->data->has_stopped == true)
		return ;
	printf("oh no i'm dead ! :(\n");
	printf("\
[id] = %d\n\
[last meal = %ld]\n\
[time to die = %d]\n\
[time to eat = %d]\n\
[time to sleep = %d]\n",
		philo->id, philo->last_meal, philo->time_to_die,
		philo->time_to_eat, philo->time_to_sleep);
	philo->is_dead = 1;
	philo->data->has_stopped = 1;
}

// TODO l44 la on prend les fourchettes
// puis on set le meal avant de liberer les fourchettes
void	do_eat(t_philo *philo)
{
	time_t	actual;

	if (philo->is_dead == true || philo->data->has_stopped)
		return ;
	actual = get_time_in_ms();
	if (actual - philo->last_meal > philo->time_to_die)
		return (die(philo));
	printf("[%ld] %d is eating\n", actual, philo->id);
	usleep(philo->time_to_eat);
	philo->nb_meal += 1;
	philo->last_meal = actual;
}

void	do_sleep(t_philo *philo)
{
	time_t	actual;

	if (philo->is_dead == true || philo->data->has_stopped)
		return ;
	actual = get_time_in_ms();
	printf("[%ld] %d is sleeping\n", actual, philo->id);
	usleep(philo->time_to_sleep);
}

void	do_think(t_philo *philo)
{
	time_t	actual;

	if (philo->is_dead == true || philo->data->has_stopped)
		return ;
	actual = get_time_in_ms();
	printf("[%ld] %d is thinking\n", actual, philo->id);
	usleep(100);
}

//i < 10 just for dev
/* 
while (i < 10 && (philo->data->has_stopped == 0
		&& ((philo->data->max_meal < 0)
			|| philo->nb_meal < philo->data->max_meal)))
*/
void	*routine(void *p_philo)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (void *)(p_philo);
	while ((philo->data->has_stopped == 0
			&& ((philo->data->max_meal < 0)
				|| philo->nb_meal < philo->data->max_meal)))
	{	
		do_eat(philo);
		do_sleep(philo);
		do_think(philo);
		i++;
		if (philo->data->has_stopped)
			break ;
	}
	return (NULL);
}
