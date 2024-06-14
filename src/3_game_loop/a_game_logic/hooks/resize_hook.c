/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:45:16 by jkauker           #+#    #+#             */
/*   Updated: 2024/06/14 13:57:42 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

void	set_background(void);

void	resize_hook(int32_t width, int32_t height, void *param)
{
	(void)param;
	game()->mlx->width = width;
	game()->mlx->height = height;
	mlx_delete_image(game()->mlx, game()->background);
	set_background();
}
