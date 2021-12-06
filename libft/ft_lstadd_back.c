/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladarys <ladarys@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:09:44 by ladarys           #+#    #+#             */
/*   Updated: 2021/10/20 16:02:11 by ladarys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*p;

	if (new)
	{
		p = *lst;
		if (!p)
			*lst = new;
		else
		{
			while (p->next)
				p = p->next;
			p->next = new;
		}
	}
}
