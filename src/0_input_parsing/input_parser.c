/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:57:51 by fschuber          #+#    #+#             */
/*   Updated: 2024/05/23 14:12:36 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	parse_input(char	*filepath)
{
	logger_verbose(LOGGER_INFO, "Parsing input file!");
	get_map_contents(filepath);
	write(STDOUT_FILENO, "a", 1);
	if (!get_persistent_data()->input_data)
		gc_exit_error();
	write(STDOUT_FILENO, "b", 1);
	validate();
	write(STDOUT_FILENO, "c", 1);
	print_walls();
}
