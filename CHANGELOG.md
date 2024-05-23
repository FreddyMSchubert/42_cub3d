# Changelog

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
