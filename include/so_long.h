/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 19:45:00 by jbrol-ca          #+#    #+#             */
/*   Updated: 2024/12/30 20:17:16 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "get_next_line.h"

/* ************************************************************************** */
/*                         Structures                                         */
/* ************************************************************************** */

typedef struct s_map_state
{
	int		collectibles;
	int		exit_found;
}	t_map_state;

/* ************************************************************************** */
/*                         Function Prototypes                                */
/* ************************************************************************** */

int		main(int argc, char **argv);
char	**load_map_from_file(const char *filename);
int		validate_map(char **map, int x, int y, t_map_state *state);
int		validate_map_structure(char **map);
int		ft_error(const char *message);
int		is_wall(const char *line);
int		ft_printf(const char *format, ...);
void	start_game(char **map);
int		find_player_x(char **map);
int		find_player_y(char **map);
char	**append_line_to_map(char **map, char *line);
int		get_next_line(int fd, char **line);

#endif /* SO_LONG_H */
