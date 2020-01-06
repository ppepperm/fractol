/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:08:48 by ppepperm          #+#    #+#             */
/*   Updated: 2019/11/13 16:08:51 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "mlx.h"
# include <math.h>
# include <stdio.h>
# include "libft.h"
# include <fcntl.h>

typedef struct	s_point2
{
	int			x;
	int			y;
}				t_point2;

typedef struct	s_point3
{
	float		x;
	float		y;
	float		z;
}				t_point3;

typedef struct	s_qatern
{
	float		s;
	float		i;
	float		j;
	float		k;
}				t_qatern;

typedef struct	s_fdf{
	void		*mlx_ptr;
	void		*win_ptr;
	t_point3	**points;
	t_point2	center;
	t_point2	size;
	int			offset_x;
	int			offset_y;
	t_point3	self_sys[3];
	int			iso;
}				t_fdf;

typedef	void(*t_draw)(t_fdf, t_point3, t_point3, int);

void			put_line(t_fdf fdf, t_point2 st, t_point2 en, int color);
void			put_iso_line(t_fdf fdf, t_point3 st, t_point3 en, int color);
void			put_half_iso_line
(t_fdf fdf, t_point3 st, t_point3 en, int color);
int				put_iso_fdf(t_fdf fdf, int color);

t_point2		init_p2(int x, int y);
t_point3		init_p3(float x, float y, float z);
t_point3		**init_table(t_point2 size);
int				free_fdf(t_fdf fdf);
void			init_fdf(t_fdf *fdf, t_point2 size);

void			x_rotate(t_point3 *point, float angle, t_fdf fdf);
void			y_rotate(t_point3 *point, float angle, t_fdf fdf);
void			z_rotate(t_point3 *point, float angle, t_fdf fdf);
void			rotate_fdf(t_fdf fdf, int angle, void
f(t_point3*, float, t_fdf));
void			mult_fdf(t_fdf fdf, float mult);

int				get_size(char *filename, t_point2 *size);
int				get_fdf(char *filename, t_point2 size, t_fdf *fdf);

t_qatern		init_qatern(float s, float i, float j, float k);
void			normalize(t_point3 *vec);
t_qatern		init_rotor(t_point3 axis, float angle);
t_qatern		inverse(t_qatern base);
t_qatern		multiply(t_qatern q, t_qatern p);

void			rotate1(t_fdf *fdf, int key);
void			rotate2(t_fdf *fdf, int key);
void			size_change(t_fdf *fdf, int key);
void			move(t_fdf *fdf, int key);
void			projection_change(t_fdf *fdf, int key);

#endif
