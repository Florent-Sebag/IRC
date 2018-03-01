/*
** main.c for h in /home/sebag/Bureau/TEK2/PSU_2016_myirc/client_src
** 
** Made by Florent Sebag
** Login   <florent.sebag@epitech.eu>
** 
** Started on  Sun Jun 11 21:37:35 2017 Florent Sebag
** Last update Sun Jun 11 21:50:24 2017 Florent Sebag
*/

#include "client.h"

int	main(int ac, char **av)
{
  (void)ac;
  if (ac > 1)
    client(atoi(av[1]));
  return (0);
}
