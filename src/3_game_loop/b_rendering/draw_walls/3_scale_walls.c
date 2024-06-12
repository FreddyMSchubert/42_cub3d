/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_scale_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:53:27 by freddy            #+#    #+#             */
/*   Updated: 2024/06/12 14:21:49 by jkauker          ###   ########.fr       */
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

	if (relative_angle < 0)
		relative_angle += 2 * M_PI;
	if (relative_angle > 2 * M_PI)
		relative_angle -= 2 * M_PI;

	// Correct for fisheye effect
	double corrected_distance = distance * cos(relative_angle);

	double wall_height = (1.0 / corrected_distance) * ((game()->mlx->width / 2) / tan(degrees_to_radians(FOV_DEG) / 2));
	return ((int)wall_height);
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
	left_distance = pos_distance(player()->transform.pos, wall.pos);
	if (left_distance <= 0)
		left_distance = 0.1;
	right_distance = pos_distance(player()->transform.pos, (t_vec2){wall.pos.x + wall.rot.x, wall.pos.y + wall.rot.y});
	if (right_distance <= 0)
		right_distance = 0.1;
	if (wall.rot.x != 0.0 && player()->transform.pos.y < wall.pos.y)
	{
		double tmp = left_distance;
		left_distance = right_distance;
		right_distance = tmp;
	}
	else if (wall.rot.y != 0.0 && player()->transform.pos.x > wall.pos.x)
	{
		double tmp = left_distance;
		left_distance = right_distance;
		right_distance = tmp;
	}
	dimensions.height_left = angle_to_wall_height(left_angle_deg, left_distance);
	dimensions.height_right = angle_to_wall_height(right_angle_deg, right_distance);
	if (dimensions.height_left < 0)
		dimensions.height_left = 0;
	if (dimensions.height_right < 0)
		dimensions.height_right = 0;
	dimensions.direction = get_wall_face(wall);
	// printf("Left Angle: %f, Right Angle: %f, Left Distance: %f, Right Distance: %f\n", left_angle_deg, right_angle_deg, left_distance, right_distance);
	// printf("Wall scale: %d - %d / %d - %d / %c\n", dimensions.x_left, dimensions.x_right, dimensions.height_left, dimensions.height_right, dimensions.direction);
	if (dimensions.x_left > dimensions.x_right)
	{
		int tmp = dimensions.x_left;
		dimensions.x_left = dimensions.x_right;
		dimensions.x_right = tmp;
		double tmp2 = dimensions.height_left;
		dimensions.height_left = dimensions.height_right;
		dimensions.height_right = tmp2;
	}
	return (dimensions);
}

void	scale_walls(t_transform *walls, int walls_amount)
{
	t_wall_scale	curr_wall_scale;
	int				i;

	i = -1;
	// printf("Wall amount: %d\n", walls_amount);
	while (++i < walls_amount)
	{
		curr_wall_scale = get_wall_dimensions(walls[i]);
		// printf("Drawing wall: [%d|%d] - ", (int)walls[i].pos.x, (int)walls[i].pos.y);
		// if (walls[i].rot.x != 0.0)
		// 	printf("Horizontal - ");
		// else
		// 	printf("Vertical   - ");
		// printf("X: %d - %d, Height: %d - %d - ", curr_wall_scale.x_left, curr_wall_scale.x_right, curr_wall_scale.height_left, curr_wall_scale.height_right);
		draw_wall(curr_wall_scale, game()->game_scene);
	}
}
