# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/30 15:35:09 by rabustam          #+#    #+#              #
#    Updated: 2022/07/26 21:46:56 by rabustam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c\
ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c ft_strlcat.c ft_strlcpy.c ft_strlen.c\
ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_tolower.c ft_toupper.c ft_memcmp.c ft_memchr.c\
ft_strdup.c ft_calloc.c ft_strjoin.c ft_substr.c ft_strtrim.c ft_split.c ft_itoa.c\
ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c\
get_next_line.c get_next_line_utils.c

OBJS	= ft_atoi.o ft_bzero.o ft_isalnum.o ft_isalpha.o ft_isascii.o ft_isdigit.o ft_isprint.o\
ft_memcpy.o ft_memmove.o ft_memset.o ft_strchr.o ft_strlcat.o ft_strlcpy.o ft_strlen.o\
ft_strncmp.o ft_strnstr.o ft_strrchr.o ft_tolower.o ft_toupper.o ft_memcmp.o ft_memchr.o\
ft_strdup.o ft_calloc.o ft_strjoin.o ft_substr.o ft_strtrim.o ft_split.o ft_itoa.o\
ft_strmapi.o ft_striteri.o ft_putchar_fd.o ft_putstr_fd.o ft_putendl_fd.o ft_putnbr_fd.o\
get_next_line.o get_next_line_utils.o

BONUS_SRC	= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c\
ft_lstclear.c ft_lstiter.c ft_lstmap.c

BONUS_OBJ	= ft_lstnew.o ft_lstadd_front.o ft_lstsize.o ft_lstlast.o ft_lstadd_back.o ft_lstdelone.o\
ft_lstclear.o ft_lstiter.o ft_lstmap.o

HEADER	= libft.h

NAME	= libft.a

.c.o: $(SRCS)
		cc -Wall -Wextra -Werror -c -o $@ $<

$(NAME): $(OBJS) $(HEADER)
		ar rcs $@ $^

bonus: $(BONUS_OBJ) $(HEADER)
		ar rcs $(NAME) $^

all:	$(NAME)

clean:
		rm -f $(OBJS) $(BONUS_OBJ)

fclean:	clean
		rm -f $(NAME)
		
re:		clean all

.PHONY: all bonus clean fclean re