/*
** protocol.c for h in /home/sebag/Bureau/TEK2/PSU_2016_myirc/server_src/
**
** Made by Florent Sebag
** Login   <florent.sebag@epitech.eu>
**
** Started on  Wed Jun  7 22:11:26 2017 Florent Sebag
** Last update Sun Jun 11 21:36:05 2017 Florent Sebag
*/

#include "server.h"

int			send_user_in(t_socket *ctx, t_channel *chan, char *room, char *acti)
{
  int			i;
  t_channel_user	*cuser;

  if (chan == NULL)
    return (dprintf(ctx->from->csock, ":%s%s%s\r\n",
		    ctx->from->nickname, acti, room));
  i = 0;
  cuser = chan->first;
  while (i < chan->size)
    {
      dprintf(cuser->user->csock, ":%s%s%s\r\n",
	      ctx->from->nickname, acti, room);
      cuser = cuser->next;
      i = i + 1;
    }
  return (0);
}

int			print_all_user_in_channel(t_socket *ctx, t_channel *chan, char *name_chan)
{
  int			i;
  t_channel_user	*cuser;

  dprintf(ctx->from->csock, "353 %s %s :", ctx->from->nickname, name_chan);
  if (chan == NULL)
    {
      dprintf(ctx->from->csock, "%s\r\n", ctx->from->nickname);
      dprintf(ctx->from->csock, "366\r\n");
      return (0);
    }
  cuser = chan->first;
  i = 0;
  while (i < chan->size)
    {
      dprintf(ctx->from->csock, "%s", cuser->user->nickname);
      if (i + 1 < chan->size)
	dprintf(ctx->from->csock, " ");
      cuser = cuser->next;
      i = i + 1;
    }
  dprintf(ctx->from->csock, "\r\n366\r\n");
  return (0);
}

int		user_cmd(t_socket *ctx, char **msg)
{
  t_user	*user;
  int		i;

  if (my_tablen(msg) < 5)
    return (send_msg(ctx->from->csock, "461\r\n"));
  i = 0;
  user = ctx->cli_list->first;
  while (i < ctx->cli_list->size)
    {
      if (ctx->from->csock == user->csock && user->is_usered == 1)
	return (send_msg(ctx->from->csock, "462\r\n"));
      i = i + 1;
      user = user->next;
    }
  ctx->from->is_usered = 1;
  return (send_msg(ctx->from->csock, "001\r\n"));
}

int	quit_cmd(t_socket *ctx, char **msg)
{
  (void)msg;
  rm_user_from_all_channel(ctx);
  send_msg(ctx->from->csock, "221\r\n");
  close(ctx->from->csock);
  ctx->cli_list->size -= 1;
  if (ctx->cli_list->size == 1)
    {
      ctx->cli_list->first = ctx->from->next;
      ctx->cli_list->last = ctx->from->next;
    }
  if (ctx->cli_list->first == ctx->from)
    ctx->cli_list->first = ctx->from->next;
  if (ctx->cli_list->last == ctx->from)
    ctx->cli_list->last = ctx->from->prev;
  ctx->from->next->prev = ctx->from->prev;
  ctx->from->prev->next = ctx->from->next;
  return (0);
}
