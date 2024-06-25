/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 08:41:35 by freddy            #+#    #+#             */
/*   Updated: 2024/06/25 20:07:20 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

void	set_background(int id)
{
	t_persistent_data	*data;
	mlx_image_t			*img;
	int					i;
	int					j;

	data = game();
	img = mlx_new_image(player(id)->mlx, player(id)->mlx->width, player(id)->mlx->height);
	if (!img || (mlx_image_to_window(player(id)->mlx, img, 0, 0) < 0))
		cub_exit("mlx image creation failed", -1);
	i = -1;
	while (++i < player(id)->mlx->height)
	{
		j = -1;
		while (++j < player(id)->mlx->width)
		{
			if (i < player(id)->mlx->height / 2)
				mlx_put_pixel(img, j, i,
					t_color_to_int(data->input_data->ceiling_color));
			else
				mlx_put_pixel(img, j, i,
					t_color_to_int(data->input_data->floor_color));
		}
	}
	player(id)->background = img;
}

void	setup_mlx_for_player(int id)
{
	mlx_t	*mlx;
	int		*hooks_id;

	if (id == 0)
		mlx = mlx_init(START_WIDTH, START_HEIGHT, WINDOW_NAME_PLAYER_1, true);
	else
		mlx = mlx_init(START_WIDTH, START_HEIGHT, WINDOW_NAME_PLAYER_2, true);
	if (!mlx)
		cub_exit("mlx setup failed.", -1);
	player(id)->dirty = true;
	player(id)->mlx = mlx;
	set_background(id);
	player(id)->inv.keys = 0;
	player(id)->game_scene = mlx_new_image(player(id)->mlx, player(id)->mlx->width, player(id)->mlx->height);
	if (!player(id)->game_scene
		|| (mlx_image_to_window(player(id)->mlx, player(id)->game_scene, 0, 0) < 0))
		cub_exit("mlx game image creation failed", -1);
	player(id)->hud = mlx_new_image(player(id)->mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	if (!player(id)->hud
		|| (mlx_image_to_window(player(id)->mlx, player(id)->hud,
				MINIMAP_LEFT_OFFSET, MINIMAP_TOP_OFFSET) < 0))
		cub_exit("mlx hud image creation failed", -1);
	player(id)->minimap_size = 5;
	setup_player(id);
	mlx_set_cursor_mode(player(id)->mlx, MLX_MOUSE_HIDDEN);
	hooks_id = gc_malloc(sizeof(int));
	*hooks_id = id;
	mlx_loop_hook(player(id)->mlx, loop_hook, hooks_id);
	mlx_key_hook(player(id)->mlx, key_hook, hooks_id);
	mlx_scroll_hook(player(id)->mlx, scroll_hook, hooks_id);
	mlx_resize_hook(player(id)->mlx, resize_hook, hooks_id);
}

void	setup_mlx(void)
{
	load_textures();
	setup_mlx_for_player(0);
	if (game()->player_count > 1)
		setup_mlx_for_player(1);
}
