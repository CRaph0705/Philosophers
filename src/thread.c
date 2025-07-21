/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 10:53:36 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/17 13:49:23 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pthread_create(pthread_t *restrict thread,
		const pthread_attr_t *restrict attr,
		void *(*start_routine)(void *),
		void *restrict arg);

int	pthread_join(pthread_t thread, void **retval);

int	pthread_detach(pthread_t thread);

/* waitpid */

/* gettimeofday */

/* usleep */

/* exit */

/* kill */

/* fork */

/* write */

/* printf */

/* memset */