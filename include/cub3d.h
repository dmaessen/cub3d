/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:43:40 by dmaessen          #+#    #+#             */
/*   Updated: 2024/01/08 15:27:49 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "../MLX42/include/MLX42/MLX42_Input.h"

#define WIDTH 1024
#define HEIGHT 1024

typedef enum s_PLAYER_FACING
{
	P_NORTH,
	P_SOUTH,
	P_WEST,
	P_EAST,
}t_PLAYER_FACING;

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
 * 
 */
typedef struct s_data_input
{
	bool	player;
	t_PLAYER_FACING		player_facing; 
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

/**
 * 
 */
typedef struct s_m
{
	double	posX; // position vector of player
	double	posY;
	double dirX; // direction vector of player
	double dirY;
	double planeX; // camera plane of player
	double planeY;
	double time; // to calculate time between frames
	double oldtime;
}t_m;

/* PARSING */
/**
 * first checks if the extension of the file is valid
 * then opens the file and initalisizes all textures/colors to -1
 * then reads into the file line by line with getnextline
 * sending each read line to parse_line(), checking each time if all went well
 * then closes the file
 * and checks if the textures and colors are valid
 * @param data main struct
 * @param file file hosting the map and texture/colors
 */
int		input_validation(t_data *data, char *file);
/**
 * first splits the line on spaces
 * then loops through the double array searching for the texture/colors
 * identifers and sends it to add_data()
 * frees the double array
 * @param data main struct
 * @param file file hosting the map and texture/colors
 */
int		parse_line(t_data *data, char *line);
/**
 * adds the argv coming after the texture/color identifer (NO/SO/EA/WE/C/F) 
 * to the struct, saving it for later
 * @param data main struct
 * @param str splitted map input
 * @param i position of the texture/color identifier (NO/SO/EA/WE/C/F) in str
 */
void	add_data(t_data *data, char **str, int i);

/**
 * first opens the input file and mallocs a double arrray to host the map
 * then reads the file line by line with getnextline and sends each line to parse_map()
 * when the whole file has been read, its being closed
 * and then we proceed to is_walkable_path() (ensuring the player can at least make one step in the map)
 * then we parse_spaces() (to check if all the spaces in the map are surrounded by walls)
 * @param data main struct
 * @param file file hosting the map and texture/colors
 */
int		map_validation(t_data *data, char *file, int i);

/**
 * loops through the map looking for the players position, when identified sends it
 * to check_walkable()
 * @param data main struct
 */
void	is_walkable_path(t_data *data);
/**
 * loops through the map looking for the row/line above and below the given row 
 * to check if there is a 0/empty space meaning the player can make a step
 * then we check if the amount of 0/empty spaces -- needs to be at least one
 * else an error message indicates that there is no walkable path
 * @param map inputed map
 * @param row row in the map to check
 * @param id start position of the player on the map
 */
void	check_walkable(char **map, int row, int id);
/**
 * loops through the map, each time it encounters a space if redirect to check_line()
 * if it returns 1 then displays an error message that the map is not properly surrounded by walls
 * @param data main struct
 */
void	parse_spaces(t_data *data);
/**
 * loops through the map until its on the given row, and then checks at the position pos
 * to see if its not a 0/N/S/E/W at that position, if that would be the case then it returns 1
 * meaning the map is not properly surrounded by walls. else if all good returns 0
 * @param map
 * @param row row in the map to check
 * @param pos position of the character to check
 */
int		check_line(char **map, int row, int pos);

/**
 * checks the extension of the file, if its ending in .cub
 * if ending in .cub returns 0, if not returns 1
 * @param file input file with the map
 */
int		format_validation(char *file);
/**
 * checks the color codes for the floor and ceiling are valid
 * if they're not throws an error message saying so
 * @param colors struct hosting the color codes
 */
void	validate_colors(t_colors *colors);
/**
 * first checks if the path to the texture has a dot/. as well as the lenght of the path
 * if already invali at this point throws an error message
 * then proceeds to check if the path has a .png or .jpg format else throws an error message
 * @param path path to texture
 */
void	check_image(char *path);
/**
 * first checks all the textures are present in the struct, else throws an error message mentionning the texture
 * that is missing
 * if all four textures are there, checks if they are all different from each other, if not throws
 * an error message about two textures being the same
 * @param t struct hosting the NO/SO/WE/EA textures
 */
void	check_doubles(t_textures *t);




/* RAYCASTING */
int raycaster_start(t_data *data);
void pos_player(t_data *data, t_m *m);
//void load_textures(t_data *data, mlx_t *mlx);


#endif