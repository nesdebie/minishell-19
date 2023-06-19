/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:52:36 by nesdebie          #+#    #+#             */
/*   Updated: 2023/05/26 16:15:12 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_free(char *s1, char *s2)
{
	if (s1)
	{
		free(s1);
		s1 = NULL;
	}
	if (s2)
	{
		free(s2);
		s2 = NULL;
	}
	return (0);
}

static char	*ft_new_buffer(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	if (buffer == NULL)
		return (0);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (0);
	}
	j = ft_strlen(buffer) - i;
	line = ft_calloc((j + 1), sizeof(char));
	if (!line)
		return (ft_free(buffer, 0));
	i++;
	j = 0;
	while (buffer[i])
		line[j++] = buffer[i++];
	free(buffer);
	return (line);
}

static char	*ft_get_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (0);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (ft_strchr(buffer, '\n'))
		i++;
	line = ft_calloc(i + 1, sizeof(char));
	if (!line)
		return (ft_free(buffer, 0));
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

static char	*read_file(int fd, char *res)
{
	char	*tmp;
	int		is_read;

	if (!res)
		res = ft_calloc(1, 1);
	if (!res)
		return (0);
	tmp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!tmp)
		return (ft_free(res, 0));
	is_read = 1;
	while (is_read > 0)
	{
		is_read = read(fd, tmp, BUFFER_SIZE);
		if (is_read == -1)
			return (ft_free(res, tmp));
		tmp[is_read] = 0;
		res = ft_strjoingnl(res, tmp);
		if (!res)
			return (ft_free(tmp, 0));
		if (ft_strchr(tmp, '\n'))
			break ;
	}
	free(tmp);
	return (res);
}

int	get_next_line(int fd, char **line)
{
	static char	*buffer[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= OPEN_MAX)
		return (0);
	buffer[fd] = read_file(fd, buffer[fd]);
	if (!buffer[fd])
		return (0);
	*line = ft_get_line(buffer[fd]);
	if (!*line)
		return (0);
	buffer[fd] = ft_new_buffer(buffer[fd]);
	return (1);
}
