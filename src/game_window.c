/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 16:57:56 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/03 21:51:48 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* *********************************************************************
 * Initializes the window for the game.
 *********************************************************************/

int init_window(t_game *game, char **map)
{
    int width, height;  // To hold the width and height of textures

    game->mlx = mlx_init();  // Initialize the MLX library
    if (!game->mlx)
    {
        ft_printf("Error: MLX initialization failed\n");
        return (0);  // Failed to initialize MLX
    }

    int map_width = ft_strlen(map[0]) * TILE_SIZE;
    int map_height = ft_strarr_len(map) * TILE_SIZE;

    // Create a new window for the game
    game->win = mlx_new_window(game->mlx, map_width, map_height, "So Long");
    if (!game->win)
    {
        ft_printf("Error: Window creation failed\n");
        mlx_destroy_display(game->mlx);  // Clean up if window creation fails
        free(game->mlx);
        return (0);  // Failed to create window
    }

    // Load the images (textures) for walls, player, collectibles, floor, and exit
    game->wall_img = mlx_xpm_file_to_image(game->mlx, "textures/wall.xpm", &width, &height);
    if (!game->wall_img)
    {
        ft_printf("Error: Failed to load wall texture\n");
        return (0);
    }

    game->player_img = mlx_xpm_file_to_image(game->mlx, "textures/player.xpm", &width, &height);
    if (!game->player_img)
    {
        ft_printf("Error: Failed to load player texture\n");
        return (0);
    }

    game->collectible_img = mlx_xpm_file_to_image(game->mlx, "textures/collectible.xpm", &width, &height);
    if (!game->collectible_img)
    {
        ft_printf("Error: Failed to load collectible texture\n");
        return (0);
    }

    game->floor_img = mlx_xpm_file_to_image(game->mlx, "textures/floor.xpm", &width, &height);
    if (!game->floor_img)
    {
        ft_printf("Error: Failed to load floor texture\n");
        return (0);
    }

    // Load the exit texture
    game->exit_img = mlx_xpm_file_to_image(game->mlx, "textures/exit.xpm", &width, &height);
    if (!game->exit_img)
    {
        ft_printf("Error: Failed to load exit texture\n");
        return (0);
    }

    return (1);  // Success
}


/* *********************************************************************
 * Renders the game (map and objects like player, collectibles, etc.)
 *********************************************************************/

void render_game(t_game *game, char **map)
{
    int x, y;

    y = 0;
    while (y < ft_strarr_len(map))
    {
        x = 0;
        while (x < (int)ft_strlen(map[y]))
        {
            // Render floor tiles (0)
            if (map[y][x] == '0')
                mlx_put_image_to_window(game->mlx, game->win, game->floor_img, x * TILE_SIZE, y * TILE_SIZE);
            
            // Render walls (1)
            if (map[y][x] == '1')
                mlx_put_image_to_window(game->mlx, game->win, game->wall_img, x * TILE_SIZE, y * TILE_SIZE);

            // Render player (P)
            if (map[y][x] == 'P')
                mlx_put_image_to_window(game->mlx, game->win, game->player_img, x * TILE_SIZE, y * TILE_SIZE);

            // Render collectibles (C)
            if (map[y][x] == 'C')
                mlx_put_image_to_window(game->mlx, game->win, game->collectible_img, x * TILE_SIZE, y * TILE_SIZE);

            // Render exit (E)
            if (map[y][x] == 'E')
                mlx_put_image_to_window(game->mlx, game->win, game->exit_img, x * TILE_SIZE, y * TILE_SIZE);

            x++;
        }
        y++;
    }
}


/* *********************************************************************
 * Cleans up the game window and MLX resources.
 *********************************************************************/

void	cleanup_game(t_game *game)
{
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);  // Close the window
}

