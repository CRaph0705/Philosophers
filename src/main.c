/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:55:24 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/17 11:38:35 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	main_func(int time_to_die, int time_to_eat, int time_to_sleep);

/**
 *  Mandatory part
 * • Each philosopher must be represented as a separate thread.
 * • There is one fork between each pair of philosophers.
 * Therefore, if there are several philosophers, 
 * each philosopher has a fork on their left side and a fork on their right side.
 * If there is only one philosopher, they will have access to just one fork.
 * • To prevent philosophers from duplicating forks, you should protect each fork’s state
 * with a mutex.
*/

void	main_func(int time_to_die, int time_to_eat, int time_to_sleep)
{
	printf("time_to_die = %d, time_to_eat = %d, time_to_sleep = %d\n", time_to_die, time_to_eat, time_to_sleep);
}


int	main(int ac, char **av)
{
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;

	if (ac < 4)
		return (printf("Usage : ./philo <time_to_die>\
			 <time_to_eat> <time_to_sleep>\n"), 1);
	time_to_die = ft_atoi(av[1]);
	time_to_eat = ft_atoi(av[2]);
	time_to_sleep = ft_atoi(av[3]);
	main_func(time_to_die, time_to_eat, time_to_sleep);
	return (0);
}
