/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 07:33:54 by fschuber          #+#    #+#             */
/*   Updated: 2024/05/23 23:13:29 by freddy           ###   ########.fr       */
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
		write(STDOUT_FILENO, "did_that", 8);
		generate_map();
		write(STDOUT_FILENO, "did that", 8);
		parse_input("generated_maze.cub");
	}
	return (EXIT_SUCCESS);
}
