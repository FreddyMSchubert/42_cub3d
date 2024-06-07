# Changelog

### [0.10.17] - 07.06.2024 - Freddy
- Fixed player often spawning in walls because player coords defined in parse.c/make_map passed to set_values.c/set_player_spawn were switched
- made rng in mapmaker util use /dev/urandom instead or /dev/random
- fixed floating point exception in mapmaker rng
- mapmaker norminettifications, removal of fprintf statements

### [0.10.16] - 07.06.2024 - Freddy
- Added mario.cub, a recreation of smb1-1 as cub format

### [0.10.15] - 06.06.2024 - Freddy
- automatically importing submodules doesnt work yet because submodule folders are cloned but not filled, which makes the check not work. added a new check which runs ls in the directories and runs the submodule command if the ls command prints something
- very annoying you cant test this without pushing a commit

### [0.10.14] - 06.06.2024 - Freddy
- made makefile automatically run setup when submodules arent installed. this should work.

### [0.10.13] - 06.06.2024 - Freddy
- Made all the draw walls stuff not malloc anything - which should improve performance greatly
	- Now the testing rectangle seems to render, and nothing else anymore, whats going on?
- Fixed some maps not having a proper spawn point
- map generator placing player in 1 sized space fix, this is because random walls were removed before setting the player, so bad luck can sometimes make you spawn trapped, now player gets set first and doesn't get overriden by either remove random walls or add rooms
- fixed map making macro misnaming & added room size changing macros

### [0.10.12] - 06.06.2024 - Freddy
- Added 12 more maps, some my own, some credited, to test various aspects
- Added invalid_maps to test parsing, very hard. Already found a segfault. For now just maps, no parser changes yet

### [0.10.11] - 06.06.2024 - Freddy
- Removed various unwanted chars from the maps which would cause parsing errors, through the help of misc/char_overview.sh, which lists amounts of each char in file

### [0.10.10] - 06.06.2024 - Freddy
- added step logging type & logging statements all over the program. now we clearly know where something broke if something broke
- removed premade walls - they are thoroughly unnecessary now that we have integrated the map generator into the main program
- fixed weird letters in zelda.cub
- removed unnecessary logging in general
- made map creator not leak literally every allocated byte by using garbage collector, fully removed mapmaker cleanup function
- made mapmaker not log map, it will be logged out soon enogh afterwards

### [0.10.9] - 06.06.2024 - Freddy
- Fixed some squarify map issues, general stability and readability improvements
- fixed issue where squarify map would turn all floors and everything following the first floor in a line into voids

### [0.10.9] - 05.06.2024 - Freddy - `20-draw-walls`
- Merged 20-draw-walls into master - it is not done, but the decision was made to sync up the state of the code as it is at the moment so we can easily continue working
- There are a lot of issues created with this, the three most notable being
	- Segfaults in 1_input_parsing
	- A map without floors voids in each line starting with the first floor of each line going to the end arriving at the validator (so, that would be an issue with the squarifier presumably)
	- abort issues
- these three issues combined let almost no executions run through as normally expected without issues
- however, well go through those together tomorrow

### [0.10.8] - 05.06.2024 - Freddy - `20-draw-walls`
- fixed maze generator placing really weird player spawns. player now no longer spawns wherever generation started
- various drawing changes

### [0.10.7] - 05.06.2024 - Freddy - `20-draw-walls`
- Fixed maze generator occasionally segfaulting when adding rooms due to incorrect maze boundary checks
- moved the important generation settings as easily changeable macros into settings.h

### [0.10.6] - 04.06.2024 - Freddy - `20-draw-walls`
- implemented view distance
- fixed vis walls count being uninitialized, leading to a segfault

### [0.10.5] - 04.06.2024 - Freddy - `20-draw-walls`
- renamed data back to name - now things work better, it compiles.
- sorted wall drawing functions a little
- implemented non-malloc approach further
- code segfaults on second frame

### [0.10.4] - 04.06.2024 - Freddy - `20-draw-walls`
- sort walls now saves walls into array & ensures wall uniqueness
	- to do this, i created a positions util that compares walls
- moved some files around & cahnged some names

### [0.10.3] - 04.06.2024 - Freddy - `20-draw-walls`
- removed mallocing from raycast intersect, general improvements
- added get_intersection_wall which returns the wall from a long list that is intersected with
- added util function to convert between degrees and directional vectors, and to normalize degrees
- continued work on sort walls function
- renamed get_persistent_game() functin to just game() and get_player() to just player()
- added half-finished wall sorting and raycasting setup, where the raycasts are performed in all the right directions, but not used yet.

### [0.10.2] - 3.06.2024 - Freddy - `20-draw-walls`
- fixed colors! it now draws colorful & doesnt repeat 4 times anymore. big success.
- Added screen clearing to 1_sort_walls, this is not a permanent solution but is helpful while I'm sorting out the drawing logic. This will be removed later.
- Added math lib include to makefile
- better color logging

### [0.10.1] - 30.05.2024 - Freddy - `20-draw-walls`
- fixed incorrect degrees to radians conversion
- reworked angle_to_Screen_x function, that should hopefully be better now
- fixed angle to screen x producing int min and int max values, making the program run predictably slowly when it loops through them. i fixed that. 
- it renders now - something. nothing correct though.

## [0.10.0] - 30.05.2024 - Freddy - `20-draw-walls`
- added calculate deviation angle, which will be helpful to draw the walls and check whether a wall is outside of the fov, ...
- added sort walls (which is supposed to eventually do the raycasting and sorting, but currently does nothing)
- added scale walls, which turns the 3d walls into 2d screen coordinates
- added draw_walls, which draws each wall
- currently, this does not work. instead, there are little lines on top of the screen, the height and width of which are influenced by the players transform.

### [0.9.3] - 29.05.2024 - Freddy - `18-player-movement`
- made mouse change rotations by scrolling because i havent found a mouse position hook - unsure that exists. would be very weird if not though.

### [0.9.2] - 29.05.2024 - Freddy - `18-player-movement`
- fixed movement not working properly because of improper dereferencing of t_tile_type value at standing map spot

### [0.9.1] - 29.05.2024 - Freddy - `18-player-movement`
- fixed parse resetting input pos to 0, thus breaking the update
- added LOG_WALLS to not log walls if not necessary as its thoroughly annoying
- i have worked toward fixing the dysfunctional moement, the position is now here properly, meaning were not in a wall anymore - but movement is still not happening

## [0.9.0] - 29.05.2024 - Freddy - `18-player-movement`
- dysfunctional movement setup, no rotations yet. values dont seem to update. but ive changed so much its committment time
- Changed seperate vec2s in player entity to use one t_transform instead
- made scale_transform use a double for precise values & made it take in any vec2 instead of a transform
- random fixes

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
