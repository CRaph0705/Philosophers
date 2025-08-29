/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 10:05:13 by rcochran          #+#    #+#             */
/*   Updated: 2025/08/29 10:26:36 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void		clean_wait(t_data *data);
void			wait_for_start(t_philo *philo);
int				start_sim(t_data *data);
int				stop_sim(t_data *data, int stop);

static	void	clean_wait(t_data *data)
{
	int	top;
	int	tt_die;
	int	tt_sleep;

	tt_die = data->time_to_die;
	tt_sleep = data->time_to_sleep;
	top = tt_sleep;
	if (tt_die > tt_sleep)
		top = tt_die;
	usleep(top * 1000);
}

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

int	start_sim(t_data *data)
{
	int	i;

	i = 0;
	if (!data)
		return (1);
	if (!data->philos)
		return (ft_putstr_fd("Error : no philos\n", 2), 1);
	set_last_meal(data);
	if (launch_monitor(data))
		return (ft_putstr_fd("Monitor thread error\n", 2), i);
	i = launch_philos(data);
	return (i);
}

int	stop_sim(t_data *data, int stop)
{
	int		i;

	i = 0;
	clean_wait(data);
	if (pthread_join(data->monitor, NULL) != 0)
	{
		pthread_mutex_lock(&data->m_print);
		ft_putstr_fd("Thread join error\n", 2);
		pthread_mutex_unlock(&data->m_print);
	}
	while (i < stop)
	{
		if (pthread_join(data->philos[i]->thread, NULL) != 0)
		{
			pthread_mutex_lock(&data->m_print);
			ft_putstr_fd("Thread join error\n", 2);
			pthread_mutex_unlock(&data->m_print);
			return (1);
		}
		i++;
	}
	return (free_data(data), 0);
}
