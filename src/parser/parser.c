/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 21:21:01 by bpires-r          #+#    #+#             */
/*   Updated: 2025/12/06 22:17:31 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_texture(char *s, char **dest, char *texture, int flag, t_cub3d *data)
{
	while (*s && is_space(*s))
		s++;
	if (!*s)
	{
		ft_putstr_fd("cub3d: '", 2);
		ft_putstr_fd(texture, 2);
		ft_putendl_fd("' path to texture is required.", 2);
		if (flag == 4)
		{
			ft_putendl_fd(TEXTURES, 2);
			exit_error(data, EXAMPLE);
		}
	}
	*dest = ft_strdup(s);
	return (*dest != NULL);
}

static int	parse_comp(char *s, int *i, int *out, t_cub3d *data)
{
	int	val;

	if (!s[*i] || !ft_isdigit((unsigned char)s[*i]))
		return (exit_error(data, NON_DIGIT), 0);
	val = 0;
	while (s[*i] && ft_isdigit((unsigned char)s[*i]))
	{
		val = val * 10 + (s[*i] - '0');
		if (val > 255)
			return (exit_error(data, CF_OVERFLOW), 0);
		(*i)++;
	}
	*out = val;
	return (1);
}

int	parse_colour(char *s, int *dest, t_cub3d *data)
{
	int	i;
	int	comp;
	int	rgb[3];

	(void)data;
	i = 0;
	comp = 0;
	skip_sp_tb(s, &i);
	if (!s[i])
		return (0);
	while (comp < 3)
	{
		skip_sp_tb(s, &i);
		if (!parse_comp(s, &i, &rgb[comp], data))
			return (0);
		skip_sp_tb(s, &i);
		if (comp < 2)
		{
			if (s[i] != ',')
				return (exit_error(data, COMMA) ,0);
			i++;
			skip_sp_tb(s, &i);
		}
		else
		{
			skip_sp_tb(s, &i);
			if (s[i])
				return (exit_error(data, NON_DIGIT), 0);
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
	int		flag;

	i = 0;
	flag = 0;
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
			flag = flag + 1;
			if (data->textures.no || !parse_texture(&line[2], &data->textures.no, "NO", flag, data))
				exit_error(data, DUP_NO);
		}
			
		else if (!ft_strncmp(line, "SO", 2) && is_space(line[2]))
		{
			flag = flag + 1;
			if (data->textures.so || !parse_texture(&line[2], &data->textures.so, "SO", flag, data))
				exit_error(data, DUP_SO);
			
		}
		else if (!ft_strncmp(line, "EA", 2) && is_space(line[2]))
		{
			flag = flag + 1;
			if (data->textures.ea || !parse_texture(&line[2], &data->textures.ea, "EA", flag, data))
				exit_error(data, DUP_EA);
		}
			
		else if (!ft_strncmp(line, "WE", 2) && is_space(line[2]))
		{
			flag = flag + 1;
			if (data->textures.we || !parse_texture(&line[2], &data->textures.we, "WE", flag, data))
				exit_error(data, DUP_WE);
		}
			
		else if (!ft_strncmp(line, "C", 1) && is_space(line[1]))
		{
			if (data->textures.ceiling != -1 || !parse_colour(&line[1], &data->textures.ceiling, data))
				exit_error(data, DUP_CEILING);
		}
			
		else if (!ft_strncmp(line, "F", 1) && is_space(line[1]))
		{
			if (data->textures.floor != -1 || !parse_colour(&line[1], &data->textures.floor, data))
				exit_error(data, DUP_FLOOR);
		}
		i++;
	}
	indetifier_checker(data);
	while (data->map.map[i] && is_empty_line(data->map.map[i]))
		i++;
	data->map.start = i;
	return (1);
}
