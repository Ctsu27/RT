# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/12 10:24:15 by kehuang           #+#    #+#              #
#    Updated: 2018/12/05 17:20:50 by kehuang          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:=			libft.a

#==============================================================================#
#------------------------------------------------------------------------------#
#                               DIRECTORIES                                    #

SRC_DIR			:=			./srcs
SRC_SUB_DIR		:=			boolean	\
							clr		\
							io		\
							memory	\
							str		\
							vec3	\

SRC_BOOL_DIR	:=			boolean
SRC_CLR_DIR		:=			clr
SRC_IO_DIR		:=			io
SRC_MEMORY_DIR	:=			memory
SRC_STR_DIR		:=			str
SRC_VEC3_DIR	:=			vec3

INC_DIR			:=			./includes
OBJ_DIR			:=			./objs

#==============================================================================#
#------------------------------------------------------------------------------#
#                                  FILES                                       #

SRC_NAME		:=			$(SRC_BOOL_DIR)/ft_isalnum.c     	\
							$(SRC_BOOL_DIR)/ft_isalpha.c     	\
							$(SRC_BOOL_DIR)/ft_isascii.c     	\
							$(SRC_BOOL_DIR)/ft_isdigit.c     	\
							$(SRC_BOOL_DIR)/ft_isprint.c     	\
							$(SRC_BOOL_DIR)/ft_iswhitespace.c	\
							$(SRC_CLR_DIR)/add_clr.c			\
							$(SRC_CLR_DIR)/modifier_clr.c		\
							$(SRC_CLR_DIR)/div_clr.c			\
							$(SRC_CLR_DIR)/mul_clr.c			\
							$(SRC_CLR_DIR)/new_clr.c			\
							$(SRC_CLR_DIR)/sub_clr.c			\
							$(SRC_CLR_DIR)/lerp_clr.c			\
							$(SRC_CLR_DIR)/clamp_clr.c			\
							$(SRC_IO_DIR)/ft_putchar.c   		\
							$(SRC_IO_DIR)/ft_putchar_fd.c		\
							$(SRC_IO_DIR)/ft_putendl.c   		\
							$(SRC_IO_DIR)/ft_putendl_fd.c		\
							$(SRC_IO_DIR)/ft_putnbr.c    		\
							$(SRC_IO_DIR)/ft_putnbr_base.c 		\
							$(SRC_IO_DIR)/ft_putnbr_fd.c 		\
							$(SRC_IO_DIR)/ft_putnbr_base_fd.c	\
							$(SRC_IO_DIR)/ft_putstr.c    		\
							$(SRC_IO_DIR)/ft_putstr_fd.c 		\
							$(SRC_IO_DIR)/ft_putunbr_fd.c		\
							$(SRC_IO_DIR)/get_next_line.c		\
							$(SRC_MEMORY_DIR)/ft_bzero.c   		\
							$(SRC_MEMORY_DIR)/ft_memalloc.c		\
							$(SRC_MEMORY_DIR)/ft_memccpy.c 		\
							$(SRC_MEMORY_DIR)/ft_memchr.c  		\
							$(SRC_MEMORY_DIR)/ft_memcmp.c  		\
							$(SRC_MEMORY_DIR)/ft_memcpy.c  		\
							$(SRC_MEMORY_DIR)/ft_memdel.c  		\
							$(SRC_MEMORY_DIR)/ft_memmove.c 		\
							$(SRC_MEMORY_DIR)/ft_memset.c  		\
							$(SRC_MEMORY_DIR)/ft_swap.c    		\
							$(SRC_STR_DIR)/ft_atoi.c     		\
							$(SRC_STR_DIR)/ft_free_str2.c		\
							$(SRC_STR_DIR)/ft_itoa.c     		\
							$(SRC_STR_DIR)/ft_itoa_base.c		\
							$(SRC_STR_DIR)/ft_str2len.c  		\
							$(SRC_STR_DIR)/ft_strcat.c   		\
							$(SRC_STR_DIR)/ft_strchr.c   		\
							$(SRC_STR_DIR)/ft_strclen.c  		\
							$(SRC_STR_DIR)/ft_strclr.c   		\
							$(SRC_STR_DIR)/ft_strcmp.c   		\
							$(SRC_STR_DIR)/ft_strcpy.c   		\
							$(SRC_STR_DIR)/ft_strdel.c   		\
							$(SRC_STR_DIR)/ft_strdup.c   		\
							$(SRC_STR_DIR)/ft_strequ.c   		\
							$(SRC_STR_DIR)/ft_striter.c  		\
							$(SRC_STR_DIR)/ft_striteri.c 		\
							$(SRC_STR_DIR)/ft_strjoin.c  		\
							$(SRC_STR_DIR)/ft_strlcat.c  		\
							$(SRC_STR_DIR)/ft_strlen.c   		\
							$(SRC_STR_DIR)/ft_strmap.c   		\
							$(SRC_STR_DIR)/ft_strmapi.c  		\
							$(SRC_STR_DIR)/ft_strncat.c  		\
							$(SRC_STR_DIR)/ft_strncmp.c  		\
							$(SRC_STR_DIR)/ft_strncpy.c  		\
							$(SRC_STR_DIR)/ft_strndup.c  		\
							$(SRC_STR_DIR)/ft_strnequ.c  		\
							$(SRC_STR_DIR)/ft_strnew.c   		\
							$(SRC_STR_DIR)/ft_strnlen.c  		\
							$(SRC_STR_DIR)/ft_strnstr.c  		\
							$(SRC_STR_DIR)/ft_strrchr.c  		\
							$(SRC_STR_DIR)/ft_strsplit.c 		\
							$(SRC_STR_DIR)/ft_splitwhitespace.c \
							$(SRC_STR_DIR)/ft_strstr.c   		\
							$(SRC_STR_DIR)/ft_strsub.c   		\
							$(SRC_STR_DIR)/ft_strtrim.c  		\
							$(SRC_STR_DIR)/ft_tolower.c  		\
							$(SRC_STR_DIR)/ft_toupper.c  		\
							$(SRC_VEC3_DIR)/new_vec3.c			\
							$(SRC_VEC3_DIR)/rnew_vec3.c			\
							$(SRC_VEC3_DIR)/add_vec3.c			\
							$(SRC_VEC3_DIR)/div_vec3.c			\
							$(SRC_VEC3_DIR)/mul_vec3.c			\
							$(SRC_VEC3_DIR)/rot_vec3.c			\
							$(SRC_VEC3_DIR)/sub_vec3.c			\
							$(SRC_VEC3_DIR)/dot_vec3.c			\
							$(SRC_VEC3_DIR)/norm_vec3.c			\
							$(SRC_VEC3_DIR)/xx_rot3.c			\
							$(SRC_VEC3_DIR)/yy_rot3.c			\
							$(SRC_VEC3_DIR)/zz_rot3.c			\

SRC_ALL			:= 			$(addprefix $(SRC_DIR)/,$(SRC_NAME))

OBJ				:=			$(addprefix $(OBJ_DIR)/,$(SRC_NAME:.c=.o))
NB				:=			$(words $(SRC_ALL))
INDEX			:=			0

#==============================================================================#
#------------------------------------------------------------------------------#
#                            COMPILER & FLAGS                                  #

CC				:=			gcc
CFLAGS			:=			-Wall -Wextra -Werror
CFLAGS			+=			-g3
CFLAGS			+=			-O2

#==============================================================================#
#------------------------------------------------------------------------------#
#                                 RULES                                        #

all:					$(NAME)

$(NAME):				$(OBJ_DIR) $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@printf "[ 100%% ] %s                                                       \n" "libft.a"

$(OBJ_DIR)/%.o:			 $(SRC_DIR)/%.c $(INC_DIR)
	@$(eval DONE=$(shell echo $$(($(INDEX)*20/$(NB)))))
	@$(eval PERCENT=$(shell echo $$(($(INDEX)*100/$(NB)))))
	@$(eval TO_DO=$(shell echo "$@"))
	@$(CC) $(CFLAGS) -o $@ -c $< -I$(INC_DIR)
	@printf "[ %d%% ] %s :: %s        \r" $(PERCENT) $(NAME) $@
	@$(eval INDEX=$(shell echo $$(($(INDEX)+1))))

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(addprefix $(OBJ_DIR)/,$(SRC_SUB_DIR))

clean:
	@rm -rf $(OBJ_DIR)
	@printf '\033[33m[ KILL ] %s\n\033[0m' "Clean of $(NAME) is done ---"

fclean: 				clean
	@rm -rf $(NAME)
	@printf '\033[33m[ KILL ] %s\n\033[0m' "Fclean of $(NAME) is done ---"

re:
	@$(MAKE) fclean
	@$(MAKE)

.PHONY: all clean fclean re build cbuild
