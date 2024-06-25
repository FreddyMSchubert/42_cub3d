/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_raycast_walls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:56:58 by freddy            #+#    #+#             */
/*   Updated: 2024/06/26 01:09:39 by freddy           ###   ########.fr       */
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
	double		start_raycasting;
	double		end_raycasting;
	double		start_ntt_raycasting;
	double		end_ntt_raycasting;
	double		start_calc;
	double		end_calc;
	double		start_ntt_calc;
	double		end_ntt_calc;

	start_rendering = mlx_get_time();
	ray_index = -1;
	while (++ray_index < RAYCASTS_PER_DEG * FOV_DEG)
	{
		start_raycasting = mlx_get_time();
		wall_intersect = perform_wall_raycast(ray_index);
		end_raycasting = mlx_get_time();
		start_ntt_raycasting = mlx_get_time();
		ntt = perform_entity_raycast(ray_index, &entity_intersect);
		end_ntt_raycasting = mlx_get_time();
		start_calc = mlx_get_time();
		calc_wall(ray_index, wall_intersect);
		end_calc = mlx_get_time();
		start_ntt_calc = mlx_get_time();
		if (ntt && entity_intersect.x != -1 && entity_intersect.y != -1 && \
				(pos_distance(player()->transform.pos, entity_intersect) < pos_distance(player()->transform.pos, wall_intersect) || RENDER_ENTITIES_THROUGH_WALLS))
			calc_entity(ray_index, entity_intersect, ntt);
		end_ntt_calc = mlx_get_time();
	}
	end_rendering = mlx_get_time();
	double rendering_time = end_rendering - start_rendering;
	double raycasting_time = end_raycasting - start_raycasting;
	double ntt_raycasting_time = end_ntt_raycasting - start_ntt_raycasting;
	double calc_time = end_calc - start_calc;
	double ntt_calc_time = end_ntt_calc - start_ntt_calc;
	printf("Total rendering time: %f, raycasting: %f (%.2f%%), ntt_raycasting: %f (%.2f%%), calc: %f (%.2f%%), ntt_calc: %f (%.2f%%)\n",
		rendering_time,
		raycasting_time, (raycasting_time / rendering_time) * 100,
		ntt_raycasting_time, (ntt_raycasting_time / rendering_time) * 100,
		calc_time, (calc_time / rendering_time) * 100,
		ntt_calc_time, (ntt_calc_time / rendering_time) * 100);
}
