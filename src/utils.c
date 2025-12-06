/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:25:39 by bpires-r          #+#    #+#             */
/*   Updated: 2025/12/02 19:38:54 by bpires-r         ###   ########.fr       */
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