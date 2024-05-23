/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 08:38:30 by fschuber          #+#    #+#             */
/*   Updated: 2024/05/23 14:00:39 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

bool	parse_attributes(char	**data, t_input_data **input_data, int *i);
bool	parse_map(char **data, t_input_data **input_data, int *i);
bool	regex(char *line, char *reg);

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
	int		length;

	file = open(filename, O_RDONLY);
	if (file < 0)
		return (NULL);
	length = get_file_length(filename);
	line = get_next_line(file);
	data = ft_calloc((length + 2), sizeof(char *));
	i = 0;
	while (line)
	{
		if ((*line == '#' && i == 0))
		{
			free(line);
			line = get_next_line(file);
			continue ;
		}
		data[i++] = line;
		if (data[i - 1][ft_strlen(data[i -1]) - 1] == '\n')
			data[i - 1][ft_strlen(data[i -1]) - 1] = 0;
		line = get_next_line(file);
	}
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

static bool	basic_validate(t_input_data **in)
{
	t_input_data	*data;

	if (!in)
		return (false);
	data = *in;
	if (data->ceiling_color.r == -1 || data->ceiling_color.g == -1 || \
										data->ceiling_color.b == -1)
	{
		logger(LOGGER_ERROR, "Ceiling color not set!");
		return (false);
	}
	if (data->floor_color.r == -1 || data->floor_color.g == -1 || \
										data->floor_color.b == -1)
	{
		logger(LOGGER_ERROR, "Floor color not set!");
		return (false);
	}
	if (!data->ea_texture_location || !data->no_texture_location || \
					!data->so_texture_location || !data->we_texture_location)
	{
		logger(LOGGER_ERROR, "Texture location not set!");
		return (false);
	}
	return (true);
}

static void	clean_struct_input(t_input_data *input_data)
{
	input_data->ceiling_color = (t_color){-1, -1, -1};
	input_data->floor_color = (t_color){-1, -1, -1};
	input_data->ea_texture_location = NULL;
	input_data->no_texture_location = NULL;
	input_data->so_texture_location = NULL;
	input_data->we_texture_location = NULL;
	input_data->map = NULL;
}

void	get_map_contents(char *filepath)
{
	t_input_data	*input_data;
	char			**data;

	data = read_file(filepath);
	if (!data)
	{
		logger(LOGGER_ERROR, "Could not read map file!");
		return ;
	}
	input_data = gc_malloc(sizeof(t_input_data));
	if (!input_data)
	{
		logger(LOGGER_ERROR, "Could not allocate memory for input data!");
		return ;
	}
	clean_struct_input(input_data);
	if (!parse_file_data(data, &input_data))
	{
		logger(LOGGER_ERROR, "Could not parse map data!");
		return ;
	}
	if (!basic_validate(&input_data)) // TODO: free stuff here
		return ;
	print_map(input_data->map, " 01");
	logger(LOGGER_INFO, "Map loaded successfully!");
	get_persistent_data()->input_data = input_data;
}
