/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_fork.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 14:03:35 by rcochran          #+#    #+#             */
/*   Updated: 2025/08/18 16:38:36 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		init_forks(t_data *data);
void	free_forks(t_fork **forks);

int	init_forks(t_data *data)
{
	int		nb_forks;
	t_fork	**forks;

	nb_forks = data->nb_philo;
	forks = malloc(sizeof(t_fork) * nb_forks);
	if (!forks)
		return (perror("Error : malloc failed\n"), 1);
	data->forks = forks;
	return (0);
}

void	free_forks(t_fork **forks)
{
	(void)forks;
	return ;
}
