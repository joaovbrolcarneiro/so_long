/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 20:14:26 by jbrol-ca          #+#    #+#             */
/*   Updated: 2024/12/30 20:41:33 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_error(const char *message)
{
	ft_printf("%s\n", message);
	return (1);
}

int	is_wall(const char *line)
{
	while (*line)
	{
		if (*line != '1')
			return (0);
		line++;
	}
	return (1);
}

int	find_player_x(char **map)
{
	int	x;

	x = 0;
	while (map[0][x])
	{
		if (map[0][x] == 'P')
			return (x);
		x++;
	}
	return (-1);
}

int	find_player_y(char **map)
{
	int	y;

	y = 0;
	while (map[y])
	{
		if (map[y][find_player_x(map)] == 'P')
			return (y);
		y++;
	}
	return (-1);
}
