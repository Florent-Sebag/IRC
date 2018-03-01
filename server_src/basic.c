/*
** basic.c for h in /home/sebag/Bureau/TEK2/PSU_2016_myirc/server_src/
**
** Made by Florent Sebag
** Login   <florent.sebag@epitech.eu>
**
** Started on  Fri Jun  9 16:14:19 2017 Florent Sebag
** Last update Sun Jun 11 21:29:48 2017 Florent Sebag
*/

#include "server.h"

char	*concat_str(char *a, char *b)
{
  int	i;
  int	j;
  char	*res;

  i = 0;
  j = 0;
  res = malloc(sizeof(char) * (strlen(a) + strlen(b) + 3));
  while (a[i])
    {
      res[i] = a[i];
      i = i + 1;
    }
  while (b[j])
    {
      res[i] = b[j];
      i = i + 1;
      j = j + 1;
    }
  res[i] = '\0';
  return (res);
}

int	del_user(t_channel *channel, t_channel_user *user)
{
  channel->size = channel->size - 1;
  if (channel->size == 1)
    {
      channel->first = user->prev;
      channel->last = user->prev;
    }
  if (user == channel->first)
    channel->first = user->next;
  if (user == channel->last)
    channel->first = user->prev;
  user->next->prev = user->prev;
  user->prev->next = user->next;
  return (0);
}
