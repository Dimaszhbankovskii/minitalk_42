SERVER	=	server
CLIENT	=	client
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra
#LIBFT	=	-L./libft -lft
#
#SRCS_SERVER	=	server.c
#SRCS_CLIENT	=	client.c

#OBJS_SERVER	=	$(SRCS_SERVER:.c=.o)
#OBJS_CLIENT	=	$(SRCS_CLIENT:.c=.o)

all :
	make -C ./libft
	$(CC) $(CFLAGS) server.c ./libft/libft.a -o $(SERVER)
	$(CC) $(CFLAGS) client.c ./libft/libft.a -o $(CLIENT)

#%.o : %.c
#	$(CC) -c $(CFLAGS) $< -o $@ -I.

clean :
	make clean -C ./libft
	rm -rf client.o server.o

fclean : clean
	make fclean -C ./libft
	rm -rf $(SERVER) $(CLIENT)

re : fclean all

.PHONY: all clean fclean re