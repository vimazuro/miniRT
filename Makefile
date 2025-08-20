# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/03 11:26:33 by vimazuro          #+#    #+#              #
#    Updated: 2025/08/19 13:46:36 by vimazuro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
BONUS_NAME = miniRT_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address

LIBFT_INC_DIR = libft/include 
MLX42_INC_DIR = MLX42/include

LIBFT_DIR = libft/
LIBFT_LIB = $(LIBFT_DIR)libft.a
MLX42_DIR = MLX42/build/
MLX42_LIB = $(MLX42_DIR)libmlx42.a

HEADER = includes/minirt.h includes/parser.h 
BONUS_HEADER = includes/bonus.h
LIBFT_HEADERS = libft/include/libft.h libft/include/ft_printf.h

SRC_COMMON = src/main.c \
			src/utils/ft_print_error.c \
			src/utils/ft_callback.c \
			src/utils/ft_free_data.c \
			src/parser/ft_parse_utils.c \
			src/parser/ft_parse_utils_3.c \
			src/render/ft_vec3_utils1.c \
			src/render/ft_vec3_utils2.c \
			src/render/ft_camera_basis.c \
			src/render/ft_generate_ray.c \
			src/render/ft_intersect_plane.c \
			src/render/ft_intersect_sphere.c \
			src/render/ft_intersect_cylinder.c \
			src/render/ft_render_scene.c \
			src/render/ft_get_normal.c \
			src/render/ft_color_utils.c \
			src/render/ft_is_in_shadow.c \
			src/parser/ft_transfer_object.c \
			src/parser/ft_remove_empty_tokens.c \

SRC_MANDATORY = $(SRC_COMMON) \
			src/render/ft_trace_ray.c \
			src/render/ft_hit_object.c \
			src/render/ft_calc_lighting.c \
			src/parser/ft_parse_acl.c \
			src/parser/ft_parse_objects.c \
			src/parser/ft_parse_file.c \
			src/parser/ft_parse_utils_2.c \


SRC_BONUS =	$(SRC_COMMON) \
			src/bonus/ft_get_reflection_bonus.c \
			src/bonus/ft_obj_chboard_bonus.c \
			src/bonus/ft_get_checker_color_bonus.c \
			src/bonus/ft_init_checker_data_plane_bonus.c \
			src/bonus/ft_init_checker_data_sphere_bonus.c \
			src/bonus/ft_init_checker_data_cylinder_bonus.c \
			src/bonus/ft_init_checker_data_cone_bonus.c \
			src/bonus/ft_trace_ray_bonus.c \
			src/bonus/ft_intersect_cone_bonus.c \
			src/bonus/ft_hit_object_bonus.c \
			src/bonus/ft_calc_lighting_bonus.c \
			src/bonus/ft_parse_acl_bonus.c \
			src/bonus/ft_parse_objects_bonus.c \
			src/bonus/ft_parse_file_bonus.c \
			src/bonus/ft_parse_utils_2_bonus.c \
			src/bonus/ft_obj_texture_bonus.c \
			src/bonus/ft_get_texture_color_bonus.c \
			src/bonus/ft_obj_bump_bonus.c \
			src/bonus/ft_get_bump_normal_bonus.c \
			src/bonus/ft_get_plane_texture_bonus.c \
			src/bonus/ft_get_sphere_texture_bonus.c \
			src/bonus/ft_get_cylinder_texture_bonus.c \
			src/bonus/ft_get_bump_uv_bonus.c \
			src/bonus/ft_parse_plane_bonus.c \
			src/bonus/ft_parse_sphere_bonus.c \
			src/bonus/ft_parse_cylinder_bonus.c \
			src/bonus/ft_parse_cone_bonus.c \

OBJS_MANDATORY = $(LIBFT_LIB) $(MLX42_LIB) $(SRC_MANDATORY:.c=.o)
OBJS_BONUS = $(SRC_BONUS:.c=.o)

all: makelibft makeMLX42 $(NAME)

bonus: makelibft makeMLX42 $(BONUS_NAME)

makelibft:
	$(MAKE) -C $(LIBFT_DIR)

makeMLX42:
	cmake -DDEBUG=1 -S MLX42 -B $(MLX42_DIR)
	cmake --build $(MLX42_DIR) -j4

$(NAME): $(OBJS_MANDATORY)
	$(CC) $(CFLAGS) -I$(LIBFT_INC_DIR) -I$(MLX42_INC_DIR) -o $(NAME) $(OBJS_MANDATORY) $(LIBFT_LIB) $(MLX42_LIB) \
	-L $(MLX42_DIR) -lmlx42 -ldl -lglfw -pthread -lm

$(BONUS_NAME): $(OBJS_BONUS)
	$(CC) $(CFLAGS) -I$(LIBFT_INC_DIR) -I$(MLX42_INC_DIR) -o $(BONUS_NAME) $(OBJS_BONUS) $(LIBFT_LIB) $(MLX42_LIB) \
	-L $(MLX42_DIR) -lmlx42 -ldl -lglfw -pthread -lm

%.o: %.c $(HEADER) $(LIBFT_HEADERS) Makefile
	$(CC) $(CFLAGS) -I$(LIBFT_INC_DIR) -I$(MLX42_INC_DIR) -c $< -o $@

src/bonus/%.o: src/bonus/%.c $(HEADER) $(BONUS_HEADER) $(LIBFT_HEADERS) Makefile
	$(CC) $(CFLAGS) -I$(LIBFT_INC_DIR) -I$(MLX42_INC_DIR) -c $< -o $@

clean:
	rm -f $(OBJS_MANDATORY) $(OBJS_BONUS)
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(MLX42_DIR)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re makelibft makeMLX42
