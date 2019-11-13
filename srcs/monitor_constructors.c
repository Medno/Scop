/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_constructors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 15:06:28 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/13 15:51:27 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitor.h"

/*
** Clear the screen from the previous iteration
*/

void			clear_window(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

static uint8_t	init_monitor_heap(t_monitor *monitor)
{
	if (!(monitor->camera = init_camera()))
		return (0);
	if (!(monitor->mesh = (t_mesh *)malloc(sizeof(t_mesh))))
	{
		free(monitor->camera);
		return (0);
	}
	if (!(monitor->transformation = create_transform()))
	{
		free(monitor->mesh);
		free(monitor->camera);
		return (0);
	}
	return (1);
}

uint8_t			init_monitor(t_monitor *monitor)
{
	if (!init_glfw_config(monitor))
		return (0);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if (!init_monitor_heap(monitor))
		return (destroy_glfw_config(monitor));
	monitor->enable_texture = 0;
	monitor->enable_mouse = 0;
	return (1);
}

/*
** Render loop.
** glfwSwapBuffers will swap the color buffer that has been used to
** draw in during this iteration and show it as output to the screen
** glfwPollEvents checks any events are triggered.
*/

uint8_t			update_monitor(t_monitor *monitor)
{
	glfwSwapBuffers(monitor->win);
	glfwPollEvents();
	return (0);
}

void			destroy_monitor(t_monitor monitor)
{
	destroy_glfw_config(&monitor);
	free(monitor.transformation);
	free(monitor.mesh);
	free(monitor.camera);
}
