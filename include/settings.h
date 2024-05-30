/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 08:45:22 by freddy            #+#    #+#             */
/*   Updated: 2024/05/30 10:36:51 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_H
# define SETTINGS_H

#include <stdbool.h>

// General

# define GREETING true
# define VERBOSE true
# define DEBUG true
# define LOG_WALLS false

// Window Setup

# define START_HEIGHT 540
# define START_WIDTH 960
# define WINDOW_NAME "cub3d"

// Player Movement Stats

# define MOVEMENT_SPEED 0.5
# define TURN_SPEED_ARROWS_DEG 5
# define TURN_SPEED_MOUSE_DEG 1

// Display Settings

# define FOV_DEG 90

#endif