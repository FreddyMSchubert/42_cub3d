/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_scale_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:53:27 by freddy            #+#    #+#             */
/*   Updated: 2024/05/30 14:46:51 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

// this is easily adjustable for better looking walls
static int	get_max_wall_height(void)
{
	return (get_persistent_data()->mlx->height * 2);
}

static int	angle_to_screen_x(double angle_deg, double fov_rad)
{
	return ((int)((angle_deg + fov_rad / 2) / fov_rad * get_persistent_data()->mlx->width));
}

static int	angle_to_wall_height(double angle_deg)
{
	return (get_max_wall_height() * (1.0 - fabs(angle_deg) / (FOV_DEG / 2)));
}

static char	get_wall_face(t_transform *wall, t_entity *player)
{
	if (wall->rot.x == 1) // vertical
	{
		if (player->transform.pos.x > wall->pos.x)
			return 'W';
		else
			return 'E';
	}
	else // horizontal
	{
		if (player->transform.pos.y > wall->pos.y)
			return 'N';
		else
			return 'E';
	}
}

static t_wall_scale	*get_wall_dimensions(t_transform *wall, t_entity *player)
{
	t_wall_scale	*dimensions;
	double			fov_rad;
	double			left_angle_deg;
	double			right_angle_deg;
	
	fov_rad = degrees_to_radians(FOV_DEG);
	left_angle_deg = calculate_deviation_angle(player->transform, wall->pos);
	right_angle_deg = calculate_deviation_angle(player->transform, (t_vec2){wall->pos.x + wall->rot.x, wall->pos.y + wall->rot.y});
	dimensions = gc_malloc(sizeof(t_wall_scale));
	dimensions->x_left = angle_to_screen_x(left_angle_deg, fov_rad / 2);
	dimensions->x_right = angle_to_screen_x(right_angle_deg, fov_rad / 2);
	dimensions->height_left = angle_to_wall_height(left_angle_deg);
	dimensions->height_right = angle_to_wall_height(right_angle_deg);
	dimensions->direction = get_wall_face(wall, player);
	return (dimensions);
}

void	scale_walls(void)
{
	t_transform		**walls;
	int				walls_amount;
	t_entity		*player;
	t_wall_scale	**wall_scales;
	int				i;

	walls = get_persistent_data()->raycasted_sorted_walls;
	walls_amount = 0;
	while (walls[walls_amount])
		walls_amount++;
	player = get_player();
	wall_scales = gc_malloc((walls_amount + 1) * sizeof(t_wall_scale));
	wall_scales[walls_amount] = NULL;
	i = -1;
	while (walls[++i])
		wall_scales[i] = get_wall_dimensions(walls[i], player);
	get_persistent_data()->walls_scaled = wall_scales;
}