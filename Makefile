# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/19 10:55:20 by rcochran          #+#    #+#              #
#    Updated: 2025/08/21 16:31:53 by rcochran         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


.PHONY : all clean fclean re debug

CC			= 	cc
CFLAGS		= 	-Wall -Werror -Wextra -MMD -MP -g3
AR			=	ar -rcs
NAME		= 	philo

INCLUDES	= 	-I ./includes

FILES		= 	s_data/t_data \
				s_fork/t_fork \
				s_philo/t_philo \
				utils/args_are_numbers \
				utils/ft_atoi \
				utils/is_digit \
				utils/is_numeric \
				death \
				routine_utils \
				routine \
				time

SRC_DIR		= 	src/
SRC_FILES	=	$(addsuffix .c, $(FILES))
SRC			=	$(addprefix $(SRC_DIR), $(SRC_FILES))

MAIN		=	main.c
OBJ_DIR		= 	obj/
# OBJ_DIR		= 	$(sort $(dir $(OBJ)))
OBJ			=	$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))
OBJ_MAIN	=	$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC_DIR)$(MAIN))

ifneq ($(filter debug, $(MAKECMDGOALS)),)
CFLAGS += -g -v
endif

all : $(NAME)

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -f $(NAME)

re : fclean all

$(NAME) : $(OBJ_DIR) $(OBJ) $(OBJ_MAIN)
	$(CC) $(CFLAGS) $(INCLUDES) -pthread $(OBJ) $(OBJ_MAIN) -o $(NAME)


$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(INCLUDES) -pthread -c $< -o $@

$(OBJ_DIR) : 
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)s_data
	mkdir -p $(OBJ_DIR)s_fork
	mkdir -p $(OBJ_DIR)s_monitor
	mkdir -p $(OBJ_DIR)s_philo
	mkdir -p $(OBJ_DIR)utils

debug : all
	valgrind --tool=helgrind ./$(NAME) 1 2000 20 20