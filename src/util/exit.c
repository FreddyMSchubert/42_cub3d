/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 08:51:31 by freddy            #+#    #+#             */
/*   Updated: 2024/07/03 17:18:39 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static inline void	free_textures(void)
{
	int	i;

	i = -1;
	while(++i < MAX_TEXTURES && game()->texture_arr[i])
		mlx_delete_texture(game()->texture_arr[i]);
	if (game()->background)
		mlx_delete_image(game()->mlx, game()->background);
	if (game()->hud)
		mlx_delete_image(game()->mlx, game()->hud);
	if (game()->screen_effect)
		mlx_delete_image(game()->mlx, game()->screen_effect);
	if (game()->game_scene)
		mlx_delete_image(game()->mlx, game()->game_scene);
	if (game()->no_texture)
		mlx_delete_texture(game()->no_texture);
	if (game()->ea_texture)
		mlx_delete_texture(game()->ea_texture);
	if (game()->so_texture)
		mlx_delete_texture(game()->so_texture);
	if (game()->we_texture)
		mlx_delete_texture(game()->we_texture);
}

void	cub_exit(char	*message, int code)
{
	if (code != 0)
		logger(LOGGER_ERROR, message);
	else
		logger(LOGGER_INFO, message);
	if (game()->texture_arr[0])
		free_textures();
	if (game()->mlx)
		mlx_terminate(game()->mlx);
	gc_exit(code);
}
