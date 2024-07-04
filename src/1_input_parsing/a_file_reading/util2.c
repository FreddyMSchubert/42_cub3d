/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:45:13 by fschuber          #+#    #+#             */
/*   Updated: 2024/07/04 01:45:53 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	print_map_line(char **split)
{
	int	i;

	if (!split || !split[0] || !split[1])
		return ;
	i = 1;
	while (split[i])
	{
		ft_putstr_fd(split[i], 1);
		ft_putstr_fd(" ", 1);
		i++;
	}
	ft_putstr_fd("\n", 1);
}
