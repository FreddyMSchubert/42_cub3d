/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 08:45:22 by freddy            #+#    #+#             */
/*   Updated: 2024/07/11 10:41:22 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_H
# define SETTINGS_H

# include <stdbool.h>

// --- General

# define VERBOSE false
# define DEBUG false
# define LOG_WALLS false
# define TERMINAL_MAP false
# define LOG_TIMING false

# define SAVE_FILE "save.cubsave"

// --- Debug

# define RENDER_ENTITIES_THROUGH_WALLS false
# define INFINITE_HEALTH false

// --- Quality of Life

# define MOUSE_SENSITIVITY 0.35
# define CAPTURE_MOUSE_AT_START true

// Map Making

# define MIN_MAP_SIZE 15
# define MAX_MAP_SIZE 25
# define MIN_ROOMS_AMOUNT 2
# define MAX_ROOMS_AMOUNT 5
# define MIN_ROOM_SIZE 1
# define MAX_ROOM_SIZE 7
# define MAX_ROOM_SIZE_TO_MAP_SIZE 3
# define WALL_REMOVAL_CHANCE_PERCENT 13

# define ENTITIY_PLACEMENT_CHANCE 13
# define ORB_PLACEMENT_CHANCE 70
# define BLIGHT_PLACEMENT_CHANCE 65
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
# define FPS 30

// --- Entities

// collisions

# define GOAL_COLLISION_DISTANCE 0.5
# define HEALTH_COLLISION_DISTANCE 0.5
# define KEY_COLLISION_DISTANCE 0.5
# define CLOSED_DOOR_ALLOWED_WALK_DISTANCE 0.4
# define DOOR_OPEN_DISTANCE 1.0
# define DEFAULT_COLLISION_DISTANCE 0.35

// speed

# define DOOR_OPEN_SPEED 0.03
# define PROJECTILE_SPEED 0.13
# define BLIGHT_SPEED 0.05

// movement

# define BLIGHT_WALKING_START_CHANCE 0.1
# define BLIGHT_STANDING_START_CHANCE 0.025
# define BLIGHT_ATTACKING_START_CHANCE 0.6
# define BLIGHT_MOVEMENT_ROTATION_SWITCH_CHANCE 0.05
# define BLIGHT_MINIUM_ROTATION_DEG 45
# define BLIGHT_MAX_SPAWN_DISTANCE 10
# define BLIGHT_SPAWN_RETURNING_DEG_VARIATION 45
# define BLIGHT_SHOOTING_INACCURACY_DEG 15

// health

# define ENEMY_STARTING_HEALTH 3
# define PLAYER_STARTING_HEALTH 10
# define MINOR_PROJECTILE_HIT_DECREASE 1
# define MAJOR_PROJECTILE_HIT_DESCREASE 3
# define MIN_HEALTH_PICKUP_AMOUNT 1
# define MAX_HEALTH_PICKUP_AMOUNT 3
# define PLAYER_BLIGHT_COLLISION_DAMAGE 1

// animations

# define BLIGHT_DEATH_ANIMATION_FRAMES 30
# define BLIGHT_ATTACK_ANIMATION_FRAMES 15
# define BLIGHT_HURT_STATE_FRAME_DURATION 3

// --- ELEMENTOR

// mvmnt
# define LMNTOR_MVMNT_SPEED 0.03
# define LMNTOR_MVMNT_WALK_START_CHANCE 0.2		// every frame
# define LMNTOR_MVMNT_WALK_STOP_CHANCE 0.01		// every frame
# define LMNTOR_MVMNT_ROT_CHANGE_CHANCE 0.03	// every frame
# define LMNTOR_MAX_DISTANCE_FROM_SPAWN 5

// attack
# define LMNTOR_ATTACK_CHANCE 0.03				// every frame
# define LMNTOR_ATTACK_SPIN_CHANCE 0.175
# define LMNTOR_ATTACK_SUMMON_CHANCE 0.085
# define LMNTOR_SHOOTING_INACCURACY_DEG 10
# define LMNTOR_SPIN_ATTACK_MIN_PROJECTILES 6
# define LMNTOR_SPIN_ATTACK_MAX_PROJECTILES 15
# define LMNTOR_BLIGHT_SPAWN_DIST 2 // int!

# define LMNTOR_RANDOM_ELEM_CHOICE_CHANCE 0.25
# define LMNTOR_MAX_SAME_ELEMENT_FRAMES 600

// health
# define LMNTOR_STARTING_HEALTH 50
# define LMNTOR_HURT_STATE_FRAME_DURATION 3
# define LMNTOR_DEATH_ANIM_TICKS 400
# define LMNTOR_MAJOR_HIT_DECREASE 2

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
# define MAX_AMMO_AMOUNT_PER_ORB 3
# define MAX_AMMO_AMOUNT_PER_OWN_ELEMENT_ORB 4
# define TICKS_BETWEEN_PLAYER_SHOTS 15

#endif