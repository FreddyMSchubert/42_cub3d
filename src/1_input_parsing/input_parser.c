/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 09:35:37 by jkauker           #+#    #+#             */
/*   Updated: 2024/06/05 14:18:17 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <stdio.h>
#include <unistd.h>

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
