/*
** client.h for h in /home/sebag/Bureau/TEK2/PSU_2016_myirc/client_src/include
** 
** Made by Florent Sebag
** Login   <florent.sebag@epitech.eu>
** 
** Started on  Sun Jun 11 21:51:07 2017 Florent Sebag
** Last update Sun Jun 11 21:51:41 2017 Florent Sebag
*/

#ifndef CLIENT_H_
# define CLIENT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <signal.h>
#include "get_next_line.h"

typedef struct		s_socket
{
  int			Clisock;
  struct sockaddr_in	Clisin;
  fd_set		readfds;
}			t_socket;

int		client(int port);
int		client2(int port);
t_socket	*init_client(int port);
int		close_cli(t_socket *ctx);
int		receive_msg(t_socket *ctx);
int		send_msg(int sock, char *msg);
void		reset_readfds(t_socket *ctx);

#endif /* !CLIENT_H_ */
