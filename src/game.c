/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:05:14 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/02 18:44:28 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* *********************************************************************
 * Starts the game and runs the main game loop.
 *********************************************************************/

int start_game(char **map)
{
    t_game game;

    // Initialize the window
    if (!init_window(&game, map))
        return (ft_error("Error: Unable to initialize the window"));

    // Initialize the key event hooks
    init_hooks(&game);

    // Main game loop
    while (game_is_running(&game))
    {
        // Handle key events in the game loop
        mlx_do_sync(game.mlx);  // Ensure the window updates correctly

        // No need for update_game_state here, as movement and checks are handled in handle_key_press

        // Render the updated game state on the window
        render_game(&game, map);
    }

    // Cleanup after the game loop ends
    cleanup_game(&game);
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

int handle_key_press(int keycode, t_game *game)
{
    // ESC key: Exit the game
    if (keycode == KEY_ESC)
    {
        mlx_destroy_window(game->mlx, game->win);
        game->win = NULL;  // Mark the window as destroyed
        exit(0);  // Exit the game
    }

    // Player movement handling
    int player_x = game->player_x;
    int player_y = game->player_y;

    if (keycode == KEY_UP)
        move_player(game, player_x, player_y - 1);  // Move up
    else if (keycode == KEY_DOWN)
        move_player(game, player_x, player_y + 1);  // Move down
    else if (keycode == KEY_LEFT)
        move_player(game, player_x - 1, player_y);  // Move left
    else if (keycode == KEY_RIGHT)
        move_player(game, player_x + 1, player_y);  // Move right

    // Check for collisions or game-over conditions
    check_for_collisions(game, player_x, player_y);

    return (0);  // Return 0 to indicate the event was handled
}

/* *********************************************************************
 * This function sets up the key hooks using mlx_key_hook.
 *********************************************************************/

void init_hooks(t_game *game)
{
    // Hook the key press events to the handle_key_press function
    mlx_key_hook(game->win, handle_key_press, game);
}
