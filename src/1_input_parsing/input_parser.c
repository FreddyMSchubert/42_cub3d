/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:57:51 by fschuber          #+#    #+#             */
/*   Updated: 2024/06/06 09:19:04 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	parse_input(char	*filepath)
{
	logger_verbose(LOGGER_INFO, "Parsing input file!");
	game()->input_data = NULL;
	get_map_contents(filepath);
	squarify_map();
	if (DEBUG)
		print_map(game()->input_data->map, ".01");
	validate();
	convert_walls();
	if (DEBUG)
		printf("%f %f\n", player()->spawn_transform.pos.x, player()->spawn_transform.pos.y);
	if (LOG_WALLS)
		print_walls();
}
