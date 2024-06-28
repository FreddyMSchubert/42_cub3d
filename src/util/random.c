/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 22:02:22 by freddy            #+#    #+#             */
/*   Updated: 2024/06/28 18:13:02 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static inline double	random_seed(void)
{
	int32_t		mouse_pos_x;
	int32_t		mouse_pos_y;
	double		rand_val;
	int			fd;
	uint64_t	buf;

	rand_val = mlx_get_time();
	if (game()->mlx)
	{
		mlx_get_mouse_pos(game()->mlx, &mouse_pos_x, &mouse_pos_y);
		rand_val *= mouse_pos_x * mouse_pos_y;
	}
	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
		return (rand_val);
	if (read(fd, &buf, sizeof(buf)) != sizeof(buf))
		return (close(fd), rand_val);
	close(fd);
	rand_val *= (double)buf / (double)UINT64_MAX;
	return (rand_val);
}

double	random_val(void)
{
	double	full_randomness;

	full_randomness = random_seed();
	if (full_randomness < 0)
		full_randomness *= -1;
	full_randomness = full_randomness - (int)full_randomness;
	return (full_randomness);
}

int	random_int(int min, int max)
{
	double	scaled;

	scaled = random_val() * (max - min + 1);
	return ((int)(scaled + min));
}
