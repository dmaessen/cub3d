/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahornstr <ahornstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:43:43 by dmaessen          #+#    #+#             */
/*   Updated: 2024/02/15 14:04:41 by ahornstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "cub3d.h"

/**
 * prints out "Error" followed by an explicit error message on a new line
 * @param str error message
 */
void	err_msg(char *str);

/**
 * frees the content of str single and double pointer
 * @param str 
 */
void	free_str(char **str);
/**
 * frees the content of the textures and colors stored in data, and resets them to NULL
 * @param data data struct
 */
void	free_struct(t_data *data);

/**
 * compares the null-terminated strings s1 and s2.
 * returns an integer greater than, equal to, or less than 0, according as the string s1 is greater than, equal
 * to, or less than the string s2. The comparison is done using unsigned characters, so that ‘\200’ is greater than ‘\0’.
 * @param s1 string 1 to be compared
 * @param s2 string 2 to be compared
 */
int		ft_strcmp(const char *s1, const char *s2);
/**
 * The calloc() function contiguously allocates enough space for count
 * objects that are size bytes of memory each and returns a pointer to the
 * allocated memory.  The allocated memory is filled with bytes of value zero.
 * If successful, calloc(), malloc(), realloc(), reallocf(), and valloc()
 * functions return a pointer to allocated memory.  If there is an error,
 * they return a NULL pointer and set errno to ENOMEM.
 * this version of calloc exits with 1 if malloc fails to allocate
 * @param count 
 * @param size
 */
void	*calloc_exit(size_t count, size_t size);
/**
 * to facilitate the parsing of the map all the spaces are removed to be able to identify
 * unwanted characters in the map
 * @param line line read from the input file
 */
char	*rm_spaces(char *line);

char	*ft_strdup_check(const char *s1);
int		ft_strarrlen(char **arr);

#endif