/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 13:10:39 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/01/29 18:06:04 by tle-rhun         ###   ########.fr       */
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
	void *mlx_ptr;
	void *win_ptr;
	void *img_ptr;
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
void	draw(t_data value, t_point **point);
#endif