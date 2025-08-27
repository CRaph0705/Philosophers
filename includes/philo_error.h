/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_error.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 11:42:17 by rcochran          #+#    #+#             */
/*   Updated: 2025/08/27 12:07:34 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ERROR_H
# define PHILO_ERROR_H

# define TRUE 1
# define FALSE 0
# define SUCCESS 0
# define ERROR 1
# define NONE -1
# define ARGS_MESS "Usage : ./philo <num_of_philo> <time_to_die> <time_to_eat> <time_to_sleep>\
 [optional]: <number_of_times_each_philosopher_must_eat>"
# define ERROR_ARG_MESS_1 "must be a positive integer greater than 0"
# define ERROR_ARG_MESS "must be a positive integer"
# define OPTION "[optional] <number_of_times_each_philosopher_must_eat>: "

#endif