/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:57:51 by fschuber          #+#    #+#             */
<<<<<<< HEAD:src/0_input_parsing/input_parser.c
/*   Updated: 2024/05/28 09:35:37 by jkauker          ###   ########.fr       */
=======
/*   Updated: 2024/05/29 09:31:40 by freddy           ###   ########.fr       */
>>>>>>> master:src/1_input_parsing/input_parser.c
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	parse_input(char	*filepath)
{
	logger_verbose(LOGGER_INFO, "Parsing input file!");
	get_persistent_data()->input_data = NULL;
	get_map_contents(filepath);
<<<<<<< HEAD:src/0_input_parsing/input_parser.c
	squarify_map();
	if (DEBUG)
		print_map(get_persistent_data()->input_data->map, ".01");
	validate();
	convert_walls();
	if (DEBUG)
=======
	printf("%f %f\n", get_player()->spawn_transform.pos.x, get_player()->spawn_transform.pos.y);
	squarify_map();
	if (!get_persistent_data()->input_data)
		gc_exit_error();
	validate();
	convert_walls();
	if (LOG_WALLS)
>>>>>>> master:src/1_input_parsing/input_parser.c
		print_walls();
}
