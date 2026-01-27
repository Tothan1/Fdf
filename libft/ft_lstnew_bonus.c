/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:15:00 by tle-rhun          #+#    #+#             */
/*   Updated: 2025/11/19 16:08:16 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*newlst;

	newlst = malloc(sizeof (t_list));
	if (!newlst)
		return (NULL);
	newlst->content = content;
	newlst->next = NULL;
	return (newlst);
}

/* #include <stdio.h>
int main (void)
{
	int content = 12;
	t_list * lst= ft_lstnew(&content);
	printf("newlst:%d", *(int *)(lst->content));
	free(lst);
	return (0);
} */