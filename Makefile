CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -fsanitize=address -g
RM			=	rm -rf
MAKELIB		=	make -C
RMLIB		=	make fclean -C

INCLUDES	=	includes/cub.h \
				get_next_line/get_next_line.h \
				libft/libft.h \
				mlx/mlx.h

SRCS		=	main.c \
				raycasting/raycasting.c \
				raycasting/cast.c \
				raycasting/final_raycasting.c \
				parsing/check_map_elements.c \
				parsing/check_elements_utils.c \
				parsing/bilal_check_map_utils.c \
				parsing/bilal_check_map.c \
				parsing/bilal_init_map.c \
				parsing/bilal_tirm_map.c \
				get_next_line/get_next_line.c \
				get_next_line/get_next_line_utils.c \

BINDIR		=	bin/
LIB			=	libft/libft.a mlx/libmlx.a
OBJS		=	$(SRCS:%.c=$(BINDIR)%.o)
OBJSDIR		=	$(dir $(OBJS))

MAKEDIR		=	mkdir -p

NAME		=	cub3D

MLX			=	-Lmlx -lmlx -framework OpenGL -framework AppKit

all:	$(NAME)

$(NAME):	$(OBJS)
	$(MAKELIB) libft
	$(MAKELIB) mlx
	$(CC) $(CFLAGS) $(MLX) $^ $(LIB) -o $@

$(BINDIR)%.o: %.c $(INCLUDES)
	$(MAKEDIR) $(OBJSDIR)
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

clean:
	$(RM) $(BINDIR)

fclean: clean
	$(RMLIB) libft
	$(RM) $(NAME)

re: fclean all
