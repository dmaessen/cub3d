/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:58:02 by dmaessen          #+#    #+#             */
/*   Updated: 2022/10/19 13:17:14 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	int		i;
	char	*x;

	x = (char *)b;
	i = 0;
	while (len > 0)
	{
		x[i] = c;
		len--;
		i++;
	}
	return (x);
}

// int	main(void)
// {
// 	char	str[100] = "everywhre";
// 	int	c = '/';
// 	ft_memset(str, c, 2);
// 	printf("%s \n", ft_memset(str, c, 2));
// 	printf("%s", memset(str, c, 2));
// }
