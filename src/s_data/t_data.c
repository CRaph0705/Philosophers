/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_data.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 13:47:30 by rcochran          #+#    #+#             */
/*   Updated: 2025/08/18 18:43:26 by rcochran         ###   ########.fr       */
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
	if (nb_philo < 1)
		return (perror("Error: wrong philo number given\n"), 2);
	if (time_to_die < 0 || time_to_eat < 0 || time_to_sleep < 0)
		return (perror("Error: wrong time number given\n"), 3);
	if (meal_number < 0)
		return (perror("Error: wrong meal number given\n"), 4);
	return (0);
}

t_data	*init_data(int ac, char **av)
{
	t_data	*data;

	if (invalid_args(ac, av))
		return (NULL);
	data = malloc(sizeof(t_data));
	if (!data)
		return (perror("Error: malloc failed\n"), NULL);
	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->max_meal = ft_atoi(av[5]);
	else
		data->max_meal = -1;
	data->philos = NULL;
	data->forks = NULL;
	if (init_forks(data))
		return (NULL);
	if (init_philo(data))
		return (NULL);
	return (data);
}

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	if (data)
	{
		if (data->forks)
			free_forks(data->forks);
		if (data->philos)
			free_philos(data->philos);
		free(data);
	}
}
