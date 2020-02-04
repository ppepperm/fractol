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
	double		re;
	double		im;
	double		abs;
	double		phase;
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
	int			acc;
	t_complex	c;
	t_complex	top_left;
	t_point2	mouse_pos;
	double		zoom;
	char		mouse_stop;
	char 		mouse_press;
}				t_julia;

typedef struct s_mandelbrot
{
	void 		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	int		*img_data;
	int 		x_size;
	int			y_size;
	int 		bpp;
	int 		line_size;
	int 		endian;
	int			acc;
	t_complex	top_left;
	t_point2	mouse_pos;
	double		zoom;
	char 		mouse_press;
}				t_mandelbrot;

typedef struct s_ship
{
	void 		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	int		*img_data;
	int 		x_size;
	int			y_size;
	int 		bpp;
	int 		line_size;
	int 		endian;
	int			acc;
	t_complex	top_left;
	t_point2	mouse_pos;
	double		zoom;
	char 		mouse_press;
}				t_ship;

t_complex	init_complex(double re, double im);
t_complex	comp_sum(t_complex z1, t_complex z2);
t_complex	comp_dif(t_complex z1, t_complex z2);
t_complex	comp_multiply(t_complex z1, t_complex z2);

int get_mand_image(t_mandelbrot mand, int *image);

void		draw_julia(t_julia julia);

int get_julia_image(t_julia julia, int *image);
int	deal_key(int key, void *param);
int	cls(void *param);
int deal_click(int button, int x, int y, void *param);
int deal_unclick (int button, int x, int y, void *param);
int deal_mish (int x, int y, void *param);
void	do_julia(void);

int get_mand_image(t_mandelbrot mand, int *image);
int	deal_key_m(int key, void *param);
int	cls_m(void *param);
int deal_click_m(int button, int x, int y, void *param);
int deal_unclick_m(int button, int x, int y, void *param);
int deal_mish_m(int x, int y, void *param);
void do_mand(void);

int get_ship_image(t_ship ship, int *image);
int	deal_key_s(int key, void *param);
int	cls_s(void *param);
int deal_click_s(int button, int x, int y, void *param);
int deal_unclick_s(int button, int x, int y, void *param);
int deal_mish_s(int x, int y, void *param);
void do_ship(void);

#endif