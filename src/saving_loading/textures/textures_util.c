/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 20:33:59 by freddy            #+#    #+#             */
/*   Updated: 2024/07/06 20:37:19 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

mlx_texture_t	*l(char *path)
{
	mlx_texture_t	*texture;
	char			*fullpath;
	static int		textures = 0;

	if (textures + 1 >= MAX_TEXTURES)
		cub_exit("Texture amount exceeds max allowed textures", -1);
	if (textures == -1)
		ft_bzero(game()->texture_arr, MAX_TEXTURES);
	fullpath = ft_strjoin2("assets/textures/", path);
	if (!fullpath)
		cub_exit("Error loading texture", -1);
	texture = mlx_load_png(fullpath);
	gc_append_element(fullpath);
	if (!texture)
	{
		printf("Problem texture: <assets/textures/%s>\n", path);
		cub_exit("Error loading texture", -1);
	}
	game()->texture_arr[textures++] = texture;
	return (texture);
}

void	load_animation_textures(char *base_path, t_animation *animation)
{
	char	*str;

	str = ft_strjoin(base_path, "1.png");
	if (!str)
		cub_exit("Error loading texture", -1);
	animation->frame1 = l(str);
	free(str);
	str = ft_strjoin(base_path, "2.png");
	if (!str)
		cub_exit("Error loading texture", -1);
	animation->frame2 = l(str);
	free(str);
	str = ft_strjoin(base_path, "3.png");
	if (!str)
		cub_exit("Error loading texture", -1);
	animation->frame3 = l(str);
	free(str);
}

void	load_orbs(void)
{
	game()->textures.water_orb = l("entities/orbs/water.png");
	game()->textures.fire_orb = l("entities/orbs/fire.png");
	game()->textures.earth_orb = l("entities/orbs/earth.png");
	game()->textures.air_orb = l("entities/orbs/air.png");
	game()->textures.water_orb_floor = l("entities/orbs/water_floor.png");
	game()->textures.fire_orb_floor = l("entities/orbs/fire_floor.png");
	game()->textures.earth_orb_floor = l("entities/orbs/earth_floor.png");
	game()->textures.air_orb_floor = l("entities/orbs/air_floor.png");
	game()->textures.water_orb_flying = l("entities/orbs/water_flying.png");
	game()->textures.fire_orb_flying = l("entities/orbs/fire_flying.png");
	game()->textures.earth_orb_flying = l("entities/orbs/earth_flying.png");
	game()->textures.air_orb_flying = l("entities/orbs/air_flying.png");
}
