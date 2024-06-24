/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:57:51 by fschuber          #+#    #+#             */
/*   Updated: 2024/06/24 10:48:13 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_entity()
{
	player()->spawn_transform.rot = (t_vec2){-1, -1};
	player()->spawn_transform.pos = (t_vec2){-1, -1};
	player()->transform = player()->spawn_transform;
}

void	parse_input(char	*filepath)
{
	logger(LOGGER_STEP, "Input file Parsing");
	game()->input_data = NULL;
	init_entity();
	get_map_contents(filepath);
	if (!game()->input_data || !game()->input_data->map)
	{
		logger(LOGGER_ERROR, "Error during input parsing!");
		gc_exit_error();
	}
	print_map(game()->input_data->map, ".01");
	logger(LOGGER_STEP, "Map Squarification");
	squarify_map();
	logger(LOGGER_STEP, "Map Validation");
	validate();
	if (DEBUG)
		print_map(game()->input_data->map, ".01");
	logger(LOGGER_STEP, "Wall Generation");
	convert_walls();
	if (LOG_WALLS)
		print_walls();
}
