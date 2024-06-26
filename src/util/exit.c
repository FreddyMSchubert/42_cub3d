/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 08:51:31 by freddy            #+#    #+#             */
/*   Updated: 2024/06/25 12:53:10 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	cub_exit(char	*message, int code)
{
	if (code != 0)
		logger(LOGGER_ERROR, message);
	else
		logger(LOGGER_INFO, message);
	gc_exit(code);
}
