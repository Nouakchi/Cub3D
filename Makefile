CC	=	cc
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -rf

INCLUDES	=	includes/cub.h
SRCS		=	main.c parsing/othman_parsing_map.c
BINDIR		=	bin/
OBJS		=	$(SRCS:%.c=$(BINDIR)%.o)
OBJSDIR		=	$(dir $(OBJS))

MAKEDIR	=	mkdir -p

NAME		=	cub3D

all:	$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(BINDIR)%.o: %.c $(INCLUDES)
	$(MAKEDIR) $(OBJSDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:	
	$(RM) $(BINDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all