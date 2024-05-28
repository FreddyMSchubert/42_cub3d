/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:57:51 by fschuber          #+#    #+#             */
/*   Updated: 2024/05/28 08:53:18 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	parse_input(char	*filepath)
{
	logger_verbose(LOGGER_INFO, "Parsing input file!");
	get_persistent_data()->input_data = NULL;
	get_map_contents(filepath);
	print_map(get_persistent_data()->input_data->map, " 01");
	squarify_map();
	print_map(get_persistent_data()->input_data->map, ".01");
	// write(STDOUT_FILENO, "a", 1);
	// if (!get_persistent_data()->input_data)
	// 	gc_exit_error();
	// write(STDOUT_FILENO, "b", 1);
	// validate();
	// write(STDOUT_FILENO, "c", 1);
	// convert_walls();
	// write(STDOUT_FILENO, "d", 1);
	// print_walls();
}
