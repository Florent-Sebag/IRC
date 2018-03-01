/*
** socket.c for h in /home/sebag/Bureau/TEK2/PSU_2016_myirc/client_src/
**
** Made by Florent Sebag
** Login   <florent.sebag@epitech.eu>
**
** Started on  Sun Jun 11 21:41:27 2017 Florent Sebag
** Last update Sun Jun 11 21:50:54 2017 Florent Sebag
*/

#include "client.h"

t_socket	*init_client(int port)
{
  t_socket	*res;

  res = malloc(sizeof(t_socket));
  res->Clisock = socket(AF_INET, SOCK_STREAM, 0);
  res->Clisin.sin_addr.s_addr = inet_addr("127.0.0.1");
  res->Clisin.sin_family = AF_INET;
  res->Clisin.sin_port = htons(port);
  if (connect(res->Clisock, (struct sockaddr *)&(res->Clisin),
	      sizeof(res->Clisin)) == -1)
    printf("Impossible de se connecter au server");
  else
    printf("connecter au serveur\n");
  return (res);
}

int	close_cli(t_socket *ctx)
{
  close(ctx->Clisock);
  return (0);
}

int	receive_msg(t_socket *ctx)
{
  char	buffer[4097];

  recv(ctx->Clisock, buffer, 4096, 0);
  printf("%s\n", buffer);
  return (0);
}

int	send_msg(int sock, char *msg)
{
  send(sock, msg, 4096, 0);
  return (0);
}

void	reset_readfds(t_socket *ctx)
{
  FD_ZERO(&(ctx->readfds));
  FD_SET(ctx->Clisock, &(ctx->readfds));
  FD_SET(0, &(ctx->readfds));
}
