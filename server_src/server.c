/*
** server.c for h in /home/sebag/Bureau/TEK2/PSU_2016_myirc
**
** Made by Florent Sebag
** Login   <florent.sebag@epitech.eu>
**
** Started on  Sun Jun 11 15:13:43 2017 Florent Sebag
** Last update Sun Jun 11 21:26:50 2017 Florent Sebag
*/

#include "server.h"

int	running = 1;

void	sig_handler(int sig)
{
  if (sig == SIGINT)
    running = 0;
}

void		reset_fd(t_socket *ctx)
{
  int		i;
  t_user	*elem;

  FD_ZERO(&(ctx->readfds));
  FD_SET((ctx->sock), &(ctx->readfds));
  i = 0;
  if (ctx->cli_list->size == 0)
    return ;
  elem = ctx->cli_list->first;
  while (i < ctx->cli_list->size)
    {
      FD_SET(elem->csock, &(ctx->readfds));
      elem = elem->next;
      i = i + 1;
    }
}

int	check_new_connection(t_socket *ctx)
{
  int	ret;

  ret = select(ctx->maxsock + 1, &(ctx->readfds), NULL, NULL, NULL);
  if (ret < 0)
    return (-1);
  if (FD_ISSET(ctx->sock, &(ctx->readfds)))
    {
      accept_func(ctx);
      return (1);
    }
  return (0);
}

int		server(int port)
{
  t_socket	*ctx;
  int		indic;

  indic = 0;
  ctx = init_server(port);
  while (running == 1)
    {
      reset_fd(ctx);
      signal(SIGINT, sig_handler);
      if (check_new_connection(ctx) == 1)
	indic = 1;
      if (indic > 0)
	pars_and_send_msg(ctx);
    }
  close_server(ctx);
  return (0);
}
