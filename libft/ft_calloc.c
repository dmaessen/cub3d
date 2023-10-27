/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:44:15 by dmaessen          #+#    #+#             */
/*   Updated: 2023/03/09 17:17:15 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	char	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < count * size)
	{
		ptr[i] = '\0';
		i++;
	}
	return (ptr);
}

// int	main(void)
// {
// 	int *ptr = (int *)ft_calloc(4, sizeof(int));
// 	for (int i = 0; i < 4; i++)
// 		printf("%d\n",ptr[i]);
// 	return (0);
// }
