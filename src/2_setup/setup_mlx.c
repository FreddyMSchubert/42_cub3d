/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 08:41:35 by freddy            #+#    #+#             */
/*   Updated: 2024/06/24 17:49:43 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	resize_hook(int32_t width, int32_t height, void *param);

// lets use purple if a texture cannot be loaded so we dont have to crash
void	load_textures(void)
{
	game()->ea_texture = mlx_load_png(game()->input_data->ea_texture_location);
	if (!game()->ea_texture)
		cub_exit_error("Failed to load east texture.");
	game()->no_texture = mlx_load_png(game()->input_data->no_texture_location);
	if (!game()->no_texture)
		cub_exit_error("Failed to load north texture.");
	game()->so_texture = mlx_load_png(game()->input_data->so_texture_location);
	if (!game()->so_texture)
		cub_exit_error("Failed to load south texture.");
	game()->we_texture = mlx_load_png(game()->input_data->we_texture_location);
	if (!game()->we_texture)
		cub_exit_error("Failed to load west texture.");
	if (game()->no_texture->height != game()->no_texture->width)
		cub_exit_error("Textures must be square.");
	if (game()->so_texture->height != game()->so_texture->width)
		cub_exit_error("Textures must be square.");
	if (game()->we_texture->height != game()->we_texture->width)
		cub_exit_error("Textures must be square.");
	if (game()->ea_texture->height != game()->ea_texture->width)
		cub_exit_error("Textures must be square.");
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
		cub_exit_error("mlx image creation failed");
	i = -1;
	while (++i < data->mlx->height)
	{
		j = -1;
		while (++j < data->mlx->width)
		{
			if (i < data->mlx->height / 2)
				mlx_put_pixel(img, j, i, t_color_to_int(data->input_data->ceiling_color));
			else
				mlx_put_pixel(img, j, i, t_color_to_int(data->input_data->floor_color));
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
		cub_exit_error("mlx setup failed.");
	data = game();
	data->dirty = true;
	data->mlx = mlx;
	set_background();
	load_textures();
	data->game_scene = mlx_new_image(data->mlx, data->mlx->width,
			data->mlx->height);
	if (!data->game_scene
		|| (mlx_image_to_window(data->mlx, data->game_scene, 0, 0) < 0))
		cub_exit_error("mlx game image creation failed");
	setup_player();

	/*
	data->visible_walls = malloc(sizeof(bool *) * data->mlx->width);
	if (!data->visible_walls)
		cub_exit_error("malloc failed");
	for (int i = 0; i < data->mlx->width; i++)
	{
		data->visible_walls[i] = malloc(sizeof(bool) * data->mlx->height);
		if (!data->visible_walls[i])
			cub_exit_error("malloc failed");
		for (int j = 0; j < data->mlx->height; j++)
			data->visible_walls[i][j] = false;
	}
	*/

	
	mlx_loop_hook(data->mlx, loop_hook, NULL);
	mlx_key_hook(data->mlx, key_hook, NULL);
	mlx_resize_hook(data->mlx, resize_hook, NULL);
}
