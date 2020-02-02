/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandel_speed.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 15:40:40 by ppepperm          #+#    #+#             */
/*   Updated: 2020/02/02 15:40:42 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fractol.h"
#include <fcntl.h>
#include <unistd.h>
#include <OpenCL/opencl.h>
#include <math.h>

int get_mand_image(t_mandelbrot mand, int *image) {
	//get source kernel in char string
	char *source;
	int fd;
	size_t f_size;
	source = (char *) malloc(sizeof(char) * 4096);
	fd = open("mand_speed.cl", O_RDWR);
	f_size = read(fd, source, 4096);
	close(fd);
	//printf("%s", source);

	//create input data array
	const int LIST_SIZE = 4;
	cl_float *A = (cl_float*)malloc(sizeof(cl_float)*LIST_SIZE);
	A[0] = 4.0 * mand.zoom/SIZE; // float increment
	A[1] = 100; //Max iter, will be converted to int
	A[2] = mand.top_left.re;
	A[3] = mand.top_left.im;

	// Get platform and device information
	cl_platform_id platform_id = NULL;
	cl_device_id device_id = NULL;
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;
	cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_CPU, 1,
						 &device_id, &ret_num_devices);
	cl_context context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);
	cl_command_queue command_queue = clCreateCommandQueue(context, device_id, 0, &ret);
	cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,
									  LIST_SIZE * sizeof(cl_float), NULL, &ret);
	cl_mem c_mem_obj = clCreateBuffer(context, CL_MEM_READ_WRITE,
									  SIZE * SIZE * sizeof(cl_int), NULL, &ret);
	ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0,
							   LIST_SIZE * sizeof(cl_float), A, 0, NULL, NULL);
	cl_program program = clCreateProgramWithSource(context, 1,
												   (const char **) &source, (const size_t *) &f_size, &ret);
	ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
	cl_kernel kernel = clCreateKernel(program, "calc_mand", &ret);
	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *) &a_mem_obj);
	ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *) &c_mem_obj);
	size_t global_item_size = SIZE; // Process the entire lists
	size_t local_item_size = SIZE/10; // Divide work items into groups of 64
	ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL,
								 &global_item_size, &local_item_size, 0, NULL, NULL);
	ret = clEnqueueReadBuffer(command_queue, c_mem_obj, CL_TRUE, 0,
							  SIZE * SIZE * sizeof(cl_int), image, 0, NULL, NULL);
	ret = clFlush(command_queue);
	ret = clFinish(command_queue);
	ret = clReleaseKernel(kernel);
	ret = clReleaseProgram(program);
	ret = clReleaseMemObject(a_mem_obj);
	ret = clReleaseMemObject(c_mem_obj);
	ret = clReleaseCommandQueue(command_queue);
	ret = clReleaseContext(context);
	free(source);
	return 0;
}
