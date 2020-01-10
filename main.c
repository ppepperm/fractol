/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 15:07:15 by ppepperm          #+#    #+#             */
/*   Updated: 2020/01/06 15:07:17 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	deal_key(int key, void *param)
{
	t_julia *julia;

	julia = (t_julia*) param;
	if (key == 65362 || key == 126)
	{
		mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
		julia->c.re += 0.005;
		draw_julia(*julia);
	}
	if (key == 65364 || key == 125)
	{
		mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
		julia->c.re -= 0.005;
		draw_julia(*julia);
	}
	if (key == 65361 || key == 123)
	{
		mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
		julia->c.im -= 0.005;
		draw_julia(*julia);
	}
	if (key == 65363 || key == 124)
	{
		mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
		julia->c.im += 0.005;
		draw_julia(*julia);
	}
	if (key == 53 || key == 65307)
	{
		exit(0);
	}
	return (0);
}

int	cls(void *param)
{
	char *kek;

	kek = (char*) param;
	kek = kek;
	exit(0);
}

int	main()
{
	t_julia		julia;

	julia.x_size = 800;
	julia.y_size = 800;
	julia.endian = 1;
	julia.bpp = 32;
	julia.line_size = 800 * 4;
	julia.c = init_complex(0 - 0.74543, 0.11301);
	julia.mlx_ptr = mlx_init();
	julia.win_ptr = mlx_new_window(julia.mlx_ptr, 800, 800, "fractol");
	julia.img_ptr = mlx_new_image(julia.mlx_ptr, julia.x_size, julia.y_size);
	julia.img_data = (int*)mlx_get_data_addr(julia.img_ptr, &(julia.bpp), &(julia.line_size), &(julia.endian));
	draw_julia(julia);
	mlx_hook(julia.win_ptr, 2, 1L << 0, deal_key, (void*) &julia);
	mlx_hook(julia.win_ptr, 17, 0L, cls, (void*) &julia);
	mlx_loop(julia.mlx_ptr);
	return (0);

}
