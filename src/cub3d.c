/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 07:33:54 by fschuber          #+#    #+#             */
/*   Updated: 2024/06/28 18:11:19 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	check_args_validity(int argc, char **argv)
{
	if (argc != 1 && argc != 2)
	{
		logger(LOGGER_ERROR,
			"Invalid number of arguments. Usage ./cub3d <path to map>\n");
		return (false);
	}
	if (argc == 2 && strlen(argv[1]) > 4 \
				&& !str_is_equal(&(argv[1][strlen(argv[1]) - 4]), ".cub"))
	{
		logger(LOGGER_ERROR,
			"Invalid file extension. Please provide a .cub file\n");
		return (false);
	}
	return (true);
}

int	main(int argc, char **argv)
{
	if (!check_args_validity(argc, argv))
		return (EXIT_FAILURE);
	if (GREETING)
		printf("🧊 %sHello cubic world!%s 🧊\n", ANSI_COLOR_CYAN, ANSI_RESET);
	load_static_textures();
	if (argc == 1)
	{
		logger(LOGGER_STEP, "Map Generation");
		generate_map();
		parse_input("generated_map.cub");
	}
	else
	{
		parse_input(argv[1]);
	}
	logger(LOGGER_STEP, "Mlx Setup");
	setup_mlx();
	logger(LOGGER_STEP, "Gameloop");
	mlx_loop(game()->mlx);
	mlx_terminate(game()->mlx);
	return (EXIT_SUCCESS);
}
