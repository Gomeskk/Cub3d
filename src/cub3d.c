/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 21:12:33 by bpires-r          #+#    #+#             */
/*   Updated: 2025/11/30 21:01:15 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_map_line(char c)
{
	if (c == ' ')
		return (1);
	return (ft_strchr("NSEW01", c) != NULL);
}

static void	skip_sp_tb(char *s, int *i)
{
	while (s[*i] && is_space(s[*i]))
		(*i)++;
}

static int	parse_texture(char *s, char **dest)
{
	while (*s && is_space(*s))
		s++;
	if (!*s)
		return (0);
	*dest = ft_strdup(s);
	return (*dest != NULL);
}

static int	is_ident_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && is_space(line[i]))
		i++;
	if (!line[i])
		return (0);
	return (ft_strchr("NSOEAWCF", line[i]) != NULL);
}

static int is_empty_line(const char *s)
{
	if (!s)
		return (1);
	while (*s)
	{
		if (!is_space(*s))
			return (0);
		s++;
	}
	return (1);
}

static int	parse_comp(char *s, int *i, int *out)
{
	int	val;

	if (!s[*i] || !ft_isdigit((unsigned char)s[*i]))
		return (0);
	val = 0;
	while (s[*i] && ft_isdigit((unsigned char)s[*i]))
	{
			val = val * 10 + (s[*i] - '0');
			if (val > 255)
				return (0);
			(*i)++;
	}
	*out = val;
	return (1);
}

int	parse_colour(char *s, int *dest)
{
	int	i;
	int	comp;
	int	rgb[3];
	
	i = 0;
	comp = 0;
	skip_sp_tb(s, &i);
	if (!s[i])
		return (0);
	while (comp < 3)
	{
		skip_sp_tb(s, &i);
		if (!parse_comp(s, &i, &rgb[comp]))
			return (0);
		skip_sp_tb(s, &i);
		if (comp < 2)
		{
			if (s[i] != ',')
				return (0);
			i++;
			skip_sp_tb(s, &i);
			if (!s[i] || !ft_isdigit((unsigned char)s[i]))
				return (0);
		}
		else
		{
			skip_sp_tb(s, &i);
			if (s[i])
				return (0);
		}
		comp++;
	}
	*dest = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	return (1);
}

int	parse_identifiers(t_cub3d *data)
{
	int		i;
	char	*line;

	data->textures.no = NULL;
	data->textures.so = NULL;
	data->textures.ea = NULL;
	data->textures.we = NULL;
	data->textures.floor = -1;
	data->textures.ceiling = -1;
	i = 0;
	if (!data->map.map)
		return (0);
	while (data->map.map[i] && is_empty_line(data->map.map[i]))
		i++;
	while (data->map.map[i] && (is_ident_line(data->map.map[i]) || is_empty_line(data->map.map[i])))
	{
		line = data->map.map[i];
		if (is_empty_line(line))
		{
			i++;
			continue ;
		}
		while (*line && is_space(*line))
			line++;
		if (!*line)
		{
			i++;
			continue ;
		}
		if (!ft_strncmp(line, "NO", 2) && is_space(line[2]))
		{
			if (data->textures.no || !parse_texture(&line[2], &data->textures.no))
			{
				ft_putendl_fd(INV_NO, 2);
				exit(127);
			}
		}
		else if (!ft_strncmp(line, "SO", 2) && is_space(line[2]))
		{
			if (data->textures.so || !parse_texture(&line[2], &data->textures.so))
			{
				ft_putendl_fd(INV_SO, 2);
				exit(127);
			}
		}
		else if (!ft_strncmp(line, "EA", 2) && is_space(line[2]))
		{
			if (data->textures.ea || !parse_texture(&line[2], &data->textures.ea))
			{
				ft_putendl_fd(INV_EA, 2);
				exit(127);
			}
		}
		else if (!ft_strncmp(line, "WE", 2) && is_space(line[2]))
		{
			if (data->textures.we || !parse_texture(&line[2], &data->textures.we))
			{
				ft_putendl_fd(INV_WE, 2);
				exit(127);
			}
		}
		else if (!ft_strncmp(line, "C", 1) && is_space(line[1]))
		{
			if (data->textures.ceiling != -1 || !parse_colour(&line[1], &data->textures.ceiling))
			{
				ft_putendl_fd(INV_CEILING, 2);
				exit(127);
			}
		}
		else if (!ft_strncmp(line, "F", 1) && is_space(line[1]))
		{
			if (data->textures.floor != -1 || !parse_colour(&line[1], &data->textures.floor))
			{
				ft_putendl_fd(INV_FLOOR, 2);
				exit(127);
			}
		}
		i++;
	}
	if (!data->textures.no || !data->textures.so || !data->textures.we || !data->textures.ea || data->textures.ceiling == -1 || data->textures.floor == -1)
		return (0);
	while (data->map.map[i] && is_empty_line(data->map.map[i]))
        i++;
	data->map.start = i;
	return (1);
}

static void	copy_line(char **dest, char *src, int max_x)
{
	int	i;

	i = 0;
	while (i < max_x)
	{
		if (i < (int)ft_strlen(src))
		{
			if (src[i] == '\t')
				(*dest)[i] = ' ';
			else
				(*dest)[i] = src[i];	
		}
		else
			(*dest)[i] = ' ';
		i++;
	}
	(*dest)[i] = '\0';
}

static char	**build_grid(t_cub3d *data)
{
	int		i;
	int		r;
	char	**grid;

	i = 0;
	r = 0;
	grid = malloc(sizeof(char *) * (data->map.row_count + 1));
	if (!grid)
		return (NULL);
	while (i < data->map.row_count)
	{
		grid[i] = malloc(data->map.col_count + 1);
		if (!grid[i])
		{
			while (--i >= 0)
                free(grid[i]);
            free(grid);
			return (NULL);
		}
		i++;
	}
	grid[data->map.row_count] = NULL;
	while (r < data->map.row_count)
	{
		//copia a linha e coloca ' ' no lugar do que falta ate atingir o data->map.col_count
		//para criar uma grid rectangular :D
		copy_line(&grid[r], data->map.map[data->map.start + r], data->map.col_count);
		r++;
	}
	return (grid);
}

static void	check_spawn(t_cub3d *data, char c, int x, int y)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		data->map.start_point++;
		data->player.pos_x = x;
		data->player.pos_y = y;
	}
}

static int	validate_map_chars(t_cub3d *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map.row_count)
	{
		x = 0;
		//alterar nome de col count e row count para max_x e max_y
		while (x < data->map.col_count)
		{
			if (!is_map_line(data->map.grid[y][x]))
				return (0);
			check_spawn(data, data->map.grid[y][x], x, y);
			x++;
		}
		y++;
	}
	return (1);
}
static int has_space_neighbor(char **g, int r, int c)
{
	if (g[r - 1][c] == ' ')
		return (1);
	if (g[r + 1][c] == ' ')
		return (1);
	if (g[r][c - 1] == ' ')
		return (1);
	if (g[r][c + 1] == ' ')
		return (1);
	return (0);
}

static int	is_closed(t_cub3d *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->map.row_count)
	{
		x = 0;
		while (x < data->map.col_count)
		{
			if (data->map.grid[y][x] == '0' || data->map.grid[y][x] == 'N' || data->map.grid[y][x] == 'S'
				|| data->map.grid[y][x] == 'E' || data->map.grid[y][x] == 'W')
			{
				if (y == 0 || y == data->map.row_count - 1 || x == 0 || x == data->map.col_count - 1)
					return (0);
				if (has_space_neighbor(data->map.grid, y, x))
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	parse_map(t_cub3d *data)
{
	data->map.start_point = 0;
	if (!data->map.map || !data->map.map[data->map.start])
		return (0);
	data->map.row_count = 0;
	data->map.col_count = 0;
	//get max len NON RECTANGULAR MAP >:C
	while (data->map.map[data->map.start + data->map.row_count])
	{
		if ((int)ft_strlen(data->map.map[data->map.start + data->map.row_count]) > data->map.col_count)
			data->map.col_count = ft_strlen(data->map.map[data->map.start + data->map.row_count]);
		data->map.row_count++;
	}
	//creating rectangular map #retangulo #espaçosparaomax_x
	data->map.grid = build_grid(data);
	if (!data->map.grid)
		return (0);
	//scan pelo mapa para validaçao e spawn
	if (!validate_map_chars(data)
		|| data->map.start_point != 1
		|| !is_closed(data))
		return (0);
	return (1);
}

void print_rgb(int color)
{
    int r = (color >> 16) & 0xFF;
    int g = (color >> 8) & 0xFF;
    int b = color & 0xFF;

    printf("R: %d, G: %d, B: %d\n", r, g, b);
}

void print_grid(char **grid)
{
    int i = 0;

    if (!grid)
    {
        printf("(grid is NULL)\n");
        return;
    }
    while (grid[i])
    {
        printf("[%d] \"%s\"\n", i, grid[i]);
        i++;
    }
}

int	main(int argc, char **argv)
{
	t_cub3d	data;
	
	if (argc != 2)
		return (ft_putendl_fd(WRONG_ARGC, 2), 1);
	if (!check_map_name(argv[1]))
		return (ft_putendl_fd(WRONG_MAP_NAME, 2), 1);
	if (!read_map(argv[1], &data))
		return (free_all(&data), ft_putendl_fd(MAP_ERROR, 2), 1);
	if (!parse_identifiers(&data))
		return (free_all(&data), ft_putendl_fd(NO_IDENTIFIERS, 2), 1);
	if (!parse_map(&data))
		return (free_all(&data), ft_putendl_fd(WRONG_MAP, 2), 1);
	printf("Ceiling Hexa: %x\nCeiling RGB = ", data.textures.ceiling);
	print_rgb(data.textures.ceiling);

	printf("Floor Hexa: %x\nFloor RGB = ", data.textures.floor);
	print_rgb(data.textures.floor);
	print_grid(data.map.grid);
	//free function create
	free_all(&data);
	//free_ar((void **)data.map.map);
}

/*
printf("Ceiling RGB = ");
print_rgb(data.textures.ceiling);

printf("Floor RGB = ");
print_rgb(data.textures.floor);
*/