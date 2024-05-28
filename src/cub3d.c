/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 07:33:54 by fschuber          #+#    #+#             */
/*   Updated: 2024/05/28 10:16:47 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	if (argc > 2)
	{
		printf("Invalid number of arguments. Usage ./cub3d <path to map>\n");
		return (EXIT_INVALID_ARGS);
	}
	if (argv[1] && strlen(argv[1]) > 4
		&& !str_is_equal(&(argv[1][strlen(argv[1]) - 4]), ".cub"))
	{
		logger(LOGGER_ERROR,
			"Invalid file extension. Please provide a .cub file\n");
		return (EXIT_INVALID_FILE_EXTENSION);
	}
	if (GREETING)
		printf("🧊 %sHello cubic world!%s 🧊\n", ANSI_COLOR_CYAN, ANSI_RESET);
	if (argv[1])
		parse_input(argv[1]);
	else
	{
		generate_map();
		parse_input("generated_maze.cub");
	}
	setup_mlx();
	mlx_loop(get_persistent_data()->mlx);
	return (EXIT_SUCCESS);
}
