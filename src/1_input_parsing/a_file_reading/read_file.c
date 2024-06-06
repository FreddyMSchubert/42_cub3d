/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 08:38:30 by fschuber          #+#    #+#             */
/*   Updated: 2024/06/06 09:54:12 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

bool	parse_attributes(char	**data, t_input_data **input_data, int *i);
bool	parse_map(char **data, t_input_data **input_data, int *i);
bool	regex(char *line, char *reg);
int		get_file_length(char *filename);
// void	clean_struct_input(t_input_data *input_data);
// bool	basic_validate(t_input_data **in);

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
	{
		logger(LOGGER_ERROR, "Could not open map file!");
		return (NULL);
	}
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
		logger(LOGGER_ERROR, "Could not parse attributes!");
		return (false);
	}
	while (!regex(data[i], MAP_TILES))
		i++;
	if (!parse_map(data, input_data, &i))
	{
		logger(LOGGER_ERROR, "Could not parse playing field!");
		return (false);
	}
	return (true);
}

static bool	basic_validate(t_input_data **in)
{
	t_input_data	*data;

	if (!*in)
		return (false);
	data = *in;
	if (data->ceiling_color.r == -1 || data->ceiling_color.g == -1
		|| data->ceiling_color.b == -1 || data->ceiling_color.a == -1)
	{
		logger(LOGGER_ERROR, "Ceiling color not set!");
		return (false);
	}
	if (data->floor_color.r == -1 || data->floor_color.g == -1
		|| data->floor_color.b == -1|| data->floor_color.a == -1)
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
	input_data->ceiling_color = (t_color){-1, -1, -1, -1};
	input_data->floor_color = (t_color){-1, -1, -1, -1};
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
	game()->input_data = input_data;
}
