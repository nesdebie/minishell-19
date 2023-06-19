# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/08 09:54:51 by nedebies          #+#    #+#              #
#    Updated: 2023/05/19 13:07:38 by nesdebie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME  = libft

SRCS 	=	ft_atoi.c\
		ft_isalpha.c\
		ft_itoa.c\
		ft_memcpy.c\
		ft_strchr.c\
		ft_strlcpy.c\
		ft_strnstr.c\
		ft_tolower.c\
		ft_bzero.c\
		ft_isascii.c\
		ft_striteri.c\
		ft_memmove.c\
		ft_strdup.c\
		ft_strlen.c\
		ft_strrchr.c\
		ft_toupper.c\
		ft_calloc.c\
		ft_isdigit.c\
		ft_memchr.c\
		ft_memset.c\
		ft_strjoin.c\
		ft_strtrim.c\
		ft_isalnum.c\
		ft_isprint.c\
		ft_memcmp.c\
		ft_split.c\
		ft_strlcat.c\
		ft_strncmp.c\
		ft_substr.c\
		ft_strmapi.c\
		ft_putchar_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\
		ft_putstr_fd.c\
		ft_strcmp.c \
		get_next_line_bonus.c \
		get_next_line_utils_bonus.c

BONUS		= ft_lstadd_back_bonus.c\
				  ft_lstadd_front_bonus.c\
				  ft_lstclear_bonus.c\
				  ft_lstdelone_bonus.c\
				  ft_lstiter_bonus.c\
				  ft_lstlast_bonus.c\
				  ft_lstnew_bonus.c\
				  ft_lstsize_bonus.c\
				  ft_lstmap_bonus.c\

CC			=	cc

FLAGS		=	-Wall -Wextra -Werror

OBJS	=	$(SRCS:.c=.o)

OBJS_B	=	$(BONUS:.c=.o)

ARRCS		=	ar rcs

RM		= rm -rf

.c.o:
	$(CC) $(FLAGS) -c -o $@ $<

$(NAME).a: 	$(OBJS)
		$(ARRCS) $(NAME).a $^

bonus: $(OBJS) $(OBJS_B)
	$(ARRCS) $(NAME).a $^

all:	 $(NAME).a

clean:
	$(RM) $(OBJS) $(OBJS_B)

fclean:		clean
		$(RM) $(NAME).a

re:		fclean all

.PHONY:			all clean fclean re bonus
