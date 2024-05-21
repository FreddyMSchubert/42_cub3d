/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 08:38:30 by fschuber          #+#    #+#             */
/*   Updated: 2024/05/21 13:29:00 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

char	**read_file(char *filename)
{
	char	**data;
	int		file;
	char	*line;
	int		i;

	file = open(filename, O_RDONLY);
	if (file == -1)
		return (NULL);
	line = get_next_line(file);
	data = ft_calloc(2, sizeof(char));
	i = -1;
	while (line)
	{
		if (!str_is_equal(line, "\n"))
		{
			free(line);
			continue ;
		}
		data = realloc(data, i + 2);
		data[++i] = line;
		line = get_next_line(file);
	}
	close(file);
	return (data);
}
