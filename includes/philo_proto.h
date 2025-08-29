/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_proto.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:37:49 by rcochran          #+#    #+#             */
/*   Updated: 2025/08/29 10:27:00 by rcochran         ###   ########.fr       */
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
void	put_forks(t_philo *philo, int nb_forks);

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
int		check_death(t_philo *philo);

/* MAIN.C */
int		set_last_meal(t_data *data);

/* CUSTOM_SLEEP.C */
int		custom_usleep(t_philo *philo, long duration_ms);

/* MONITOR.C */
void	*monitor(void *arg);

int		safe_mutex_lock(pthread_mutex_t *m, t_data *data);
int		is_philo_dead(t_data *data, long now, int i);
int		nb_meal_reached(t_data *data);

void	wait_for_start(t_philo *philo);
int		start_sim(t_data *data);
int		stop_sim(t_data *data, int stop);
int		launch_monitor(t_data *data);
int		launch_philos(t_data *data);

#endif
