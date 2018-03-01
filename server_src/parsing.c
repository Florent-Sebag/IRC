/*
** parsing.c for h in /home/sebag/Bureau/TEK2/PSU_2016_myirc/src/server/
**
** Made by Florent Sebag
** Login   <florent.sebag@epitech.eu>
**
** Started on  Wed May 31 19:29:52 2017 Florent Sebag
** Last update Sun Jun 11 14:55:12 2017 Florent Sebag
*/

#include "server.h"

t_cmd	cmd[] =
  {
    {"NICK", &nick_cmd},
    {"LIST", &list_cmd},
    {"JOIN", &join_cmd},
    {"PART", &part_cmd},
    {"NAMES", &names_cmd},
    {"PRIVMSG", &private_msg},
    {"USER", &user_cmd},
    {"QUIT", &quit_cmd},
    {NULL, NULL}
  };

t_user		*check_activity(t_socket *ctx)
{
  int		i;
  t_user	*elem;

  i = 0;
  elem = ctx->cli_list->first;
  if (FD_ISSET(ctx->sock, &(ctx->readfds)))
    return (NULL);
  while (i < ctx->cli_list->size)
    {
      if (FD_ISSET(elem->csock, &(ctx->readfds)))
	return (elem);
      elem = elem->next;
      i = i + 1;
    }
  return (NULL);
}

int		launch_cmd(t_socket *ctx, char *ret)
{
  int		i;
  char		**msg;

  msg = my_str_to_wordtab(ret, ' ');
  if (msg[0] == NULL)
    return (-1);
  i = 0;
  while (cmd[i].ptr != NULL)
    {
      if (strcmp(cmd[i].cmd, msg[0]) == 0)
	return (cmd[i].ptr(ctx, msg));
      i = i + 1;
    }
  return (send_msg_to_all(ctx, ret));
}

int		pars_and_send_msg(t_socket *ctx)
{
  char		*ret;
  int		i;
  int		j;
  char		*cmd;

  i = j = -1;
  if ((ctx->from = check_activity(ctx)) == NULL)
    return (0);
  if ((ret = rec_msg(ctx->from->csock)) == NULL)
    return (quit_cmd(ctx, NULL));
  cmd = malloc(sizeof(char) * strlen(ret) + 1);
  while (ret[++i])
    {
      cmd[++j] = ret[i];
      if (cmd[j] == '\n' && cmd[j - 1] == '\r')
	{
	  cmd[j - 1] = '\0';
	  j = -1;
	  launch_cmd(ctx, cmd);
	  reset_fd(ctx);
	}
    }
  free(cmd);
  free(ret);
  return (0);
}
