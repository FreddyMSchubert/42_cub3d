/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 08:12:38 by jkauker           #+#    #+#             */
/*   Updated: 2024/07/07 16:27:12 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

bool	set_entity_spawn(char dir, t_vec2 pos, t_tile_type ***map)
{
	static int	player_count = 0;

	if (++player_count > 1)
		cub_exit("Multiple player spawns detected!", -1);
	player()->spawn_trans.rot.x = 0;
	player()->spawn_trans.rot.y = 0;
	if (dir == 'N')
		player()->spawn_trans.rot.y = -1;
	else if (dir == 'S')
		player()->spawn_trans.rot.y = 1;
	else if (dir == 'E')
		player()->spawn_trans.rot.x = 1;
	else if (dir == 'W')
		player()->spawn_trans.rot.x = -1;
	else
	{
		logger_v(LOGGER_ERROR, "Player spawn look dir is not valid dir");
		return (false);
	}
	player()->spawn_trans.pos = pos;
	player()->trans = player()->spawn_trans;
	*(map[(int)pos.y][(int)pos.x]) = FLOOR;
	return (true);
}

bool	set_value(char	**value, char	*set)
{
	int		file;

	if (!value || *value)
		return (false);
	*value = ft_strdup(set);
	if (!*value)
		return (false);
	gc_append_element(*value);
	if ((*value)[ft_strlen(*value) - 1] == '\n')
		(*value)[ft_strlen(*value) - 1] = 0;
	if (strlen(*value) > 4
		&& !str_is_equal(&((*value)[strlen(*value) - 4]), ".png"))
	{
		logger(LOGGER_ERROR,
			"Invalid texture file extension. Please provide a .png file!");
		return (false);
	}
	file = open(*value, O_RDONLY);
	if (file < 0)
	{
		logger(LOGGER_WARNING, "Failed to open texture file!");
		return (false);
	}
	close(file);
	return (true);
}

bool	set_color(t_color *color, char *color_val)
{
	char	**cols;

	if (!color_val || !regex(color_val, "0123456789,"))
		return (false);
	cols = ft_split(color_val, ',');
	if (!cols || split_len(cols) < 3 || split_len(cols) > 4)
		return (free_split(cols, false));
	color->r = ft_atoi(cols[0]);
	color->g = ft_atoi(cols[1]);
	color->b = ft_atoi(cols[2]);
	if (!(color->r < 256 && color->r >= 0) || \
		!(color->g < 256 && color->g >= 0) || \
		!(color->b < 256 && color->b >= 0))
		return (free_split(cols, false));
	if (split_len(cols) == 4)
	{
		color->a = ft_atoi(cols[3]);
		if (!(color->a < 256 && color->a >= 0))
			return (free_split(cols, false));
	}
	else
		color->a = 255;
	free_split(cols, NULL);
	return (true);
}

bool	set_fog(char *fog_val, t_input_data **input_data)
{
	char	**fog_vals;
	int		intensity;
	t_color	col;

	if (!fog_val || !regex(fog_val, "0123456789,"))
		return (false);
	fog_vals = ft_split(fog_val, ',');
	if (!fog_vals || split_len(fog_vals) < 4 || split_len(fog_vals) > 4)
		return (free_split(fog_vals, false));
	intensity = ft_atoi(fog_vals[0]);
	col.r = ft_atoi(fog_vals[1]);
	col.g = ft_atoi(fog_vals[2]);
	col.b = ft_atoi(fog_vals[3]);
	col.a = 255;
	if (!(col.r < 256 && col.r >= 0) || \
		!(col.g < 256 && col.g >= 0) || \
		!(col.b < 256 && col.b >= 0) || \
		!(intensity >= 0))
		return (free_split(fog_vals, false));
	free_split(fog_vals, NULL);
	(*input_data)->fog_color = col;
	(*input_data)->fog_enabled = true;
	(*input_data)->fog_intensity = intensity;
	return (true);
}

bool	set_minimap(char *minimap_val, t_input_data **input_data)
{
	if (!minimap_val || !regex(minimap_val, "OFN"))
		return (false);
	if (ft_strlen(minimap_val) < 2)
		return (false);
	if (minimap_val[1] == 'F')
		(*input_data)->show_minimap = false;
	else
		(*input_data)->show_minimap = true;
	return (true);
}
