/*
** get_next_line.h for h in /home/sebag/Bureau/CPE_colle_semaine4/
**
** Made by Florent Sebag
** Login   <sebag_f@epitech.eu>
**
** Started on  Thu May 19 16:40:24 2016 Florent Sebag
** Last update Sun Jun 11 21:51:59 2017 Florent Sebag
*/

#ifndef GET_NEXT_LINE_H_
# define GET_NEXT_LINE_H_

#ifndef READ_SIZE
# define READ_SIZE (4096)

#endif /* !READ_SIZE */

typedef	struct	s_char_err
{
  int		err;
  char		c;
}		t_char_err;

typedef	struct	s_result
{
  t_char_err	x;
  char		*result;
  int		i;
}		t_result;

int		test_size(int);
int		verif_return(int);
int		call_gnl_to_end(int);
int		test_char(t_result, int);
int		new_other_gnl(t_result, int);
char		*get_next_line(const int);
char		*re_alloc(char *, int);
t_char_err	get_next_char(const int, int);
t_result	new_gnl(t_result, int, int, int);
char		*change_ret(char *ret);

#endif /* !GET_NEXT_LINE_H_ */
