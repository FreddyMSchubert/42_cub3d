/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 08:45:22 by freddy            #+#    #+#             */
/*   Updated: 2024/06/10 12:01:47 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_H
# define SETTINGS_H

# include <stdbool.h>

// General

# define GREETING true
# define VERBOSE true
# define DEBUG true
# define LOG_WALLS false

// Player
# define PLAYER_MAX_HEALTH 100
# define PLAYER_MAX_ARMOR 100
# define PLAYER_MAX_AMMO 100

# define MAX_PLAYER_COUNT 1

// Map Making

# define MIN_MAP_SIZE 7
# define MAX_MAP_SIZE 20
# define MIN_ROOMS_AMOUNT 0
# define MAX_ROOMS_AMOUNT 0
# define MIN_ROOM_SIZE 1
# define MAX_ROOM_SIZE 3
# define WALL_REMOVAL_CHANCE_PERCENT 30

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
# define RAYCASTS_PER_DEG 1
# define RENDER_DISTANCE 25

#endif