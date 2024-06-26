/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 08:41:35 by freddy            #+#    #+#             */
/*   Updated: 2024/06/26 15:26:46 by jkauker          ###   ########.fr       */
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
	mlx_t				*mlx;
	t_persistent_data	*data;

	mlx = mlx_init(START_WIDTH, START_HEIGHT, WINDOW_NAME, true);
	if (!mlx)
		cub_exit("mlx setup failed.", -1);
	data = game();
	data->dirty = true;
	data->mlx = mlx;
	set_background();
	load_textures();
	data->game_scene = mlx_new_image(data->mlx, data->mlx->width,
			data->mlx->height);
	if (!data->game_scene
		|| (mlx_image_to_window(data->mlx, data->game_scene, 0, 0) < 0))
		cub_exit("mlx game image creation failed", -1);
	data->hud = mlx_new_image(data->mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	if (!data->hud
		|| (mlx_image_to_window(data->mlx, data->hud,
				MINIMAP_LEFT_OFFSET, MINIMAP_TOP_OFFSET) < 0))
		cub_exit("mlx hud image creation failed", -1);
	data->minimap_size = 5;
	setup_player();
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	mlx_loop_hook(data->mlx, loop_hook, NULL);
	mlx_key_hook(data->mlx, key_hook, NULL);
	mlx_scroll_hook(data->mlx, scroll_hook, NULL);
	mlx_cursor_hook(data->mlx, cursor_hook, NULL);
	mlx_resize_hook(data->mlx, resize_hook, NULL);
	mlx_mouse_hook(data->mlx, mouse_click_hook, NULL);
}
