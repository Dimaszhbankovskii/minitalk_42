/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladarys <ladarys@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 15:15:20 by ladarys           #+#    #+#             */
/*   Updated: 2021/10/20 16:02:13 by ladarys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_char_in_set(char chr, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == chr)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	start;
	size_t	end;
	size_t	i;

	start = 0;
	while (ft_char_in_set(s1[start], set) && s1[start])
		start++;
	end = ft_strlen(s1);
	while (ft_char_in_set(s1[end - 1], set) && end > start)
		end--;
	str = (char *)malloc((sizeof(*s1) * (end - start + 1)));
	if (!str)
		return (NULL);
	i = 0;
	while (start < end)
		str[i++] = s1[start++];
	str[i] = '\0';
	return (str);
}
