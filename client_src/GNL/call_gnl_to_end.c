/*
** call_gnl_to_end.c for h in /home/sebag/Bureau/CPE_colle_semaine4/
**
** Made by Florent Sebag
** Login   <sebag_f@epitech.eu>
**
** Started on  Thu May 19 16:41:21 2016 Florent Sebag
** Last update Fri Jun  9 00:54:36 2017 Florent Sebag
*/

#include <stdlib.h>
#include <string.h>
#include "get_next_line.h"

char	*change_ret(char *ret)
{
  int	size;

  size = strlen(ret);
  ret[size] = '\r';
  ret[++size] = '\n';
  ret[++size] = '\0';
  return (ret);
}

int		verif_return(int ret)
{
  if (ret > 0)
    return (1);
  return (0);
}

int		new_other_gnl(t_result res, int indic)
{
  if (test_char(res, indic) == 1)
    return (1);
  if (res.x.err == 4)
    return (2);
  return (0);
}

t_result	new_gnl(t_result res, int i, int fd, int reset)
{
  if (i == 0)
    {
      res.i = 0;
      res.result = malloc(sizeof(char) * ((READ_SIZE) + 2));
      res.x = get_next_char(fd, reset);
    }
  else
    {
      if (res.i % READ_SIZE == 0)
        res.result = re_alloc(res.result, res.i);
      res.x = get_next_char(fd, reset);
    }
  return (res);
}

int		call_gnl_to_end(int fd)
{
  char		*tmp;

  tmp = get_next_line(fd);
  while (tmp != NULL)
    {
      tmp = get_next_line(fd);
      free(tmp);
    }
  return (0);
}
