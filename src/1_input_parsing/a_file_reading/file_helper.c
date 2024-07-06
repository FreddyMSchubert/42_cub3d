/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 08:27:08 by jkauker           #+#    #+#             */
/*   Updated: 2024/07/06 20:11:55 by freddy           ###   ########.fr       */
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
	input_data->ceiling_color = (t_color){-1, -1, -1, -1};
	input_data->floor_color = (t_color){-1, -1, -1, -1};
	input_data->ea_texture_location = NULL;
	input_data->no_texture_location = NULL;
	input_data->so_texture_location = NULL;
	input_data->we_texture_location = NULL;
	input_data->map = NULL;
}

bool	check_player(bool *invalid)
{
	if (*invalid)
		return (false);
	if (player()->spawn_trans.rot.x == -1
		&& player()->spawn_trans.rot.y == -1)
	{
		*invalid = true;
		logger(LOGGER_ERROR, "Player spawn look dir not set!");
	}
	if (player()->spawn_trans.pos.x == -1
		&& player()->spawn_trans.pos.y == -1)
	{
		*invalid = true;
		logger(LOGGER_ERROR, "Player spawn position not set!");
	}
	return (!*invalid);
}
