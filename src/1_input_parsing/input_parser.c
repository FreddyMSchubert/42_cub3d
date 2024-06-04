/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:57:51 by fschuber          #+#    #+#             */
/*   Updated: 2024/06/04 09:51:43 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	parse_input(char	*filepath)
{
	logger_verbose(LOGGER_INFO, "Parsing input file!");
	get_map_contents(filepath);
	squarify_map();
	if (!data()->input_data)
		gc_exit_error();
	validate();
	convert_walls();
	if (LOG_WALLS)
		print_walls();
}
