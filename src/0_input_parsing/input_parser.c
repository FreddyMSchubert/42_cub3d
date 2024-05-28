/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:57:51 by fschuber          #+#    #+#             */
/*   Updated: 2024/05/28 09:35:37 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	parse_input(char	*filepath)
{
	logger_verbose(LOGGER_INFO, "Parsing input file!");
	get_persistent_data()->input_data = NULL;
	get_map_contents(filepath);
	squarify_map();
	if (DEBUG)
		print_map(get_persistent_data()->input_data->map, ".01");
	validate();
	convert_walls();
	if (DEBUG)
		print_walls();
}
