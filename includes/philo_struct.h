/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:33:53 by rcochran          #+#    #+#             */
/*   Updated: 2025/08/26 17:13:56 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_STRUCT_H
# define PHILO_STRUCT_H
# include <pthread.h>

typedef struct s_fork	t_fork;
typedef pthread_mutex_t	t_mutex;

/**
 * typedef struct s_philo
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
*/
typedef struct s_philo
{
	struct s_data	*data;
	time_t			start_time;
	pthread_t		thread;
	unsigned int	m_right;
	unsigned int	m_left;
	long			last_meal;
	int				id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meal;
	bool			is_dead;
}	t_philo;

/** 
typedef	struct s_data
{
	int	nb_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	t_philo	*philos;
	t_mutex	**forks;
	int nb_meal;
	int	has_stopped;
}	t_data;
*/
typedef struct s_data
{
	pthread_t	monitor;
	t_philo		**philos;
	t_mutex		*forks;
	t_mutex		m_print;
	t_mutex		m_death;
	t_mutex		m_time;
	t_mutex		m_meals;
	time_t		start_time;
	int			nb_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			max_meal;
	int			nb_meals;
	bool		has_stopped;
}	t_data;

#endif