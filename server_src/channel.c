/*
** channel.c for h in /home/sebag/Bureau/TEK2/PSU_2016_myirc/server_src/
**
** Made by Florent Sebag
** Login   <florent.sebag@epitech.eu>
**
** Started on  Fri Jun  9 00:15:50 2017 Florent Sebag
** Last update Sun Jun 11 19:19:08 2017 Florent Sebag
*/

#include "server.h"

int	find_size(int from, char **msg)
{
  int	res;

  res = 1;
  while (msg[from])
    {
      res = res + strlen(msg[from]) + 1;
      from += 1;
    }
  return (res);
}

char	*concat_msg(int from, char **msg)
{
  char	*res;
  int	i;
  int	j;

  if ((res = malloc(sizeof(char) * (find_size(from, msg) + 3))) == NULL)
    return (NULL);
  i = -1;
  j = -1;
  while (msg[from])
    {
      while (msg[from][++i])
	res[++j] = msg[from][i];
      res[++j] = ' ';
      i = -1;
      from += 1;
    }
  res[j] = '\0';
  return (res);
}

int			channel_msg(t_socket *ctx, t_channel *channel, char **msg)
{
  int			i;
  t_channel_user	*c_user;
  char			*to_send;

  c_user = channel->first;
  i = 0;
  to_send = concat_msg(2, msg);
  while (i < channel->size)
    {
      if (ctx->from != c_user->user)
	dprintf(c_user->user->csock, ":%s PRIVMSG %s %s\r\n",
		ctx->from->nickname, channel->room, to_send);
      c_user = c_user->next;
      i = i + 1;
    }
  free(to_send);
  return (0);
}

int		find_and_send_channel(t_socket *ctx, char **msg)
{
  int		i;
  t_channel	*channel;

  i = 0;
  channel = ctx->list_channel->first;
  while (i < ctx->list_channel->size)
    {
      if (strcmp(msg[1], channel->room) == 0)
	return (channel_msg(ctx, channel, msg));
      channel = channel->next;
      i = i + 1;
    }
  return (send_msg(ctx->from->csock, "401\r\n"));
}

int		rm_user_from_all_channel(t_socket *ctx)
{
  int		i;
  t_channel	*chan;

  i = 0;
  chan = ctx->list_channel->first;
  while (i < ctx->list_channel->size)
    {
      if (rm_user_from_channel(ctx, chan, 0) == 1)
	i -= 1;
      if (ctx->list_channel->size == 0)
	return (0);
      chan = chan->next;
      i = i + 1;
    }
  return (0);
}
