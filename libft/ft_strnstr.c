/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:14:17 by dmaessen          #+#    #+#             */
/*   Updated: 2022/10/27 11:03:35 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	size;
	char	*str;

	str = (char *)haystack;
	if (needle[0] == 0)
	{
		return (str);
	}
	size = 0;
	while (haystack[size] != '\0' && size < len)
	{
		i = 0;
		while ((haystack[size + i] == needle[i]) && needle[i] != '\0')
		{
		i++;
			if ((needle[i] == '\0') && (ft_strlen(needle) <= len)
				&& ((size + i) <= len))
			{
				return (&str[size]);
			}
		}
		size++;
	}
	return (0);
}

// int	main(void)
// {
// 	// const char	haystack[100] = "gfdsrhg";
// 	// const char	needle[100] = "hg";
// 	printf("%p \n", ft_strnstr("aaxx", "xx", 3));
// 	printf("%s \n", ft_strnstr("aaxx", "xx", 3));
// 	printf("%p", strnstr("aaxx", "xx", 3));
// 	printf("%s", strnstr("aaxx", "xx", 3));
// }
