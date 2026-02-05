/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 13:10:39 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/02/05 17:08:01 by tle-rhun         ###   ########.fr       */
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
	int		column;
	int		index_point;
}			t_point;

typedef struct img
{
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		length;
	int		width;
	int		*buffer_img;
	void	*img;
}			t_img;

typedef struct mlx
{
	char *av;
	int		fd;
	int		zoom;
	int		height;
	int		line;
	int		column;
	int		discrepancy;
	void	*win;
	void	*mlx;
	t_img img;
	t_point	**point;
	t_point	**iso;
}			t_data;

void	transform_on_3d(t_data *mlx);
void	recover_map(t_data *mlx, t_point ***point);

void all_process(t_data mlx);

/* EVENT */
int	close_window(void *old_mlx);
void	redirection_event(int key, t_data *mlx);
void	redirection_event2(int key, int x, int y, t_data *mlx);
void	zoom_or_height_or_discrepancy(t_data *mlx, int nb, char var);



/* DRAW */
int			get_index(int x, int y, int size_line);
void		draw_segment(t_point point1, t_point point2, t_img **img);
void		draw(t_data *value, t_img *img);

#endif