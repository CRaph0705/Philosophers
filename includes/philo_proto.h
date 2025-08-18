/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_proto.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:37:49 by rcochran          #+#    #+#             */
/*   Updated: 2025/08/18 16:45:50 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_PROTO_H
# define PHILO_PROTO_H

int		ft_atoi(const char *str);

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

void	free_forks(t_fork **forks);

/* ROUTINE.C */

/*  */
void	do_eat(int t_eat);
/*  */
void	do_sleep(int t_sleep);
/*  */
void	do_think(void);
/*  */
void	*routine(void *data);

#endif
