/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 13:48:48 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/01/28 17:12:34 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_find_end_of_the_line(char *stash, int from)
{
	int	a;

	a = 0;
	while (stash[a] != '\n' && stash[a] != '\0')
		a++;
	if (from == 1)
	{
		if (stash[a] == '\n')
			return (0);
		else
			return (a);
	}
	else
		return (a);
}

char	*ft_line_and_clean_stash(char *stash, char from)
{
	int		place_n;
	int		lenstash;
	char	*line;
	char	*temp_stash;

	lenstash = 0;
	if (stash != NULL)
		lenstash = ft_strlen(stash);
	place_n = ft_find_end_of_the_line(stash, 0);
	if (from == 'l')
	{
		line = ft_substr(stash, 0, place_n + 1);
		return (line);
	}
	else
	{
		temp_stash = stash;
		stash = ft_substr(temp_stash, place_n + 1, (lenstash - place_n));
		free(temp_stash);
		return (stash);
	}
}

char	*ft_line(char *buffer, char **stash, ssize_t endfile, int fd)
{
	char	*line;
	int		check_end;
	char	*temp_stash_for_free;

	line = NULL;
	check_end = 0;
	while (check_end == 0 && endfile != 0)
	{
		temp_stash_for_free = *stash;
		*stash = ft_strjoin_limits(temp_stash_for_free, buffer, endfile);
		free(temp_stash_for_free);
		if (!ft_find_end_of_the_line(*stash, 1))
		{
			line = ft_line_and_clean_stash(*stash, 'l');
			check_end = 1;
		}
		else
			endfile = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	if (endfile < BUFFER_SIZE && ft_strlen(*stash) > 0 && check_end == 0)
		line = ft_line_and_clean_stash(*stash, 'l');
	else if (endfile <= 0)
		return (free(*stash), *stash = NULL, NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*buffer;
	char		*result;
	ssize_t		endfile;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	endfile = read(fd, buffer, BUFFER_SIZE);
	if (endfile == -1)
		return (free(stash), stash = NULL, free(buffer), NULL);
	buffer[endfile] = '\0';
	result = ft_line(buffer, &stash, endfile, fd);
	if (stash != NULL)
		stash = ft_line_and_clean_stash(stash, 's');
	return (result);
}
