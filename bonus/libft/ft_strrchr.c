/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladarys <ladarys@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 16:17:19 by ladarys           #+#    #+#             */
/*   Updated: 2021/10/20 16:02:13 by ladarys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *string, int symbol)
{
	char	*str;
	char	c;

	str = (char *)(string + ft_strlen(string));
	c = (char) symbol;
	while ((*str != c) && str > string)
		str--;
	if (*str == c)
		return (str);
	else
		return (NULL);
}
