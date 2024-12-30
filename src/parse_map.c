/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 19:48:23 by jbrol-ca          #+#    #+#             */
/*   Updated: 2024/12/30 19:48:27 by jbrol-ca         ###   ########.fr       */
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
	while (get_next_line(fd, &line))
	{
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
