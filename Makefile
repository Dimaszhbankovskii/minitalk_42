SERVER			=	server
CLIENT			=	client
CC				=	gcc
CFLAGS			=	-Wall -Werror -Wextra
LIB				=	-L./libft -lft
LIBFT			=	./libft/libft.a
INCLUDES		=	-I./includes
HEADER			=	./includes/minitalk.h

SRCS_DIR		=	./srcs/
SRCS_SERVER		=	server.c
SRCS_CLIENT		=	client.c
SRCS_SERVER_C	=	$(addprefix ${SRCS_DIR}, $(SRCS_SERVER))
SRCS_CLIENT_C	=	$(addprefix ${SRCS_DIR}, $(SRCS_CLIENT))

OBJS_SERVER		=	$(SRCS_SERVER:.c=.o)
OBJS_CLIENT		=	$(SRCS_CLIENT:.c=.o)

all : $(SERVER) $(CLIENT)

$(SERVER) : $(HEADER) $(LIBFT) $(OBJS_SERVER) $(SRCS_SERVER_C) Makefile
	@$(CC) $(CFLAGS) -o $@ $(OBJS_SERVER) $(LIBFT) $(INCLUDES)
	@echo "program server was done."

$(CLIENT) : $(HEADER) $(LIBFT) $(OBJS_CLIENT) $(SRCS_CLIENT_C) Makefile
	@$(CC) $(CFLAGS) -o $@ $(OBJS_CLIENT) $(LIBFT) $(INCLUDES)
	@echo "program client was done."

$(LIBFT) : ./libft/Makefile ./libft/libft.h ./libft/*.c
	@$(MAKE) -C ./libft

%.o : $(addprefix $(SRCS_DIR), %.c)
	@$(CC) -c $(CFLAGS) $< -o $@ $(INCLUDES)

clean :
	@rm -rf $(OBJS_SERVER) $(OBJS_CLIENT)
	@$(MAKE) clean -C ./libft
	@echo "command 'clean' was done."

fclean : clean
	@$(MAKE) fclean -C ./libft
	@rm -rf $(SERVER) $(CLIENT)
	@echo "command 'fclean' was done."

re : fclean all
	@echo "command 're' was done."

.PHONY: all clean fclean re
