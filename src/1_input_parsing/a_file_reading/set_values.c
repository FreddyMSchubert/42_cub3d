/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 08:12:38 by jkauker           #+#    #+#             */
/*   Updated: 2024/06/10 10:59:55 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

int		split_len(char **split);
bool	free_split(char	**split, bool ret);
bool	regex(char *line, char *reg);

void	set_player_spawn(char dir, t_vec2 pos, t_tile_type ***map)
{
	if (dir == 'N')
		player()->spawn_transform.rot = (t_vec2){-1, 0};
	else if (dir == 'S')
		player()->spawn_transform.rot = (t_vec2){1, 0};
	else if (dir == 'E')
		player()->spawn_transform.rot = (t_vec2){0, 1};
	else if (dir == 'W')
		player()->spawn_transform.rot = (t_vec2){0, -1};
	else
		logger(LOGGER_WARNING, "Player spawn look dir is not valid dir");
	player()->spawn_transform.pos = pos;
	player()->transform.pos = player()->spawn_transform.pos;
	player()->transform.rot = player()->spawn_transform.rot;
	(*map)[(int)pos.x][(int)pos.y] = FLOOR;
}

bool	set_value(char	**value, char	*set)
{
	int		file;

	if (!value || *value)
		return (false);
	*value = ft_strdup(set);
	if (!*value)
		return (false);
	if ((*value)[ft_strlen(*value) - 1] == '\n')
		(*value)[ft_strlen(*value) - 1] = 0;
	if (strlen(*value) > 4
		&& !str_is_equal(&((*value)[strlen(*value) - 4]), ".png"))
	{
		logger(LOGGER_WARNING,
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

bool	set_color(t_color *color, char *color_val) // TODO: check if all is a number
{
	char	**cols;

	if (!color_val || !regex(color_val, "0123456789,"))
		return (false);
	cols = ft_split(color_val, ',');
	if (!cols)
		return (false);
	if (split_len(cols) < 3 || split_len(cols) > 4)
		return (free_split(cols, false));
	color->r = ft_atoi(cols[0]);
	if (!(color->r < 256 && color->r >= 0))
		return (free_split(cols, false));
	color->g = ft_atoi(cols[1]);
	if (!(color->g < 256 && color->g >= 0))
		return (free_split(cols, false));
	color->b = ft_atoi(cols[2]);
	if (!(color->b < 256 && color->b >= 0))
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