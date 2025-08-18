/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:55:24 by rcochran          #+#    #+#             */
/*   Updated: 2025/08/18 12:15:24 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main_func(int nb_philo,
			int time_to_die, int time_to_eat, int time_to_sleep, int meal_number);


t_data	*init_data(int nb_philo, int time_to_die, int time_to_eat, int time_to_sleep, int meal_number);

t_data	*init_data(int nb_philo, int time_to_die, int time_to_eat, int time_to_sleep, int meal_number)
{
	t_data	*data;
	
	if (nb_philo < 1)
		return (perror("Error: wrong philo number given\n"), NULL);
	if (time_to_die < 0 || time_to_eat < 0 || time_to_sleep < 0)
		return (perror("Error: wrong time number given\n"), NULL);
	if (meal_number < 0)
		return (perror("Error: wrong meal number given\n"), NULL);
	data = malloc(sizeof(t_data));
	if (!data)
		return (perror("Error: malloc failed\n"), NULL);
	data->nb_philo = nb_philo;
	data->time_to_die = time_to_die;
	data->time_to_eat = time_to_eat;
	data->time_to_sleep = time_to_sleep;
	data->nb_meal = meal_number;
	data->philos = NULL;
	// data->philos = init_philo();
	return (data);	
}
/**
 *  Mandatory part
 * • Each philosopher must be represented as a separate thread.
 * • There is one fork between each pair of philosophers.
 * Therefore, if there are several philosophers, 
 * each philosopher has a fork on their left side and a fork on their right side.
 * If there is only one philosopher, they will have access to just one fork.
 * • To prevent philosophers from duplicating forks,
 * you should protect each fork’s state with a mutex.
*/
int	main_func(int nb_philo,
			int time_to_die, int time_to_eat, int time_to_sleep, int meal_number)
{
	printf("[> nb_philo = %d\n> time_to_die = %d\n> time_to_eat = %d\n> time_to_sleep = %d\n",nb_philo, time_to_die, time_to_eat, time_to_sleep);

	pthread_t t1, t2;
	t_data	*data;
	data = init_data(nb_philo, time_to_die, time_to_eat, time_to_sleep, meal_number);
	// init_sim(data);
	if (pthread_create(&t1, NULL, &routine,  (void *)data) != 0)
		return (1);
	if (pthread_create(&t2, NULL, &routine,  (void *)data) != 0)
		return (2);
	if (pthread_join(t1, NULL) != 0)
		return (3);
	if (pthread_join(t2, NULL) != 0)
		return (4);
	return (0);
}


pthread_mutex_t	mutex;

int	main(int ac, char **av)
{
	// pthread_t	p1;
	int			philo_nb;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			meal_number;

	pthread_mutex_init(&mutex, NULL);

	if (ac < 5)
		return (printf("Usage : ./philo <numer_of_philosophers> <time_to_die> \
<time_to_eat> <time_to_sleep>\n"), 1);

	philo_nb = ft_atoi(av[1]);
	time_to_die = ft_atoi(av[2]);
	time_to_eat = ft_atoi(av[3]);
	time_to_sleep = ft_atoi(av[4]);
	if (philo_nb <= 0|| time_to_die <= 0 || time_to_eat <= 0 || time_to_sleep <= 0)
		return (1);
	if (ac < 6)
			meal_number = -1;
	else
		meal_number = ft_atoi(av[5]);
	main_func(philo_nb, time_to_die, time_to_eat, time_to_sleep, meal_number);
	return (0);
}



