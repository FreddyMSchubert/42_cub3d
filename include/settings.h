/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 08:45:22 by freddy            #+#    #+#             */
/*   Updated: 2024/06/14 10:47:49 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_H
# define SETTINGS_H

# include <stdbool.h>

// General

# define GREETING true
# define VERBOSE true
# define DEBUG false
# define LOG_WALLS false
# define TERMINAL_MAP true

// Map limits

# define MAX_PLAYER_COUNT 1
# define MAX_GOAL_COUNT 1

// Quality of Life

# define MOUSE_SENSITIVITY 0.35

// Map Making

# define MIN_MAP_SIZE 5
# define MAX_MAP_SIZE 30
# define MIN_ROOMS_AMOUNT 0
# define MAX_ROOMS_AMOUNT 3
# define MIN_ROOM_SIZE 2
# define MAX_ROOM_SIZE 5
# define WALL_REMOVAL_CHANCE_PERCENT 20

// Window Setup

# define START_HEIGHT 540
# define START_WIDTH 960
# define WINDOW_NAME "cub3d"

// Player Movement Stats

# define MOVEMENT_SPEED 0.03
# define TURN_SPEED_ARROWS_DEG 5
# define TURN_SPEED_MOUSE_DEG 1

// Display Settings

# define FOV_DEG 96
# define RAYCASTS_PER_DEG 5
# define RENDER_DISTANCE 50
# define FPS 60

#endif