/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_proto.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:37:49 by rcochran          #+#    #+#             */
/*   Updated: 2025/08/18 12:03:27 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_PROTO_H
# define PHILO_PROTO_H

int	ft_atoi(const char *str);


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
