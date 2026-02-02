#### 02/01/26

*__TO DO__*
	º Estudar *Raycast*
	º Análise de implementação de acordo com a atual implementação de movimento diagonal (diagonal factor)
	º Inicío de implementação de *Raycast*

-[[Cube3d Parser]]
-[[Cub3d Player Movement]]
-[[Raycast]]


## WHAT I NEED FOR RAYCASTER
#### _Before Actual Raycasting_
##### 1. **Player Direction & Plane Vectors**

My player currently only has position. For raycasting, I need:

- **Direction vector** (where player is looking)
- **Camera plane vector** (perpendicular to direction, determines field of view)

These are typically stored as `dir_x`, `dir_y`, `plane_x`, `plane_y` in your player structure.

#### _Actual Raycasting_
##### 2. **Ray Calculation Loop**

The main raycasting happens in a loop from x = 0 to screen width:

- For each screen column (x), calculate a ray direction
- Cast the ray into the map using DDA to find wall hits
- Calculate wall distance and height to draw

##### 3. **DDA Algorithm Needs Modification**

Current DDA draws pixels along a line. For raycasting, you need DDA that:

- Steps through map grid squares
- Checks each square for walls ('1' in your map)
- Stops when hitting a wall and returns the distance

##### 4. **Wall Rendering**

Once we have the distance to a wall:

- Calculate wall height on screen based on distance
- Draw a vertical line from floor to ceiling
- Apply textures (xuxu job)

## Step-by-Step Starting Approach

- [ ] **Phase 1: Basic Ray Structure**

1. Add direction and plane vectors to `t_player` structure
2. Initialize these based on the starting direction (N, S, E, W from themap)

- [ ] **Phase 2: Single Ray**

1. Modify DDA to detect wall collisions instead of drawing pixels
2. Cast one ray (screen center) and print the distance - this validates DDA

- [ ] **Phase 3: Full Raycasting**

1. Loop through all screen columns
2. For each column, calculate ray direction
3. Use DDA to find wall distance
4. Draw vertical wall slice

- [ ] **Phase 4: Textures & Optimization**

1. Add texture rendering to walls
2. Add floor/ceiling colors
3. Optimize performance

Current `draw_minimap` function is perfect for debugging - you can overlay rays on it to visualize what our raycasting is doing!

## _REFERENCES_

RAYCAST X RAYTRACING
https://youtu.be/yds-8Ii0wSM
https://youtu.be/H5TB2l7zq6s

RAYCAT
https://youtu.be/gYRrGTC7GtA
https://youtu.be/PC1RaETIx3Y
https://www.youtube.com/watch?v=NbSee-XM7WA&t=12s DDA

