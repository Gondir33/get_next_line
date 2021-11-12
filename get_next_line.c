/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 19:00:16 by marvin            #+#    #+#             */
/*   Updated: 2021/10/28 19:00:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_subline(char **rem, char **line)
{
	size_t	len;
	char	*new_rem;

	len = 0;
	new_rem = NULL;
	while ((*rem)[len] != '\n' && (*rem)[len])
		++len;
	if ((*rem)[len] == '\n')
	{
		++len;
		*line = ft_substr(*rem, 0, len);
		new_rem = ft_strdup(*rem + len);
	}
	else
		*line = ft_strdup(*rem);
	free(*rem);
	return (new_rem);
}

size_t	ft_get_line(char **rem, char **line, char **buff, int fd)
{
	size_t	rb;

	rb = 1;
	while (rb && !ft_strchr(*rem, '\n'))
	{
		rb = read(fd, *buff, BUFFER_SIZE);
		(*buff)[rb] = 0;
		*rem = ft_strjoin(*rem, *buff);
	}
	free(*buff);
	*rem = ft_subline(rem, line);
	if (!**line)
	{
		free(*line);
		*line = NULL;
	}
	return (rb);
}

char	*get_next_line(int fd)
{
	char		*buff;
	char		*line;
	static char	*rem = NULL;
	size_t		rb;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	buff = (char *)malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	if (read(fd, buff, 0) < 0)
	{
		free(buff);
		return (NULL);
	}
	if (!rem)
		rem = ft_strdup("");
	rb = ft_get_line(&rem, &line, &buff, fd);
	if (!rb && !line)
		return (NULL);
	return (line);
}
