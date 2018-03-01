/*
** main.c for h in /home/sebag/Bureau/TEK2/PSU_2016_myirc/server_src/
**
** Made by Florent Sebag
** Login   <florent.sebag@epitech.eu>
**
** Started on  Sun Jun 11 13:29:32 2017 Florent Sebag
** Last update Sun Jun 11 13:29:33 2017 Florent Sebag
*/

#include "server.h"

int	help(char *str)
{
  if (strcmp(str, "--help") == 0)
    {
      printf("USAGE: ./server port\n");
      return (1);
    }
  return (0);
}

int	main(int ac, char **av)
{
  if (ac == 2)
    {
      if (help(av[1]) == 0)
	server(atoi(av[1]));
    }
  return (0);
}
