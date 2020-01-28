/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 12:31:45 by ppepperm          #+#    #+#             */
/*   Updated: 2020/01/22 14:21:00 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fractol.h"
#include <fcntl.h>
#include <unistd.h>
#include <OpenCL/opencl.h>
#include <math.h>

int get_julia_image(t_julia julia, int *image) {
	//get source kernel in char string
	char *source;
	int fd;
	size_t f_size;
	source = (char *) malloc(sizeof(char) * 4096);
	fd = open("Robert_E_O_Speedwagon.cl", O_RDWR);
	f_size = read(fd, source, 4096);
	close(fd);
	//printf("%s", source);

	//create input data array
	const int LIST_SIZE = 7;
	cl_float *A = (cl_float*)malloc(sizeof(cl_float)*LIST_SIZE);
	A[0] = 4.0 * julia.zoom/1000.0; // float increment
	A[1] = julia.c.re; // ReC
	A[2] = julia.c.im; //ImC
	A[3] = 200; //Max iter, will be converted to int
	A[4] = (1.0 + sqrt(1 + 4 * julia.c.abs))/2.0; // fractal haracteristic number
	A[5] = julia.top_left.re;
	A[6] = julia.top_left.im;

	// Get platform and device information
	cl_platform_id platform_id = NULL;
	cl_device_id device_id = NULL;
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;
	cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
	//printf("1 %d\n", ret);
	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_CPU, 1,
						 &device_id, &ret_num_devices);
	//printf("2 %d\n", ret);
	// Create an OpenCL context
	cl_context context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);
	//printf("3 %d\n", ret);
	// Create a command queue
	cl_command_queue command_queue = clCreateCommandQueue(context, device_id, 0, &ret);
	//printf("4 %d\n", ret);
	// Create memory buffers on the device for each vector
	cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,
									  LIST_SIZE * sizeof(cl_float), NULL, &ret);
	//printf("5 %d\n", ret);
	cl_mem c_mem_obj = clCreateBuffer(context, CL_MEM_READ_WRITE,
									  1000 * 1000 * sizeof(cl_int), NULL, &ret);
	//printf("6 %d\n", ret);
	// Copy the data array
	ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0,
							   LIST_SIZE * sizeof(cl_float), A, 0, NULL, NULL);
	//printf("7 %d\n", ret);
	// Create a program from the kernel source
	cl_program program = clCreateProgramWithSource(context, 1,
												   (const char **) &source, (const size_t *) &f_size, &ret);
	//printf("8 %d\n", ret);
	// Build the program
	ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
	//printf("9 %d\n", ret);
	// Create the OpenCL kernel
	cl_kernel kernel = clCreateKernel(program, "calc_julia", &ret);
	//printf("10 %d\n", ret);
	// Set the arguments of the kernel
	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *) &a_mem_obj);
	//printf("11 %d\n", ret);
	ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *) &c_mem_obj);
	//printf("12 %d\n", ret);
	// Execute the OpenCL kernel on the list
	size_t global_item_size = 1000; // Process the entire lists
	size_t local_item_size = 100; // Divide work items into groups of 64
	ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL,
								 &global_item_size, &local_item_size, 0, NULL, NULL);
	//printf("13 %d\n", ret);
	// Read the memory buffer C on the device to the local variable C
	//cl_int *C = (cl_int *) malloc(sizeof(cl_int) * 800 * 800);
	ret = clEnqueueReadBuffer(command_queue, c_mem_obj, CL_TRUE, 0,
							  1000 * 1000 * sizeof(cl_int), image, 0, NULL, NULL);
	//printf("14 %d\n", ret);
	// Display the result to the screen
	/*for ( int i = 0; i < 800 * 800; i++) {
		if (C[i] == 0) {
			printf("%d\n", C[i]);
		}
	}*/

	// Clean up
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
