/*
** linked.h for h in /home/sebag/Bureau/TEK2/PSU_2016_myirc
**
** Made by Florent Sebag
** Login   <florent.sebag@epitech.eu>
**
** Started on  Sun Jun 11 15:10:10 2017 Florent Sebag
** Last update Sun Jun 11 15:19:33 2017 Florent Sebag
*/

#ifndef LINKED_H_
# define LINKED_H_

typedef struct		s_user
{
  struct s_user		*prev;
  char			*nickname;
  int			csock;
  struct sockaddr_in	csin;
  int			is_usered;
  int			is_set_nick;
  struct s_user		*next;
}			t_user;

typedef struct		s_index
{
  t_user		*first;
  t_user		*last;
  int			size;
}			t_index;

typedef struct		s_channel_user
{
  struct s_channel_user	*prev;
  t_user		*user;
  struct s_channel_user	*next;
}			t_channel_user;

typedef struct		s_channel
{
  struct s_channel	*prev;
  char			*room;
  t_channel_user	*first;
  t_channel_user	*last;
  int			size;
  struct s_channel	*next;
}			t_channel;

typedef struct		s_index_channel
{
  t_channel		*first;
  t_channel		*last;
  int			size;
}			t_index_channel;

int	add_user(t_index *list, int clisock, struct sockaddr_in clisin);
int	create_channel(t_index_channel *list, char *room, t_user *user);
int	add_elem_user_in(t_channel *channel, t_user *user);

#endif /* !LINKED_H_ */
