/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:41:28 by dmaessen          #+#    #+#             */
/*   Updated: 2023/10/31 17:23:26 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../include/cub3d.h"
#include "../include/utils.h"
#include <fcntl.h>
#include <stdlib.h>

static char *rm_map_spaces(char *line)
{
	char *newline;
	int i;
	int spaces;
	int j;

	i = 0;
	spaces = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			spaces++;
		i++;
	}
	newline = ft_calloc((ft_strlen(line) - spaces + 1), sizeof(char));
	if (!newline)
		err_msg("Calloc failed.\n");
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] != ' ')
		{
			newline[j] = line[i];
			j++;
			i++;
		}
		else
			i++;
	}
	return (newline);
}

static int parse_map(t_data *data, char *line, int i)
{
	char *newline;
	size_t	j;

	// MAYBE GOOD PLAN INSTEAD OF SPLITTING WRITE A "TRIM" FUNCTION TO RM ALL SPACES
	// SO TO HAVE ONE CONTINUOUS LINE WITHOUT SPACES
	newline = rm_map_spaces(line); // can this go wrong somehow?
	j = 0;
	if (i > 6)
	{
		printf("%s", newline);
		if (i == 7 || i == data->input->nb_lines) // if first or last line of map
		{
			while (newline[j])
			{
				if (newline[j] != 49 && !newline[j])
					err_msg("Invalid map, there is an empty space instead of a wall\n"); // or return here??
				j++;
			}
		}
		else
		{
			while (newline[j])
			{
				if (j == 0 || j == ft_strlen(newline))
				{
					if (newline[j] != 49 && !newline[j])
						err_msg("Invalid map, there is an empty space instead of a wall\n"); // or return here??
				}
				else
				{
					if ((newline[j] != 'N' || newline[j] != 'S' || newline[j] != 'W' 
					|| newline[j] != 'E' || newline[j] != 48 || newline[j] != 49 || newline[j] != '\0')) 
						err_msg("Invalid map, unidentified character in the map\n"); // or return here??
					if ((newline[j] == 'N' || newline[j] == 'S' || newline[j] == 'W' 
					|| newline[j] == 'E') && data->input->player == true)
						err_msg("Invalid map, only one player allowed in the map\n"); // or return here??
					if ((newline[j] == 'N' || newline[j] == 'S' || newline[j] == 'W' 
					|| newline[j] == 'E') && data->input->player == false)
						data->input->player = true;
				}
				j++;
			}
		}
	}
	free(newline);
	// but how do you know a path is walkable??
	return (0);
}

int	map_validation(t_data *data, char *file)
{
	int	fd;
    char *line;
	int	i;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		err_msg("Opening the file\n");
	data->input->player = false;
	i = 0;
	while (1)
	{
		line = get_next_line_exit(fd);
		if (line == NULL)
			break;
		if (ft_strcmp(line, "\n\0") != 0) // is this enough or we need spaces here too??
			i++;
		if (parse_map(data, line, i) == 1)
			return (free(line), close(fd), 1); // or exit??
		free(line);
	}
	close(fd);
	return (0);
}

