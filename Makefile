# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/03 11:26:33 by vimazuro          #+#    #+#              #
#    Updated: 2025/07/24 12:14:51 by hmunoz-g         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
LIBFT_INC_DIR = libft/include 
MLX42_INC_DIR = MLX42/include
LIBFT_DIR = libft/
LIBFT_LIB = $(LIBFT_DIR)libft.a
MLX42_DIR = MLX42/build/
MLX42_LIB = $(MLX42_DIR)libmlx42.a
HEADER = includes/minirt.h includes/parser.h
LIBFT_HEADERS = libft/include/libft.h libft/include/ft_printf.h

SRC_FILES = src/main.c \
			src/utils/ft_print_error.c \
			src/utils/ft_callback.c \
			src/utils/ft_free_data.c \
			src/parser/ft_parse_acl.c \
			src/parser/ft_parse_file.c \
			src/parser/ft_parse_utils.c \
			src/parser/ft_parse_utils_2.c \
			src/parser/ft_parse_objects.c \
			src/render/ft_calc_lighting.c \
			src/render/ft_vec3_utils1.c \
			src/render/ft_vec3_utils2.c \
			src/render/ft_camera_basis.c \
			src/render/ft_generate_ray.c \
			src/render/ft_intersect_plane.c \
			src/render/ft_intersect_sphere.c \
			src/render/ft_intersect_cylinder.c \
			src/render/ft_trace_ray.c \
			src/render/ft_render_scene.c \
			src/render/ft_hit_object.c \
			src/render/ft_get_normal.c \
			src/render/ft_color_utils.c \

OBJS = $(LIBFT_LIB) $(MLX42_LIB) $(SRC_FILES:.c=.o)

all: makelibft makeMLX42 $(NAME)

makelibft:
	$(MAKE) -C $(LIBFT_DIR)

makeMLX42:
	cmake -DDEBUG=1 -S MLX42 -B $(MLX42_DIR)
	cmake --build $(MLX42_DIR) -j4

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -I$(LIBFT_INC_DIR) -I$(MLX42_INC_DIR) -o $(NAME) $(OBJS) $(LIBFT_LIB) $(MLX42_LIB) \
	-L $(MLX42_DIR) -lmlx42 -ldl -lglfw -pthread -lm

%.o: %.c $(HEADER) $(LIBFT_HEADERS) Makefile
	$(CC) $(CFLAGS) -I$(LIBFT_INC_DIR) -I$(MLX42_INC_DIR) -c $< -o $@

clean:
	rm -f $(SRC_FILES:.c=.o)
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(MLX42_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re makelibft makeMLX42
