/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:57:51 by fschuber          #+#    #+#             */
/*   Updated: 2024/06/07 09:54:08 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	parse_input(char	*filepath)
{
	logger(LOGGER_STEP, "Input file Parsing");
	game()->input_data = NULL;
	get_map_contents(filepath);
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