/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_proto.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:37:49 by rcochran          #+#    #+#             */
/*   Updated: 2025/08/18 18:44:32 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_PROTO_H
# define PHILO_PROTO_H

/* S_DATA.C */

/*  */
int		invalid_args(int ac, char **av);
/*  */
t_data	*init_data(int ac, char **av);
/*  */
void	free_data(t_data *data);

/* S_DATA.C */

/*  */
int		init_forks(t_data *data);

/*  */
int		init_forks(t_data *data);

/* S_PHILO.C */

/*  */
int		init_philo(t_data *data);

/*  */
void	free_philos(t_philo **philo);

/* S_FORK.C */

void	free_forks(t_mutex *forks);

/* ROUTINE.C */

/*  */
void	do_eat(t_philo *philo);

/*  */
void	do_sleep(t_philo *philo);

/*  */
void	do_think(t_philo *philo);

/*  */
void	*routine(void *p_philo);


/* UTILS */
int		is_numeric(char *str);
int		is_digit(int c);
int		ft_atoi(const char *str);
int		args_are_numbers(int ac, char **av);

#endif
