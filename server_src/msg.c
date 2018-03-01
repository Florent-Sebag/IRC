/*
** msg.c for h in /home/sebag/Bureau/TEK2/PSU_2016_myirc/src/server/
**
** Made by Florent Sebag
** Login   <florent.sebag@epitech.eu>
**
** Started on  Wed May 31 20:14:09 2017 Florent Sebag
** Last update Sun Jun 11 21:34:16 2017 Florent Sebag
*/

#include "server.h"

int		list_cmd(t_socket *ctx, char **msg)
{
  t_channel	*elem;
  int		i;

  i = 0;
  send_msg(ctx->from->csock, "321\r\n");
  elem = ctx->list_channel->first;
  if (msg[1] == NULL)
    {
      while (i < ctx->list_channel->size)
	{
	  dprintf(ctx->from->csock, "322 %s\r\n", elem->room);
	  elem = elem->next;
	  i = i + 1;
	}
    }
  send_msg(ctx->from->csock, "323\r\n");
  return (0);
}

int		users_cmd(t_socket *ctx, char **msg)
{
  t_user	*elem;
  int		i;

  (void)msg;
  i = 0;
  elem = ctx->cli_list->first;
  while (i < ctx->cli_list->size)
    {
      send_nickname(ctx->from, elem);
      elem = elem->next;
      i = i + 1;
    }
  return (0);
}

int		names_cmd(t_socket *ctx, char **msg)
{
  t_channel	*chan;
  int		i;

  i = -1;
  if (msg[1] == NULL)
    return (users_cmd(ctx, msg));
  chan = ctx->list_channel->first;
  while (++i < ctx->list_channel->size)
    {
      if (strcmp(msg[1], chan->room) == 0)
	return (print_all_user_in_channel(ctx, chan, chan->room));
      chan = chan->next;
    }
  return (send_msg(ctx->from->csock, "401\r\n"));
}

int		private_msg(t_socket *ctx, char **msg)
{
  t_user	*user;
  int		i;
  char		*to_send;

  i = -1;
  if (my_tablen(msg) < 3)
    return (send_msg(ctx->from->csock, "412\r\n"));
  user = ctx->cli_list->first;
  while (++i < ctx->cli_list->size)
    {
      if (strcmp(user->nickname, msg[1]) == 0)
	break;
      user = user->next;
    }
  if (i == ctx->cli_list->size)
    return (find_and_send_channel(ctx, msg));
  to_send = concat_msg(2, msg);
  dprintf(user->csock, ":%s PRIVMSG %s %s\r\n",
	  ctx->from->nickname, user->nickname, to_send);
  free(to_send);
  return (0);
}

int		send_msg_to_all(t_socket *ctx, char *msg)
{
  int		i;
  t_user	*elem;

  i = 0;
  elem = ctx->cli_list->first;
  while (i < ctx->cli_list->size)
    {
      if (elem != ctx->from)
	send_msg(elem->csock, msg);
      elem = elem->next;
      i = i + 1;
    }
  return (0);
}
