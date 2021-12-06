/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladarys <ladarys@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 14:45:31 by ladarys           #+#    #+#             */
/*   Updated: 2021/10/20 16:02:12 by ladarys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *src, int chr, size_t n)
{
	unsigned char	*s;
	unsigned char	c;

	s = (unsigned char *) src;
	c = (unsigned char) chr;
	while (n--)
	{
		if (*s == c)
			return ((void *)s);
		s++;
	}
	return (0);
}
