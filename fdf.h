/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 13:10:39 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/02/02 17:31:01 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "./libft/libft.h"
# include "./minilibx-linux/mlx.h"
# include <math.h>

typedef struct point
{
	int		x;
	int		y;
	int		z;
	int		index_point;
}			t_point;

typedef struct mlx
{
	char *av;
	int		fd;
	int		zoom;
	int		line;
	int		column;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		length_win;
	int		width_win;
	int		*buffer_img;
	void	*img;
	void	*win;
	void	*mlx;
	t_point	**point;
	t_point	**iso;
}			t_data;

/* DRAW */
int			get_index(int x, int y, int size_line);
void		draw_segment(t_point point1, t_point point2, t_data *value);
void		draw(t_data *value);
#endif