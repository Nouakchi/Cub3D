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

SRCS_B		=	main.c \
				raycasting/raycasting.c \
				raycasting/cast_bonus.c \
				raycasting/final_raycasting.c \
				parsing/check_map_elements.c \
				parsing/check_elements_utils.c \
				parsing/bilal_check_map_utils.c \
				parsing/bilal_check_map.c \
				parsing/bilal_init_map.c \
				parsing/bilal_tirm_map.c \
				get_next_line/get_next_line.c \
				get_next_line/get_next_line_utils.c \

LIBC_SRCS	=	ft_atoi.c \
				ft_bzero.c \
				ft_calloc.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_itoa.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memset.c \
				ft_putchar_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_putstr_fd.c \
				ft_split.c \
				ft_strchr.c \
				ft_strdup.c \
				ft_striteri.c \
				ft_strjoin.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_strmapi.c \
				ft_strncmp.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_strtrim.c \
				ft_substr.c \
				ft_tolower.c \
				ft_toupper.c \

BIN_FOLDERS = 	bin/ bin/raycasting/ bin/parsing/ bin/get_next_line bin/libft
BINDIR		=	bin/
LIB			=	libft/libft.a mlx/libmlx.a
OBJS		=	$(SRCS:%.c=$(BINDIR)%.o)
OBJS_B		=	$(SRCS_B:%.c=$(BINDIR)%.o)
LIBC		=	libft/
MAKEDIR		=	mkdir -p
LIBC_OBJS	=	$(LIBC_SRCS:%.c=$(BINDIR)$(LIBC)%.o)

NAME		=	cub3D
NAME_B		=	cub3D_bonus

MLX			=	-Lmlx -lmlx -framework OpenGL -framework AppKit

all: $(BIN_FOLDERS) $(LIB) $(NAME)

bonus:	$(BIN_FOLDERS) $(NAME_B)


$(BIN_FOLDERS):
	$(MAKEDIR) $@

$(LIB): $(LIBC_OBJS)

$(BINDIR)$(LIBC)%.o: $(LIBC)%.c
	$(MAKELIB) libft
	$(MAKELIB) mlx

$(NAME): $(OBJS) $(LIBC_OBJS)
	$(CC) $(CFLAGS) $(MLX) $^ $(LIB) -o $@


$(NAME_B):	$(OBJS_B) $(LIBC_OBJS)
	$(CC) $(CFLAGS) $(MLX) $^ $(LIB) -o $@

$(BINDIR)%.o: %.c $(INCLUDES)
	$(CC) $(CFLAGS) -Imlx -c $< -o $@


clean:
	$(RM) $(BINDIR)

fclean: clean
	$(RMLIB) libft
	make clean -C mlx
	$(RM) $(NAME)
	$(RM) $(NAME_B)

re: fclean all
