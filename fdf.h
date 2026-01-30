/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 13:10:39 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/01/30 18:31:01 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include "./libft/libft.h"
#include "./minilibx-linux/mlx.h"

#include <math.h>

typedef struct mlx
{
	int bits_per_pixel;
	int size_line;
	int endian;
	int * buffer_img;
	void *img_ptr;
	void *win_ptr;
	void *mlx_ptr;
}		t_data;

typedef struct point
{
	int x;
	int y;
	int z;
	int line;
	int column;
	int last_of_the_line;
}		t_point;

	/* DRAW */ 
int	get_index(int x, int y, int size_line);
void	draw_segment(t_point point1, t_point point2, t_data value);
void	draw(t_data value, t_point **point);
#endif