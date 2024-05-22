/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:39:02 by jkauker           #+#    #+#             */
/*   Updated: 2024/05/22 10:39:45 by jkauker          ###   ########.fr       */
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

	val = *value;
	if (!value || val)
		return (false);
	val = ft_strdup(set);
	if (!val)
		return (false);
	if (val[ft_strlen(val) - 1] == '\n')
		val[ft_strlen(val) - 1] = 0;
	return (true);
}

static bool	set_color(t_color *color, char *color_val)
{
	char	**cols;

	if (color)
		return (false);
	cols = ft_split(color_val, ',');
	if (!cols)
		return (false);
	if (split_len(cols) != 3) // TODO: check wether to set default vals when not all rgb is set
		return (free_split(cols, false));
	color->r = ft_atoi(cols[0]);
	if (!color->r)
		return (free_split(cols, false));
	color->g = ft_atoi(cols[1]);
	if (!color->g)
		return (free_split(cols, false));
	color->b = ft_atoi(cols[2]);
	if (!color->b)
		return (free_split(cols, false));
	return (true);
}

// TODO: add a check if in the map you dont set NO twice for example
bool	parse_textures(char	**data, t_input_data **input_data, int *i)
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
		else
			return (free_split(split, true)); // TODO: this will return once something that is not a teture is in the file which is wrong and i should fix soon
		free_split(split, NULL);
	}
	logger(LOGGER_INFO, "Parsed textures");
	return (true);
}

bool	parse_colors(char	**data, t_input_data **input_data, int *i)
{
	char	**split;

	if (!data[(*i)--])
		return (true);
	while (data[++(*i)])
	{
		split = ft_split(data[*i], ' ');
		if (!split || split_len(split) != 2) // TODO: check if we really shouldnt add all libft to gc
			return (free_split(split, false));
		if (str_is_equal(split[0], "F")
			&& !set_color(&((*input_data)->floor_color), split[1]))
			return (free_split(split, false));
		else if (str_is_equal(split[0], "C"))
			return (free_split(split, false));
		free_split(split, NULL);
	}
	logger(LOGGER_INFO, "Parsed colors");
	return (true);
}
