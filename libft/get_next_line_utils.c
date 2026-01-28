/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 13:49:06 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/01/28 16:48:36 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_secondtab_limits(int i, char *newstr, char *s2, int limits)
{
	int	b;

	b = 0;
	while (s2 != NULL && s2[b] != '\0' && b < limits)
	{
		newstr[i] = s2[b];
		i++;
		b++;
	}
	newstr[i] = '\0';
	return (newstr);
}

char	*ft_strjoin_limits(char *s1, char *s2, int limits)
{
	int		i;
	int		len;
	char	*newstr;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + limits;
	newstr = (char *)malloc(sizeof(char) * len + 1);
	if (newstr == NULL)
		return (NULL);
	i = 0;
	while (s1 != NULL && s1[i])
	{
		newstr[i] = s1[i];
		i++;
	}
	return (ft_secondtab_limits(i, newstr, s2, limits));
}
