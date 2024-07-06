/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:57:51 by fschuber          #+#    #+#             */
/*   Updated: 2024/07/06 20:11:55 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static inline void	init_player_pos(void)
{
	player()->spawn_trans.rot.x = -1;
	player()->spawn_trans.rot.y = -1;
	player()->spawn_trans.pos.x = -1;
	player()->spawn_trans.pos.y = -1;
	player()->trans = player()->spawn_trans;
}

void	parse_input(char	*filepath)
{
	logger_v(LOGGER_STEP, "Input file Parsing");
	game()->input_data = NULL;
	init_player_pos();
	get_map_contents(filepath);
	if (!game()->input_data || !game()->input_data->map)
		cub_exit("Error during input parsing!", -1);
	logger_v(LOGGER_STEP, "Map Squarification");
	squarify_map();
	logger_v(LOGGER_STEP, "Map Validation");
	validate();
	if (DEBUG)
		print_map(game()->input_data->map, ".01");
	logger_v(LOGGER_STEP, "Wall Generation");
	convert_walls();
	if (LOG_WALLS)
		print_walls();
}
