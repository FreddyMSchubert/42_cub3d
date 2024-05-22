/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 07:33:54 by fschuber          #+#    #+#             */
/*   Updated: 2024/05/22 10:41:57 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Invalid number of arguments. Usage ./cub3d <path to map>\n");
		return (EXIT_INVALID_ARGS);
	}
	if (strlen(argv[1]) > 4
		&& !str_is_equal(&(argv[1][strlen(argv[1]) - 4]), ".cub"))
	{
		logger(LOGGER_ERROR,
			"Invalid file extension. Please provide a .cub file\n");
		return (EXIT_INVALID_FILE_EXTENSION);
	}
	if (GREETING)
		printf("🧊 %sHello cubic world!%s 🧊\n", ANSI_COLOR_CYAN, ANSI_RESET);
	get_persistent_data()->input_data = get_map_contents(argv[1]);
	return (EXIT_SUCCESS);
}
