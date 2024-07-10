# Cub3d by [FreddyMSchubert](https://github.com/FreddyMSchubert) && [Reptudn](https://github.com/Reptudn)

[![YOUTUBE SHOWCASE VIDEO](https://img.youtube.com/vi/YGmE1SxFchE/0.jpg)](https://www.youtube.com/watch?v=YGmE1SxFchE)
### 💧🔥🪨💨 42 cub3d game - [full campaign] - project created by FreddyMSchubert & Reptudn
> [!NOTE]
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

> Many maps can be found at [./assets/maps/valid/*.cub](https://github.com/FreddyMSchubert/42_cub3d/tree/master/assets/maps/valid), but you can easily make your own! More on that in a bit.

If you want to play a randomly generated level, run:

`./cub3D`

![Boundary](https://github.com/FreddyMSchubert/42_cub3d/blob/master/assets/readme/boundaries/boundary-2.png)

> [!NOTE]
> Don't like the amount of health you start out with? \
> Don't like the enemy movement speed? \
> Wan't to play around and tweak the map generation? \
> Every single important settings is defined in [settings.h](https://github.com/FreddyMSchubert/42_cub3d/blob/master/include/settings.h), you can play around with anything & see what happens.

> [!NOTE]
> If you want to get a look behind the scenes, turn on some of the settings in the general section of [settings.h](https://github.com/FreddyMSchubert/42_cub3d/blob/master/include/settings.h) - they will enable some very extensive logging, amount other things.

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

We also made it possible to turn off the minimap and to log stuff when a map is loaded. The minimap is a subject requirement, but it makes a lot of maps pretty easy and boring.

> [!NOTE]
> For a full overview of how to create a map, check out [./assets/maps/template_map.cub](https://github.com/FreddyMSchubert/42_cub3d/blob/master/assets/maps/template_map.cub)

![Boundary](https://github.com/FreddyMSchubert/42_cub3d/blob/master/assets/readme/boundaries/boundary-4.png)

# Notes on the journey

This is the kind of project that will be super excited for, then you'll sit down, think about what you would actually start with, realize you don't know how to accomplish any of the tasks at hand, and then start by coding a really good parsing setup.

Our parsing setup is really good.

It is noteworthy that working in a team was already quite a lot easier now. After having spent a month in the perils of the worst git has to offer while making [minishell](https://github.com/FreddyMSchubert/42_minishell), we were both a lot better at coordinating co-op coding. If we had worked on this project before [minishell](https://github.com/FreddyMSchubert/42_minishell), I'm certain it would have taken considerably longer.

While I was on holidays in the Netherlands and Jonas was still ironing out kinks in the parsing, I started with an initial approach to something being properly visible. I thought - hey, sure you can use raycasting as the subject expects and calculate one ray per horizontal pixel, do a stepping algorithm and everything, or we could just do it with maths. The game wouldn't need any complex 3D models after all, we could just, based on the players rotation and position relative to a given wall, calculate how many degrees the wall diverges from the center of the players view, and then translate that to a horizontal pixel. Getting a height for the left and right side of a wall based on the angle to the player and the distance shouldn't be hard either.

We did actually get this to sort of work. The walls had a nasty habit of not always showing up, but we eventually ditched this concept because we simply underestimated the complexity of the maths involved. Our best versions still either had the top and bottom edges of two orthogonal walls look completely parallel if looked at from a 45 degree angle or other stuff break rather dramatically.

Lesson learned, maybe get some rendering going before immediately trying to outsmart the guy smarter than you who put thought into designing this exercise.

Things very quickly turned around when I decided to try the normal raycasting though, because I had basic walls working in less than a day. Literally, I got up quite early that day, and by the time Jonas arrived, the walls were already showing. There were still a few issues, like some fisheye effect, which Jonas and me cleared up over the next few days. This method is the one we have stuck with until the end.

With this done, things picked up pace very quickly. Jonas delivered a very cool looking minimap, while I worked on collisions, but I very quickly started turning my eyes on massively overinterpreting the requirement of "an animated sprite" in the subject.

I knew I was doing this. I did not care. Other folks literally just put a torch that wobbled around a little into the HUD. Jonas and me had previously dreamed of a pretty extendable entity system, which would allow for bullets, stuff on the floor, enemies, and maybe even a boss. I implemented this system, and once Jonas was done with the minimap, we both just started going into gameplay mode. Most 42 cub3d implementations, there are many on GitHub, feature basically no incentives or anything to do but look at the north wall and realize that it has a different texture to the south wall.

Thus, I added doors unlockable with keys, and Jonas created an inventory for held item management, to which soon ammo was added. I didn't want to create a Wolfenstein-like military shooter, I am more of a splatoon person myself, so I created enemies and ammo based on the elements instead. The next week was spent with making health, refining fighting, and making a whole dynamic map generator which places the keys, maps, doors and goals.

I even added a campaign with 7 main levels & an epic bossfight to show off the functionality, which I think turned out great.

In general, Jonas focused more on parsing & the HUD, while I did rendering & the entity system.

We both had a lot of fun making this project, and learned a lot about splitting work efficiently & creating such a complex program with a heavy focus on efficiency, especially in graphics rendering.

> [!NOTE]
> We have documented this entire process in great detail in the [Changelog](https://github.com/FreddyMSchubert/42_cub3d/blob/master/CHANGELOG.md).

But, well, how does it actually - *work*?

![Boundary](https://github.com/FreddyMSchubert/42_cub3d/blob/master/assets/readme/boundaries/boundary-1.png)

# The Approach / Implementation

## Saving / Loading

We created a nice saving system to allow for the creation of proper progressive levels with increasing difficulty, like the campaign demonstrates. To do this, we save the amount of inventory items the player has, their health and their chosen element into a custom data format in a `save.cubsave` file. This gets loaded at the start of the game and if it's valid, the player can continue right from where they left off.

## Map Generation

This is a mode I was anxious about at the start, but that came together really well. Here's the basic steps:

1. Create a labyrinth
	- Recursively, step through an empty map, always going in a random direction when there are multiple unvisited directions. Once all 3 available directions from your current tile are visited, step back through your path until there is an unvisited direction, and go there, then repeat that until you are right at the start again.
	- This method will create a full labyrinth. But that's neither very fun to explore as it's just an infinite [right-hand-method](https://www.wikiwand.com/en/Maze-solving_algorithm#Hand_On_Wall_Rule) simulator, so let's add some
2. Rooms
	- When you aren't permanently in a cramped space it breaks up the gameplay nicely. This will later be levaraged even more by enemies.
	- These are held in check by the total labyrinth scale, but generally very random.
3. Remove random walls
	- This makes the maze both harder and easier depending on the situation. It turns the maze from something where you can just walk forward and know you've explored everything behind you into an environment where you actually have to build up a complex map of your surroundings in your mind, which is great.
	- It sounds stupid but when I stopped trying to find another smart way to add depth to this map gen system intelligently and just randomly removed some walls it got way more fun. Experimentation is key.
4. Add Entities
	- Entities are not only Enemies, but also the orbs you use to defeat them, and health drops so you can actually sustainably go through some of these randomly generated dungeons.
	- I used a method borrowed from [Spelunky](https://www.wikiwand.com/en/Spelunky) I found in [this video](https://www.youtube.com/watch?v=Uqk5Zf0tw3o) by [GameMakersToolkit / GMTK](https://www.youtube.com/@GMTK), which worked super well. Basically, we go through all the spaces in the map an enemy could be spawned, and check how many walls are in the vicinity. If there are a lot, that means we increase the likelihood of a health drop or an orb (ammo), if there are few, we make enemy spawns likely.
	- This makes it more likely for ammo and health to spawn in corridors, and enemies in the larger rooms. Tweaking the random values, enemies very much still spawn in corridors, but there's a general intuition that enemies spend their time in rooms.
	- Since most corridors are broken up by a room every now and then, this creates a nice micro gameplay loop.
5. The goal, a door and a hidden key
	- We then pick a secluded space where the goal and a door locking it is found. A key is also placed with a similar method to the orbs & health pickups earlier. When no adequate goal spot is found, it is placed randomly & without a door, which can make it either easier or pretty hard to find.

Instead of passing this generated map through to the rest of the program, this segmented off section just writes the maze into it's own file which then gets re-read by the program, allowing for saving, editing and replaying of the custom map, which I've used to create most of the campaign maps, as I really do like how the level generator turned out.

Now, onto the main part.

![Boundary](https://github.com/FreddyMSchubert/42_cub3d/blob/master/assets/readme/boundaries/boundary-2.png)

## Parsing

Parse it.

*Thank you for coming to my TED talk.*

## Validation

Besides basic validations like there only being one player, the texture files being valid & the RGB values being functional, we also do a [flood fill](https://www.wikiwand.com/en/Flood_fill) starting from the player position. If this ever reaches the side of the map or the void, the map is invalid.

## Wall Conversion

There is one very helpful thing we do to make our program run smoother:

***Culling***.

> Here's [more info on culling](https://youtu.be/4O0_-1NaWnY?si=sG17TOvLLpkSwQgH&t=171) in the context of Minecraft.

When looking at the stem of a tree in Minecraft, each log block actually only has 4 sides the game draws, because the top and bottom ones won't be visible anyways. In the example of a tree, this is rather inconsequential, but if Minecraft was to draw all the sides of the stone block in a cave 100 blocks beneath you, your PC would explode.

We culled the wall sides that touched other wall tiles using a twodimensional boolean array. In this process, we also converted the walls to the format we'll be using them in later.

![Boundary](https://github.com/FreddyMSchubert/42_cub3d/blob/master/assets/readme/boundaries/boundary-3.png)

## Game Loop

We created a timing system to lock our program to only update every 30 (or whatever you choose) frames. That way, we don't ever have to worry about enemies moving faster if the program is running faster.

Since the game loop runs every frame, its vital to keep it efficient. One of the ways we have done this is to keep dynamic allocation to a minimum.

### Game logic

First thing we do every frame is to update the game state before rendering.

Here entities get spawned, doors get opened, enemies get killed and health gets picked up.

#### Entities

The entities have a very nice system. Every entity is contained in a single data struct, with all it's data contained. For example, there are three functions passed into that struct when the entity is created:

```
mlx_texture_t	*(*get_texture)(t_entity *self);
void		(*tick)(t_entity *self);
void		(*on_collision)(t_entity *self, t_entity *collider);
```

These three functions will be called at different times by a generic script that handles all entities. Otherwise, handling entities would have been an absolute nightmare and not maintainable in the slightest. I recommend taking a look at the full system.

The tick method of every entity gets called every frame (e.g. for moving / attacking), every entity gets checked for a collision with every other entity ever frame, and the get texture method is called whenever the texture is needed, allowing for dynamic animations based on the entities current state.

> Check out the [template_entity.c](https://github.com/FreddyMSchubert/42_cub3d/blob/master/src/3_game_loop/a_game_logic/entities/template_entity.c) file for more info on the entity system.

In terms of entities we have:

- Blights
	- These fully utilize this entity system, they move around, dodge your shots, and shoot back in their tick method. They deal damage when colliding with the player, and they have 4 dynamic animations created via the get_texture method.
- Elementor (the boss)
	- Basically, a very leveled up blight, but with different attacks, multiple phases and a whole bunch more complex logic.
- Doors
	- Yes, these are entities, more info soon.
	- Doors have two subtypes, the ones with the copper texture will are unlocked, but the ones with the iron texture will require the player to hold a key before opening and staying open.
	- Fun fact: I added the copper doors 1 hour before handing in the project because we didn't realize the subject said that the doors not only had to open but also close again. Stressful stuff.
- Explosion
	- A simple explosion animation that will die right after it's animation is done.
- Goal
	- When it's collision function gets called, the player has won & it displays a win screen.
- Health, Keys, Orbs
	- These lie on the floor or are dropped by enemies or the boss. When picked up, the player collects them into their inventory or gains hearts.
- Projectile
	- These move around using their tick method, dealing damage when colliding with an enemy or player.

> It only took me about 10 minutes to add and test the explosion entity, thanks to the high expandability of this entity system. Without it, this many entities would never have been feasible.

There is an interesting distinction in the entities. Most of them use billboard rendering, meaning they permanently turn to you. This is how it was done in Wolfenstein. But some of them, like our doors, will not turn toward you. Beyond that, the doors use exactly the same functions, even though they seem super different. Nobody would think that the doors and enemies have the same setup except for one toggled boolean, but that just shows how cool this entity system is.

> And yes, we've tried it, and yes, our program handles over 1000 entities firing at you at once pretty well.

#### Player Movement

Every frame we check whether the WASD keys are held down. If so, we move our position based on our rotational vector using simple maths.

> To all 42ers, don't use the MLX provided key hook, it is super choppy. If you want smooth movement and not just one-time inputs (e.g. to close the window using ESC), the key hook wont be helpful, use the loop hook.

But instead of just applying that movement to our positions immediately, we first check whether the new position is valid and not within a wall. This is done in two steps. By doing this check and applying the position on the x and y axis seperately, we allow for wall hugging, where you can still walk while you are technically facing a wall, just slow.

![Boundary](https://github.com/FreddyMSchubert/42_cub3d/blob/master/assets/readme/boundaries/boundary-4.png)

### Rendering

#### Raycasting

> Finally, the meat of the matter. Here's the simplified version:

This whole game is just "fake-3d". All of the calculations we do are done on in a 2d format. The fact it seems to be 3d is the *magic* part.

At the very center, we have a mathematical function that simply takes two vectors and returns the precise intersection point.

Using this, we can shoot a bunch of rays from the player position around the players view.

Every ray will then intersect with a wall. We then do some very cool maths I won't explain here to know exactly how high to draw the wall at the few pixels a given ray is responsible for.

Using the precise intersection point, we can also calculate at what specific spot of a wall we have hit it, allowing us to determine the exact pixel on the texture of that wall we'll need to apply to those pixels.

Since all walls are the same height, we can just work with one wall per ray. But for the entities, we need to raycast every single one and then sort them in order. Otherwise, if there is another entity behind the transparent parts of anther entities texture, it would turn invisible.

This is one of the few times in the program we use allocate heap memory during the game loop, to store and sort the ray-intersected entities. The only other allocated time something gets mallocated is when a new entity is created.

#### Drawing

For the basic wall rendering, the raycasting section did all our work.

Another cool feature we added though is fog, which dynamically tints everything stronger and stronger to a given color, based on the distance from the player. This effect is used in the most striking way in the [mine level from the campaign](https://youtu.be/YGmE1SxFchE?si=QElL8_gvkua2dQRh&t=175). To do this, the color to be rendered is tinted more and more depending on the distance between the player and the intersection point, allowing for e.g. an underwater effect.

Another very cool element of the program is the texture of [elementor, the boss](https://youtu.be/YGmE1SxFchE?si=XPG2pm9XV69Flb7H&t=571). (Last chance for spoilers).

When fighting him, his cloak changes color based on the amount of elements he is currently harnessing. When it is more than one, he will cycle through these elements in a fluid animation.
If we had tried to create this animation like the blight animations, using multiple textures, it would have taken roughly 250 textures for a similar effect. Obviously, thats no what we did.

Instead, for elementors texture, if we are about to draw a pixel for his cloak, instead of putting one of the almost fully transparent pixels of [the actual behind-the-scenes texture](https://github.com/FreddyMSchubert/42_cub3d/blob/master/assets/textures/entities/elementor), we check the pixel of the texture we are currently placing and get the right texture from a function that defines the animation instead.

For the fourth phase, when he harnesses more elements than he is able to sustain and implodes, we just pick between the normal, 4 color animation and a random choice with an increasing likelihood the longer the animation progresses.

And just like that, we have an impressive & unique effect by leveraging in-engine animations.

#### HUD

The minimap draws its spaces with decreasing opacity based on the distance, creating a nice torch / flashlight effect.

![Boundary](https://github.com/FreddyMSchubert/42_cub3d/blob/master/assets/readme/boundaries/boundary-1.png)

## Other interesting elements

- The "garbage collector"
	- is not at all a garbage collector in the traditional sense, it's really just an abstraction for malloc.
	- When we call gc_malloc, it automatically protects the allocation, making the actual usage code a lot cleaner. It immediately appends the newly allocated element to a linked list of all the allocated elements, which gets freed whenever the program exits. This way, when the malloc in gc_malloc fails, it can just print and error message and stop the program, reducing the amount of annoying C generic boilerplate protection code necessary to do basic actions.
	- It's a very safe abstraction, e.g. not appending the same element to the list twice, preventing double-frees.
- Persistent data
	- We save all of our main important data in a function that keeps the struct saved as a static variable, allowing for access anywhere without reducing performance, as the data truly necessary throughout the whole program. We use this to save generic general data, the player data and the garbage collector list.
