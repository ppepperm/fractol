/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 15:22:31 by ppepperm          #+#    #+#             */
/*   Updated: 2020/01/06 15:22:33 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define SIZE 1000
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

typedef struct 	s_complex
{
	float		re;
	float		im;
	float		abs;
	float		phase;
}				t_complex;

typedef struct  s_julia
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	int		*img_data;
	int 		x_size;
	int			y_size;
	int 		bpp;
	int 		line_size;
	int 		endian;
	t_complex	c;
	t_complex	top_left;
	t_point2	mouse_pos;
	float		zoom;
	char		mouse_stop;
	char 		mouse_press;
}				t_julia;

typedef struct s_mandelbrot
{
	void 		*mlx_ptr;
	void		*win_ptr;
	t_point2	offset;
}				t_mandelbrot;

t_complex	init_complex(float re, float im);
t_complex	comp_sum(t_complex z1, t_complex z2);
t_complex	comp_dif(t_complex z1, t_complex z2);
t_complex	comp_multiply(t_complex z1, t_complex z2);

int			check_if_mand(t_complex c, int max_iter);

void		draw_julia(t_julia julia);

int get_julia_image(t_julia julia, int *image);

#endif