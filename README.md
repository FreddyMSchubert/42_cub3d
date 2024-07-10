## Cub3d by [FreddyMSchubert](https://github.com/FreddyMSchubert) && [Reptudn](https://github.com/Reptudn)

[![YOUTUBE SHOWCASE VIDEO](https://img.youtube.com/vi/YGmE1SxFchE/0.jpg)](https://www.youtube.com/watch?v=YGmE1SxFchE)
> [!INFO]
> Click on the thumbnail up there to watch the full project showcase on YouTube.

![Boundary](https://github.com/FreddyMSchubert/42_cub3d/blob/master/assets/readme/boundaries/boundary-1.png)

# Installation

(The program was tested on Mac & Linux.)

Simply run this command:

`git clone https://github.com/FreddyMSchubert/42_cub3d.git cub3d && cd cub3d && make`

Now you have the compiled executable called "cub3D" in your current folder.

Then, to experience all of the features in a handcrafted experience, run:

`./play_campaign`

If you wish to play a specific map, you can run:

`./cub3D [path to map]`

> Many maps can be found at [./assets/maps/valid/*.cub](https://github.com/FreddyMSchubert/42_cub3d/tree/master/assets/maps/valid), but you can easily make your own!

If you want to play a randomly generated level, run:

`./cub3D`

![Boundary](https://github.com/FreddyMSchubert/42_cub3d/blob/master/assets/readme/boundaries/boundary-2.png)

# Project introduction

> This project is inspired by the world-famous Wolfenstein 3D game, which was the first FPS ever. \
> It will enable you to explore ray-casting. \
> Your goal will be to make a dynamic view inside a maze, in which you’ll have to find your way.

This project’s objectives are similar to all this first year’s objectives: Rigor, use of C, use of basic algorithms, information research etc.

As a graphic design project, cub3D will enable you to improve your skills in these areas: windows, colors, events, fill shapes, etc.

To conclude cub3D is a remarkable playground to explore the playful practical applications of mathematics without having to understand the specifics.

With the help of the numerous documents available on the internet, you will use mathematics as a tool to create elegant and efficient algorithms.

> You can check out the original Wolfenstein3D game & find out what we were working off here: [Wolfenstein 3D](http://users.atw.hu/wolf3d)

![Boundary](https://github.com/FreddyMSchubert/42_cub3d/blob/master/assets/readme/boundaries/boundary-3.png)

# The task

> As always, for both the bonus and the main part of the task, we had to rigidly keep to the [42 norminette](https://github.com/FreddyMSchubert/42_cursus/blob/main/en.norm.pdf). Have a read, some rules in there are very restrictive.

> You can also read [the subject](https://github.com/FreddyMSchubert/42_cub3d/blob/main/en.subject.pdf).

- You must use MLX42.
- The window management must remain smooth.

### File format (.cub)

- Display different wall textures depending on the cardinal direction of a wall (North, South, East, West).
- Display different floor & ceiling colors.
- The map must be made up of 0s, 1s, Spaces and NSEWs.
	- 1 stands for a wall
	- 0 stands for a floor
	- ' ' stands for a void tile
	- NSEW stands for where the player spawns, giving info on the direction they should be facing.
	- The player must be unable to reach the edge of the map & the void.

An example map could look something like this:

```
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture

F 220,100,0
C 225,30,0

1111111111111111111111111
1000000000110000000000001
1011000001110000000000001
1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

## The bonus

Add:
- Wall collisions
- A minimap system
- Doors which can open and close
- An animated sprite
- View rotation with the mouse

## OUR bonus

Well, but we didn't just stop there.

This project was great fun, so we decided to also do:

- Random map generation which generates nice & playable map with goals, keys, ammo, enemies, and an interesting new layout every time.
- A full entity system that is dynamic & easily expandable
- A fighting & faction system based on the four elements.
- Enemies (called blights) that, move, dodge, shoot, and die. (with cool animations)
- A boss with multiple phases that has three different attack patterns & with a dynamic in-engine modified texture.
- A dynamic fog system with any RGB color & intensity.
- Health. Don't die!
- Saving & Loading of the games state
- An inventory system
- Locked doors, unlockable with a key
- I probably forgot some of it.

All of this combined makes a final map leveraging all of our features looking more like this:

```
C 0,0,0
F 0,0,0 

EA ./assets/textures/walls/coal_ore.png
NO ./assets/textures/walls/redstone_ore.png
SO ./assets/textures/walls/lapis_ore.png
WE ./assets/textures/walls/diamond_ore.png

FO 450,0,0,0
MM OFF

> ----- THE MINE -----
> Turns out, that fighting dojo where nobody was inside gets their money from taking all the people that walk inside and forcing them to work by mining ores in dangerous conditions.
> This fun occupation has now also been thrust upon you.
> You better get out of there to continue your journey!

# This is a comment. It won't have any effect!

1111111111111111
1000000000|0h1h1
10a11100101111p1
1010dK101000V001
1010111000011111
1000001011000001
1001100011011101
1001101000000101
10000011S1110001
1011101000010101
1010000011000101
100011011w01s101
101r110000110101
1010001110100001
101010VG100h1001
1010111110011101
1000000000000001
1111111111111111
```

We also made it possible to turn off the minimap and to log stuff when a map is loaded.

> [!NOTE]
> For a full overview of how to create a map, check out [./assets/maps/template_map.cub](https://github.com/FreddyMSchubert/42_cub3d/blob/master/assets/maps/template_map.cub)

![Boundary](https://github.com/FreddyMSchubert/42_cub3d/blob/master/assets/readme/boundaries/boundary-4.png)
