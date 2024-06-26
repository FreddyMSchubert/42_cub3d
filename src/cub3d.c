/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 07:33:54 by fschuber          #+#    #+#             */
/*   Updated: 2024/07/01 21:57:59 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static inline void	printf_element(int element)
{
	printf("Very well, harnesser of the ");
	if (element == TYPE_WATER)
		printf("neptunian");
	else if (element == TYPE_EARTH)
		printf("terrene");
	else if (element == TYPE_FIRE)
		printf("igneous");
	else if (element == TYPE_AIR)
		printf("aerian");
	printf(" arts. May you find the star ⭐️ you seek.\x1b[0m\n");
}

static inline void	set_player_element(void)
{
	char	input;
	int		bytes_read;

	write(STDOUT_FILENO, "\x1b[35mGreetings, Adventurer! 🧌", 33);
	write(STDOUT_FILENO, " Choose your element 💧🔥🪨💨", 38);
	write(STDOUT_FILENO, " [WFEA] [ENTER for random pick]: ", 35);
	bytes_read = read(STDIN_FILENO, &input, 1);
	if (bytes_read < 0)
		input = '\n';
	if (input == 'W')
		player()->element = TYPE_WATER;
	else if (input == 'F')
		player()->element = TYPE_FIRE;
	else if (input == 'E')
		player()->element = TYPE_EARTH;
	else if (input == 'A')
		player()->element = TYPE_AIR;
	else if (input == '\n')
		player()->element = random_int(0, 3);
	printf_element(player()->element);
}

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
	init_random_seed();
	if (argc == 1)
	{
		logger(LOGGER_STEP, "Map Generation");
		generate_map();
		parse_input("generated_map.cub");
	}
	else
		parse_input(argv[1]);
	logger(LOGGER_STEP, "Player Element Input");
	set_player_element();
	logger(LOGGER_STEP, "Mlx Setup");
	setup_mlx();
	logger(LOGGER_STEP, "Gameloop");
	mlx_loop(game()->mlx);
	mlx_terminate(game()->mlx);
	return (EXIT_SUCCESS);
}
