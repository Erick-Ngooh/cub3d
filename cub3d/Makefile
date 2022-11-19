# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: engooh <engooh@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/24 11:27:17 by engooh            #+#    #+#              #
#    Updated: 2022/11/19 15:54:35 by engooh           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                                                                              #
#                               INCLUDES                                       # 
#                                                                              #
################################################################################
INC = -I ./include

################################################################################
#                                                                              #
#                               SOURCE FILES                                   # 
#                                                                              #
################################################################################		

SRC = ./source/main/main.c\
	./source/parsing/get_next_line_utils.c\
	 ./source/parsing/get_next_line.c\
	 ./source/parsing/parsing_map.c\
	 ./source/parsing/parsing_utils.c\
	 ./source/parsing/parsing_element.c\
	 ./source_r/draw_circle.c\
	 ./source_r/draw_line.c\
	 ./source_r/print_3d.c\
	 ./source_r/raycasting.c\
	 ./source_r/test.c

################################################################################
#                                                                              #
#                               OBJECT FILES                                   # 
#                                                                              #
################################################################################
OBJ = ${SRC:%.c=%.o}

################################################################################
#                                                                              #
#                               LIBRARY                                        # 
#                                                                              #
################################################################################
LIB = ./source/share/libft/libft.a
MINILIBX = ./source/share/minilibx-linux/libmlx_Linux.a
# MINILIBX1 = ./source/share/minilibx-linux/libmlx.a
################################################################################
#                                                                              #
#                               DEPENDENCE                                     # 
#                                                                              #
################################################################################
DEPS = ${SRC:%.c=%.d}

################################################################################
#                                                                              #
#                               COMPILATIONS FLAGS                             # 
#                                                                              #
################################################################################
CC = clang
CFLAG = -Werror -Wall -Wextra -g3 -Ofast
LINK = -lft -lmlx_Linux -lXext -lX11 -lm
LIBPATH = -Lsource/share/libft -Lsource/share/minilibx-linux/mlx -L/usr/lib

################################################################################
#                                                                              #
#                               OTHER MAKE                                     # 
#                                                                              #
################################################################################
NAME = cub3d
PATH_LIBFT = ./source/share/libft/
PATH_MINILIBX = ./source/share/minilibx-linux/mlx

################################################################################
#                                                                              #
#                               RULES                                          # 
#                                                                              #
################################################################################
all:  $(NAME)

# MAKE_OTHER
$(NAME) : $(OBJ)
	make -C $(PATH_LIBFT)
	make -C $(PATH_MINILIBX)
	$(CC) $(CFLAG) $(OBJ) $(LIBPATH) $(LINK) $(INC) $(LIB) $(MINILIBX) -o $@
# $(MINILIBX1)

#MAKE_OTHER:

%.o: %.c
	$(CC) $(CFLAG) -MMD -c $< -o $@ $(INC)

exec: $(NAME)
	./$(NAME)
clean:
	rm -f $(OBJ)
	rm -f $(DEPS)
	make clean -C $(PATH_LIBFT)
	make clean -C $(PATH_MINILIBX)

fclean : clean
	rm -f $(NAME)
	make - fclean -C $(PATH_LIBFT)
	make - clean -C $(PATH_MINILIBX)

re: fclean
	make all

.PHONY: all fclean clean re 
