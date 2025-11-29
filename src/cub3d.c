/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 21:12:33 by bpires-r          #+#    #+#             */
/*   Updated: 2025/11/29 19:47:10 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	parse_map(t_cub3d *data)
{
	
}

void print_rgb(int color)
{
    int r = (color >> 16) & 0xFF;
    int g = (color >> 8) & 0xFF;
    int b = color & 0xFF;

    printf("R: %d, G: %d, B: %d\n", r, g, b);
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
	//if (!parse_map(&data))
	//	return (ft_putendl_fd(WRONG_MAP, 2), 1);
	printf("Ceiling Hexa: %x\nCeiling RGB = ", data.textures.ceiling);
	print_rgb(data.textures.ceiling);

	printf("Floor Hexa: %x\nFloor RGB = ", data.textures.floor);
	print_rgb(data.textures.floor);

	//free function create
	free_all(&data);
	free_ar((void **)data.map.map);
}

/*
printf("Ceiling RGB = ");
print_rgb(data.textures.ceiling);

printf("Floor RGB = ");
print_rgb(data.textures.floor);
*/