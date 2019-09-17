/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 17:03:00 by pchadeni          #+#    #+#             */
/*   Updated: 2019/09/17 17:09:24 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitor.h"

static uint8_t	error_glfw(const char *err)
{
	dprintf(2, "Error : %s\n", err);
	return (0);
}

void	key_callback(GLFWwindow *w, int key, int scancode, int act, int mods)
{
	(void)scancode;
	(void)mods;
	if (key == GLFW_KEY_ESCAPE && act == GLFW_PRESS)
		glfwSetWindowShouldClose(w, GLFW_TRUE);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
} 

uint8_t	init_monitor(t_monitor *monitor)
{
	if (!glfwInit())
		return error_glfw("Error during initialization of GLFW");
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	monitor->win = glfwCreateWindow(WIDTH, HEIGHT, "Scop", NULL, NULL);
	if (!monitor->win)
	{
		glfwTerminate();
		return error_glfw("Error while creating a window");
	}
	glfwSetKeyCallback(monitor->win, key_callback);
	glfwMakeContextCurrent(monitor->win);
	glViewport(0, 0, WIDTH, HEIGHT);
	glfwSetFramebufferSizeCallback(monitor->win, framebuffer_size_callback);  
	return (1);
}

void	destroy_monitor(t_monitor *monitor)
{
	glfwDestroyWindow(monitor->win);
	glfwTerminate();
}

void	clear_window(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}

uint8_t	update_monitor(t_monitor monitor)
{
	glfwSwapBuffers(monitor.win);
	glfwPollEvents();
	return (0);
}
