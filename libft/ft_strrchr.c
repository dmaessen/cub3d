/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 10:47:46 by dmaessen          #+#    #+#             */
/*   Updated: 2022/10/27 10:55:22 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;
	char	*str;

	str = (char *)s;
	len = ft_strlen(s);
	while (len >= 0)
	{
		if (s[len] == (char)c)
			return (&str[len]);
	len--;
	}
	return (0);
}

// int	main(void)
// {
// 	const char s[30] = "Everyth1ing h25-el1se";
// 	// ft_strrchr(s, 'e');
// 	printf("%s MINE \n", ft_strrchr(s, '1'));
// 	printf("%s THEIRS", strrchr(s, '1'));
// }
