SERVER		=	server
CLIENT		=	client
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra
LIBFT		=	-L./libft -lft
LIB			=	libft
INCLUDES	=	-I./includes

SRCS_DIR	=	./srcs/
SRCS_SERVER	=	server.c
SRCS_CLIENT	=	client.c
SRCS_SERVER_C	= $(addprefix ${SRCS_DIR}, $(SRCS_SERVER))
SRCS_CLIENT_C	= $(addprefix ${SRCS_DIR}, $(SRCS_CLIENT))

OBJS_DIR	=	./objs/
OBJS_SERVER	=	${patsubst %.c, %.o, $(addprefix ${OBJS_DIR}, $(SRCS_SERVER))}
OBJS_CLIENT	=	${patsubst %.c, %.o, $(addprefix ${OBJS_DIR}, $(SRCS_CLIENT))}

all : $(SERVER) $(CLIENT)
	@echo "program server and client was done."

$(SERVER) : libft/libft.a $(OBJS_SERVER) $(OBJS_DIR) $(SRCS_SERVER_C)
	@$(CC) $(CFLAGS) -o $@ $(OBJS_SERVER) $(LIBFT) $(INCLUDES)
	@echo "program server was done."

$(CLIENT) : $(LIB) $(OBJS_CLIENT) $(OBJS_DIR) $(SRCS_CLIENT_C)
	@$(CC) $(CFLAGS) -o $@ $(OBJS_CLIENT) $(LIBFT) $(INCLUDES)
	@echo "program client was done."

libft/libft.a :
	@$(MAKE) -C ./libft

$(addprefix $(OBJS_DIR), %.o) : $(addprefix $(SRCS_DIR), %.c) $(OBJS_DIR)
	@$(CC) -c $(CFLAGS) $< -o $@ $(INCLUDES)

$(OBJS_DIR) :
	@mkdir -p $@

clean :
	@rm -rf $(OBJS_DIR)
	@$(MAKE) clean -C ./libft
	@echo "command 'clean' was done."

fclean : clean
	@$(MAKE) fclean -C ./libft
	@rm -rf $(SERVER) $(CLIENT)
	@echo "command 'fclean' was done."

re : fclean all
	@echo "command 're' was done."

.PHONY: all clean fclean re
