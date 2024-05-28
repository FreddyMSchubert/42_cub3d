/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 08:41:35 by freddy            #+#    #+#             */
/*   Updated: 2024/05/28 09:34:12 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	set_sky(void)
{
	t_persistent_data	*data;
	mlx_image_t			*img;
	int					i;
	int					j;

	data = get_persistent_data();
	img = mlx_new_image(data->mlx, data->mlx->width, data->mlx->height);
	if (!img || (mlx_image_to_window(data->mlx, img, 0, 0) < 0))
		cub_exit_error("mlx image creation failed");
	i = -1;
	while (++i < data->mlx->height)
	{
		j = -1;
		while (++j < data->mlx->width)
		{
			printf("%c", i < data->mlx->height / 2 ? 'c' : 'f');
			if (i < data->mlx->height / 2)
				mlx_put_pixel(img, j, i, t_color_to_int(data->input_data->ceiling_color));
			else
				mlx_put_pixel(img, j, i, t_color_to_int(data->input_data->floor_color));
		}
		printf("\n");
	}
	data->background = img;
	printf("width: %d, height_ %d\n", data->mlx->width, data->mlx->height);
}

void	setup_mlx(void)
{
	mlx_t				*mlx;
	t_persistent_data	*data;

	mlx = mlx_init(START_WIDTH, START_HEIGHT, WINDOW_NAME, true);
	if (!mlx)
		cub_exit_error("Mlx setup failed.");
	data = get_persistent_data();
	data->mlx = mlx;
	set_sky();
}
