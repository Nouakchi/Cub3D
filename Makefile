CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
RM			=	rm -rf
MAKELIB		=	make -C
RMLIB		=	make fclean -C

INCLUDES	=	includes/cub.h \
				get_next_line/get_next_line.h \
				libft/libft.h

SRCS		=	main.c \
				parsing/othman_parsing_map.c \
				parsing/bilal_check_map_utils.c \
				parsing/bilal_check_map.c \
				parsing/bilal_init_map.c \
				get_next_line/get_next_line.c \
				get_next_line/get_next_line_utils.c \
				raycasting/bilal_gotomlx.c \

BINDIR		=	bin/
LIB			=	libft/libft.a
OBJS		=	$(SRCS:%.c=$(BINDIR)%.o)
OBJSDIR		=	$(dir $(OBJS))

MAKEDIR		=	mkdir -p

NAME		=	cub3D

MLX			=	-L/usr/local/lib/ -lmlx -framework OpenGL -framework AppKit

all:	$(NAME)

$(NAME):	$(OBJS)
	$(MAKELIB) libft
	$(CC) $(CFLAGS) $(MLX) $^ $(LIB) -o $@

$(BINDIR)%.o: %.c $(INCLUDES)
	$(MAKEDIR) $(OBJSDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(BINDIR)

fclean: clean
	$(RMLIB) libft
	$(RM) $(NAME)

re: fclean all
