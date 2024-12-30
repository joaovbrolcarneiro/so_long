/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 19:57:11 by jbrol-ca          #+#    #+#             */
/*   Updated: 2024/12/30 19:57:24 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	validate_map(char **map, int x, int y, t_map_state *state)
{
	if (x < 0 || y < 0 || map[y][x] == '\0' || map[y][x] == '\n')
		return (0);
	if (map[y][x] == '1' || map[y][x] == 'V')
		return (0);
	if (map[y][x] == 'C')
		state->collectibles++;
	if (map[y][x] == 'E')
		state->exit_found = 1;
	map[y][x] = 'V';
	validate_map(map, x + 1, y, state);
	validate_map(map, x - 1, y, state);
	validate_map(map, x, y + 1, state);
	validate_map(map, x, y - 1, state);
	return (1);
}
