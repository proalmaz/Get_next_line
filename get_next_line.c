/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vping <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 21:11:21 by vping             #+#    #+#             */
/*   Updated: 2020/11/30 19:53:22 by vping            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*check_ost(char **line, char **ost)
{
	char		*point;

	point = NULL;
	if (*ost)
	{
		if ((point = ft_strchr(*ost, '\n')))
		{
			*point = '\0';
			*line = *ost;
			point++;
			*ost = ft_strdup(point);
		}
		else
		{
			*line = *ost;
			*ost = NULL;
		}
	}
	else
		*line = ft_strdup("");
	return (point);
}

int		for_read(int fd, char **line, char **ost)
{
	char		*buf;
	char		*point;
	int			i;

	point = NULL;
	if (!(buf = (char *)malloc(BUFFER_SIZE + 1)))
		return (-1);
	while (!point && (i = read(fd, buf, BUFFER_SIZE)))
	{
		buf[i] = '\0';
		if (i == -1)
			return (-1);
		if ((point = ft_strchr(buf, '\n')))
		{
			*point = '\0';
			point++;
			if (!(*ost = ft_strdup(point)))
				return (-1);
		}
		if (!(*line = ft_strjoin(*line, buf)))
			return (-1);
	}
	free(buf);
	return (i);
}

int		get_next_line(int fd, char **line)
{
	static char	*ost;
	int			rd;

	rd = 0;
	if (BUFFER_SIZE <= 0 || read(fd, NULL, 0) == -1 || !line)
		return (-1);
	if (!(check_ost(line, &ost)))
	{
		rd = for_read(fd, line, &ost);
	}
	if (rd == -1)
		return (-1);
	if (!rd && !ost)
		return (0);
	return (1);
}
