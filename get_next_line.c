/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:19:16 by lhopp             #+#    #+#             */
/*   Updated: 2024/03/04 16:53:34 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"
#define MAX_FD 1024
#define BUFFER_SIZE 1024

void	append_line(char **line, const char *buffer)
{
	int		i;
	int		j;
	int		old_length;
	char	*new_line;

	old_length = 0;
	i = 0;
	j = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\n')
		i++;
	if (*line != NULL)
		old_length = (int) ft_strlen(*line);
	new_line = malloc(sizeof(char) * (old_length + i + 1));
	if (new_line == NULL)
		return ;
	if (*line != NULL)
	{
		ft_strlcpy(new_line, *line, old_length + 1);
		free(*line);
	}
	while (j < i)
	{
		new_line[old_length + j] = buffer[j];
		j++;
	}
	new_line[old_length + j] = '\0';
	*line = new_line;
}

int	read_buffer(int fd, char **buffer)
{
	ssize_t	bytes_read;

	if (*buffer == NULL)
		*buffer = malloc(BUFFER_SIZE + 1);
	if (*buffer == NULL)
		return (0);
	bytes_read = read(fd, *buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free(*buffer);
		*buffer = NULL;
		return (0);
	}
	(*buffer)[bytes_read] = '\0';
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*buffer[MAX_FD];
	char		*line;
	char const	*new_line_character;
	int			read_success;

	line = NULL;
	if (fd >= 0 && fd < MAX_FD)
	{
		while (1)
		{
			if (buffer[fd] == NULL || ft_strlen(buffer[fd]) <= 0)
			{
				read_success = read_buffer(fd, &buffer[fd]);
				if (read_success == 0)
					return (line);
			}
			new_line_character = ft_strchr(buffer[fd], '\n');
			if (new_line_character != NULL)
			{
				append_line(&line, buffer[fd]);
				ft_memmove(buffer[fd], new_line_character + 1,
						   ft_strlen(new_line_character));
				return (line);
			}
			else
			{
				append_line(&line, buffer[fd]);
				free(buffer[fd]);
				buffer[fd] = NULL;
			}
		}
	}
	return (line);
}
