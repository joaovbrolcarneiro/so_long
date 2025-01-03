/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 19:59:02 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/03 20:39:15 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int main(int argc, char **argv)
{
    char        **map;
    t_map_state state;
    int         i;
    int         map_width = 0;
    int         map_height = 0;
    int         player_x, player_y;

    state.collectibles = 0;
    state.exit_found = 0;

    if (argc != 2)
        return (ft_printf("Usage: ./so_long <map_file>\n"));

    // Load the map from the file
    map = load_map_from_file(argv[1]);

    // Debug log: Check the map contents
    if (map)
    {
        ft_printf("Loaded map:\n");
        for (i = 0; map[i]; i++) // Iterate through each row
        {
            ft_printf("Row %d: %s\n", i, map[i]);
        }

        // Set map dimensions
        map_width = ft_strlen(map[0]);  // Assuming all rows have the same width
        map_height = i;  // The height is the number of rows in the map

        // Debug: Print map dimensions
        ft_printf("Map dimensions: Width = %d, Height = %d\n", map_width, map_height);
    }
    else
    {
        ft_printf("Error: Failed to load map.\n");
        return 1;
    }

    // Validate map structure
    if (!map || !validate_map_structure(map))
        return (ft_printf("Error: Invalid map structure\n"));

    // Find the player's starting position
    player_x = find_player_x(map);
    player_y = find_player_y(map);

    // Debug log: Check the player's starting position
    ft_printf("Player starting position: x=%d, y=%d\n", player_x, player_y);

    // Initialize map state with map dimensions
    state.map_width = map_width;
    state.map_height = map_height;

    // Count the collectibles before validating the map
    state.collectibles = count_collectibles(map, &state);

    // We pass 'V' as the visit flag to start marking visited cells
    char visit_flag = 'V'; // This is the flag we'll use for visited cells

    // Validate map configuration using player position and map state
    if (!validate_map(map, player_x, player_y, &state, visit_flag))
        return (ft_printf("Error: Invalid map configuration\n"));

    // Check for reachable collectibles and exit
    ft_printf("Collectibles: %d, Exit Found: %d\n", state.collectibles, state.exit_found);
    if (state.collectibles == 0 || state.exit_found == 0)
        return (ft_printf("Error: Unreachable collectibles or exit\n"));
    
    ft_printf("Sucess: validation complete. Game will start:\n");

    // Start the game
    start_game(map);
    return (0);
}





/*
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
*/
/*
int	main(int argc, char **argv)
{
	char		**map;
	t_map_state	state;
	int			i; // For debugging the map contents

	state.collectibles = 0;
	state.exit_found = 0;

	if (argc != 2)
		return (ft_printf("Usage: ./so_long <map_file>\n"));

	// Load the map from the file
	map = load_map_from_file(argv[1]);

	// Debug log: Check the map contents
	if (map)
	{
		ft_printf("Loaded map:\n");
		for (i = 0; map[i]; i++) // Iterate through each row
		{
			ft_printf("Row %d: %s\n", i, map[i]);
		}
	}
	else
	{
		ft_printf("Error: Failed to load map.\n");
	}

	// Validate map structure
	if (!map || !validate_map_structure(map))
		return (ft_printf("Error: Invalid map structure\n"));

	// Find the player's starting position
	int player_x = find_player_x(map);
	int player_y = find_player_y(map);

	// Debug log: Check the player's starting position
	ft_printf("Player starting position: x=%d, y=%d\n", player_x, player_y);

	// Validate map configuration (using player position)
	if (!validate_map(map, player_x, player_y, &state))
		return (ft_printf("Error: Invalid map configuration\n"));

	// Check for reachable collectibles and exit
	if (state.collectibles == 0 || state.exit_found == 0)
		return (ft_printf("Error: Unreachable collectibles or exit\n"));

	// Start the game
	start_game(map);
	return (0);
}
*/

