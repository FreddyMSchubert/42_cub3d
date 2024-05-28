# Changelog

### [0.8.2] - 28.05.2024 - Freddy - `15-validation-flood-fill`
- made map generation place player pos where generation started, so pretty much the center of the labrinth
- some map gen fixes & refactorings

### [0.8.1] - 28.05.2024 - Freddy - `15-validation-flood-fill`
- norminettification & efficiency improvements of new flood filled validator

## [0.8.0] - 28.05.2024 - Freddy - `15-validation-flood-fill`
- made validator use a flood fill system starting from the player pos to authenticate the maps & made it set all unreachable fields to void for effiency
- removed random testing code
- random squarify map & parser fixes

### [0.7.2] - 28.05.2024 - Freddy - `14-very-basic-rendering-setup`
- added hook setup & loop hook & key hook
- made program close when esc is received

### [0.7.1] - 28.05.2024 - Freddy - `14-very-basic-rendering-setup`
- Made t_color struct hold unsigned chars, more efficient.
- Made colors as ints use unsigned int instead, as that keeps the data properly
- ceiling & floor colors now render properly

## [0.7.0] - 28.05.2024 - Freddy - `14-very-basic-rendering-setup`
- Added an alpha field to color struct & added conversion to and from int utils
- added mlx setup function & created basic window & drew background white. currently the colors dont appear properly.

### [0.6.1] - 24.05.2024 - Freddy - `12-raycasting-rendering-util`
- Changed infinitify_transform to scale_transform, which takes in an int to set the combined distance of the newly adjusted vectors to.
  - using this, we can implement a render distance easily.

## [0.6.0] - 24.05.2024 - Freddy - `12-raycasting-rendering-utils`
- added pos_distance function
- added infinitify_transform function which makes an inputted vectors rotation as long as possible while keeping the same relative value
- added raycast intersect which returns a vec2 position of where the two vectors intersected or NULL if they dont. This does only work as far as the vectors actually go though - use infinitify vector to make the vector long.

### [0.5.1] - 24.05.2024 - Freddy - `12-raycasting-rendering-utils`
- Added better project structure
- Made Makefile only attempt to import submodules if theyre not there
- Changed vec2s to use doubles
  - Resolved problems created by this
- Removed t_size struct as it was unnecessary
- Removed a bunch of weird write calls that were unnecessary

## [0.5.0] - 23.05.2024 - Freddy
- Added map generation setup & integrated it into project. Use ./cub3d without an argument to have one dynamically generated.
- reordered folders in src files
- added changed validator logging statement

### [0.4.1] - 23.05.2024 - Freddy
- Added `wall_displayer.py` in misc/, which takes in the printed out generated wall and plots them out visually to verify everything is working correctly

## [0.4.0] - 23.05.2024 - Jonas
  - map squarification (added voids at end of map if it was non-rectangular before)

### [0.3.7] - 23.05.2024 - Freddy
- Fixes to maps that had some issues

### [0.3.6] - 23.05.2024 - Freddy
- Various fixes. problem detected: map returned by file reading is not square.

### [0.3.5] - 23.05.2024 - Jonas
 - basic file parsing with basic error checking

### [0.3.4] - 23.05.2024 - Freddy
- Various refactorings & improvements to wall_conversion.c, mainly carrying over map array changes from [0.3.2]
	- wall allocation logic fix
	- made sure to only add walls directly next to a floor, which guarantees optimal performance (will always save ~ `(maze_width + maze_height + amount_of_void_spaces * 2) - 2` walls from having to be calculated with every frame)
- Added testing setup

### [0.3.3] - 23.05.2024 - Freddy
- Added some auto-generated mazes created with the generator I made to the project
- Made start_random_cub3d_map not pick .DS_Store or any other files that may eventually pop up in there

### [0.3.2] - 23.05.2024 - Freddy
- Fixed map not being terminated by properly (**map -> ***map), various changes in validator to reflect this
- Added a testing setup to validator
- Added testcases for fun (merry_go_round + 42)
- Renamed previous printing to logging, instead creating printing, filling it with a function to print out the map in its current state

### [0.3.1] - 22.05.2024 - Freddy
- found out how to render images starting with a png, changed back the file endings in the maps

## [0.3.0] - 22.05.2024 - Freddy - `6-input-validation`
- added input validation function that ensures no floor tiles touch any void tiles or walls

### [0.2.1] - 22.05.2024 - Freddy - `3-enum-map-to-wall-vectors`
- in `wall_conversion.c`, converted bool map to wall array
	- various refactorings & improvements in structure and logic
	- added some comments to clarify the logic

## [0.2.0] - 22.05.24 - Freddy - `3-enum-map-to-wall-vectors`
- made `wall_conversion.c`, which converts the tile types into a boolean array, which removes duplicate overlapping walls.
	- now only walls that can actually seen are in this boolean array. it only needs to be converted to transforms now.

### [0.1.8] - 22.05.2024 - Freddy
- Added 5 more maps that are a good bit more difficult

### [0.1.7] - 22.05.2024 - Freddy
- Added some nice map files that test various things in ./assets/maps/*
- Added a good amount of minecraft textures as walls
- added `start_random_cub3d_map.sh`, which picks a random map to execute and starts ./cub3d
	- made gitignore not ignore shell files

### [0.1.6] - 21.05.2024 - Freddy
- made gc static
- various refactorings & norminettifications

### [0.1.5] - 21.05.2024 - Freddy
- fixed Makefile not working importing submodules

### [0.1.4] - 21.05.2024 - Freddy
- added src folder structure
- added a test map
- added minecraft coral blocks as temp assets
- minecraft assets removal

### [0.1.3] - 21.05.2024 - Jonas
- added structs:
  - vector2 for position and rotation
  - transform which includes pos and rot
  - entity for player / mob
  - input data

### [0.1.2] - 21.05.2024 - Freddy
- Fixed makefile not working with submodule importing properly

### [0.1.1] - 21.05.2024 - Freddy
- removed assets folder, instead added whole minecraft resources as submodule

## [0.1.0] - 21.05.2024 - Freddy
- Added duplicate protected garbage collector with gc_malloc
- added logger and verbose logger
- makefile object folder subdirectories fix
- makefile not properly cleaning submodules fix

## [0.0.0] - 21.05.2024 - Freddy
- initial commit
- Basic project setup
  - colors header with all allowed includes
  - gnl, libft, mlx42 libs as submodules
  - makefile
- test window to verify mlx42 is functional
