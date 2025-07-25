# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/24 17:15:01 by vimazuro          #+#    #+#              #
#    Updated: 2025/06/24 17:15:05 by vimazuro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC_DIR = srcs
PRINTF_DIR = $(SRC_DIR)/printf
INC_DIR = include
SRC_FILES = \
	    $(SRC_DIR)/ft_atoi.c $(SRC_DIR)/ft_bzero.c \
	    $(SRC_DIR)/ft_atof.c \
	    $(SRC_DIR)/ft_calloc.c $(SRC_DIR)/ft_isalnum.c \
	    $(SRC_DIR)/ft_isalpha.c $(SRC_DIR)/ft_isascii.c \
	    $(SRC_DIR)/ft_isdigit.c $(SRC_DIR)/ft_isprint.c \
	    $(SRC_DIR)/ft_isfloatpoint.c \
	    $(SRC_DIR)/ft_itoa.c $(SRC_DIR)/ft_memchr.c \
	    $(SRC_DIR)/ft_memcmp.c $(SRC_DIR)/ft_memcpy.c \
	    $(SRC_DIR)/ft_memmove.c $(SRC_DIR)/ft_memset.c \
	    $(SRC_DIR)/ft_putchar_fd.c $(SRC_DIR)/ft_putendl_fd.c \
	    $(SRC_DIR)/ft_putnbr_fd.c $(SRC_DIR)/ft_putstr_fd.c \
	    $(SRC_DIR)/ft_split.c $(SRC_DIR)/ft_strchr.c \
	    $(SRC_DIR)/ft_strdup.c $(SRC_DIR)/ft_strndup.c \
		$(SRC_DIR)/ft_strndup_shift.c $(SRC_DIR)/ft_striteri.c \
	    $(SRC_DIR)/ft_strjoin.c $(SRC_DIR)/ft_strjoin_free.c $(SRC_DIR)/ft_strjoin_3.c \
		$(SRC_DIR)/ft_strlcat.c \
	    $(SRC_DIR)/ft_strlcpy.c $(SRC_DIR)/ft_strlen.c $(SRC_DIR)/ft_strcpy.c \
	    $(SRC_DIR)/ft_strmapi.c \
		$(SRC_DIR)/ft_strcmp.c $(SRC_DIR)/ft_strncmp.c \
	    $(SRC_DIR)/ft_strnstr.c $(SRC_DIR)/ft_strrchr.c \
	    $(SRC_DIR)/ft_strtrim.c $(SRC_DIR)/ft_substr.c \
	    $(SRC_DIR)/ft_tolower.c $(SRC_DIR)/ft_toupper.c \
	    $(SRC_DIR)/ft_lstadd_back.c $(SRC_DIR)/ft_lstadd_front.c \
	    $(SRC_DIR)/ft_lstclear.c $(SRC_DIR)/ft_lstdelone.c \
	    $(SRC_DIR)/ft_lstiter.c $(SRC_DIR)/ft_lstlast.c \
	    $(SRC_DIR)/ft_lstmap.c $(SRC_DIR)/ft_lstnew.c \
	    $(SRC_DIR)/ft_lstsize.c $(SRC_DIR)/get_next_line.c
PRINTF_FILES = \
	       $(PRINTF_DIR)/ft_printf.c \
	       $(PRINTF_DIR)/ft_print_format_c.c \
	       $(PRINTF_DIR)/ft_print_format_d_i.c \
	       $(PRINTF_DIR)/ft_print_format_p.c \
	       $(PRINTF_DIR)/ft_print_format_percent.c \
	       $(PRINTF_DIR)/ft_print_format_s.c \
	       $(PRINTF_DIR)/ft_print_format_u.c \
	       $(PRINTF_DIR)/ft_print_format_x.c
SRC = $(SRC_FILES) $(PRINTF_FILES)
OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) Makefile
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

RM = rm -f

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
