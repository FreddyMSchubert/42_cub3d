/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 22:02:22 by freddy            #+#    #+#             */
/*   Updated: 2024/07/01 21:58:15 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

#include <time.h>

void	init_random_seed(void)
{
	int32_t		mouse_pos_x;
	int32_t		mouse_pos_y;
	double		rand_val;
	int			fd;
	uint64_t	buf;

	rand_val = mlx_get_time() * 1000 + getpid() + getppid() + time(NULL);
	if (game()->mlx)
	{
		mlx_get_mouse_pos(game()->mlx, &mouse_pos_x, &mouse_pos_y);
		rand_val *= mouse_pos_x * mouse_pos_y;
	}
	fd = open("/dev/urandom", O_RDONLY);
	if (fd >= 0)
	{
		if (read(fd, &buf, sizeof(buf)) == sizeof(buf))
			srand((unsigned int)buf ^ (unsigned int)rand_val);
		close(fd);
	}
	else
		srand((unsigned int)rand_val);
}

double	random_val(void)
{
	return ((double)rand() / RAND_MAX);
}

int	random_int(int min, int max)
{
	double	scaled;

	scaled = random_val() * (max - min + 1);
	return ((int)(scaled + min));
}
