/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahornstr <ahornstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:17:40 by dmaessen          #+#    #+#             */
/*   Updated: 2024/02/14 17:41:55 by ahornstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../include/cub3d.h"
#include "../include/utils.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int	check_line(char **map, int row, int pos)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		if (i == row)
		{
			while (map[i][j])
			{
				if (j == pos)
				{
					if (map[i][j] == 48 || map[i][j] == 'N' || map[i][j] == 'S'
					|| map[i][j] == 'W' || map[i][j] == 'E')
						return (1);
					else
						return (0);
				}
				j++;
			}
		}
		i++;
	}
	return (0);
}

void	parse_spaces(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->input->parsed_map[i])
	{
		j = 0;
		while (data->input->parsed_map[i][j])
		{
			if (data->input->parsed_map[i][j] == ' ')
			{
				if (check_line(data->input->parsed_map, i - 1, j) != 0
					|| check_line(data->input->parsed_map, i + 1, j) != 0)
					err_msg("Invalid map, a wall is \
					missing to properly enclose the map\n");
			}
			j++;
		}
		i++;
	}
}

static int	check_walkable2(char **map, int i, int j, int id)
{
	int	step;

	step = 0;
	while (map[i][j])
	{
		if (j == id)
		{
			if (map[i][j - 1] == 48)
				step++;
			if (map[i][j + 1] == 48)
				step++;
		}
		j++;
	}
	return (step);
}

void	check_walkable(char **map, int row, int id)
{
	int	i;
	int	j;
	int	step;

	i = 0;
	step = 0;
	while (map[i])
	{
		j = 0;
		if (i == row - 1 || i == row + 1)
		{
			while (map[i][j])
			{
				if (j == id)
					if (map[i][j] == 48)
						step++;
				j++;
			}
		}
		else if (i == row)
			step += check_walkable2(map, i, j, id);
		i++;
	}
	if (step < 1)
		err_msg("Invalid map, no walk-able path for the player\n");
}

void	is_walkable_path(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->input->parsed_map[i])
	{
		j = 0;
		while (data->input->parsed_map[i][j])
		{
			if (data->input->parsed_map[i][j] == 'N'
				|| data->input->parsed_map[i][j] == 'S'
				|| data->input->parsed_map[i][j] == 'W'
				|| data->input->parsed_map[i][j] == 'E')
			{
				check_walkable(data->input->parsed_map, i, j);
				break ;
			}
			j++;
		}
		i++;
	}
}
