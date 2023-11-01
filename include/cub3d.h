/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:43:40 by dmaessen          #+#    #+#             */
/*   Updated: 2023/11/01 15:19:27 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "../MLX42/include/MLX42/MLX42_Input.h"

/* defines to help set values for functions that validates the map */
# define MAP_CHAR "01NSEW"
# define MAP_POS "NSEW"

/**
 * input with regards to the textures to use for the walls
 * @param no_texture path to the north wall texture
 * @param so_texture path to the south wall texture
 * @param we_texture path to the west wall texture
 * @param ea_texture path to the east wall texture
 */
typedef struct s_textures
{
	char *no_texture;
	char *so_texture;
	char *we_texture;
	char *ea_texture;
}t_textures;

/**
 * input with regards to the colors
 * @param c_color R,G,B formatted color for the ceilling
 * @param f_color R,G,B formatted color for the floor
 */
typedef struct s_colors
{
	int f_color_r;
	int f_color_g;
	int f_color_b;
	int c_color_r;
	int c_color_g;
	int c_color_b;
}t_colors;

/**
 * input with regards to the colors
 * @param c_color R,G,B formatted color for the ceilling
 * @param f_color R,G,B formatted color for the floor
 */
typedef struct s_data_input
{
	bool	player;
	int		nb_lines;
	char	**parsed_map; // needs to be freed at some point
}t_data_input;

/**
 * Main struct with all the information that is needed to run
 * @param 
 */
typedef struct s_data
{
 	t_textures 		*textures;
	t_colors		*colors;
	t_data_input	*input;

}t_data;

/* PARSING */
int		input_validation(t_data *data, char *file);
int		parse_line(t_data *data, char *line);
void	add_data(t_data *data, char **str, int i);
void	check_image(char *path);

int		map_validation(t_data *data, char *file);
char	*rm_spaces(char *line);


#endif