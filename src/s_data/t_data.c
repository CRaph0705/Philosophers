/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_data.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 13:47:30 by rcochran          #+#    #+#             */
/*   Updated: 2025/08/29 10:17:31 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		invalid_args(int ac, char **av);
t_data	*init_data(int ac, char **av);
void	free_data(t_data *data);

int	invalid_args(int ac, char **av)
{
	int			nb_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			meal_number;

	if (ac < 5 || ac > 7 || !args_are_numbers(ac, av))
		return (printf("Usage : ./philo <number_of_philosophers> <time_to_die> \
<time_to_eat> <time_to_sleep>\n"), 1);
	nb_philo = ft_atoi(av[1]);
	time_to_die = ft_atoi(av[2]);
	time_to_eat = ft_atoi(av[3]);
	time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		meal_number = ft_atoi(av[5]);
	else
		meal_number = 1;
	if (nb_philo < 1 || nb_philo > 200)
		return (ft_putstr_fd("Error: wrong philo number given\n", 2), 2);
	if (time_to_die < 0 || time_to_eat < 0 || time_to_sleep < 0)
		return (ft_putstr_fd("Error: wrong time number given\n", 2), 3);
	if (meal_number < 0)
		return (ft_putstr_fd("Error: wrong meal number given\n", 2), 4);
	return (0);
}

int	init_mtx(t_data *data)
{
	pthread_mutex_t	death;
	pthread_mutex_t	meals;
	pthread_mutex_t	print;
	pthread_mutex_t	ready;
	pthread_mutex_t	stop;

	if (pthread_mutex_init(&death, NULL) != 0)
		return (ft_putstr_fd("Error : mutex error", 2), 1);
	data->m_death = death;
	if (pthread_mutex_init(&meals, NULL) != 0)
		return (ft_putstr_fd("Error : mutex error", 2), 1);
	data->m_meals = meals;
	if (pthread_mutex_init(&print, NULL) != 0)
		return (ft_putstr_fd("Error : mutex error", 2), 1);
	data->m_print = print;
	if (pthread_mutex_init(&ready, NULL) != 0)
		return (ft_putstr_fd("Error : mutex error", 2), 1);
	data->m_ready = ready;
	if (pthread_mutex_init(&stop, NULL) != 0)
		return (ft_putstr_fd("Error : mutex error", 2), 1);
	data->m_stop = stop;
	return (init_forks(data));
}

t_data	*init_data(int ac, char **av)
{
	t_data			*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (ft_putstr_fd("Error: malloc failed\n", 2), NULL);
	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->ready_count = 0;
	if (ac == 6)
		data->max_meal = ft_atoi(av[5]);
	else
		data->max_meal = -1;
	data->philos = NULL;
	data->forks = NULL;
	data->simulation_stop = 0;
	data->ready_count = 0;
	data->nb_meals = 0;
	if (init_mtx(data))
		return (free_data(data), NULL);
	return (data);
}

void	destroy_mutexes(t_data *data)
{
	pthread_mutex_lock(&data->m_death);
	pthread_mutex_lock(&data->m_meals);
	pthread_mutex_lock(&data->m_print);
	pthread_mutex_lock(&data->m_ready);
	pthread_mutex_lock(&data->m_stop);
	pthread_mutex_unlock(&data->m_death);
	pthread_mutex_destroy(&data->m_death);
	pthread_mutex_unlock(&data->m_meals);
	pthread_mutex_destroy(&data->m_meals);
	pthread_mutex_unlock(&data->m_print);
	pthread_mutex_destroy(&data->m_print);
	pthread_mutex_unlock(&data->m_ready);
	pthread_mutex_destroy(&data->m_ready);
	pthread_mutex_unlock(&data->m_stop);
	pthread_mutex_destroy(&data->m_stop);
}

void	free_data(t_data *data)
{
	if (data)
	{
		if (data->philos)
			free_philos(data);
		if (data->forks)
			free_forks(data);
		destroy_mutexes(data);
		free(data);
	}
}
