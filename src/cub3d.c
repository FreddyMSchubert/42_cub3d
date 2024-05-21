/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 07:33:54 by fschuber          #+#    #+#             */
/*   Updated: 2024/05/21 08:05:40 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	esc_close_hook(void *param)
{
	mlx_t	*mlx;

	mlx = (mlx_t *)param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

static int	test_libmlx_functional(void)
{
	mlx_t	*mlx;

	mlx = mlx_init(800, 600, "Test Window", true);
	if (!mlx)
	{
		fprintf(stderr, "Failed to initialize MLX42\n");
		return (EXIT_FAILURE);
	}

	mlx_loop_hook(mlx, esc_close_hook, mlx);

	mlx_loop(mlx);

	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	if (GREETING)
		printf("%sHello cubic world!%s\n", ANSI_COLOR_CYAN, ANSI_RESET);

	test_libmlx_functional();

	(void)argc;
	(void)argv;
}
