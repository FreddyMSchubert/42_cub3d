/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 08:45:22 by freddy            #+#    #+#             */
/*   Updated: 2024/07/04 12:44:21 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_H
# define SETTINGS_H

# include <stdbool.h>

// --- General

# define VERBOSE false
# define DEBUG false
# define LOG_WALLS false
# define TERMINAL_MAP true

# define SAVE_FILE "save.cubsave"

// --- Debug

# define RENDER_ENTITIES_THROUGH_WALLS false
# define INFINITE_HEALTH false

// --- Quality of Life

# define MOUSE_SENSITIVITY 0.35
# define CAPTURE_MOUSE_AT_START true

// Map Making

# define MIN_MAP_SIZE 13
# define MAX_MAP_SIZE 30
# define MIN_ROOMS_AMOUNT 2
# define MAX_ROOMS_AMOUNT 5
# define MIN_ROOM_SIZE 3
# define MAX_ROOM_SIZE 10
# define MAX_ROOM_SIZE_TO_MAP_SIZE 3
# define WALL_REMOVAL_CHANCE_PERCENT 18

# define ENTITIY_PLACEMENT_CHANCE 13
# define ORB_PLACEMENT_CHANCE 50
# define BLIGHT_PLACEMENT_CHANCE 55
# define HEALTH_DROP_CHANCE_PERCENT 3

// --- Window Setup

# define START_HEIGHT 540
# define START_WIDTH 960
# define WINDOW_NAME "cub3d"

// --- Player Movement Stats

# define MOVEMENT_SPEED 0.0625
# define MOVEMENT_SPRINT_MULTIPLIER 2
# define TURN_SPEED_ARROWS_DEG 10
# define TURN_SPEED_MOUSE_DEG 1
# define WALL_COLLISION_MARGIN 0.25

// --- Display Settings

# define FOV_DEG 96
# define RAYCASTS_PER_DEG 5
# define FISHEYE_CORRECTION_FACTOR 0.5
# define VIEW_DIST 3
# define FPS 24

// --- Entities

// collisions

# define GOAL_COLLISION_DISTANCE 0.5
# define HEALTH_COLLISION_DISTANCE 0.5
# define KEY_COLLISION_DISTANCE 0.5
# define CLOSED_DOOR_ALLOWED_WALK_DISTANCE 0.4
# define DOOR_OPEN_DISTANCE 1.0
# define DEFAULT_COLLISION_DISTANCE 0.25

// speed

# define DOOR_OPEN_SPEED 0.03
# define PROJECTILE_SPEED 0.13
# define BLIGHT_SPEED 0.05

// movement

# define BLIGHT_WALKING_START_CHANCE 0.1
# define BLIGHT_STANDING_START_CHANCE 0.025
# define BLIGHT_ATTACKING_START_CHANCE 0.5
# define BLIGHT_MOVEMENT_ROTATION_SWITCH_CHANCE 0.05
# define BLIGHT_MINIUM_ROTATION_DEG 45
# define BLIGHT_MAX_SPAWN_DISTANCE 10
# define BLIGHT_SPAWN_RETURNING_DEG_VARIATION 45
# define BLIGHT_SHOOTING_INACCURACY_DEG 30

// health

# define ENEMY_STARTING_HEALTH 3
# define PLAYER_STARTING_HEALTH 10
# define MINOR_PROJECTILE_HIT_DECREASE 1
# define MAJOR_PROJECTILE_HIT_DESCREASE 3
# define HEALTH_PICKUP_AMOUNT 1
# define PLAYER_BLIGHT_COLLISION_DAMAGE 1

// animations

# define BLIGHT_DEATH_ANIMATION_FRAMES 25
# define BLIGHT_ATTACK_ANIMATION_FRAMES 20
# define BLIGHT_HURT_STATE_FRAME_DURATION 150

// --- HUD Settings

// Minimap Settings

# define MINIMAP_WIDTH 200
# define MINIMAP_HEIGHT 200
# define MINIMAP_LEFT_OFFSET 25
# define MINIMAP_TOP_OFFSET 25
# define MINIMAP_BORDER_WIDTH 5

// Elements Visualization

# define ELEMENTS_VIS_RIGHT_OFFSET 25
# define ELEMENTS_VIS_TOP_OFFSET 25
# define ELEMENTS_VIS_SCALE 1.5

// --- Gameplay Balancing

# define MIN_AMMO_AMOUNT_PER_ORB 1
# define MAX_AMMO_AMOUNT_PER_ORB 4

#endif