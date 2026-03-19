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

## Menu UI

The menu UI system provides a complete graphical interface for game configuration and navigation before entering gameplay. It features custom-drawn sprites, double-buffered rendering, and a hierarchical navigation system.

### Menu Architecture

**Screen States:**
- `MAIN_MENU` - Primary menu with Start/Options/Credits
- `DIFFICULTY_SCREEN` - Difficulty selection (Easy/Medium/Hard)
- `SKIN_SELECT_SCREEN` - Player skin customization
- `OPTIONS_SCREEN` - Settings configuration
- `CREDITS_SCREEN` - Developer credits display

**Double Buffering System:**
All menu elements are rendered to an off-screen buffer (`screen_buffer`) before being displayed. This prevents flickering and allows for complex compositing operations including alpha-channel transparency.

### Navigation System

The menu uses a state machine approach with distinct handlers for each screen:

```c
// Example: Main menu navigation
- Up/Down arrows or W/S: Cycle through options
- Enter: Select current option
- ESC: Exit game or return to previous screen
```

Each menu screen maintains its own:
- Current selection index
- Rendering function
- Input handler
- State transition logic

**Tab Navigation:**
The tab key cycles through different option sections, particularly useful in the Options menu where users can navigate between Sound, Controls, and Display settings.

### Options & Settings

**Configurable Parameters:**

1. **Sensibility** (5 levels: 0-4)
   - Controls mouse rotation speed
   - Converts to movement multiplier (0.0x to 2.0x)
   - Level 0: No rotation, Level 2: Default (1.0x), Level 4: Double speed (2.0x)

2. **Difficulty** (3 modes)
   - Easy: 0.60x enemy speed and vision
   - Medium: 1.0x baseline difficulty
   - Hard: 1.25x enemy speed and vision
   - Applied dynamically to all active enemies

3. **Volume** (Audio level control)
   - Visual indicator with level bars
   - Saved across menu sessions

4. **Resolution** (Dynamic screen size)
   - Changes window dimensions in real-time
   - Confirmation dialog to prevent accidental changes
   - Rebuilds all menu images at new resolution

### Image Management

**Image Loading:**
- All menu images loaded from `Png_images/` directory
- Categories: StartGame, Difficulty, Options, SkinSelection, Credits
- Uses MiniLibX XPM format for transparency support

**Transparency Rendering:**
Custom alpha-blending implementation using **bitshifting**:
- Extracts RGB channels from source and destination
- Blends colors based on alpha value
- Optimized for real-time menu rendering

```c
// Transparency overlay: menu elements drawn over backgrounds
// Prevents hard edges and allows layered UI composition
```

### Resolution System

**Dynamic Resize Flow:**
1. User adjusts resolution slider in Options
2. Arrow direction tracking for visual feedback
3. Confirmation dialog appears
4. If confirmed:
   - All XPM images reloaded at new dimensions
   - Screen buffer recreated
   - Menu state preserved across resize
5. If cancelled: reverts to previous resolution

**Resolution Confirmation:**
- Prevents accidental window size changes
- Two-step process: adjust → confirm
- Clear visual feedback during selection

### Menu Rendering

**Render Pipeline:**
1. Clear screen buffer
2. Draw background image
3. Composite foreground elements with transparency
4. Apply highlights to selected options
5. Display buffer to window

**Visual Feedback:**
- Selected menu items highlighted
- Arrow indicators for multi-choice options
- Real-time preview of settings changes
- Smooth state transitions

### Input Handling

**Keyboard Input:**
- Arrow keys / WASD: Navigation
- Enter: Confirm selection
- ESC: Back/Exit
- Tab: Switch option sections

**Input Loop:**
The menu runs in a separate event loop from gameplay, processing inputs through screen-specific handlers. Each screen's input function returns control flow instructions (continue menu, start game, exit, etc.).

> [!example] Summary
> The menu UI provides a complete pre-game interface with customizable settings, smooth navigation, and professional visual presentation using double-buffering and custom transparency rendering.

## Texture Mapping

The texture mapping system transforms flat 2D images (XPM files) onto 3D wall surfaces, creating the illusion of depth and detail. This involves loading textures, selecting the correct face based on ray collision, and sampling pixels based on where the ray hit the wall.

### Texture Loading

**XPM Format:**
All wall textures are loaded from XPM (X PixMap) files using MiniLibX:
- North, South, East, West walls (from `.cub` file)
- Door texture (`Png_images/Walls/Door.xpm`)
- Button texture (`Png_images/Walls/Button.xpm`)

**Loading Process:**
```c
// Each texture is loaded with:
1. mlx_xpm_file_to_image() - creates image from file
2. mlx_get_data_addr() - retrieves pixel buffer
3. Stores: width, height, bits per pixel, size_line, endian
```

Each texture becomes a `t_img` structure containing:
- Image pointer (for MiniLibX)
- Pixel data buffer (direct memory access)
- Dimensions (width × height in pixels)
- Metadata (bpp, size_line, endian)

### Face Detection

**Directional Texture Selection:**
The system automatically selects the correct wall texture based on which side the ray hit:

**Hit Priority:**
1. **Button surfaces** - If ray hits a 'B' tile
2. **Door surfaces** - If ray hits a 'D' tile
3. **Directional walls** - Based on ray side and step direction:
   - X-side hit + positive step → West texture
   - X-side hit + negative step → East texture
   - Y-side hit + positive step → North texture
   - Y-side hit + negative step → South texture

This ensures each wall face shows the appropriate texture regardless of viewing angle.

### Wall Hit Position (wall_x)

**Calculating Exact Hit Point:**
When a ray hits a wall, we need to know **where along the wall face** it hit (horizontal position on the wall surface).

```c
// For X-side hits: use Y coordinate progression
wall_x = player.pos_y + perp_wall_dist * ray_dir_y

// For Y-side hits: use X coordinate progression
wall_x = player.pos_x + perp_wall_dist * ray_dir_x
```

**Fractional Part Extraction:**
```c
wall_x -= floor(wall_x);  // Keep only 0.0 to 1.0
```

This gives us a normalized position (0.0 to 1.0) representing how far across the wall face the hit occurred. A wall_x of 0.25 means the ray hit at 25% across the wall surface.

### Texture Coordinate Mapping

**Horizontal Mapping (tex_x):**
Converts the wall hit position into a texture column:

```c
tex_x = (int)(wall_x * texture_width)
```

**Texture Mirroring:**
Certain wall orientations need horizontal flipping for correct appearance:
- West walls (ray coming from left)
- South walls (ray coming from top)

```c
if (needs_mirror)
    tex_x = texture_width - tex_x - 1;
```

This prevents textures from appearing reversed when viewed from different angles.

**Vertical Mapping (tex_y):**
Uses a **stepping system** to sample the correct vertical position in the texture:

```c
// Calculate vertical step per screen pixel
step = texture_height / line_height

// Initialize starting position (accounts for pitch and z_offset)
tex_pos = (draw_start - pitch - z_offset + wall_center_offset) * step

// For each screen Y pixel:
tex_y = (int)tex_pos
tex_pos += step
```

### Vertical Texture Stepping

**Why Stepping?**
A wall might be rendered as 200 pixels tall on screen, but the texture might be only 64 pixels tall. The step value determines how much to advance through the texture per screen pixel.

**Step Calculation:**
```c
step = (double)texture_height / (double)line_height
```

Examples:
- 64px texture, 200px wall → step = 0.32 (slow texture scroll)
- 64px texture, 32px wall → step = 2.0 (fast texture scroll)

**Accounting for Camera Effects:**
The initial texture position adjusts for:
1. **Pitch** - Looking up/down shifts texture sampling
2. **Z-offset** - Jumping/crouching vertically offsets the viewport
3. **Wall centering** - Aligns texture middle with screen middle

### Modulo Wrapping

**Handling Texture Overflow:**
When pitch or z_offset push sampling beyond texture bounds, modulo wrapping keeps coordinates valid:

```c
tex_y = tex_y % texture_height;
if (tex_y < 0)
    tex_y += texture_height;  // Handle negative values
```

This allows unlimited camera pitch and jumping without texture coordinate errors.

### Pixel Sampling

**Direct Memory Access:**
Instead of slow pixel-by-pixel API calls, the renderer reads directly from texture memory:

```c
// Calculate byte position in texture buffer
row_offset = tex_y * size_line
col_offset = tex_x * (bpp / 8)
pixel_address = texture_data + row_offset + col_offset

// Read color value (32-bit ARGB)
color = *(unsigned int *)pixel_address
```

**Bounds Safety:**
Before sampling, coordinates are validated:
```c
if (x < 0 || x >= width || y < 0 || y >= height)
    return 0x000000;  // Return black for out-of-bounds
```

### Rendering Pipeline

**Per-Column Texture Rendering:**
For each screen column `x` from `draw_start` to `draw_end`:

1. Select appropriate wall texture (face detection)
2. Calculate `tex_x` from wall hit position
3. Initialize `tex_pos` with offset adjustments
4. Loop through screen Y pixels:
   - Calculate `tex_y` from current `tex_pos`
   - Wrap `tex_y` with modulo
   - Sample texture pixel at (`tex_x`, `tex_y`)
   - Draw pixel to screen at (`x`, `y`)
   - Increment `tex_pos` by `step`

### Special Textures

**Interactive Elements:**
- **Doors** - Render door texture when hitting 'D' tiles
- **Buttons** - Render button texture when hitting 'B' tiles
- Priority system ensures correct texture even if multiple types overlap

**Texture Swapping:**
The system supports runtime texture swapping:
```c
data->wall_textures.textures_swapped = 0;  // Can toggle alternative textures
```

This allows for dynamic texture changes during gameplay (alternate skins, damage states, etc.).

> [!example] Summary
> Texture mapping converts wall ray hits into pixel-perfect textured columns by calculating precise hit positions (wall_x), mapping them to texture coordinates (tex_x, tex_y), and sampling with adjustments for camera pitch, jumping, and wall orientation. The system handles face detection, mirroring, modulo wrapping, and direct memory access for optimal performance.
