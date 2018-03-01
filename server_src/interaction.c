/*
** interaction.c for h in /home/sebag/Bureau/TEK2/PSU_2016_myirc/src/server/
**
** Made by Florent Sebag
** Login   <florent.sebag@epitech.eu>
**
** Started on  Wed May 31 20:14:24 2017 Florent Sebag
** Last update Sun Jun 11 21:28:45 2017 Florent Sebag
*/

#include "server.h"

int	server_cmd(t_socket *ctx, char **msg)
{
  (void)ctx;
  (void)msg;
  return (0);
}

void		send_msg_nickname(t_socket *ctx, char *new_nickname)
{
  int		i;
  t_user	*user;

  i = 0;
  user = ctx->cli_list->first;
  while (i < ctx->cli_list->size)
    {
      dprintf(user->csock, "%s NICK %s\r\n", ctx->from->nickname, new_nickname);
      i = i + 1;
      user = user->next;
    }
}

int		nick_cmd(t_socket *ctx, char **msg)
{
  int		i;
  t_user	*user;

  i = 0;
  user = ctx->cli_list->first;
  if (msg[1] == NULL)
    return (send_msg(ctx->from->csock, "431\r\n"));
  while (i < ctx->cli_list->size)
    {
      if (strcmp(user->nickname, msg[1]) == 0)
	return (send_msg(ctx->from->csock, "433\r\n"));
      user = user->next;
      i = i + 1;
    }
  if (ctx->from->is_set_nick != 0)
    send_msg_nickname(ctx, msg[1]);
  ctx->from->nickname = msg[1];
  ctx->from->is_set_nick = 1;
  return (0);
}

int		part_cmd(t_socket *ctx, char **msg)
{
  int		i;
  t_channel	*channel;

  i = 0;
  channel = ctx->list_channel->first;
  if (msg[1] == NULL)
    return (send_msg(ctx->from->csock, "461\r\n"));
  while (i < ctx->list_channel->size)
    {
      if (strcmp(msg[1], channel->room) == 0)
	{
	  send_user_in(ctx, channel, channel->room, " PART ");
	  return (rm_user_from_channel(ctx, channel, 1));
	}
      channel = channel->next;
      i = i + 1;
    }
  return (send_msg(ctx->from->csock, "403\r\n"));
}

int	accept_file_cmd(t_socket *ctx, char **msg)
{
  (void)ctx;
  (void)msg;
  return (0);
}
