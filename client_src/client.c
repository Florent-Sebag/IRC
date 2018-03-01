/*
** client.c for h in /home/sebag/Bureau/TEK2/PSU_2016_myirc/client_src
**
** Made by Florent Sebag
** Login   <florent.sebag@epitech.eu>
**
** Started on  Sun Jun 11 21:38:20 2017 Florent Sebag
** Last update Sun Jun 11 21:50:04 2017 Florent Sebag
*/

#include "client.h"

int	running = 1;

void	sig_handler(int sig)
{
  if (sig == SIGINT)
    running = 0;
}

int		client(int port)
{
  t_socket	*ctx;
  char		*ret;

  ctx = init_client(port);
  while (running == 1)
    {
      reset_readfds(ctx);
      signal(SIGINT, sig_handler);
      select(ctx->Clisock + 1, &(ctx->readfds), NULL, NULL, NULL);
      if (FD_ISSET(0, &(ctx->readfds)))
	{
	  ret = get_next_line(0);
	  send_msg(ctx->Clisock, ret);
	}
      if (FD_ISSET(ctx->Clisock, &(ctx->readfds)))
	receive_msg(ctx);
    }
  close_cli(ctx);
  return (0);
}
