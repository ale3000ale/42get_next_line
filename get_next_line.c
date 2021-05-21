/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 15:17:58 by amarcell          #+#    #+#             */
/*   Updated: 2021/01/18 15:18:01 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

long	extract(char **line, char *str_buff)
{
	long i;
	long j;
	long len;

	i = 0;
	if (!(*line = ft_strjoin(*line, str_buff)))
		return (0);
	while (str_buff[i])
		i++;
	len = i;
	i = 0;
	while ((*line)[i] != '\n' && (*line)[i])
		i++;
	(*line)[i++] = 0;
	j = 0;
	while (str_buff[i + j])
	{
		str_buff[j] = str_buff[i + j];
		j++;
	}
	while (str_buff[j])
		str_buff[j++] = 0;
	return (i);
}

int		get_control(long control, int end, t_list *buffer, t_list **base)
{
	int j;

	j = 0;
	if (!control || (!end && control < BUFFER_SIZE))
	{
		while ((buffer->content)[j])
			(buffer->content)[j++] = 0;
		ft_lstdelone(base, buffer->fd);
		return (0);
	}
	else
		return (1);
}

int		freezer(char **line)
{
	free(*line);
	*line = 0;
	return (-1);
}

int		get_line(char **line, t_list *buffer, t_list **base)
{
	long	control;
	char	*str_buff;
	int		end;

	control = BUFFER_SIZE;
	if (!(str_buff = (char*)malloc(BUFFER_SIZE + 1)))
	{
		free(*line);
		return (-1);
	}
	while (!(end = isendline(buffer->content)) && control == BUFFER_SIZE)
	{
		if (0 > (control = read(buffer->fd, str_buff, BUFFER_SIZE)))
			return (freezer(line));
		str_buff[control] = 0;
		if (!(buffer->content = ft_strjoin(buffer->content, str_buff)))
			return (freezer(line));
	}
	free(str_buff);
	if (!(extract(line, buffer->content)))
		return (-1);
	return (get_control(control, end, buffer, base));
}

int		get_next_line(int fd, char **line)
{
	static t_list	*buff_list;
	t_list			*node;
	int				res;

	if (BUFFER_SIZE < 0 && !line)
		return (-1);
	if (!(node = find_create(&buff_list, fd)))
		return (-1);
	if (!(*line = (char*)malloc(1)))
		return (-1);
	line[0][0] = 0;
	res = get_line(line, node, &buff_list);
	return (res);
}
