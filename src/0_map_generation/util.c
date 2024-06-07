/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:52:39 by freddy            #+#    #+#             */
/*   Updated: 2024/06/07 10:16:51 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	get_random_bytes(unsigned int *bytes_read)
{
	int	fd;
	int	ret_val;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		exit(1);
	}
	ret_val = read(fd, &bytes_read, sizeof(*bytes_read));
	if (ret_val < 0)
	{
		perror("read");
		close(fd);
		exit(1);
	}
	else if (ret_val != sizeof(*bytes_read))
	{
		printf("Failed to read enough bytes for an integer\n");
		close(fd);
		exit(1);
	}
	close(fd);
}

int	random_int(int limit1, int limit2)
{
	unsigned int	bytes_read;
	int				range;
	int				min;
	int				max;

	if (limit1 == limit2)
		return (limit1);
	min = limit1;
	max = limit2;
	if (limit1 > limit2)
	{
		min = limit2;
		max = limit1;
	}
	get_random_bytes(&bytes_read);
	range = max - min + 1;
	if (range <= 0)
	{
		printf("Invalid range: limit1 %d, limit2 %d\n", limit1, limit2);
		exit(1);
	}
	return ((bytes_read % range) + min);
}
