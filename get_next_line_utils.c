/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 15:18:41 by amarcell          #+#    #+#             */
/*   Updated: 2021/01/18 15:18:43 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*last_and_find(t_list **lst, int fd, int find)
{
	if (!(*lst))
		return (0);
	while ((*lst)->next)
	{
		if (find && (*lst)->fd == fd)
			return (*lst);
		*lst = (*lst)->next;
	}
	if (find)
	{
		if ((*lst)->fd == fd)
			return (*lst);
		else
			return (0);
	}
	return (*lst);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	long		i;
	long		len[2];
	char		*str;

	i = 0;
	while (s1[i])
		i++;
	len[0] = i;
	i = 0;
	while (s2[i])
		i++;
	len[1] = i;
	if (!(str = (char*)malloc(len[0] + len[1] + 1)))
		return (0);
	i = 0;
	while (i < len[0] + len[1])
	{
		str[i] = i < len[0] ? s1[i] : s2[i - len[0]];
		i++;
	}
	str[i] = '\0';
	free(s1);
	return (str);
}

void	ft_lstdelone(t_list **lst, int fd)
{
	t_list	*current;
	t_list	*pred;

	if (lst)
	{
		current = *lst;
		while (current->fd != fd)
			current = current->next;
		pred = *lst;
		if (pred->fd == fd)
		{
			free(current->content);
			free(current);
			*lst = 0;
			return ;
		}
		while (pred->next->fd != fd)
			pred = pred->next;
		pred->next = current->next;
		free(current->content);
		free(current);
	}
}

t_list	*find_create(t_list **lst, int fd)
{
	t_list *node;
	t_list *new;

	if ((node = last_and_find(lst, fd, 1)))
		return (node);
	else
	{
		if (!(new = (t_list*)malloc(sizeof(t_list))))
			return (0);
		if (!(new->content = (char*)malloc(BUFFER_SIZE)))
		{
			free(new);
			return (0);
		}
		new->fd = fd;
		if (*lst)
		{
			(*lst) = last_and_find(lst, 0, 0);
			(*lst)->next = new;
		}
		else
			*lst = new;
		node = *lst;
	}
	return (node);
}

long	isendline(char *buffer)
{
	long i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i++] == '\n')
			return (i);
	}
	return (0);
}
