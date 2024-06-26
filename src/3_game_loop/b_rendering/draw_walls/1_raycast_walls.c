/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_raycast_walls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:56:58 by freddy            #+#    #+#             */
/*   Updated: 2024/06/26 11:14:22 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

double	get_fisheye_corrected_ray_angle(int ray_index)
{
	double	relative_position;
	double	angle_correction;

	relative_position = ((double)ray_index / ((RAYCASTS_PER_DEG * FOV_DEG) / 2)) - 1;
	angle_correction = atan(relative_position * tan(deg_to_rad(FOV_DEG / 2)));
	return (rad_to_deg(angle_correction));
}

static t_entity	*perform_entity_raycast(int i, t_vec2 *entity_intersection)
{
	t_transform	ray;
	double		p_angle;
	double		ray_angle;
	t_entity	*entity;

	p_angle = dir_vec_to_deg(player()->transform.rot);
	ray_angle = get_fisheye_corrected_ray_angle(i);
	ray_angle += p_angle;
	ray.rot = deg_to_dir_vec(ray_angle);
	ray.rot = scale_vector(ray.rot, VIEW_DIST);
	ray.pos = player()->transform.pos;
	*entity_intersection = get_entity_intersection(game()->entities, ray, &entity);
	return (entity);
}

static inline t_vec2	perform_wall_raycast(int ray_index)
{
	t_transform	ray;
	double		p_angle_deg;
	double		angle_correction;
	double		ray_angle_deg;

	p_angle_deg = dir_vec_to_deg(player()->transform.rot);
	angle_correction = get_fisheye_corrected_ray_angle(ray_index);
	ray_angle_deg = p_angle_deg + angle_correction;
	ray.rot = deg_to_dir_vec(ray_angle_deg);
	ray.rot = scale_vector(ray.rot, VIEW_DIST);
	ray.pos = player()->transform.pos;
	return (get_wall_intersection(game()->input_data->walls, ray));
}

void	raycast_walls(void)
{
	int			ray_index;
	t_vec2		wall_intersect;
	t_vec2		entity_intersect;
	t_entity	*ntt;
	double		start_rendering;
	double		end_rendering;
	double		raycasting;
	double		ntt_raycasting;
	double		wall_calc;
	double		wall_draw;
	double		entity_calc;
	double		entity_draw;
	double		temp_val;
	double		temp_val_2;

	start_rendering = mlx_get_time();
	ray_index = -1;
	end_rendering = 0;
	raycasting = 0;
	ntt_raycasting = 0;
	wall_calc = 0;
	wall_draw = 0;
	entity_calc = 0;
	entity_draw = 0;
	while (++ray_index < RAYCASTS_PER_DEG * FOV_DEG)
	{
		temp_val = mlx_get_time();
		wall_intersect = perform_wall_raycast(ray_index);
		raycasting += mlx_get_time() - temp_val;

		temp_val = mlx_get_time();
		ntt = perform_entity_raycast(ray_index, &entity_intersect);
		ntt_raycasting += mlx_get_time() - temp_val;

		// Wall calculations and drawing
		temp_val = mlx_get_time();
		temp_val_2 = calc_wall(ray_index, wall_intersect);
		wall_calc += mlx_get_time() - temp_val - temp_val_2;
		wall_draw += temp_val_2;

		// Entity calculations and drawing
		if (ntt && entity_intersect.x != -1 && entity_intersect.y != -1 &&
			(pos_distance(player()->transform.pos, entity_intersect) < pos_distance(player()->transform.pos, wall_intersect) || RENDER_ENTITIES_THROUGH_WALLS)) {
			temp_val = mlx_get_time();
			temp_val_2 = calc_entity(ray_index, entity_intersect, ntt);
			entity_calc += mlx_get_time() - temp_val - temp_val_2;
			entity_draw += temp_val_2;
		}
	}
	end_rendering = mlx_get_time();
	double	rendering_time = end_rendering - start_rendering;
	printf("Total rendering time: %f, raycasting: %f (%.2f%%), ntt_raycasting: %f (%.2f%%), wall_calc: %f (%.2f%%), wall_draw: %f (%.2f%%), entity_calc: %f (%.2f%%), entity_draw: %f (%.2f%%)\n",
		rendering_time,
		raycasting, (raycasting / rendering_time) * 100,
		ntt_raycasting, (ntt_raycasting / rendering_time) * 100,
		wall_calc, (wall_calc / rendering_time) * 100,
		wall_draw, (wall_draw / rendering_time) * 100,
		entity_calc, (entity_calc / rendering_time) * 100,
		entity_draw, (entity_draw / rendering_time) * 100);
}
