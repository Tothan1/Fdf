/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 13:10:41 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/01/30 18:42:04 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int	fill_struct_point(int j, int line, t_point **point, int fd)
{
	char	**split;
	int		collumn;
	int		i;

	i = 0;
	collumn = 0;
	split = ft_split(get_next_line(fd), ' ');
	while (split[collumn] != NULL)
		collumn++;
	point[j] = malloc(sizeof(t_point) * collumn);
	while (i < collumn)
	{
		point[j][i].x = i;
		point[j][i].y = j;
		point[j][i].z = ft_atoi (split[i]);
		point[j][i].column = collumn;
		point[j][i].line = line;
		point[j][i].last_of_the_line = 1;
		printf("tab[%d][%d]  y:%d x:%d z:%d column: %d line: %d\n", j, i, point[j][i].y, point[j][i].x, point[j][i].z, point[j][i].column, point[j][i].line);
		i++;
	}
	ft_free_tab(split);
	printf ("\n\n");
	// point[j][i].last_of_the_line = 0;
	j++;
	return(j);
}
t_point	**recover_map(char **av)
{
	t_point	**point;
	int		line;
	int		fd;
	int		i;

	line = 0;
	fd = open(av[1], O_RDONLY);
	while ((get_next_line(fd)) != NULL)
		line++;
	close(fd);
	fd = open(av[1], O_RDONLY);
	point = malloc(sizeof(t_point *) * (line + 1));
	i = 0;
	while (i < line)
		i = fill_struct_point(i, line, point, fd);
	point[i] = NULL;
	// printf("tab[2][0] x:%d y:%d\n", point[2][0].x, point[2][0].y);

	return (point);
}

int	close_window(void *valu)
{
	t_data	*value;

	value = (t_data *)valu;
	mlx_destroy_image(value->mlx_ptr, value->img_ptr);
	mlx_destroy_window((value->mlx_ptr), value->win_ptr);
	mlx_loop_end(value->mlx_ptr);
	// free(value->img_ptr);
	// free(value->win_ptr);
	// free(value->mlx_ptr);
	return (1);
}

int	redirection_event(int key, void *valu)
{
	if (key == 65307)
		close_window(valu);
	return (1);
}

int	main(int ac, char **av)
{
	t_data value;
	t_point **point;
	// t_point **isométrique;
	if (ac == 2)
	{
		point = recover_map(av);
		// printf("boucle while:%d", (point[j][0].column -1 ));
		value.mlx_ptr = mlx_init();
		value.win_ptr = mlx_new_window(value.mlx_ptr, 1920, 1080, "FDF 42");
		value.img_ptr = mlx_new_image(value.mlx_ptr, 1920, 1080);
		draw(value, point);
		mlx_key_hook(value.win_ptr, redirection_event, &value);
		mlx_hook(value.win_ptr, 17, 0, close_window, &value);
		mlx_loop(value.mlx_ptr);
		mlx_loop_end(value.mlx_ptr);
	}
}