/*
** linked_channel.c for h in /home/sebag/Bureau/TEK2/PSU_2016_myirc/src/server/
**
** Made by Florent Sebag
** Login   <florent.sebag@epitech.eu>
**
** Started on  Thu Jun  1 14:27:37 2017 Florent Sebag
** Last update Sun Jun 11 14:51:16 2017 Florent Sebag
*/

#include "server.h"

int			add_elem_user_in(t_channel *channel, t_user *user)
{
  t_channel_user	*elem;

  if ((elem = malloc(sizeof(t_channel_user))) == NULL)
    return (-1);
  elem->user = user;
  if (channel->size == 0)
    {
      elem->prev = elem;
      elem->next = elem;
      channel->first = elem;
      channel->last = elem;
    }
  else
    {
      elem->next = channel->first;
      elem->prev = channel->last;
      channel->first->prev = elem;
      channel->last->next = elem;
      channel->last = elem;
    }
  channel->size += 1;
  return (0);
}

int			rm_user_from_channel(t_socket *ctx, t_channel *channel, int indic)
{
  t_channel_user	*user;
  int			i;

  if (channel->size == 1)
    return (rm_channel(ctx, channel));
  i = -1;
  user = channel->first;
  while (++i < channel->size && user->user != ctx->from)
    user = user->next;
  if (i == channel->size && indic == 1)
    return (send_msg(ctx->from->csock, "442\r\n"));
  if (i == channel->size && indic == 0)
    return (0);
  del_user(channel, user);
  free(user);
  return (0);
}

int		create_list_channel(t_index_channel *list, char *room, t_user *user)
{
  t_channel	*elem;

  if ((elem = malloc(sizeof(t_channel))) == NULL)
    return (-1);
  elem->size = 0;
  add_elem_user_in(elem, user);
  elem->room = room;
  list->size = 1;
  elem->prev = elem;
  elem->next = elem;
  list->first = elem;
  list->last = elem;
  return (0);
}

int		add_case_end_channel(t_index_channel *list, char *room, t_user *user)
{
  t_channel	*new_elem;

  if ((new_elem = malloc(sizeof(t_channel))) == NULL)
    return (-1);
  new_elem->size = 0;
  add_elem_user_in(new_elem, user);
  new_elem->room = room;
  new_elem->next = list->first;
  new_elem->prev = list->last;
  list->first->prev = new_elem;
  list->last->next = new_elem;
  list->last = new_elem;
  list->size += 1;
  return (0);
}

int	create_channel(t_index_channel *list, char *room, t_user *user)
{
  if (list->size == 0)
    return (create_list_channel(list, room, user));
  return (add_case_end_channel(list, room, user));
}
