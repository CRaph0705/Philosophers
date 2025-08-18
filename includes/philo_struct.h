/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:33:53 by rcochran          #+#    #+#             */
/*   Updated: 2025/08/14 16:51:27 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_STRUCT_H
# define PHILO_STRUCT_H
# include <pthread.h>

typedef struct s_fork t_fork;
typedef pthread_mutex_t t_mutex;
typedef struct s_philo
{
	bool			is_dead;
	bool			is_eating;
	bool			is_sleeping;
	bool			is_thinking;
	t_mutex			*m_right;
	t_mutex			*m_left;
	t_fork			*f_right;
	t_fork			*f_left;
}	t_philo;

typedef struct s_fork
{
	t_mutex			*mutex;
	bool			is_used;
}	t_fork;


/* typedef struct s_monitor
{
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	t_philo	*philo_list;
	t_fork	*fork_list;
}	t_monitor;
 */
#endif