/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:41:23 by dmaessen          #+#    #+#             */
/*   Updated: 2023/11/01 16:55:38 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../include/cub3d.h"
#include "../include/utils.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h> // needed?

static void init_data(t_data *data)
{
	data->textures = calloc_exit(1, sizeof(t_textures));
	data->textures->no_texture = ft_strdup("-1");
	if (!data->textures->no_texture)
		err_msg("Malloc failed\n");
	data->textures->so_texture = ft_strdup("-1");
	if (!data->textures->so_texture)
		err_msg("Malloc failed\n");
	data->textures->we_texture = ft_strdup("-1");
	if (!data->textures->we_texture)
		err_msg("Malloc failed\n");
	data->textures->ea_texture = ft_strdup("-1");
	if (!data->textures->ea_texture)
		err_msg("Malloc failed\n");
	data->colors = calloc_exit(1, sizeof(t_colors));
	data->colors->c_color_b = -1;
	data->colors->c_color_g = -1;
	data->colors->c_color_r = -1;
	data->colors->f_color_b = -1;
	data->colors->f_color_g = -1;
	data->colors->f_color_r = -1;
	data->input = calloc_exit(1, sizeof(t_data_input));
}

static void split_colorcode(t_data *data, char *color, int id)
{
	char **color_code;

	color_code = ft_split(color, ',');
	if (!color_code)
		err_msg("Split failed\n");
	if (id == 1)
	{
		if (color_code[0])
			data->colors->c_color_b = ft_atoi(color_code[0]);
		if (color_code[1])
			data->colors->c_color_g = ft_atoi(color_code[1]);
		if (color_code[2])
			data->colors->c_color_r = ft_atoi(color_code[2]);
	}
	if (id == 2)
	{
		if (color_code[0])
			data->colors->f_color_b = ft_atoi(color_code[0]);
		if (color_code[1])
			data->colors->f_color_g = ft_atoi(color_code[1]);
		if (color_code[2])
			data->colors->f_color_r = ft_atoi(color_code[2]);
	}
	free_str(color_code);
}

void add_data(t_data *data, char **str, int i)
{
	if (ft_strncmp(str[i], "C", 1) == 0)
		if (str[i+1])
			split_colorcode(data, str[i+1], 1);
	if (ft_strncmp(str[i], "F", 1) == 0)
		if (str[i+1])
			split_colorcode(data, str[i+1], 2);
	if (ft_strncmp(str[i], "NO", 2) == 0 && str[i+1])
	{
		data->textures->no_texture = ft_strdup(str[i+1]);
		check_image(data->textures->no_texture);
	}
	if (ft_strncmp(str[i], "SO", 2) == 0 && str[i+1])
	{
		data->textures->so_texture = ft_strdup(str[i+1]);
		check_image(data->textures->so_texture);
	}
	if (ft_strncmp(str[i], "WE", 2) == 0 && str[i+1])
	{
		data->textures->we_texture = ft_strdup(str[i+1]);
		check_image(data->textures->we_texture);
	}
	if (ft_strncmp(str[i], "EA", 2) == 0 && str[i+1])
	{
		data->textures->ea_texture = ft_strdup(str[i+1]);
		check_image(data->textures->ea_texture);
	}
	if (!data->textures->no_texture || !data->textures->so_texture 
		|| !data->textures->we_texture || !data->textures->ea_texture)
			err_msg("Malloc failed\n");
}

int parse_line(t_data *data, char *line)
{
	char **str;
	int i;

	str = ft_split(line, ' ');
	if (!str)
		err_msg("Spliting line\n");
	
	//printf("str0 == %s str1 == %s str2 == %s\n", str[0], str[1], str[2]); // to rm
	i = 0;
	while (str[i])
	{
		if (ft_strncmp(str[i], "NO", 2) == 0 || ft_strncmp(str[i], "SO", 2) == 0 
		|| ft_strncmp(str[i], "WE", 2) == 0 || ft_strncmp(str[i], "EA", 2) == 0
		|| ft_strncmp(str[i], "C", 1) == 0 || ft_strncmp(str[i], "F", 1) == 0)
			add_data(data, str, i);
		i++;
	}
	free_str(str);
	return (0);
}

static int format_validation(char *file)
{
	char	*res;

	if (ft_strlen(file) < 4)
		return (1);
	res = ft_substr(file, ft_strlen(file) - 4, 4);
	if (!res)
		err_msg("Malloc failed.\n");
	if (ft_strcmp(res, ".cub") != 0)
		return (free(res), 1);
	free(res);
	return (0);
}

static void validate_colors(t_colors *colors)
{
	if (colors->c_color_b == -1 || colors->c_color_g == -1
		|| colors->c_color_r == -1)
		err_msg("Color for the ceiling missing.\n");
	if (colors->f_color_b == -1 || colors->f_color_g == -1
		|| colors->f_color_r == -1)
		err_msg("Color for the floor missing.\n");
	if ((colors->c_color_b < 0) || (colors->c_color_b > 255) 
		|| (colors->c_color_r < 0) || (colors->c_color_r > 255) 
		|| (colors->c_color_g < 0) || (colors->c_color_g > 255))
		err_msg("Invalid color code for the ceiling.\n");
	if ((colors->f_color_b < 0) || (colors->f_color_b > 255) 
		|| (colors->f_color_r < 0) || (colors->f_color_r > 255) 
		|| (colors->f_color_g < 0) || (colors->f_color_g > 255))
		err_msg("Invalid color code for the floor.\n");
	if ((colors->f_color_b == colors->c_color_b) 
		&& (colors->f_color_r == colors->c_color_r) 
		&& (colors->f_color_g == colors->c_color_g))
		err_msg("Colors of the floor and ceiling need to be different.\n");
}

static void check_doubles(t_data *data)
{
	if (ft_strcmp(data->textures->no_texture, "-1") == 0)
		err_msg("NO texture missing.\n");
	if (ft_strcmp(data->textures->so_texture, "-1") == 0)
		err_msg("SO texture missing.\n");
	if (ft_strcmp(data->textures->we_texture, "-1") == 0)
		err_msg("WE texture missing.\n");
	if (ft_strcmp(data->textures->ea_texture, "-1") == 0)
		err_msg("EA texture missing.\n");
	if (ft_strcmp(data->textures->no_texture, data->textures->so_texture) == 0
	&& ft_strlen(data->textures->no_texture) == ft_strlen(data->textures->so_texture))
		err_msg("The textures of NO and SO need to be different.\n");
	if (ft_strcmp(data->textures->no_texture, data->textures->we_texture) == 0
	&& ft_strlen(data->textures->no_texture) == ft_strlen(data->textures->we_texture))
		err_msg("The textures of NO and WE need to be different.\n");
	if (ft_strcmp(data->textures->no_texture, data->textures->ea_texture) == 0
	&& ft_strlen(data->textures->no_texture) == ft_strlen(data->textures->ea_texture))
		err_msg("The textures of NO and EA need to be different.\n");
	if (ft_strcmp(data->textures->so_texture, data->textures->we_texture) == 0
	&& ft_strlen(data->textures->so_texture) == ft_strlen(data->textures->we_texture))
		err_msg("The textures of WE and SO need to be different.\n");
	if (ft_strcmp(data->textures->so_texture, data->textures->ea_texture) == 0
	&& ft_strlen(data->textures->so_texture) == ft_strlen(data->textures->ea_texture))
		err_msg("The textures of SO and EA need to be different.\n");
	if (ft_strcmp(data->textures->we_texture, data->textures->ea_texture) == 0
	&& ft_strlen(data->textures->we_texture) == ft_strlen(data->textures->ea_texture))
		err_msg("The textures of WE and EA need to be different.\n");
}

// void check_image(char *path)
// {
// 	char	*res;

// 	if (ft_strlen(path) < 4) // 5 then
// 		err_msg("Wrong texture extension, only .png and .jpg supported\n");
// 	printf("len == %zu // %s\n", ft_strlen(path), path); // to rm
// 	if (path[ft_strlen(path) - 1] == '\n')
// 		res = ft_substr(path, ft_strlen(path) - 5, 4);
// 	else
// 		res = ft_substr(path, ft_strlen(path) - 4, 4); // PROB IF MORE THAN 1 NEWLIN BUT PRBLEM FOR LATER -- do strrchr and res == the 4 chars
// 	printf("res == %s\n", res); // to rm
// 	if (ft_strcmp(res, ".png") != 0 && ft_strcmp(res, ".jpg") != 0)
// 	{
// 		free(res);
// 		printf("you??\n");
// 		err_msg("Wrong texture extension, only .png and .jpg supported\n");
// 	}
// 	free(res);
// }

void check_image(char *path)
{
	char	*res;
	char	*pos; // to free this one add a new char* to ass it on..

	pos = ft_strrchr(path, '.');
	if (ft_strlen(path) < 4 || ft_strlen(pos) < 4 || pos == NULL)
		err_msg("Wrong texture extension, only .png and .jpg supported\n");
	while (ft_strchr(pos, '\n') != 0)
		pos = ft_strtrim(pos, "\n");
	res = ft_substr(pos, 0, ft_strlen(pos));
	if (ft_strcmp(res, ".png") != 0 && ft_strcmp(res, ".jpg") != 0)
	{
		free(res);
		err_msg("Wrong texture extension, only .png and .jpg supported\n");
	}
	//free(pos);
	free(res);
}

int input_validation(t_data *data, char *file)
{
	int fd;
	char *line;

	if (format_validation(file) == 1)
		err_msg("Wrong file extension, should be: .cub\n");
	fd = open(file, O_RDONLY);
	if (fd < 0)
		err_msg("Opening the file\n");
	init_data(data);
	data->input->nb_lines = 0;
	while (1)
	{
		line = get_next_line_exit(fd);
		if (line == NULL)
			break;
		if (ft_strcmp(line, "\n\0") != 0) // is this enough or we need spaces here too??
			data->input->nb_lines++;
		if (parse_line(data, line) == 1)
			return (free(line), close(fd), 1); // or exit??
		free(line);
	}
	close(fd);
	check_doubles(data);
	validate_colors(data->colors);
	return (0);
}
