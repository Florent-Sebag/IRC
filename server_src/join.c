/*
** join.c for h in /home/sebag/Bureau/TEK2/PSU_2016_myirc/server_src/
**
** Made by Florent Sebag
** Login   <florent.sebag@epitech.eu>
**
** Started on  Sun Jun 11 13:29:38 2017 Florent Sebag
** Last update Sun Jun 11 21:28:28 2017 Florent Sebag
*/

#include "server.h"

int	joining_step(t_socket *ctx, t_channel *chan, char **msg)
{
  if (chan != NULL)
    add_elem_user_in(chan, ctx->from);
  else
    create_channel(ctx->list_channel, msg[1], ctx->from);
  send_user_in(ctx, chan, msg[1], " JOIN ");
  dprintf(ctx->from->csock, "331 TOPIC %s: No topic is set\r\n", msg[1]);
  return (print_all_user_in_channel(ctx, chan, msg[1]));
}

int		join_cmd(t_socket *ctx, char **msg)
{
  t_channel	*chan;
  int		i;

  i = -1;
  if (msg[1] == NULL)
    return (send_msg(ctx->from->csock, "461\r\n"));
  chan = ctx->list_channel->first;
  while (++i < ctx->list_channel->size)
    {
      if (strcmp(chan->room, msg[1]) == 0)
	  return (joining_step(ctx, chan, msg));
      chan = chan->next;
    }
  return (joining_step(ctx, NULL, msg));
}
