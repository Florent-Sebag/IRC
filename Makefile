##
## Makefile for h in /home/sebag/Bureau/TEK2/save/PSU_2016_philo/
##
## Made by Florent Sebag
## Login   <florent.sebag@epitech.eu>
##
## Started on  Sat Mar 18 22:19:28 2017 Florent Sebag
## Last update Sun Jun 11 21:43:57 2017 Florent Sebag
##

SRC_CLIENT		= client_src/main.c \
								client_src/client.c \
								client_src/GNL/call_gnl_to_end.c \
								client_src/GNL/get_next_line.c \
								client_src/socket.c

SRC_SERVER		= server_src/main.c \
								server_src/server.c \
								server_src/socket.c \
								server_src/linked.c \
								server_src/msg.c \
								server_src/parsing.c \
								server_src/interaction.c \
								server_src/my_str_to_wordtab.c \
								server_src/linked_channel.c \
								server_src/protocol.c \
								server_src/channel.c \
								server_src/basic.c \
								server_src/join.c

NAME_CLIENT		= client

NAME_SERVER		= server

CC		= gcc -g3

OBJS_CLIENT		= $(SRC_CLIENT:.c=.o)

OBJS_SERVER		= $(SRC_SERVER:.c=.o)

CFLAGS		= -W -Wall -Wextra -Werror -I./client_src/include -I./server_src/include

LDFLAGS		=

RM		= rm -f

all:		$(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT):	$(OBJS_CLIENT)
	$(CC) $(OBJS_CLIENT) $(LDFLAGS) -o $(NAME_CLIENT)

$(NAME_SERVER):	$(OBJS_SERVER)
	$(CC) $(OBJS_SERVER) $(LDFLAGS) -o $(NAME_SERVER)

clean:
	$(RM) $(OBJS_CLIENT)
	$(RM) $(OBJS_SERVER)

fclean: clean
	$(RM) $(NAME_CLIENT)
	$(RM) $(NAME_SERVER)

re: fclean all

.PHONY: all clean fclean re
