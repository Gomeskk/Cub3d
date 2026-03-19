This project has been created as part of the 42 curriculum by [bpires-r], [joafaust].

# Cub3d

## Description

Cub3d is a graphics project that introduces you to raycasting, a rendering technique that creates a 3D perspective from a 2D map. Inspired by the groundbreaking game Wolfenstein 3D, this project challenges you to build your own simplified 3D game engine from scratch.

The program parses a scene description file (`.cub`) containing:

- Map layout
- Wall textures
- Floor and ceiling colors
- Player starting position and orientation

Using this information the engine casts rays from the player’s point of view and renders textured walls, creating a first-person perspective inside the map.
This project focuses on:

## Features

- Personal sprites drawn, ilustrated and designed by us (we tried :C)
- DDA raycasting 3D renderer
- Event handling
- Textured walls with face detection
- Floor and ceiling RGB colors usign **bitshifting**
- Strict .cub parser and validator
- Closed map and spawn checks
- Keyboard + mouse movement/rotation
- Sprint, crouch and jump camera offsets
- Minimap with player direction and field vision
- Interactive doors, buttons and FOV
- Enemy sprites with depth occlusion - closer object wins, farther object gets occluded (hidden)
- Enemy sprites animation with a shinning effect using **bitshifting**
- Flashlight post-process shading using **bitshifting**
- In-game menu with settings
- FPS counter

## Project Structure

- `inc/` -> headers, structs and defines
- `src/` -> main game source code
- `src/parser/` -> map and identifiers parser
- `src/raycaster/` -> DDA, rays and wall drawing
- `src/player/` -> movement, rotation and collisions
- `src/features/` -> doors, enemies, minimap, flashlight
- `src/textures/` -> texture loading and sampling
- `src/menu_ui/` -> menu navigation and rendering
- `maps/` -> test and example `.cub` maps
- `Png_images/` -> game/menu/wall assets
- `complete_lib/` -> libft, printf, gnl and MiniLibX graphics library

## Instructions

### Compilation

1. Clone the repository
2. Make inside the repository
   This will compile the project and create the executable: ./cub3d

### Execution

Run the program with a valid `.cub` map file:
./cub3D maps/example.cub
**Map File Format (.cub)**
The configuration file must contain:

- Texture paths for each wall direction
- Floor and ceiling colors (RGB)
- A closed map layout
- One player start position (N/S/E/W)

> [!example]
> NO textures/north.xpm
> SO textures/south.xpm
> WE textures/west.xpm
> EA textures/east.xpm
> F 220,100,0
> C 225,30,0
>
> 111111
> 100001
> 10N001
> 100001
> 111111

If you want to test the parsing you can try breaking these rules:

**Error Handling**
For the Error handling you can also check `defines.h` which is where all our error handle macros are.
The program validates:

- Map enclosure
- Valid characters
- Single player start
- Texture path accessibility
- Correct color format
- Duplicate or missing identifiers
- WIPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP

On error, the program exits with an error message.
For more information on the parsing you can also check the **Parsing** section in this README.

### Controls

| Key             | Action                 |
| --------------- | ---------------------- |
| W - up arrow    | Move forward           |
| S - down arrow  | Move backward          |
| A - left arrow  | Move left              |
| D - right arrow | Move right             |
| space           | Jump                   |
| ← / → - mouse   | Rotate camera          |
| ctrl            | Crouch                 |
| left shift      | Sprint                 |
| tab             | next selection - menu  |
| F               | Flashlight             |
| V               | FOV change             |
| ESC             | Exit program / go back |

## Resources

This is where I share my tools used for learning in this project. Every Highlited word will be a direct link for the reference used.

Keeping in mind that some learning resources came from bpires-r's job - SHARKCODERS.
SHARKCODERS is a coding school so I, (bpires-r), used a lot of my learnings and teachings through the gameDev courses I lecture to apply here.

### Raycasting && Graphics

- How [Raycast](https://youtu.be/yds-8Ii0wSM "Visual Reference") is Visualized.

- How [Raycast](https://lodev.org/cgtutor/raycasting.html) works through the Raycasting Documentation

- How [Raytracing](https://youtu.be/H5TB2l7zq6s "Raytracing") works.

- What is [Euclidean Geometry](https://en.wikipedia.org/wiki/Euclidean_space) and studies around it.

### MiniLibX

- 42 MiniLibX documentation inside [42 Docs](https://harm-smits.github.io/42docs/libs/minilibx "42 Docs MinilibX")

### Mathematics

- Introduction to [Linear Algebra](https://en.wikipedia.org/wiki/Linear_algebra "Linear Algebra")

- [Tranformation Matrix](https://en.wikipedia.org/wiki/Transformation_matrix) and [Rotation](<https://en.wikipedia.org/wiki/Rotation_(mathematics)> "rotation")

- The [DDA Algorythm](https://www.youtube.com/watch?v=W5P8GlaEOSI)

- [Calculus Introduction](https://www.youtube.com/watch?v=WsQQvHm4lSw&t=183s)

- [Camera Bob](https://developer.valvesoftware.com/wiki/Camera_Bob) for the Hands motion.

## AI Usage Disclosure

AI tools were used during the development of this project for:

- Research on harder topics for our best understanding

All final code was written, reviewed, tested, and validated manually.

# Implementation

## Technical Choices

- Raycasting using DDA algorithm
- Blah blah blah

## Parser

The parser is done in two simple parts:

1. Read and validate identifiers (`NO`, `SO`, `WE`, `EA`, `F`, `C`)
2. Read and validate the map grid

### Simple parser flow

1. Check if file is `.cub`

- If not, parser exits with error.

2. Read the file line by line

- Store all lines in memory for validation.

3. Parse identifiers first

- Accept texture paths and floor/ceiling colors.
- Reject duplicates and missing identifiers.
- Parse RGB as `R,G,B` in range `0-255`.

4. Build the map grid

- Everything after identifiers is treated as map.
- Short lines are padded with spaces.
- Tabs are normalized into spaces.

5. Validate map rules

- Allowed chars: `0 1 N S E W D B F` and spaces.
- Map must be closed by walls.
- Must have exactly one player spawn (`N/S/E/W`).

6. Final parser setup

- Spawn is saved and converted to floor internally.
- Doors, buttons and enemies are initialized from map markers.

> [!example] Resume
> The parser first validates config (textures + colors), then validates world (map + spawn + closure).
> If any rule fails, it exits with a clear error message.

## Player Movement/Direction

**Direction Vector System Overview**

The player direction system uses **unit vectors** to represent where the player is facing. Instead of just storing an angle, it stores two components:

- `dir_x`: horizontal component of direction (-1 to 1)
- `dir_y`: vertical component of direction (-1 to 1)

**Math Explanation:**

- **Unit vectors**: Each direction vector has a magnitude of 1 (√(dir_x² + dir_y²) = 1)
  - 0 - no vertical/horizontal movement
  - 1 - pointing right/down
  - -1 - pointing left/up
- **Coordinate system**: In computer graphics, Y increases downward, so "up" is negative Y
- **Angle storage**: The angle is stored in radians for trigonometric calculations

In C the `sin` and` cos` will use radian values. So instead of 0-360 degrees it will be it's 0 to 2π.![[degrees to radians.png]]
This we just looked into is the player direction initial setup now let's go into the mouse rotation.

The rotation uses the **2D rotation matrix** formula:

```C
static void rotate_player(t_cub3d *data, double angle)
{
    double old_dirx = data->player.dir_x;
    double old_diry = data->player.dir_y;

    // 2D Rotation Matrix Application:
    data->player.dir_x = old_dirx * cos(angle) - old_diry * sin(angle);
    data->player.dir_y = old_dirx * sin(angle) + old_diry * cos(angle);
}
```

In [linear algebra](https://en.wikipedia.org/wiki/Linear_algebra "Linear algebra"), a **rotation matrix** is a [transformation matrix](https://en.wikipedia.org/wiki/Transformation_matrix "Transformation matrix") that is used to perform a [rotation](<https://en.wikipedia.org/wiki/Rotation_(mathematics)> "Rotation (mathematics)") in [Euclidean space](https://en.wikipedia.org/wiki/Euclidean_space "Euclidean space").

The rotation matrix formula for rotating a point by angle θ is:

- x' = x _ cos(θ) - y _ sin(θ)
- y' = x _ sin(θ) + y _ cos(θ)

> [!example] Meaning
> The ' in x and y means x/y after the transformation or new x/y.
> x-prime
> y-prime

So:

- new*x = old_x * cos(θ) - old*y * sin(θ)
- new*y = old_x * sin(θ) + old*y * cos(θ)

**Mouse Distance Calculation:**
**\*How it works:**

- Calculates how far mouse is from screen center
- Converts distance to rotation speed
- Resets mouse to center after each rotation
- Applies rotation to direction vectors (dir and plane)

**Movement System**

The movement system uses the direction vectors for different types of movement.
To get perpendicular direction (90° clockwise rotation):

- If current facing direction is (x, y), then perpendicular direction for strafing is (y, -x)
- This comes from the 90° rotation matrix: `[0 to -1;1 to 0]`

## Raycasting

> [!example] The Basic Idea
> The basic idea of raycasting is as follows: the map is a 2D square grid, and each square can either be 0 (= no wall), or a positive value (= a wall with a certain color or texture).

Some raycasters work with Euclidean angles to represent the direction of the player and the rays, and determinate the Field Of View with another angle.

Instead of using only Euclidean angles for each ray, this implementation follows the vector + camera plane approach:

- Player position: `(pos_x, pos_y)`
- Forward direction: `(dir_x, dir_y)`
- Camera plane (perpendicular to direction): `(plane_x, plane_y)`

That gives us a stable and clean way to project the full field of view.

### Before actual raycasting

For each screen column `x`:

- Convert `x` to camera space:
  `camera_x = 2 * x / screen_width - 1`
- Build ray direction:
  `ray_dir = dir + plane * camera_x`
- Convert player world position to map space:
  `map_x = (int)(pos_x / tile)` and `map_y = (int)(pos_y / tile)`

This is the setup step before DDA starts walking the map.

### my implementation

1. Initialize ray values

- Compute `camera_x`, `ray_dir_x`, `ray_dir_y`.
- Compute `delta_dist_x = |1 / ray_dir_x|` and `delta_dist_y = |1 / ray_dir_y|`.

2. Setup DDA start distances

- Decide `step_x` and `step_y` from ray direction sign.
- Compute initial `side_dist_x` and `side_dist_y`.

3. Run DDA loop

- Compare `side_dist_x` and `side_dist_y`.
- Advance in the smallest one (x-side hit or y-side hit).
- Move map cell by `step_x` or `step_y`.
- Stop when we hit blocking content.

4. Hit rules used in this project

- `1` blocks always.
- `D` blocks only if the door is closed.
- `B` (button tile) is also treated as hit for rendering.
- Out-of-bounds also ends the ray safely.

5. Compute perpendicular distance

- If last step hit an x-side, use x-side distance equation.
- If last step hit a y-side, use y-side distance equation.

This is the anti-fisheye part because we use perpendicular distance to the camera.

6. Project wall height to screen

- `line_height` is inversely proportional to distance.
- Add vertical offsets from pitch and jump/crouch (`z_offset`).
- Bounds `draw_start` and `draw_end` to visible screen.

7. Paint one full column

- Draw ceiling color from top until wall start.
- Draw textured wall segment between start/end.
- Draw floor color from wall end to bottom.

8. Save depth and finish frame

- Store `perp_wall_dist` in `z_buffer[x]`.
- After all columns, render enemies with depth test against z-buffer.
- Apply flashlight shading as final post-process.

### Studied documentation vs my implementation

1. Concept from docs

- Classic tutorials describe grid DDA raycaster with one ray per screen column.
- My implementation matches this directly.

2. Camera model

- Docs suggest direction + camera plane vectors (instead of per-ray angle trig every time).
- My code uses this exact approach with `dir` and `plane`.

3. DDA collision rule

- Docs usually stop only at walls.
- My version extends it with gameplay cells: closed doors and buttons.

4. Projection math

- Docs project wall height from perpendicular distance.
- My version does that, plus pitch and vertical offsets for jump/crouch && looking up/down.

6. Depth handling

- Docs commonly introduce z-buffer for sprites.
- My renderer stores per-column depth and uses it for enemy occlusion.

> [!example] Resume
> Studied version: classic Wolf3D DDA raycaster.
> My version: same mathematical base, but adapted to game features (doors, buttons, enemies, pitch/jump offsets, and flashlight post effect).

## Enemies

### Enemy idea

The enemy is marked as F in the map and is a sprite "AI" entity with 2 behaviour states:

1. Patrol mode: moves Left-Right in a precomputed horizontal lane based on free space to walk on (basically collisions with walls, buttons and doors)
2. Chase mode: once player enters the vision/listening radius, the enemy caughts their presence and starts following the player with collision checks.

### Full enemy flow (simple)

1. Parse map and find all `F` tiles

- `F` means enemy spawn point in the map file.
- We count how many there are and allocate an enemy array with exact size.

2. Save enemy data

- Store spawn grid position (`grid_x`, `grid_y`).
- Compute patrol limits (`patrol_min`, `patrol_max`) by scanning left/right on the same row.
- Set enemy speed and vision radius (scaled by difficulty).
- Replace map `F` with `0` because runtime enemy now lives in `map.enemies[]`.

3. Convert grid spawn to world position

- Runtime movement/rendering uses pixel/world coordinates (`pos_x`, `pos_y`).
- Position is centered in tile: `grid * tile + tile/2`.

4. Every game frame

- `update_enemies(dt)`:
  - if `chasing == 0` -> patrol
  - if `chasing == 1` -> chase player
- `check_enemy_detection()`:
  - if player is close enough, set `chasing = 1`
- `check_enemy_collision()`:
  - if too close to player, game over

5. Render frame

- Raycast walls first and fill `z_buffer`.
- Sort enemies by distance (far -> near).
- Project each enemy sprite to screen.
- Draw only if enemy depth is in front of wall depth (`z_buffer` check).

### Patrol logic

Enemy patrol is horizontal (X axis only) between two precomputed limits.

- `new_x = pos_x + dir * speed * dt`
- if reached min/max limit:
  - flip direction (`dir *= -1`)
  - clamp position to limit

`dir` is either `+1` (right) or `-1` (left).

### Chase logic

We compute vector from enemy to player:

- `dx = player_x - enemy_x`
- `dy = player_y - enemy_y`

Distance:

```C
dist = sqrt(dx * dx + dy * dy);
```

If distance is almost zero, return early to avoid division issues.

Normalize direction (unit vector):

```C
u_x = dx / dist;
u_y = dy / dist;
```

Frame movement:

```C
new_x = enemy_x + u_x * speed * dt
```

```C
new_y = enemy_y + u_y * speed * dt
```

This gives constant speed independent of distance and FPS.

### Why `dt` is used everywhere

`dt` = delta time (seconds since last frame).

- With `dt`, movement is frame-rate independent.
- Without `dt`, same code moves faster on higher FPS and slower on lower FPS.

### Enemy collision checks (map)

Enemy movement only enters valid cells:

- blocks on `1` (wall)
- blocks on `B` (button tile)
- blocks on closed `D` door
- allows open `D` door

This is why enemies do not pass through solid geometry.

### Detection + game over radii

Both use Euclidean distance in world units.

Detection:

```C
dist < vision_radius * tile
```

Game over collision:

```C
dist < ENEMY_COLLISION_RADIUS * tile
```

Simple meaning: one radius is "enemy sees you", another smaller radius is "enemy caught you".

### Enemy projection math (render)

After sorting by distance, each enemy is projected into camera space.

1. Relative sprite position from player:

- `sx = enemy_x - player_x` (in tile units)
- `sy = enemy_y - player_y`

2. Transform to camera space using inverse camera matrix:

- `tx` = left/right position on screen space
- `ty` = depth in front of camera

If `ty <= 0`, sprite is behind camera, so skip.

3. Screen placement:

- `screen_x` comes from `tx/ty`
- sprite `height` is proportional to `1/ty`

Near enemy => bigger sprite.
Far enemy => smaller sprite.

### Depth occlusion (why enemies hide behind walls)

For each screen stripe of the sprite, compare:

- enemy depth `ty`
- wall depth `z_buffer[stripe]`

Draw sprite stripe only if enemy is closer than wall.

That is the exact reason occlusion works.

### Animation + hue effect (simple)

Enemy texture frame:

- `frame = (time * ENEMY_ANIM_FPS) % frame_count`

Hue shift:

- only selected blue-ish pixels are tinted
- target RGB and mix are generated from smooth `sin()` waves
- original color is blended toward animated target color

This creates the shiny animated enemy effect without recoloring everything.

### Difficulty scaling

Difficulty multiplier affects:

- enemy speed
- enemy vision radius
- chase speed still multiplies with chase constant

So difficulty changes both pressure (speed) and detection range.

> [!example] Resume
> Enemy system = spawn from map markers -> patrol/chase AI with distance math -> collision checks -> sprite projection + depth test render.
> Main math ideas are: Euclidean distance, vector normalization, delta-time movement, and perspective scaling (`1/depth`).

## Texture Mapping

vai gomes :D
