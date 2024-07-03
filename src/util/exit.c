/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 08:51:31 by freddy            #+#    #+#             */
/*   Updated: 2024/07/03 16:35:39 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static inline void	free_textures(void)
{
	int	i;

	i = -1;
	while(++i < MAX_TEXTURES && game()->texture_arr[i])
		mlx_delete_texture(game()->texture_arr[i]);
}

void	cub_exit(char	*message, int code)
{
	if (code != 0)
		logger(LOGGER_ERROR, message);
	else
		logger(LOGGER_INFO, message);
	free_textures();
	if (game()->mlx)
		mlx_terminate(game()->mlx);
	gc_exit(code);
}
