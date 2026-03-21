/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 21:21:01 by bpires-r          #+#    #+#             */
/*   Updated: 2026/03/21 16:14:34 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_texture(char *s, char **dest)
{
	while (*s && is_space(*s))
		s++;
	if (!*s)
		*dest = ft_strdup("1");
	else
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

	i = 0;
	comp = -1;
	skip_sp_tb(s, &i);
	if (!s[i])
		return (0);
	while (++comp < 3)
	{
		skip_sp_tb(s, &i);
		if (!parse_comp(s, &i, &rgb[comp], data))
			return (0);
		skip_sp_tb(s, &i);
		if (comp < 2 && s[i] != ',')
			return (exit_error(data, COMMA), 0);
		if (comp < 2)
			i++;
	}
	skip_sp_tb(s, &i);
	if (s[i])
		return (exit_error(data, NON_DIGIT), 0);
	*dest = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	return (1);
}

static void	parse_identifier_line(t_cub3d *data, char *line)
{
	if (!ft_strncmp(line, "NO", 2) && is_space(line[2]) && ((data->textures.no
			|| !parse_texture(&line[2], &data->textures.no))))
		exit_error(data, DUP_NO);
	else if (!ft_strncmp(line, "SO", 2) && is_space(line[2])
		&& ((data->textures.so || !parse_texture(&line[2], &data->textures.so))))
		exit_error(data, DUP_SO);
	else if (!ft_strncmp(line, "EA", 2) && is_space(line[2])
		&& ((data->textures.ea || !parse_texture(&line[2], &data->textures.ea))))
		exit_error(data, DUP_EA);
	else if (!ft_strncmp(line, "WE", 2) && is_space(line[2])
		&& ((data->textures.we || !parse_texture(&line[2], &data->textures.we))))
		exit_error(data, DUP_WE);
	else if (!ft_strncmp(line, "C", 1) && is_space(line[1])
		&& (data->textures.ceiling != -1
			|| !parse_colour(&line[1], &data->textures.ceiling, data)))
		exit_error(data, DUP_CEILING);
	else if (!ft_strncmp(line, "F", 1) && is_space(line[1])
		&& (data->textures.floor != -1
			|| !parse_colour(&line[1], &data->textures.floor, data)))
		exit_error(data, DUP_FLOOR);
}

int	parse_identifiers(t_cub3d *data)
{
	int		i;
	char	*line;

	i = 0;
	if (!data->map.map)
		return (0);
	while (data->map.map[i] && is_empty_line(data->map.map[i]))
		i++;
	while (data->map.map[i] && (is_ident_line(data->map.map[i])
			|| is_empty_line(data->map.map[i])))
	{
		line = data->map.map[i];
		while (*line && is_space(*line))
			line++;
		if (*line)
			parse_identifier_line(data, line);
		i++;
	}
	indetifier_checker(data);
	while (data->map.map[i] && is_empty_line(data->map.map[i]))
		i++;
	data->map.start = i;
	return (1);
}
