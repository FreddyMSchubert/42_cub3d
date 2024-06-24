/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 08:12:38 by jkauker           #+#    #+#             */
/*   Updated: 2024/06/24 13:23:25 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

bool	set_entity_spawn(char dir, t_vec2 pos, t_tile_type ***map)
{
	static int	player_count = 0;

	if (++player_count > 1)
		cub_exit_error("Multiple player spawns detected!");
	if (dir == 'N')
		player()->spawn_transform.rot = (t_vec2){-1, 0};
	else if (dir == 'S')
		player()->spawn_transform.rot = (t_vec2){1, 0};
	else if (dir == 'E')
		player()->spawn_transform.rot = (t_vec2){0, 1};
	else if (dir == 'W')
		player()->spawn_transform.rot = (t_vec2){0, -1};
	else
	{
		logger(LOGGER_WARNING, "Player spawn look dir is not valid dir");
		return (false);
	}
	player()->spawn_transform.pos = pos;
	player()->transform = player()->spawn_transform;
	*(map[(int)pos.y][(int)pos.x]) = FLOOR;
	return (true);
}

bool	set_goal(t_vec2 pos, t_tile_type ***map)
{
	static int	goal_count = 0;
	mlx_texture_t	*texture;

	printf("setting the goal \n");
	if (++goal_count > MAX_GOAL_COUNT)
	{
		logger(LOGGER_WARNING, "Maximum goal count already reached!");
		return (false);
	}
	*(map[(int)pos.y][(int)pos.x]) = FLOOR;
	texture = mlx_load_png("./assets/entities/star.png");
	if (!texture)
		cub_exit_error("Failed to load goal texture!");
	create_entity(pos, (t_vec2){0, 1}, GOAL_E, texture);
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
