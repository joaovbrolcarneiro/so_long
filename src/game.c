/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:05:14 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/04 18:50:11 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* *********************************************************************
 * Starts the game and runs the main game loop.
 *********************************************************************/

int start_game(char **map)
{
    t_game game;

    // Set player position
    game.player_x = find_player_x(map);
    game.player_y = find_player_y(map);
    ft_printf("Player position initialized: x=%d, y=%d\n", game.player_x, game.player_y);

    // Assign the map to the game structure
    game.map = map;

    // Initialize the window
    if (!init_window(&game, map))
        return (ft_error("Error: Unable to initialize the window"));

    // Initialize the key event hooks
    init_hooks(&game);

    // Main game loop
    mlx_loop(game.mlx);  // Start the event loop to process key presses and render the game

    cleanup_game(&game);  // Cleanup after the game loop ends
    return (0);
}

/* *********************************************************************
 * Checks if the game is still running (window is open).
 *********************************************************************/

int game_is_running(t_game *game)
{
    if (game->win == NULL)
        return (0);
    return (1);
}

/* *********************************************************************
 * This function is called when a key is pressed.
 * It handles key events like ESC and player movement.
 *********************************************************************/

/* *********************************************************************
 * This function is called when a key is pressed.
 * It handles key events like ESC and player movement.
 *********************************************************************/

int handle_key_press(int keycode, t_game *game)
{
    ft_printf("Key pressed: %d\n", keycode);  // Debugging print

    // ESC key: Exit the game
    if (keycode == KEY_ESC)
    {
        mlx_destroy_window(game->mlx, game->win);
        game->win = NULL;
        exit(0);
    }

    // Player movement handling
    if (keycode == KEY_UP)
    {
        ft_printf("Moving UP\n");
        if (game->player_y > 0 && game->map[game->player_y - 1][game->player_x] != '1') // Check if within bounds and not a wall
            game->player_y -= 1;
    }
    else if (keycode == KEY_DOWN)
    {
        ft_printf("Moving DOWN\n");
        if (game->player_y < game->map_height - 1 && game->map[game->player_y + 1][game->player_x] != '1') // Check if within bounds and not a wall
            game->player_y += 1;
    }
    else if (keycode == KEY_LEFT)
    {
        ft_printf("Moving LEFT\n");
        if (game->player_x > 0 && game->map[game->player_y][game->player_x - 1] != '1') // Check if within bounds and not a wall
            game->player_x -= 1;
    }
    else if (keycode == KEY_RIGHT)
    {
        ft_printf("Moving RIGHT\n");
        if (game->player_x < game->map_width - 1 && game->map[game->player_y][game->player_x + 1] != '1') // Check if within bounds and not a wall
            game->player_x += 1;
    }

    // After updating position, re-render the map if the player moved
    ft_printf("Player position updated to: (%d, %d)\n", game->player_x, game->player_y);
    update_game_map(game);  // Update the map with new player position, collectibles, etc.
    render_game(game, game->map);  // Render the updated game state after movement

    return (0);
}


/* *********************************************************************
 * This function updates the entire game map, including player, 
 * collectibles, and any other dynamic objects.
 *********************************************************************/

void update_game_map(t_game *game)
{
    for (int y = 0; y < ft_strarr_len(game->map); y++) 
    {
        for (size_t x = 0; x < ft_strlen(game->map[y]); x++) 
        {
            // If a previous player position is found, replace it with empty space
            if (game->map[y][x] == 'P')
                game->map[y][x] = '0'; 

            // If the current position matches the player's new position, place the player
            if ((size_t)x == (size_t)game->player_x && (size_t)y == (size_t)game->player_y) 
                game->map[y][x] = 'P';  // Place player at the new position
        }
    }

    // Debugging: Print the updated map
    for (int y = 0; y < ft_strarr_len(game->map); y++) 
    {
        ft_printf("Row %d: %s\n", y, game->map[y]);
    }
}



/* *********************************************************************
 * This function sets up the key hooks using mlx_key_hook.
 *********************************************************************/

void init_hooks(t_game *game)
{
    // Hook the key press events to the handle_key_press function
    mlx_key_hook(game->win, handle_key_press, game);
}

/*int is_valid_move(t_game *game, int new_x, int new_y)
{
    // Check if the new position is within the bounds of the map
    if (new_x < 0 || new_x >= game->map_state.map_width || new_y < 0 || new_y >= game->map_state.map_height)
        return 0;  // Invalid move (out of bounds)
    
    // Check if the new position is a wall (1)
    if (game->map[new_y][new_x] == '1')
        return 0;  // Invalid move (wall)

    return 1;  // Valid move
}
*/



