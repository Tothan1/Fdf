/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 13:10:39 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/02/04 19:35:11 by tle-rhun         ###   ########.fr       */
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

typedef struct img
{
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		length_win;
	int		width_win;
	int		*buffer_img;
	void	*old_img;
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
	void	*win;
	void	*mlx;
	t_img img;
	t_point	**point;
	t_point	**old_point;
	t_point	**iso;
}			t_data;

void	transform_on_3d(t_data *mlx);
void	recover_map(t_data *mlx, t_point ***point);

void all_process(t_data mlx);

/* EVENT */
int	close_window(void *old_mlx);
void	redirection_event(int key, t_data *mlx);
void	redirection_event2(int key, int x, int y, t_data *mlx);
void	zoom(t_data	*mlx, int nb);



/* DRAW */
int			get_index(int x, int y, int size_line);
void		draw_segment(t_point point1, t_point point2, t_img **img);
void		draw(t_data *value, t_img *img);
int	check_point(t_data *mlx);

#endif