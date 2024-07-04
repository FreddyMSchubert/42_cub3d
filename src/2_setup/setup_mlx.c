/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 08:41:35 by freddy            #+#    #+#             */
/*   Updated: 2024/07/04 15:25:34 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	resize_hook(int32_t width, int32_t height, void *param);

// lets use purple if a texture cannot be loaded so we dont have to crash
void	load_textures(void)
{
	game()->ea_texture = mlx_load_png(game()->input_data->ea_texture_location);
	if (!game()->ea_texture)
		cub_exit("Failed to load east texture.", -1);
	game()->no_texture = mlx_load_png(game()->input_data->no_texture_location);
	if (!game()->no_texture)
		cub_exit("Failed to load north texture.", -1);
	game()->so_texture = mlx_load_png(game()->input_data->so_texture_location);
	if (!game()->so_texture)
		cub_exit("Failed to load south texture.", -1);
	game()->we_texture = mlx_load_png(game()->input_data->we_texture_location);
	if (!game()->we_texture)
		cub_exit("Failed to load west texture.", -1);
	if (game()->no_texture->height != game()->no_texture->width)
		cub_exit("Textures must be square.", -1);
	if (game()->so_texture->height != game()->so_texture->width)
		cub_exit("Textures must be square.", -1);
	if (game()->we_texture->height != game()->we_texture->width)
		cub_exit("Textures must be square.", -1);
	if (game()->ea_texture->height != game()->ea_texture->width)
		cub_exit("Textures must be square.", -1);
}

void	set_background(void)
{
	t_persistent_data	*data;
	mlx_image_t			*img;
	int					i;
	int					j;

	data = game();
	img = mlx_new_image(data->mlx, data->mlx->width, data->mlx->height);
	if (!img || (mlx_image_to_window(data->mlx, img, 0, 0) < 0))
		cub_exit("mlx image creation failed", -1);
	i = -1;
	while (++i < data->mlx->height)
	{
		j = -1;
		while (++j < data->mlx->width)
		{
			if (i < data->mlx->height / 2)
				mlx_put_pixel(img, j, i,
					t_color_to_int(data->input_data->ceiling_color));
			else
				mlx_put_pixel(img, j, i,
					t_color_to_int(data->input_data->floor_color));
		}
	}
	data->background = img;
}

void	setup_mlx(void)
{
	game()->mlx = mlx_init(START_WIDTH, START_HEIGHT, WINDOW_NAME, false);
	if (!game()->mlx)
		cub_exit("mlx setup failed.", -1);
	set_background();
	load_textures();
	game()->game_scene = mlx_new_image(game()->mlx, game()->mlx->width,
		game()->mlx->height);
	if (!game()->game_scene
		|| (mlx_image_to_window(game()->mlx, game()->game_scene, 0, 0) < 0))
		cub_exit("mlx game image creation failed", -1);
	game()->hud = mlx_new_image(game()->mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	if (!game()->hud
		|| (mlx_image_to_window(game()->mlx, game()->hud,
				MINIMAP_LEFT_OFFSET, MINIMAP_TOP_OFFSET) < 0))
		cub_exit("mlx hud image creation failed", -1);
	game()->minimap_size = 5;
	game()->game_over = false;
	game()->screen_effect = NULL;
	setup_player();
	update_mouse_visibility();
	mlx_loop_hook(game()->mlx, loop_hook, NULL);
	mlx_key_hook(game()->mlx, key_hook, NULL);
	mlx_scroll_hook(game()->mlx, scroll_hook, NULL);
	mlx_resize_hook(game()->mlx, resize_hook, NULL);
	mlx_mouse_hook(game()->mlx, mouse_click_hook, NULL);
}
