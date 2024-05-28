/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:23:50 by freddy            #+#    #+#             */
/*   Updated: 2024/05/28 10:35:45 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

void	key_hook(mlx_key_data_t keydata, void *param)
{
	if (keydata.action == MLX_PRESS)
		printf("\nReceived key press %u input!\n", keydata.key);
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(get_persistent_data()->mlx);
	(void) param;
}
