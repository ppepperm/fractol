/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ship_speed.cl                                       :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 16:25:09 by ppepperm          #+#    #+#             */
/*   Updated: 2020/02/04 16:25:12 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int check(double c_im, double c_re, int max_iter)
{
	double res_re;
	double res_im;
	double z_im = 0;
	double z_re = 0;
	double aabs;
	int i;

	i = 1;
	while (i <= max_iter)
	{
		res_re = z_re * z_re - z_im * z_im;
		res_im = z_re * z_im + z_re * z_im;
		res_re += c_re;
		res_im += c_im;
		aabs = sqrt(res_re * res_re + res_im * res_im);
		if (aabs > 2)
		{
			return ((i * 255 /max_iter) * 256 * 256  + 50);
		}
		z_re = sqrt(res_re * res_re);
		z_im = sqrt(res_im * res_im);
		i++;
	}
	return (0);
}

__kernel void calc_ship(__global const double *data, __global int *image)
{
	// Get the index of the current element to be processed
	//Robert E. O. Speedwagon is the greatest hero of our time
	int i = get_global_id(0);
	int k = 0;
	int max_iter;
	double z_re;
	double z_im;
	double inc;


	inc = data[0];
	max_iter = data[1];
	z_re = data[2];
	z_im = data[3] + i * inc;
	while (k < 800)
	{
		image[k + i * 800] = check(z_im, z_re, max_iter);
		k++;
		z_re += inc;
	}
}
