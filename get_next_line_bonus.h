/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 17:35:53 by amarcell          #+#    #+#             */
/*   Updated: 2021/01/23 17:35:55 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# include <unistd.h>

typedef struct	s_list
{
	int						fd;
	char					*content;
	struct s_list			*next;
}				t_list;
int				get_next_line(int fd, char **line);
t_list			*last_and_find(t_list **lst, int fd, int find);
char			*ft_strjoin(char *s1, char const *s2);
void			ft_lstdelone(t_list **lst, int fd);
t_list			*find_create(t_list **lst, int fd);
long			isendline(char *buffer);
#endif
