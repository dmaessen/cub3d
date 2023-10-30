#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "../MLX42/include/MLX42/MLX42_Input.h"

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
	char *f_color;
	char *c_color;
}t_colors;

/**
 * Main struct with all the information that is needed to run
 * @param 
 */
typedef struct s_data
{
 	t_textures 	*textures;
	t_colors	*colors;
}t_data;


#endif