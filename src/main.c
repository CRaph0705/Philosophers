/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:55:24 by rcochran          #+#    #+#             */
/*   Updated: 2025/08/11 14:50:19 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	main_func(int nb_philo,
			int time_to_die, int time_to_eat, int time_to_sleep);

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
void	main_func(int nb_philo,
			int time_to_die, int time_to_eat, int time_to_sleep)
{
	printf("nb_philo = %d, time_to_die = %d, time_to_eat = %d,\
		 time_to_sleep = %d\n",nb_philo, time_to_die, time_to_eat, time_to_sleep);
}


pthread_mutex_t	mutex;

/* int	main(int ac, char **av)
{
	pthread_t	p1;
	int			philo_nb;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;

	pthread_mutex_init(&mutex, NULL);

	if (ac < 5)
		return (printf("Usage : ./philo <numer_of_philosophers> <time_to_die>\
			 <time_to_eat> <time_to_sleep>\n"), 1);

	philo_nb = ft_atoi(av[1]);
	time_to_die = ft_atoi(av[2]);
	time_to_eat = ft_atoi(av[3]);
	time_to_sleep = ft_atoi(av[4]);
	main_func(philo_nb, time_to_die, time_to_eat, time_to_sleep);
	return (0);
} */

void	routine(void)
{
	printf("Coucou je suis un thread\n");
	sleep(3);
	printf("fin du thread\n");
}
int main(void)
{
	pthread_t t1, t2;
	if (!pthread_create(&t1, NULL, &routine, NULL))
		return (1);
	if (!pthread_create(&t2, NULL, &routine, NULL))
		return (1);
	if (!pthread_join(t1, NULL))
		return (1);
	if (!pthread_join(t2, NULL))
		return (1);
	return (0);
}		