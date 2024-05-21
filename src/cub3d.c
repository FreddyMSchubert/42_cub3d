/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 07:33:54 by fschuber          #+#    #+#             */
/*   Updated: 2024/05/21 13:30:12 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Invalid number of arguments. Usage ./cub3d <path to map>\n");
		return (1);
	}
	if (strlen(argv[1]) > 3
		&& !strncmp(&(argv[1][strlen(argv[1]) - 4]), ".cub", 4))
	if (GREETING)
		printf("🧊 %sHello cubic world!%s 🧊\n", ANSI_COLOR_CYAN, ANSI_RESET);
	
	char **data = read_file(argv[1]);
	for (int i = 0; data[i]; i++)
		printf("%s\n", data[i]);
}
