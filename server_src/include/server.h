/*
** server.h for h in /home/sebag/Bureau/TEK2/PSU_2016_myirc
**
** Made by Florent Sebag
** Login   <florent.sebag@epitech.eu>
**
** Started on  Sun Jun 11 15:10:02 2017 Florent Sebag
** Last update Sun Jun 11 15:13:30 2017 Florent Sebag
*/

#ifndef SERVER_H_
# define SERVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>
#include "linked.h"

typedef struct		s_socket
{
  int			sock;
  struct sockaddr_in	sin;
  t_index		*cli_list;
  int			indic;
  fd_set		readfds;
  int			maxsock;
  t_user		*from;
  t_index_channel	*list_channel;
  int			nb_guest;
}			t_socket;

typedef struct		s_cmd
{
  char			*cmd;
  int			(*ptr)(t_socket *, char **);
}			t_cmd;

int		server(int port);
int		close_server(t_socket *ctx);
int		send_msg(int dest, char *msg);
void		accept_func(t_socket *ctx);
t_socket	*init_server(int port);
char		*rec_msg(int from);
char		**my_str_to_wordtab(char *str, char sep);
int		list_cmd(t_socket *ctx, char **msg);
int		users_cmd(t_socket *ctx, char **msg);
int		names_cmd(t_socket *ctx, char **msg);
int		private_msg(t_socket *ctx, char **msg);
int		server_cmd(t_socket *ctx, char **msg);
int		nick_cmd(t_socket *ctx, char **msg);
int		join_cmd(t_socket *ctx, char **msg);
int		part_cmd(t_socket *ctx, char **msg);
int		accept_file_cmd(t_socket *ctx, char **msg);
int		send_msg_to_all(t_socket *ctx, char *msg);
int		pars_and_send_msg(t_socket *ctx);
void		reset_fd(t_socket *ctx);
int		send_nickname(t_user *from, t_user *user);
int		rm_user_from_channel(t_socket *ctx, t_channel *channel, int indic);
int		rm_channel(t_socket *ctx, t_channel *channel);
int		my_tablen(char **tab);
int		user_cmd(t_socket *ctx, char **msg);
int		quit_cmd(t_socket *ctx, char **msg);
int		find_and_send_channel(t_socket *ctx, char **msg);
char		*concat_msg(int from, char **msg);
int		print_all_user_in_channel(t_socket *ctx, t_channel *chan, char *name_chan);
char		*concat_str(char *a, char *b);
char		*put_syntax(t_user *from, char *to, char *msg);
int		send_prefix(char *nb, char *nickname, char *room, int to);
int		rm_user_from_all_channel(t_socket *ctx);
int		send_user_in(t_socket *ctx, t_channel *chan, char *room, char *acti);
int		get_size_list_user_chan(t_channel *chan, char *name);
int		joining_step(t_socket *ctx, t_channel *chan, char **msg);
int		get_prefix(char *nb, char *nickname, char *room, char *buffer);
int		get_len_prefix(char *title, char *room);
int		del_user(t_channel *channel, t_channel_user *user);
void		concat_send_user(char *to_send, t_channel *chan, t_socket *ctx);

#endif /* !SERVER_H_ */
