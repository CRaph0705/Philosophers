/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:33:53 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/17 14:05:17 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_STRUCT_H
# define PHILO_STRUCT_H

typedef struct s_monitor
{
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	t_philo	*philo_list;
	t_fork	*fork_list;
}	t_monitor;

typedef struct s_philo
{
	t_philo	*head;
	t_philo	*next;
	t_philo	*prev;
	bool	is_dead;
	bool	is_eating;
	bool	is_sleeping;
	bool	is_thinking;
	bool	right_available;
	bool	left_alaible;
}	t_philo;

typedef struct s_fork
{
	t_fork	*head;
	t_fork	*next;
	t_fork	*prev;
	bool	is_used;
}	t_fork;

#endif