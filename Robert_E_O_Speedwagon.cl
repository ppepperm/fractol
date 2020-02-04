/* **************************************************************************** */
/*                                                                              */
/*                                                         :::      ::::::::    */
/*    Robert_E_O_Speedwagon.cl                           :+:      :+:    :+:    */
/*                                                     +:+ +:+         +:+      */
/*    By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+             */
/*   Created: 2020/01/22 14:31:32 by ppepperm          #+#    #+#               */
/*    Updated: 2020/01/22 14:31:35 by ppepperm         ###   ########.fr        */
/*                                                                              */
/* **************************************************************************** */

int check(double z_im, double z_re, double c_im, double c_re, double r, int max_iter)
{
	double res_re;
	double res_im;
	double abs;
	int i;

	i = 1;
	while (i <= max_iter)
	{
		res_re = z_re * z_re - z_im * z_im;
		res_im = z_re * z_im + z_re * z_im;
		res_re += c_re;
		res_im += c_im;
		abs = sqrt(res_re * res_re + res_im * res_im);
		if (abs > r)
		{
			return ((i * 255 /max_iter) * 256 * 256  + 50);
		}
		z_re = res_re;
		z_im = res_im;
		i++;
	}
	return (0);
}

__kernel void calc_julia(__global const double *data, __global int *image)
{
	// Get the index of the current element to be processed
	//Robert E. O. Speedwagon is the greatest hero of our time
	int i = get_global_id(0);
	int k = 0;
	int max_iter;
	double z_re;
	double z_im;
	double c_im;
	double c_re;
	double inc;
	double r;


	inc = data[0];
	c_re = data[1];
	c_im = data[2];
	max_iter = data[3];
	r = data[4];
	z_re = data[5];
	z_im = data[6] + i * inc;
	while (k < 1000)
	{
		image[k + i * 1000] = check(z_im, z_re, c_im, c_re, r, max_iter);
		k++;
		z_re += inc;
	}
}