/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 19:59:02 by jbrol-ca          #+#    #+#             */
/*   Updated: 2024/12/30 20:12:40 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	char		**map;
	t_map_state	state;

	state.collectibles = 0;
	state.exit_found = 0;
	if (argc != 2)
		return (ft_printf("Usage: ./so_long <map_file>"));
	map = load_map_from_file(argv[1]);
	if (!map || !validate_map_structure(map))
		return (ft_printf("Error: Invalid map structure"));
	if (!validate_map(map, find_player_x(map), find_player_y(map), &state))
		return (ft_printf("Error: Invalid map configuration"));
	if (state.collectibles == 0 || state.exit_found == 0)
		return (ft_printf("Error: Unreachable collectibles or exit"));
	start_game(map);
	return (0);
}
