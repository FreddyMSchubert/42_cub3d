/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:57:51 by fschuber          #+#    #+#             */
/*   Updated: 2024/07/01 12:10:46 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static inline void	init_player_pos(void)
{
	player()->spawn_transform.rot.x = -1;
	player()->spawn_transform.rot.y = -1;
	player()->spawn_transform.pos.x = -1;
	player()->spawn_transform.pos.y = -1;
	player()->transform = player()->spawn_transform;
}

void	parse_input(char	*filepath)
{
	logger(LOGGER_STEP, "Input file Parsing");
	game()->input_data = NULL;
	init_player_pos();
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
