/*
** socket.c for h in /home/sebag/Bureau/TEK2/PSU_2016_myirc/server_src
**
** Made by Florent Sebag
** Login   <florent.sebag@epitech.eu>
**
** Started on  Sun Jun 11 14:58:02 2017 Florent Sebag
** Last update Sun Jun 11 21:36:59 2017 Florent Sebag
*/

#include "server.h"

t_socket	*init_server(int port)
{
  t_socket	*res;

  res = malloc(sizeof(t_socket));
  res->sock = socket(AF_INET, SOCK_STREAM, 0);
  res->maxsock = res->sock;
  res->sin.sin_addr.s_addr = htonl(INADDR_ANY);
  res->sin.sin_family = AF_INET;
  res->sin.sin_port = htons(port);
  res->cli_list = malloc(sizeof(t_index));
  res->cli_list->size = 0;
  bind(res->sock, (struct sockaddr *)&(res->sin), sizeof(res->sin));
  listen(res->sock, 5);
  res->list_channel = malloc(sizeof(t_index_channel));
  res->list_channel->size = 0;
  res->nb_guest = 0;
  return (res);
}

void			accept_func(t_socket *ctx)
{
  unsigned int		size;
  int			csock;
  struct sockaddr_in	csin_;

  size = sizeof(struct sockaddr_in);
  csock = accept(ctx->sock, (struct sockaddr *)&csin_, &size);
  ctx->maxsock = csock;
  add_user(ctx->cli_list, csock, csin_);
  ctx->cli_list->last->nickname = malloc(22);
  snprintf(ctx->cli_list->last->nickname, 21, "GUEST%d", ctx->nb_guest);
  ctx->nb_guest += 1;
  send_msg(csock, "001\r\n");
  reset_fd(ctx);
}

int	send_msg(int dest, char *msg)
{
  write(dest, msg, strlen(msg));
  return (0);
}

char	*rec_msg(int from)
{
  char	*buffer;
  int	size;

  if ((buffer = malloc(sizeof(char) * 4097)) == NULL)
    return (NULL);
  if ((size = read(from, buffer, 4096)) == 0)
    {
      free(buffer);
      return (NULL);
    }
  buffer[size] = '\0';
  return (buffer);
}

int	close_server(t_socket *ctx)
{
  shutdown(ctx->sock, 2);
  close(ctx->sock);
  return (0);
}
