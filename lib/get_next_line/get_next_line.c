/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:17:34 by jkauker           #+#    #+#             */
/*   Updated: 2024/05/22 09:28:34 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * Combines the existing buffer and a new buffer into a single string.
 */
char	*buff_to_line(char *buffer, char *buf)
{
	char	*temp;

	temp = ft_strjoin2(buffer, buf);
	free(buffer);
	return (temp);
}

/**
 * move pointer to next line and keep everything that
 * was alredy in the buffer from new line in memory
 */
char	*next(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	line = ft_calloc2((ft_strlen2(buffer) - i + 1), sizeof(char));
	if (!line)
	{
		free(buffer);
		return (NULL);
	}
	i++;
	j = 0;
	while (buffer[i])
		line[j++] = buffer[i++];
	free(buffer);
	return (line);
}

/**
	* Extracts the content of the buffer until
	the first newline character ('\n') encountered.
 */
char	*get_line_mine(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc2(i + 2, sizeof(char));
	if (!line)
		return (NULL);
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

/**
 * read out file and put into buffer
 */
char	*fill_buffer(int fd, char *res)
{
	char	*buffer;
	size_t	byte_read;

	if (!res)
		res = ft_calloc2(1, 1);
	buffer = ft_calloc2(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	byte_read = read(fd, buffer, BUFFER_SIZE);
	while (byte_read > 0)
	{
		buffer[byte_read] = '\0';
		res = buff_to_line(res, buffer);
		if (ft_strchr2(buffer, '\n') || byte_read == 0)
			break ;
		byte_read = (size_t)read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	if (byte_read <= 0 && res[0] == '\0')
	{
		free(res);
		return (NULL);
	}
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = fill_buffer(fd, buffer);
	if (!buffer)
		return (NULL);
	line = get_line_mine(buffer);
	buffer = next(buffer);
	return (line);
}
