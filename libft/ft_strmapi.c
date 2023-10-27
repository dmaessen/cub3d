/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:06:34 by dmaessen          #+#    #+#             */
/*   Updated: 2022/10/26 17:36:51 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	str = malloc((i + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

// char	f(unsigned int i, char a)
// {
// 	char str;

// 	str = a + i;
// 	return (str);
// }

// int	main(void)
// {
// 	char const s[100] = "abcd";
// 	printf("%s", ft_strmapi(s, f));
// 	return (0);
// }
