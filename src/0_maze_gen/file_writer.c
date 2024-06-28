/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_writer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:51:32 by freddy            #+#    #+#             */
/*   Updated: 2024/06/28 19:01:15 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

#define TEXTURES_AMOUNT 22

static char	*get_random_texture(void)
{
	char	*textures[TEXTURES_AMOUNT];

	textures[0] = "./assets/textures/walls/amethyst_block.png";
	textures[1] = "./assets/textures/walls/bamboo_block.png";
	textures[2] = "./assets/textures/walls/bamboo_mosaic.png";
	textures[3] = "./assets/textures/walls/bamboo_planks.png";
	textures[4] = "./assets/textures/walls/blackstone.png";
	textures[5] = "./assets/textures/walls/bookshelf.png";
	textures[6] = "./assets/textures/walls/brain_coral.png";
	textures[7] = "./assets/textures/walls/bricks.png";
	textures[8] = "./assets/textures/walls/bubble_coral.png";
	textures[9] = "./assets/textures/walls/cherry_planks.png";
	textures[10] = "./assets/textures/walls/chiseled_tuff.png";
	textures[11] = "./assets/textures/walls/chiseled_tuff_top.png";
	textures[12] = "./assets/textures/walls/chiseled_tuff_bricks.png";
	textures[13] = "./assets/textures/walls/chiseled_tuff_bricks_top.png";
	textures[14] = "./assets/textures/walls/diamond_ore.png";
	textures[15] = "./assets/textures/walls/fire_coral.png";
	textures[16] = "./assets/textures/walls/horn_coral.png";
	textures[17] = "./assets/textures/walls/redstone_ore.png";
	textures[18] = "./assets/textures/walls/structure_block.png";
	textures[19] = "./assets/textures/walls/structure_block_corner.png";
	textures[20] = "./assets/textures/walls/structure_block_data.png";
	textures[21] = "./assets/textures/walls/structure_block_load.png";
	return (textures[random_int(0, TEXTURES_AMOUNT - 1)]);
}

static void	write_parameters(int fd)
{
	char	*texture;

	write(fd, "NO ", 3);
	texture = get_random_texture();
	write(fd, texture, ft_strlen(texture));
	write(fd, "\n", 1);
	write(fd, "SO ", 3);
	texture = get_random_texture();
	write(fd, texture, ft_strlen(texture));
	write(fd, "\n", 1);
	write(fd, "WE ", 3);
	texture = get_random_texture();
	write(fd, texture, ft_strlen(texture));
	write(fd, "\n", 1);
	write(fd, "EA ", 3);
	texture = get_random_texture();
	write(fd, texture, ft_strlen(texture));
	write(fd, "\n", 1);
}

static void	write_random_color(int fd, int min, int max)
{
	char	*color;
	int		color_int;

	color_int = random_int(min, max);
	color = ft_itoa(color_int);
	write(fd, color, ft_strlen(color));
}

static void	write_colors(int fd)
{
	write(fd, "F ", 2);
	write_random_color(fd, 0, 255);
	write(fd, ",", 1);
	write_random_color(fd, 0, 255);
	write(fd, ",", 1);
	write_random_color(fd, 0, 255);
	write(fd, "\n", 1);
	write(fd, "C ", 2);
	write_random_color(fd, 0, 255);
	write(fd, ",", 1);
	write_random_color(fd, 0, 255);
	write(fd, ",", 1);
	write_random_color(fd, 0, 255);
	write(fd, "\n", 1);
}

void	write_cub_file(char **maze, int height, int width, char *filename)
{
	int	fd;
	int	x;
	int	y;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write_parameters(fd);
	write_colors(fd);
	y = -1;
	while (++y < height)
	{
		x = -1;
		while (++x < width)
			write(fd, &maze[y][x], 1);
		write(fd, "\n", 1);
	}
	close(fd);
}