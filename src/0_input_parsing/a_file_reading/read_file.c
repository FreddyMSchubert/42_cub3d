/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 08:38:30 by fschuber          #+#    #+#             */
/*   Updated: 2024/05/22 13:27:08 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

bool	parse_attributes(char	**data, t_input_data **input_data, int *i);

static int	get_file_length(char *filename)
{
	int		file;
	char	*line;
	int		i;

	file = open(filename, O_RDONLY);
	if (file < 0)
		return (-1);
	i = 0;
	line = get_next_line(file);
	while (line)
	{
		if (!str_is_equal(line, "\n") && *line != '#')
			i++;
		free(line);
		line = get_next_line(file);
	}
	close(file);
	return (i);
}

static char	**read_file(char *filename)
{
	char	**data;
	int		file;
	char	*line;
	int		i;

	file = open(filename, O_RDONLY);
	if (file < 0)
		return (NULL);
	line = get_next_line(file);
	data = ft_calloc(get_file_length(filename) + 1, sizeof(char *));
	i = 0;
	while (line)
	{
		if (str_is_equal(line, "\n") || (*line == '#' && i == 0))
		{
			free(line);
			line = get_next_line(file);
			continue ;
		}
		data[i++] = line;
		line = get_next_line(file);
	}
	close(file);
	return (data);
}

static	void	print_file_data(char **data)
{
	int	i;

	i = -1;
	printf("\n\n-----------------FILEDATA-----------------\n");
	while (data[++i])
		printf("FILEDATA:  (%d)\t\t%s", i, data[i]);
	printf("\n------------------------------------------\n\n");
}

static bool	parse_file_data(char **data, t_input_data **input_data)
{
	int	i;

	i = -1;
	parse_attributes(data, input_data, &i); // FIXME: data in there segv for soem reason
	// parse map here starting at i
	return (true);
}

t_input_data	*get_map_contents(char *filepath)
{
	t_input_data	*input_data;
	char			**data;

	logger(LOGGER_INFO, "Loading map...");
	data = read_file(filepath);
	if (!data)
	{
		logger(LOGGER_ERROR, "Could not read map file!");
		return (NULL);
	}
	print_file_data(data);
	input_data = gc_malloc(sizeof(t_input_data));
	if (!input_data)
	{
		logger(LOGGER_ERROR, "Could not allocate memory for input data!");
		return (NULL);
	}
	if (!parse_file_data(data, &input_data))
	{
		logger(LOGGER_ERROR, "Could not parse map data!");
		return (NULL);
	}
	logger(LOGGER_INFO, "Map loaded successfully!");
	return (input_data);
}
