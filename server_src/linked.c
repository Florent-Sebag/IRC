/*
** linked.c for h in /home/sebag/Bureau/dante/recup/
**
** Made by Florent Sebag
** Login   <sebag_f@epitech.eu>
**
** Started on  Fri May 20 14:02:19 2016 Florent Sebag
** Last update Sun Jun 11 15:12:52 2017 Florent Sebag
*/

#include "server.h"

int		rm_channel(t_socket *ctx, t_channel *channel)
{
  if (ctx->list_channel->size == 1)
    {
      ctx->list_channel->size = 0;
      free(channel->room);
      free(channel);
      return (0);
    }
  ctx->list_channel->size = ctx->list_channel->size - 1;
  if (ctx->list_channel->size == 1)
    {
      ctx->list_channel->first = channel->prev;
      ctx->list_channel->last = channel->prev;
    }
  if (channel == ctx->list_channel->first)
    ctx->list_channel->first = channel->next;
  if (channel == ctx->list_channel->last)
    ctx->list_channel->first = channel->prev;
  channel->next->prev = channel->prev;
  channel->prev->next = channel->next;
  free(channel->room);
  return (1);
}

int		create_list(t_index *list, int clisock, struct sockaddr_in clisin)
{
  t_user	*elem;

  if ((elem = malloc(sizeof(t_user))) == NULL)
    return (-1);
  list->size = 1;
  elem->csock = clisock;
  elem->csin = clisin;
  elem->is_set_nick = 0;
  elem->is_usered = 0;
  elem->nickname = NULL;
  elem->prev = elem;
  elem->next = elem;
  list->first = elem;
  list->last = elem;
  return (0);
}

int		add_case_end(t_index *list, int clisock, struct sockaddr_in clisin)
{
  t_user	*new_elem;

  if ((new_elem = malloc(sizeof(t_user))) == NULL)
    return (-1);
  new_elem->csock = clisock;
  new_elem->csin = clisin;
  new_elem->is_set_nick = 0;
  new_elem->is_usered = 0;
  new_elem->next = list->first;
  new_elem->prev = list->last;
  list->first->prev = new_elem;
  list->last->next = new_elem;
  list->last = new_elem;
  list->size += 1;
  return (0);
}

void		free_linked(t_index *list)
{
  t_user	*elem;
  t_user	*tmp;
  int		i;

  elem = list->first;
  tmp = elem->next;
  i = 0;
  while (i < list->size - 2)
    {
      free(elem);
      elem = tmp;
      tmp = tmp->next;
      i = i + 1;
    }
  free(elem);
  free(tmp);
}

int		add_user(t_index *list, int clisock, struct sockaddr_in clisin)
{
  if (list->size == 0)
    return (create_list(list, clisock, clisin));
  return (add_case_end(list, clisock, clisin));
}
