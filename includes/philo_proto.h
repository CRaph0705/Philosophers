/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_proto.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:37:49 by rcochran          #+#    #+#             */
/*   Updated: 2025/08/26 00:54:54 by rcochran         ###   ########.fr       */
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
void	free_philos(t_data *data);

/* S_FORK.C */

void	free_forks(t_data *data);

/* ROUTINE_UTILS.C */

/*  */
int		do_die(t_philo *philo);

/*  */
int		get_forks(t_philo *philo);

/*  */
void	put_forks(t_philo *philo);

/*  */
void	wait_for_start(t_philo *philo);

/* ROUTINE.C */

/*  */
int		do_eat(t_philo *philo);

/*  */
int		do_sleep(t_philo *philo);

/*  */
int		do_think(t_philo *philo);

/*  */
void	*routine(void *p_philo);

/* UTILS */

/*  */
int		is_numeric(char *str);

/*  */
int		is_digit(int c);

/*  */
int		ft_atoi(const char *str);

/*  */
void	ft_putstr_fd(char *str, int fd);

/*  */
int		args_are_numbers(int ac, char **av);

/* TIME.C */

/*  */
time_t	get_time_in_ms(void);

/* DEATH.C */
int		get_data_hasstopped(t_philo *philo);
int		check_if_death(t_philo *philo);
int		am_i_dead(t_philo *philo);

/* MAIN.C */
int		set_last_meal(t_data *data);

/* CUSTOM_SLEEP.C */
int		custom_usleep(t_philo *philo, long duration_ms);

#endif
