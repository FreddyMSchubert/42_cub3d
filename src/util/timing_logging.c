/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing_logging.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 20:24:48 by freddy            #+#    #+#             */
/*   Updated: 2024/07/04 22:11:42 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	log_totals(double total, double hud_render, double world_render)
{
	printf(\
	"TOTAL %.5f (%.1f%% of frame) (%.2f%% HUD render, %.2f%% world render [", \
		total, (total / (1.0 / FPS)) * 100, hud_render, world_render);
}

static void	log_walls(double walls, double raycast, double calc, double draw)
{
	printf("%.2f%% walls {%.2f%% raycast, %.2f%% calc, %.2f%% draw}, ", \
				walls, raycast, calc, draw);
}

static void	log_ntts(double ntts, double raycast, double calc, double draw)
{
	printf("%.2f%% ntts {%.2f%% raycast, %.2f%% calc, %.2f%% draw}])\n", \
				ntts, raycast, calc, draw);
}

void	log_timing(double timing[10])
{
	double	wall_calc;
	double	wall_raycast;
	double	ntt_calc;
	double	ntt_raycast;

	wall_calc = timing[TIMING_TYPE_WALL_CALC] - timing[TIMING_TYPE_WALL_DRAW];
	wall_raycast = timing[TIMING_TYPE_WALL_RAYCAST] - \
									(wall_calc + timing[TIMING_TYPE_WALL_DRAW]);
	ntt_calc = timing[TIMING_TYPE_NTT_CALC] - timing[TIMING_TYPE_NTT_DRAW];
	ntt_raycast = timing[TIMING_TYPE_NTT_RAYCAST] - \
									(ntt_calc + timing[TIMING_TYPE_NTT_DRAW]);
	log_totals(timing[TIMING_TYPE_LOOP], (timing[TIMING_TYPE_HUD_RENDERING] / \
		timing[TIMING_TYPE_LOOP]) * 100, ((timing[TIMING_TYPE_WALL_RAYCAST] + \
		timing[TIMING_TYPE_NTT_RAYCAST]) / timing[TIMING_TYPE_LOOP]) * 100);
	log_walls((timing[TIMING_TYPE_WALL_RAYCAST] / timing[TIMING_TYPE_LOOP]) \
		* 100, (wall_raycast / timing[TIMING_TYPE_LOOP]) * 100, (wall_calc / \
		timing[TIMING_TYPE_LOOP]) * 100, (timing[TIMING_TYPE_WALL_DRAW] / \
		timing[TIMING_TYPE_LOOP]) * 100);
	log_ntts((timing[TIMING_TYPE_NTT_RAYCAST] / timing[TIMING_TYPE_LOOP]) * \
		100, (ntt_raycast / timing[TIMING_TYPE_LOOP]) * 100, (ntt_calc / \
		timing[TIMING_TYPE_LOOP]) * 100, (timing[TIMING_TYPE_NTT_DRAW] / \
		timing[TIMING_TYPE_LOOP]) * 100);
}
