/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 13:31:39 by ppepperm          #+#    #+#             */
/*   Updated: 2020/01/07 13:31:43 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void draw_julia(t_julia julia)
{
	get_julia_image(julia, (int*)julia.img_data);
	mlx_put_image_to_window(julia.mlx_ptr, julia.win_ptr, julia.img_ptr, 0,0);
}

void do_julia(void)
{
	t_julia		julia;

	julia.x_size = SIZE;
	julia.y_size = SIZE;
	julia.endian = 1;
	julia.bpp = 32;
	julia.line_size = SIZE * 4;
	julia.c = init_complex(0 - 0.74543, 0.11301);
	julia.mlx_ptr = mlx_init();
	julia.win_ptr = mlx_new_window(julia.mlx_ptr, SIZE, SIZE, "fractol");
	julia.img_ptr = mlx_new_image(julia.mlx_ptr, julia.x_size, julia.y_size);
	julia.img_data = (int*)mlx_get_data_addr(julia.img_ptr, &(julia.bpp), &(julia.line_size), &(julia.endian));
	julia.zoom = 1;
	julia.acc = 100;
	julia.top_left = init_complex(-2,-2);
	julia.mouse_press = 0;
	draw_julia(julia);
	mlx_hook(julia.win_ptr, 2, 1L << 0, deal_key, (void*) &julia);
	mlx_hook(julia.win_ptr, 4, 0L, deal_click, (void*) &julia);
	mlx_hook(julia.win_ptr, 5, 0L, deal_unclick, (void*) &julia);
	mlx_hook(julia.win_ptr, 6, 0L, deal_mish, (void*) &julia);
	mlx_hook(julia.win_ptr, 17, 0L, cls, (void*) &julia);
	mlx_loop(julia.mlx_ptr);
}

int	deal_key(int key, void *param) {
	t_julia *julia;

	julia = (t_julia *) param;
	if (key == 65362 || key == 126) {
		mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
		julia->c.re += (0.001 * julia->zoom);
		draw_julia(*julia);
	}
	if (key == 65364 || key == 125) {
		mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
		julia->c.re -= (0.001 * julia->zoom);
		draw_julia(*julia);
	}
	if (key == 65361 || key == 123) {
		mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
		julia->c.im -= (0.001 * julia->zoom);
		draw_julia(*julia);
	}
	if (key == 65363 || key == 124) {
		mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
		julia->c.im += (0.001 * julia->zoom);
		draw_julia(*julia);
	}
	if (key == 15) {
		mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
		julia->zoom *= 0.95;
		julia->top_left.re += (4 * julia->zoom / 0.95 - 4 * julia->zoom) / 2;
		julia->top_left.im += (4 * julia->zoom / 0.95 - 4 * julia->zoom) / 2;
		draw_julia(*julia);
	}
	if (key == 3) {
		mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
		julia->zoom /= 0.95;
		julia->top_left.re += (4 * julia->zoom * 0.95 - 4 * julia->zoom) / 2;
		julia->top_left.im += (4 * julia->zoom * 0.95 - 4 * julia->zoom) / 2;
		draw_julia(*julia);
	}
	if (key == 13) {
		mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
		julia->top_left.im += (0.01 * julia->zoom);
		draw_julia(*julia);
	}
	if (key == 1) {
		mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
		julia->top_left.im -= (0.01 * julia->zoom);
		draw_julia(*julia);
	}
	if (key == 0) {
		mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
		julia->top_left.re += (0.01 * julia->zoom);
		draw_julia(*julia);
	}
	if (key == 2) {
		mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
		julia->top_left.re -= (0.01 * julia->zoom);
		draw_julia(*julia);
	}
	if (key == 36) {
		if (julia->mouse_stop)
			julia->mouse_stop = 0;
		else
			julia->mouse_stop = 1;
	}
	if (key == 53 || key == 65307) {
		exit(0);
	}
	if (key == 24)
	{
		mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
		julia->acc += 5;
		draw_julia(*julia);
	}
	if (key == 27)
	{
		mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
		julia->acc -= 5;
		draw_julia(*julia);
	}
	//ft_putnbr(key);
	return (0);
}

int	cls(void *param)
{
	char *kek;

	kek = (char*) param;
	exit(0);
}

int deal_click(int button, int x, int y, void *param)
{
	t_julia *julia;

	julia = (t_julia*)param;
	//printf("%d %d %d\n", button, x, y);
	if (button == 4)
	{
		mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
		julia->zoom *= 0.95;
		julia->top_left.re += (4 * julia->zoom / 0.95 - 4 * julia->zoom)/2;
		julia->top_left.im += (4 * julia->zoom / 0.95 - 4 * julia->zoom)/2;
		draw_julia(*julia);
	}
	if (button == 5)
	{
		mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
		julia->zoom /= 0.95;
		julia->top_left.re += (4 * julia->zoom * 0.95 - 4 * julia->zoom)/2;
		julia->top_left.im += (4 * julia->zoom * 0.95 - 4 * julia->zoom)/2;
		draw_julia(*julia);
	}
	if (button == 1)
	{
		mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
		julia->top_left.re += (x - SIZE / 2) * (4 * julia->zoom / SIZE);
		julia->top_left.im -= (SIZE / 2 - y) * (4 * julia->zoom / SIZE);
		draw_julia(*julia);
	}
	if (button == 2)
	{
		julia->mouse_press = 1;
	}
	return (0);
}

int deal_unclick (int button, int x, int y, void *param)
{
	t_julia *julia;

	julia = (t_julia*)param;
	//printf("%d %d %d\n", button, x, y);
	if (button == 2)
	{
		julia->mouse_press = 0;
	}
	julia->mouse_pos.x = x - SIZE/2;
	julia->mouse_pos.y = SIZE/2 - y;
	return (0);
}

int deal_mish (int x, int y, void *param)
{
	t_julia *julia;

	julia = (t_julia*)param;
	if (!julia->mouse_stop)
	{
		if (julia->mouse_pos.x < x - SIZE/2)
		{
			mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
			julia->c.re += (0.001 * julia->zoom);
			draw_julia(*julia);
		}
		if (julia->mouse_pos.x > x - SIZE/2)
		{
			mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
			julia->c.re -= (0.001 * julia->zoom);
			draw_julia(*julia);
		}
		if (julia->mouse_pos.y < SIZE/2 - y)
		{
			mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
			julia->c.im += (0.001 * julia->zoom);
			draw_julia(*julia);
		}
		if (julia->mouse_pos.x > SIZE/2 - y)
		{
			mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
			julia->c.im -= (0.001 * julia->zoom);
			draw_julia(*julia);
		}
	}
	if (julia->mouse_stop && julia->mouse_press)
	{
		if (julia->mouse_pos.x < x - SIZE/2)
		{
			mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
			julia->top_left.re -= (0.01 * julia->zoom);
			draw_julia(*julia);
		}
		if (julia->mouse_pos.x > x - SIZE/2)
		{
			mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
			julia->top_left.re += (0.01 * julia->zoom);
			draw_julia(*julia);
		}
		if (julia->mouse_pos.y < SIZE/2 - y)
		{
			mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
			julia->top_left.im += (0.01 * julia->zoom);
			draw_julia(*julia);
		}
		if (julia->mouse_pos.x > SIZE/2 - y)
		{
			mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
			julia->top_left.im -= (0.01 * julia->zoom);
			draw_julia(*julia);
		}
	}
	julia->mouse_pos.x = x - SIZE/2;
	julia->mouse_pos.y = SIZE/2 - y;
	return (0);
}
