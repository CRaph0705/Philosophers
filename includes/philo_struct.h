/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:33:53 by rcochran          #+#    #+#             */
/*   Updated: 2025/08/19 16:22:05 by rcochran         ###   ########.fr       */
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
	int				id;
	pthread_t		thread;
	bool			is_dead;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	t_mutex			*m_right;
	t_mutex			*m_left;
	long			last_meal;
	struct s_data	*data;
	int				nb_meal;
	t_mutex			mtx;
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
	int		nb_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	t_philo	**philos;
	t_mutex	*forks;
	int		max_meal;
	int		has_stopped;
	time_t	start;
}	t_data;

#endif