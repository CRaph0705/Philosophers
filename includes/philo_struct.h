/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:33:53 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/17 15:12:08 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_STRUCT_H
# define PHILO_STRUCT_H

typedef struct s_philo
{
	struct s_philo	*head;
	struct s_philo	*next;
	struct s_philo	*prev;
	bool			is_dead;
	bool			is_eating;
	bool			is_sleeping;
	bool			is_thinking;
	bool			right_available;
	bool			left_alaible;
}	t_philo;

typedef struct s_fork
{
	struct s_fork	*head;
	struct s_fork	*next;
	struct s_fork	*prev;
	bool			is_used;
}	t_fork;

typedef struct s_monitor
{
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	t_philo	*philo_list;
	t_fork	*fork_list;
}	t_monitor;

#endif