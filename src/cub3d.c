/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 07:33:54 by fschuber          #+#    #+#             */
/*   Updated: 2024/05/21 14:29:59 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	if (GREETING)
		printf("🧊 %sHello cubic world!%s 🧊\n", ANSI_COLOR_CYAN, ANSI_RESET);
	(void)argc;
	(void)argv;
}
