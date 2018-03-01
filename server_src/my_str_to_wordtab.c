/*
** my_str_to_wordtab.c for h in /home/sebag/Bureau/TEK2/PSU_2016_myirc/server_src/
**
** Made by Florent Sebag
** Login   <florent.sebag@epitech.eu>
**
** Started on  Sat Jun 10 03:15:26 2017 Florent Sebag
** Last update Sun Jun 11 21:34:46 2017 Florent Sebag
*/

#include <stdlib.h>
#include "server.h"

int	my_tablen(char **tab)
{
  int	i;

  i = 0;
  while (tab[i] != NULL)
    i = i + 1;
  return (i);
}

int	send_nickname(t_user *from, t_user *user)
{
  if (user->nickname == NULL)
    send_msg(from->csock, "undefined");
  else
    send_msg(from->csock, user->nickname);
  return (0);
}

int		count_w(char *str, char sep)
{
  int		i;
  int		count;

  i = -1;
  count = 1;
  while (str[++i])
    {
      if (str[i] == sep || str[i] == '\t')
	count += 1;
    }
  return (count);
}

int		my_strlen_space(char *str, char sep)
{
  int		i;

  i = -1;
  while (str[++i])
    {
      if (str[i] == sep || str[i] == '\t')
	return (i);
    }
  return (i);
}

char		**my_str_to_wordtab(char *str, char sep)
{
  char		**tab;
  int		nb_w;
  int		count;
  int		j;

  j = -1;
  nb_w = count_w(str, sep);
  tab = malloc(sizeof(char *) * (nb_w + 1));
  while (++j != nb_w)
    {
      tab[j] = malloc(sizeof(char) * (my_strlen_space(str, sep) + 1));
      count = -1;
      while (++count < my_strlen_space(str, sep))
	tab[j][count] = str[count];
      tab[j][count] = '\0';
      str += my_strlen_space(str, sep) + 1;
    }
  tab[j] = NULL;
  return (tab);
}
