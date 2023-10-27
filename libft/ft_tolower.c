/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:12:17 by dmaessen          #+#    #+#             */
/*   Updated: 2022/10/19 11:52:12 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
	{
		c = (c +32);
	}
	return (c);
}

// int	main(void)
// {
// 	int	c;

// 	c = '5';
// 	ft_tolower(c);
// 	printf("%d \n", ft_tolower(c));
// 	printf("%d", tolower(c));
// 	return (0);
// }
