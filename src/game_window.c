/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 16:57:56 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/02 18:26:56 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* *********************************************************************
 * Initializes the window for the game.
 *********************************************************************/

int	init_window(t_game *game, char **map)
{
	game->mlx = mlx_init();  // Initialize the MLX library
	if (!game->mlx)
		return (0);  // Failed to initialize MLX
	game->win = mlx_new_window(game->mlx,
			ft_strlen(map[0]) * TILE_SIZE,
			ft_strarr_len(map) * TILE_SIZE, "So Long");
	if (!game->win)
		return (0);  // Failed to create window
	return (1);  // Success
}

/* *********************************************************************
 * Renders the game (map and objects like player, collectibles, etc.)
 *********************************************************************/

void	render_game(t_game *game, char **map)
{
	int	x;
	int	y;

	y = 0;
	while (y < ft_strarr_len(map))
	{
		x = 0;
		while (x < (int)ft_strlen(map[y]))
		{
			if (map[y][x] == '1')
				mlx_put_image_to_window(game->mlx, game->win,
					game->wall_img, x * TILE_SIZE, y * TILE_SIZE);
			// Additional rendering conditions for player, collectibles, etc.
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

