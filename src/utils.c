/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:25:39 by bpires-r          #+#    #+#             */
/*   Updated: 2025/12/16 19:36:07 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_ident_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && is_space(line[i]))
		i++;
	if (!line[i])
		return (0);
	return (ft_strchr("NSOEAWCF", line[i]) != NULL);
}

int is_empty_line(const char *s)
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

void	skip_sp_tb(char *s, int *i)
{
	while (s[*i] && is_space(s[*i]))
		(*i)++;
}

int	get_tile_size(t_cub3d *data)
{
	int	size;

	if (data->map.row_count <= 0 || data->map.col_count <= 0)
		return (1);
	size = data->img.width / data->map.col_count;
	if (size > data->img.height / data->map.row_count)
		size = data->img.height / data->map.row_count;
	if (size < 1)
		size = 1;
	return (size);
}

int	load_xpm_with_data(void *mlx, t_menu_img *img, char *path)
{
	img->image = mlx_xpm_file_to_image(mlx, path, &img->width, &img->height);
	if (!img->image)
		return (-1);
	img->data = mlx_get_data_addr(img->image, &img->bpp,
			&img->size_line, &img->endian);
	if (!img->data)
		return (-1);
	return (0);
}