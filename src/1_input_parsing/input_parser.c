/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:57:51 by fschuber          #+#    #+#             */
/*   Updated: 2024/06/25 18:45:57 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_entity(int id)
{
	player(id)->spawn_transform.rot = (t_vec2){-1, -1};
	player(id)->spawn_transform.pos = (t_vec2){-1, -1};
	player(id)->transform = player(id)->spawn_transform;
}

void	parse_input(char	*filepath)
{
	logger(LOGGER_STEP, "Input file Parsing");
	game()->input_data = NULL;
	init_entity(0);
	if (game()->player_count > 1)
		init_entity(1);
	get_map_contents(filepath);
	if (!game()->input_data || !game()->input_data->map)
	{
		logger(LOGGER_ERROR, "Error during input parsing!");
		gc_exit(-1);
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
