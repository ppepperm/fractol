/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ship.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 16:24:53 by ppepperm          #+#    #+#             */
/*   Updated: 2020/02/04 16:24:55 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void draw_ship(t_ship ship)
{
	get_ship_image(ship, ship.img_data);
	mlx_put_image_to_window(ship.mlx_ptr, ship.win_ptr, ship.img_ptr, 0,0);
}

void do_ship(void)
{
	t_ship ship;

	ship.x_size = SIZE;
	ship.y_size = SIZE;
	ship.endian = 1;
	ship.bpp = 32;
	ship.line_size = SIZE * 4;
	ship.mlx_ptr = mlx_init();
	ship.win_ptr = mlx_new_window(ship.mlx_ptr, SIZE, SIZE, "fractol");
	ship.img_ptr = mlx_new_image(ship.mlx_ptr, ship.x_size, ship.y_size);
	ship.img_data = (int*)mlx_get_data_addr(ship.img_ptr, &(ship.bpp), &(ship.line_size), &(ship.endian));
	ship.zoom = 1;
	ship.acc = 100;
	ship.top_left = init_complex(-2,-2);
	ship.mouse_press = 0;
	draw_ship(ship);
	mlx_hook(ship.win_ptr, 2, 1L << 0, deal_key_s, (void*) &ship);
	mlx_hook(ship.win_ptr, 4, 0L, deal_click_s, (void*) &ship);
	mlx_hook(ship.win_ptr, 5, 0L, deal_unclick_s, (void*) &ship);
	mlx_hook(ship.win_ptr, 6, 0L, deal_mish_s, (void*) &ship);
	mlx_hook(ship.win_ptr, 17, 0L, cls_s, (void*) &ship);
	mlx_loop(ship.mlx_ptr);
}

int	deal_key_s(int key, void *param)
{
	t_ship *ship;

	ship = (t_ship*)param;
	if (key == 15)
	{
		mlx_clear_window(ship->mlx_ptr, ship->win_ptr);
		ship->zoom *= 0.95;
		ship->top_left.re += (4 * ship->zoom / 0.95 - 4 * ship->zoom)/2;
		ship->top_left.im += (4 * ship->zoom / 0.95 - 4 * ship->zoom)/2;
		draw_ship(*ship);
	}
	if (key == 3)
	{
		mlx_clear_window(ship->mlx_ptr, ship->win_ptr);
		ship->zoom /= 0.95;
		ship->top_left.re += (4 * ship->zoom * 0.95 - 4 * ship->zoom)/2;
		ship->top_left.im += (4 * ship->zoom * 0.95 - 4 * ship->zoom)/2;
		draw_ship(*ship);
	}
	if (key == 13)
	{
		mlx_clear_window(ship->mlx_ptr, ship->win_ptr);
		ship->top_left.im += (0.01 * ship->zoom);
		draw_ship(*ship);
	}
	if (key == 1)
	{
		mlx_clear_window(ship->mlx_ptr, ship->win_ptr);
		ship->top_left.im -= (0.01 * ship->zoom);
		draw_ship(*ship);
	}
	if (key == 0)
	{
		mlx_clear_window(ship->mlx_ptr, ship->win_ptr);
		ship->top_left.re += (0.01 * ship->zoom);
		draw_ship(*ship);
	}
	if (key == 2)
	{
		mlx_clear_window(ship->mlx_ptr, ship->win_ptr);
		ship->top_left.re -= (0.01 * ship->zoom);
		draw_ship(*ship);
	}
	if (key == 24)
	{
		mlx_clear_window(ship->mlx_ptr, ship->win_ptr);
		ship->acc += 5;
		draw_ship(*ship);
	}
	if (key == 27)
	{
		mlx_clear_window(ship->mlx_ptr, ship->win_ptr);
		ship->acc -= 5;
		draw_ship(*ship);
	}
	if (key == 53 || key == 65307)
	{
		free_ship(*ship);
		exit(0);
	}
	//ft_putnbr(key);
	return (0);
}

int	cls_s(void *param)
{
	t_ship *kek;

	kek = (t_ship*) param;
	free_ship(*kek);
	exit(0);
}

int deal_click_s(int button, int x, int y, void *param)
{
	t_ship *ship;

	ship = (t_ship*)param;
	//printf("%d %d %d\n", button, x, y);
	if (x >= 0 && x <= SIZE && y >= 0 && y <= SIZE) {
		if (button == 4) {
			mlx_clear_window(ship->mlx_ptr, ship->win_ptr);
			ship->zoom *= 0.95;
			ship->top_left.re += (4 * ship->zoom / 0.95 - 4 * ship->zoom) / 2;
			ship->top_left.im += (4 * ship->zoom / 0.95 - 4 * ship->zoom) / 2;
			draw_ship(*ship);
		}
		if (button == 5) {
			mlx_clear_window(ship->mlx_ptr, ship->win_ptr);
			ship->zoom /= 0.95;
			ship->top_left.re += (4 * ship->zoom * 0.95 - 4 * ship->zoom) / 2;
			ship->top_left.im += (4 * ship->zoom * 0.95 - 4 * ship->zoom) / 2;
			draw_ship(*ship);
		}
		if (button == 1) {
			mlx_clear_window(ship->mlx_ptr, ship->win_ptr);
			ship->top_left.re += (x - SIZE / 2) * (4 * ship->zoom / SIZE);
			ship->top_left.im -= (SIZE / 2 - y) * (4 * ship->zoom / SIZE);
			draw_ship(*ship);
		}
		if (button == 2) {
			ship->mouse_press = 1;
		}
	}
	return (0);
}

int deal_unclick_s(int button, int x, int y, void *param)
{
	t_ship *ship;

	ship = (t_ship*)param;
	//printf("%d %d %d\n", button, x, y);
	if (button == 2)
	{
		ship->mouse_press = 0;
	}
	ship->mouse_pos.x = x - SIZE/2;
	ship->mouse_pos.y = SIZE/2 - y;
	return (0);
}

int deal_mish_s(int x, int y, void *param)
{
	t_ship *ship;

	ship = (t_ship*)param;
	if (x >= 0 && x <= SIZE && y >= 0 && y <= SIZE) {
		if (ship->mouse_press) {
			if (ship->mouse_pos.x < x - SIZE / 2) {
				mlx_clear_window(ship->mlx_ptr, ship->win_ptr);
				ship->top_left.re -= (0.01 * ship->zoom);
				draw_ship(*ship);
			}
			if (ship->mouse_pos.x > x - SIZE / 2) {
				mlx_clear_window(ship->mlx_ptr, ship->win_ptr);
				ship->top_left.re += (0.01 * ship->zoom);
				draw_ship(*ship);
			}
			if (ship->mouse_pos.y < SIZE / 2 - y) {
				mlx_clear_window(ship->mlx_ptr, ship->win_ptr);
				ship->top_left.im += (0.01 * ship->zoom);
				draw_ship(*ship);
			}
			if (ship->mouse_pos.x > SIZE / 2 - y) {
				mlx_clear_window(ship->mlx_ptr, ship->win_ptr);
				ship->top_left.im -= (0.01 * ship->zoom);
				draw_ship(*ship);
			}
		}
		ship->mouse_pos.x = x - SIZE / 2;
		ship->mouse_pos.y = SIZE / 2 - y;
	}
	return (0);
}