/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:39:02 by jkauker           #+#    #+#             */
/*   Updated: 2024/05/22 13:27:52 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

bool	free_split(char	**split, bool ret)
{
	int	i;

	i = -1;
	if (!split)
		return (ret);
	while (split[++i])
		free(split[i]);
	free(split);
	return (ret);
}

int	split_len(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return (0);
	while (split[i])
		i++;
	return (i);
}

static bool	set_value(char	**value, char	*set)
{
	char	*val;
	int		file;

	val = *value;
	if (!value || val)
		return (false);
	val = ft_strdup(set);
	if (!val)
		return (false);
	if (val[ft_strlen(val) - 1] == '\n')
		val[ft_strlen(val) - 1] = 0;
	printf("adding value: %s\n", val);
	if (strlen(val) > 4
		&& !str_is_equal(&(val[strlen(val) - 4]), ".xpm"))
	{
		logger(LOGGER_WARNING,
			"Invalid texture file extension. Please provide a .xpm file\n");
		return (false);
	}
	file = open(val, O_RDONLY);
	if (file < 0)
	{
		logger(LOGGER_WARNING, "Failed to open texture file!");
		return (false);
	}
	close(file);
	return (true);
}

static bool	set_color(t_color *color, char *color_val)
{
	char	**cols;

	if (!color_val) // TODO: set default color vals to all -1
		return (false);
	cols = ft_split(color_val, ',');
	if (!cols)
		return (false);
	if (split_len(cols) != 3) // TODO: check wether to set default vals when not all rgb is set
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
	free_split(cols, NULL);
	printf("color set: %s\n", color_val);
	return (true);
}

// TODO: add a check if in the map you dont set NO twice for example
bool	parse_attributes(char	**data, t_input_data **input_data, int *i)
{
	char	**split;

	if (!data[(*i)--])
		return (true);
	while (data[++(*i)])
	{
		split = ft_split(data[*i], ' ');
		if (!split || split_len(split) != 2) // TODO: check if we really shouldnt add all libft to gc
			return (free_split(split, false));
		if (str_is_equal(split[0], "NO")
			&& !set_value(&(*input_data)->no_texture_location, split[1]))
			return (free_split(split, false));
		else if (str_is_equal(split[0], "SO")
			&& !set_value(&(*input_data)->so_texture_location, split[1]))
			return (free_split(split, false));
		else if (str_is_equal(split[0], "WE")
			&& !set_value(&(*input_data)->we_texture_location, split[1]))
			return (free_split(split, false));
		else if (str_is_equal(split[0], "EA")
			&& !set_value(&(*input_data)->ea_texture_location, split[1]))
			return (free_split(split, false));
		else if (str_is_equal(split[0], "F")
			&& !set_color(&((*input_data)->floor_color), split[1]))
			return (free_split(split, false));
		else if (str_is_equal(split[0], "C")
			&& !set_color(&((*input_data)->ceiling_color), split[1]))
			return (free_split(split, false));
		free_split(split, NULL);
	}
	return (true);
}
