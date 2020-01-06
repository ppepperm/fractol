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
	char *kek;

	kek = (char*) param;
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
	exit(0);
}

int	main()
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_complex	c;
	int			colour;

	c.re = -2;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1000, 1000, "fractol");
	mlx_pixel_put(mlx_ptr, win_ptr, 10, 10, 255);
	while (c.re < 2)
	{
		c.im = -2;
		while (c.im < 2)
		{
			colour = (check_if_mand(c, 500));
			mlx_pixel_put(mlx_ptr, win_ptr, c.re * 250 + 500, c.im * 250 + 500, colour);
			c.im += 0.002;
		}
		c.re += 0.002;
	}
	mlx_hook(win_ptr, 2, 1L << 0, deal_key, (void*) mlx_ptr);
	mlx_hook(win_ptr, 17, 0L, cls, (void*) mlx_ptr);
	mlx_loop(mlx_ptr);
	return (0);

}
