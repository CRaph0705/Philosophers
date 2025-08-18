/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:56:06 by rcochran          #+#    #+#             */
/*   Updated: 2025/08/14 17:03:21 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	do_eat(void);
void	do_sleep(void);
void	do_think(void);
void	*routine();

void	do_eat(void)
{
	printf("eating...\n");
	sleep(3);
}

void	do_sleep(void)
{
	printf("sleeping...\n");
	sleep(3);
}

void	do_think(void)
{
	printf("thinking...\n");
	sleep(3);
}

void	*routine()
{
	do_eat();
	do_sleep();
	do_think();
	return (NULL);
}