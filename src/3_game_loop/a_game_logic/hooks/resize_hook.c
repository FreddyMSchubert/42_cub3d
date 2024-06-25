/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:45:16 by jkauker           #+#    #+#             */
/*   Updated: 2024/06/25 19:24:39 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

void	set_background(void);

void	resize_hook(int32_t width, int32_t height, void *param)
{
	int		id;

	id = *((int *) param);
	player(id)->mlx->width = width;
	player(id)->mlx->height = height;
	mlx_delete_image(player(id)->mlx, player(id)->background);
	set_background();
}
