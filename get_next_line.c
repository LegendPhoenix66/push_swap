/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:00:28 by lhopp            #+#    #+#             */
/*   Updated: 2024/06/20 13:46:19 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*extract_line(char *line)
{
	char	*next_line;
	size_t	i;
	size_t	line_buffer;

	if (!line)
		return (NULL);
	i = 0;
	line_buffer = ft_strlen(line);
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\n')
		i++;
	next_line = ft_substr(line, i, line_buffer);
	if (!next_line || next_line[0] == '\0')
	{
		if (next_line[0] == '\0')
			free(next_line);
		next_line = NULL;
	}
	free(line);
	return (next_line);
}

static char	*get_line(char *line)
{
	size_t	line_len;
	size_t	i;
	char	*cpy;

	if (!line)
		return (NULL);
	line_len = 0;
	while (line[line_len] != '\n' && line[line_len] != '\0')
		line_len++;
	if (line[line_len] == '\n')
		line_len++;
	cpy = malloc(line_len + 1);
	if (!cpy)
		return (NULL);
	i = 0;
	while (i < line_len)
	{
		cpy[i] = line[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

static char	*read_buffer(int fd, char *store, char *buffer)
{
	ssize_t	byte_num;
	char	*tmp;

	byte_num = 1;
	while (!ft_strchr(store, '\n') && byte_num != 0)
	{
		byte_num = read(fd, buffer, 1000);
		if (byte_num < 0)
		{
			free(store);
			return (NULL);
		}
		else if (byte_num == 0)
			return (store);
		buffer[byte_num] = '\0';
		tmp = store;
		store = ft_strjoin(tmp, buffer);
		free(tmp);
	}
	return (store);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*one_line;
	char		*buffer;
	char		*store;

	if (fd < 0)
		return (NULL);
	buffer = malloc(1001);
	if (!buffer)
		return (NULL);
	if (!line)
		store = ft_strdup("");
	else
		store = line;
	line = read_buffer(fd, store, buffer);
	free(buffer);
	if (!line || line[0] == '\0')
	{
		if (line[0] == '\0')
			free(line);
		line = NULL;
	}
	one_line = get_line(line);
	line = extract_line(line);
	return (one_line);
}
