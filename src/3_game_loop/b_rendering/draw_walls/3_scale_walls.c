/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_scale_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:53:27 by freddy            #+#    #+#             */
/*   Updated: 2024/06/07 18:36:04 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

static int	angle_to_screen_x(double angle_deg)
{
	double	angle_rad;
	double	player_angle_rad;
	double	relative_angle;
	double	fov_rad;
	int		x;

	angle_rad = degrees_to_radians(angle_deg);
	player_angle_rad = degrees_to_radians(dir_vector_to_degrees(player()->transform.rot));
	relative_angle = angle_rad - player_angle_rad;
	while (relative_angle > M_PI)
		relative_angle -= 2 * M_PI;
	while (relative_angle < -M_PI)
		relative_angle += 2 * M_PI;
	fov_rad = degrees_to_radians(FOV_DEG);
	x = (int)((relative_angle + fov_rad / 2) / fov_rad * game()->mlx->width);
	return (x);
}

static int angle_to_wall_height(double angle_deg, double distance)
{
	double player_angle_rad = degrees_to_radians(dir_vector_to_degrees(player()->transform.rot));
	double angle_rad = degrees_to_radians(angle_deg);
	double relative_angle = angle_rad - player_angle_rad;

	// Correct for fisheye effect
	while (relative_angle > M_PI) relative_angle -= 2 * M_PI;
    while (relative_angle < -M_PI) relative_angle += 2 * M_PI;

	double corrected_distance = distance * cos(relative_angle);
	double wall_height = (1.0 / corrected_distance) * (game()->mlx->width / 2) / tan(degrees_to_radians(FOV_DEG) / 2);
	return (int)wall_height;
}


static char	get_wall_face(t_transform wall)
{
	if (wall.rot.x == 1.0)
	{
		if (player()->transform.pos.x > wall.pos.x)
			return ('W');
		else
			return ('E');
	}
	else
	{
		if (player()->transform.pos.y > wall.pos.y)
			return ('N');
		else
			return ('S');
	}
}

static t_wall_scale	get_wall_dimensions(t_transform wall)
{
	t_wall_scale	dimensions;
	double			left_angle_deg;
	double			right_angle_deg;
	double			left_distance;
	double			right_distance;

	left_angle_deg = calculate_deviation_angle(player()->transform, wall.pos);
	right_angle_deg = calculate_deviation_angle(player()->transform, (t_vec2){wall.pos.x + wall.rot.x, wall.pos.y + wall.rot.y});
	dimensions.x_left = angle_to_screen_x(left_angle_deg);
	dimensions.x_right = angle_to_screen_x(right_angle_deg);
	left_distance = pos_distance(player()->transform.pos, wall.pos); // TODO: these two gotta be switched if player is standing on other side
	if (left_distance <= 0)
		left_distance = 0.1;
	right_distance = pos_distance(player()->transform.pos, (t_vec2){wall.pos.x + wall.rot.x, wall.pos.y + wall.rot.y});
	if (right_distance <= 0)
		right_distance = 0.1;
	dimensions.height_left = angle_to_wall_height(left_angle_deg, left_distance);
	dimensions.height_right = angle_to_wall_height(right_angle_deg, right_distance);
	dimensions.direction = get_wall_face(wall);
	printf("Left Angle: %f, Right Angle: %f, Left Distance: %f, Right Distance: %f\n", left_angle_deg, right_angle_deg, left_distance, right_distance);
    printf("Wall scale: %d - %d / %d - %d / %c\n", dimensions.x_left, dimensions.x_right, dimensions.height_left, dimensions.height_right, dimensions.direction);
	return (dimensions);
}

void	scale_walls(t_transform *walls, int walls_amount)
{
	t_wall_scale	curr_wall_scale;
	int				i;

	i = -1;
	while (++i < walls_amount)
	{
		curr_wall_scale = get_wall_dimensions(walls[i]);
		draw_wall(curr_wall_scale, game()->game_scene);
	}
}
