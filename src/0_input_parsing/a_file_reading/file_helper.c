/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 08:27:08 by jkauker           #+#    #+#             */
/*   Updated: 2024/05/28 09:05:38 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

int	get_file_length(char *filename)
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

void	clean_struct_input(t_input_data *input_data)
{
	input_data->ceiling_color = (t_color){-1, -1, -1};
	input_data->floor_color = (t_color){-1, -1, -1};
	input_data->ea_texture_location = NULL;
	input_data->no_texture_location = NULL;
	input_data->so_texture_location = NULL;
	input_data->we_texture_location = NULL;
	input_data->map = NULL;
}

bool	basic_validate(t_input_data **in)
{
	t_input_data	*data;

	if (!in)
		return (false);
	data = *in;
	if (data->ceiling_color.r == -1 || data->ceiling_color.g == -1
		|| data->ceiling_color.b == -1)
	{
		logger(LOGGER_ERROR, "Ceiling color not set!");
		return (false);
	}
	if (data->floor_color.r == -1 || data->floor_color.g == -1
		|| data->floor_color.b == -1)
	{
		logger(LOGGER_ERROR, "Floor color not set!");
		return (false);
	}
	if (!data->ea_texture_location || !data->no_texture_location
		|| !data->so_texture_location || !data->we_texture_location)
	{
		logger(LOGGER_ERROR, "Texture location not set!");
		return (false);
	}
	return (true);
}