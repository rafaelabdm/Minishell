# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/20 09:09:51 by rapdos-s          #+#    #+#              #
#    Updated: 2023/01/07 15:19:20 by rabustam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
LIBFT_DIR	= libft/
LIBFT		= ${LIBFT_DIR}libft.a
SRC			= main.c utils.c free.c \
			  lexer.c \
			  parser.c parser_utils.c \
			  syntax_checker.c \
			  expander.c expander_utils.c\
			  executor.c executor_utils.c\
			  child.c \
			  path.c \
			  redirect.c redirect_utils.c \
			  builtins.c echo.c cd.c pwd.c export.c unset.c env.c exit.c
OBJ_DIR		= objects/
OBJ			= ${addprefix ${OBJ_DIR}, ${SRC:%.c=%.o}}
VPATH		= sources sources/builtin
INCLUDES	= headers/ ${LIBFT_DIR}
INCLUDES	:= ${addprefix -I, ${INCLUDES}}
CC			= cc
CFLAGS		= -Wall -Werror -Wextra
RLFLAGS		= -lreadline
RM			= rm -rf

all: ${NAME}

$(NAME): ${LIBFT} ${OBJ_DIR} ${OBJ}
	${CC} ${CFLAGS} ${OBJ} ${INCLUDES} ${LIBFT} ${RLFLAGS} -o ${NAME}

clean:
	make clean -C ${LIBFT_DIR}
	${RM} ${OBJ_DIR}

fclean: clean
	make fclean -C ${LIBFT_DIR}
	${RM} ${NAME}

re: fclean all

${LIBFT}:
	make -C ${LIBFT_DIR}

${OBJ_DIR}:
	mkdir -p ${OBJ_DIR}

${OBJ_DIR}%.o: %.c
	${CC} -c ${CFLAGS} ${INCLUDES} $< -o $@

.PHONY: all clean fclean re
