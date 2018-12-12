# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/08 16:59:52 by kehuang           #+#    #+#              #
#    Updated: 2018/12/12 13:22:42 by kehuang          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:=			RT

#==============================================================================#
#------------------------------------------------------------------------------#
#                               DIRECTORIES                                    #

SRC_DIR			:=			./srcs
PARSER_DIR		:=			parser
MLX_DIR			:=			./mlx_macos
INC_DIR			:=			./includes
OBJ_DIR			:=			./objs
LIB_DIR			:=			./libft

#==============================================================================#
#------------------------------------------------------------------------------#
#                                  FILES                                       #

SRC				:=			main.c					\
							ft_raytracer.c			\
							projection.c			\
							obj_inter.c				\
							obj_normal.c			\
							phong.c					\
							init.c					\
							raytracing.c			\
							ray_distorted.c			\
							gi_ray_distorted.c		\
							global_illumination.c	\
							fresnel.c				\
							get_all_inter.c			\
							transparent.c			\
							screenshot.c			\

SRC_PARSER		:=			parser_json.c			\
							json_key.c				\
							json_val.c				\
							json_utils.c			\
							json_obj_separator.c	\
							get_color.c				\
							take_ptr_vec.c			\
							handle_double.c			\
							handle_string.c			\
							allocation.c			\
							ft_atod.c				\

OBJ_PARSER		:=			$(addprefix $(OBJ_DIR)/,$(SRC_PARSER:.c=.o))

OBJ				:=			$(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
OBJ				+=			$(OBJ_PARSER)

SRC_ALL			:=			$(SRC_PARSER)
SRC_ALL			+=			$(SRC)

NB				:=			$(words $(SRC_ALL))
INDEX			:=			0

#==============================================================================#
#------------------------------------------------------------------------------#
#                            COMPILER & FLAGS                                  #

CC				:=			gcc
CFLAGS			:=			-Wall -Wextra -Werror
CFLAGS			+=			-g3
CFLAGS			+=			-O2
MLXFLAGS		:=			-framework OpenGL -framework AppKit


#==============================================================================#
#------------------------------------------------------------------------------#
#                                LIBRARY                                       #

LIBFT			:=			$(LIB_DIR)/libft.a
CLIB			:=			-L$(LIB_DIR) -lft
LIB_MLX			:=			$(MLX_DIR)/libmlx.a
L_FT			:=			$(LIB_DIR)

#==============================================================================#
#------------------------------------------------------------------------------#
#                                 RULES                                        #

all:					$(NAME)

$(NAME):				$(LIBFT) $(OBJ_DIR) $(OBJ)
	@$(MAKE) -C $(MLX_DIR)
	@$(CC) $(CFLAGS) $(MLXFLAGS) -o $(NAME) $(OBJ) $(CLIB) $(LIB_MLX)
	@printf '\033[33m[ READY ] %s\n\033[0m' "Compilation of $(NAME) is done ---"

$(LIBFT):
	@make -C $(LIB_DIR)

$(OBJ_DIR)/%.o:			$(SRC_DIR)/%.c $(INC_DIR)
	@$(eval DONE=$(shell echo $$(($(INDEX)*20/$(NB)))))
	@$(eval PERCENT=$(shell echo $$(($(INDEX)*100/$(NB)))))
	@$(eval TO_DO=$(shell echo "$@"))
	@$(CC) $(CFLAGS) -o $@ -c $< -I$(INC_DIR)
	@printf "[ %d%% ] %s :: %s        \r" $(PERCENT) $(NAME) $@
	@$(eval INDEX=$(shell echo $$(($(INDEX)+1))))

$(OBJ_DIR)/%.o:			$(SRC_DIR)/$(PARSER_DIR)/%.c $(INC_DIR)
	@$(eval DONE=$(shell echo $$(($(INDEX)*20/$(NB)))))
	@$(eval PERCENT=$(shell echo $$(($(INDEX)*100/$(NB)))))
	@$(eval TO_DO=$(shell echo "$@"))
	@$(CC) $(CFLAGS) -o $@ -c $< -I$(INC_DIR)
	@printf "[ %d%% ] %s :: %s        \r" $(PERCENT) $(NAME) $@
	@$(eval INDEX=$(shell echo $$(($(INDEX)+1))))

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -f $(OBJ)
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIB_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean
	@printf '\033[33m[ KILL ] %s\n\033[0m' "Clean of $(NAME) is done ---"

fclean: 				clean
	@rm -rf $(NAME)
	@$(MAKE) -C $(LIB_DIR) fclean
	@$(MAKE) -C $(MLX_DIR) fclean
	@printf '\033[33m[ KILL ] %s\n\033[0m' "Fclean of $(NAME) is done ---"

re:
	@$(MAKE) fclean
	@$(MAKE)

.PHONY: all clean fclean re build cbuild
