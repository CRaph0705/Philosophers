/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:55:47 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/17 11:33:37 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/**
 * No Libft
 * external functions :
 * memset, printf, malloc, free, write,
 * usleep, gettimeofday, pthread_create,
 * pthread_detach, pthread_join, pthread_mutex_init,
 * pthread_mutex_destroy, pthread_mutex_lock,
 * pthread_mutex_unlock
 */
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

int	ft_atoi(const char *str);

#endif