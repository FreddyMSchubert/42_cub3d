/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 08:51:31 by freddy            #+#    #+#             */
/*   Updated: 2024/07/03 11:25:35 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	cub_exit(char	*message, int code)
{
	mlx_close_window(game()->mlx);
	if (code != 0)
		logger(LOGGER_ERROR, message);
	else
		logger(LOGGER_INFO, message);
	gc_exit(code);
}
