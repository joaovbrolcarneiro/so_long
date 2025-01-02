/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 19:48:23 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/02 15:23:48 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**load_map_from_file(const char *filename)
{
	char	**map;
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = NULL;
	while ((line = get_next_line(fd)))
	{
		strip_newline(line); // Call strip_newline here
		map = append_line_to_map(map, line);
		free(line);
	}
	close(fd);
	return (map);
}

int	validate_map_structure(char **map)
{
	int	i;
	int	len;

	len = ft_strlen(map[0]);
	i = 0;
	while (map[i])
	{
		if ((int)ft_strlen(map[i]) != len)
			return (0);
		if (map[i][0] != '1' || map[i][len - 1] != '1')
			return (0);
		i++;
	}
	if (!is_wall(map[0]) || !is_wall(map[i - 1]))
		return (0);
	return (1);
}

char	**append_line_to_map(char **map, char *line)
{
	char	**new_map;
	int		i;

	if (!line)
		return (map);
	i = 0;
	while (map && map[i])
		i++;
	new_map = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_map)
		return (NULL);
	i = 0;
	while (map && map[i])
	{
		new_map[i] = map[i];
		i++;
	}
	new_map[i] = line;
	new_map[i + 1] = NULL;
	free(map);
	return (new_map);
}

void	strip_newline(char *line)
{
	int	len;

	if (!line)
		return;
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

