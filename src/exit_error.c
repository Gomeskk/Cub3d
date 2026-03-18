/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 21:14:59 by bpires-r          #+#    #+#             */
/*   Updated: 2026/03/18 23:21:09 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_error(t_cub3d *data, char *message)
{
	ft_putendl_fd(message, 2);
	free_all(data);
	exit(127);
}

void	exit_game(char *end_game, t_cub3d *data)
{
	free_all(data);
	ft_putendl_fd(end_game, 1);
	exit(0);
}

int	x_window(t_cub3d *data)
{
	exit_game("Thank you for Playing "
		"\033[1;35mbpires-r's\033[1;0m and "
		"\033[1;35mjoafaust's\033[1;0m game!",
		data);
	return (0);
}
