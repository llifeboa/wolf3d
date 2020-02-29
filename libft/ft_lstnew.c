/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llifeboa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 10:52:43 by llifeboa          #+#    #+#             */
/*   Updated: 2019/04/15 10:52:44 by llifeboa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list		*list;

	list = (t_list *)malloc(sizeof(*list));
	if (!list)
		return (0);
	if (!content)
	{
		list->content = 0;
		list->content_size = 0;
	}
	else
	{
		list->content = (void*)malloc(content_size);
		if (!content)
		{
			free(list);
			return (0);
		}
		ft_memcpy(list->content, content, content_size);
		list->content_size = content_size;
	}
	list->next = 0;
	return (list);
}
