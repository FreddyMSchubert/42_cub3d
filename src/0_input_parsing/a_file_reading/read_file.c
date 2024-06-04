/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 08:38:30 by fschuber          #+#    #+#             */
/*   Updated: 2024/06/04 10:59:24 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

bool	parse_attributes(char	**data, t_input_data **input_data, int *i);
bool	parse_map(char **data, t_input_data **input_data, int *i);
bool	regex(char *line, char *reg);
int		get_file_length(char *filename);
void	clean_struct_input(t_input_data *input_data);
bool	basic_validate(t_input_data **in);

static void	read_file_loop(char ***data, int file)
{
	char	*line;
	int		i;

	line = get_next_line(file);
	i = 0;
	while (line)
	{
		if ((*line == '#' && i == 0))
		{
			free(line);
			line = get_next_line(file);
			continue ;
		}
		(*data)[i++] = line;
		if ((*data)[i - 1][ft_strlen((*data)[i -1]) - 1] == '\n')
			(*data)[i - 1][ft_strlen((*data)[i -1]) - 1] = 0;
		line = get_next_line(file);
	}
}

static char	**read_file(char *filename)
{
	char	**data;
	int		file;
	int		length;

	file = open(filename, O_RDONLY);
	if (file < 0)
		return (NULL);
	length = get_file_length(filename);
	data = ft_calloc((length + 2), sizeof(char *));
	if (!data)
	{
		close(file);
		return (NULL);
	}
	read_file_loop(&data, file);
	close(file);
	return (data);
}

static bool	parse_file_data(char **data, t_input_data **input_data)
{
	int	i;

	i = 0;
	if (!parse_attributes(data, input_data, &i))
	{
		if (DEBUG)
			printf("(%d)\t", i + 1);
		logger(LOGGER_ERROR, "Could not parse attributes!");
		return (false);
	}
	while (!regex(data[i], MAP_TILES))
		i++;
	if (!parse_map(data, input_data, &i))
	{
		if (DEBUG)
			printf("(%d)\t", i + 1);
		logger(LOGGER_ERROR, "Could not parse playing field!");
		return (false);
	}
	logger(LOGGER_INFO, "Map load complete.");
	return (true);
}

void	get_map_contents(char *filepath)
{
	t_input_data	*input_data;
	char			**data;

	data = read_file(filepath);
	if (!data)
	{
		logger(LOGGER_ERROR, "Could not read map file!");
		gc_exit_error();
	}
	input_data = gc_malloc(sizeof(t_input_data));
	if (!input_data)
	{
		logger(LOGGER_ERROR, "Could not allocate memory for input data!");
		gc_exit_error();
	}
	clean_struct_input(input_data);
	if (!parse_file_data(data, &input_data))
	{
		logger(LOGGER_ERROR, "Could not parse map data!");
		gc_exit_error();
	}
	if (!basic_validate(&input_data))
		gc_exit_error();
	logger(LOGGER_INFO, "Map loaded successfully!");
	get_persistent_data()->input_data = input_data;
}
