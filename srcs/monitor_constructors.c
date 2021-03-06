/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_constructors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 15:06:28 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/16 18:54:31 by pchadeni         ###   ########.fr       */
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

static uint8_t	init_monitor_heap(t_monitor *monitor, const char *filename)
{
	monitor->transformation = NULL;
	monitor->camera = NULL;
	monitor->mesh = NULL;
	monitor->light = NULL;
	monitor->obj_shader = NULL;
	monitor->light_shader = NULL;
	monitor->light_trans = NULL;
	if (!(monitor->mesh = create_mesh(filename))
		|| !(monitor->obj_shader = construct_shader("./res/basicShader"))
		|| !(monitor->camera = init_camera())
		|| !(monitor->transformation = create_transform()))
		return (destroy_monitor(*monitor));
	if (monitor->mesh->len_normals > 0
		&& (!(monitor->light = create_mesh("./res/obj_files/cube.obj"))
		|| !(monitor->light_shader = construct_shader("./res/lightShader"))
		|| !(monitor->light_trans = create_transform())))
		return (destroy_monitor(*monitor));
	if (monitor->light_trans)
	{
		monitor->light_trans->position = vec3_new(1.2f, 1.0f, 2.0f);
		monitor->light_trans->scale = vec3_new(0.2f, 0.2f, 0.2f);
	}
	return (1);
}

uint8_t			init_monitor(t_monitor *monitor, const char *filename)
{
	monitor->win = NULL;
	if (!init_glfw_config(monitor))
		return (0);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if (!init_monitor_heap(monitor, filename))
		return (0);
	monitor->enable_texture = 0;
	monitor->enable_mouse = 0;
	monitor->enable_light = 0;
	monitor->enable_rotation = 1;
	monitor->mode = OBJ_MODE;
	monitor->color_mode = COLOR_GREY;
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
	use_shader(monitor->obj_shader);
	update_obj_shader(monitor);
	draw_mesh(*monitor->mesh);
	if (monitor->light && monitor->enable_light)
	{
		use_shader(monitor->light_shader);
		update_light_shader(monitor);
		draw_mesh(*monitor->light);
	}
	if (monitor->enable_rotation)
		monitor->transformation->rotation.y -= 0.0001f;
	glfwSwapBuffers(monitor->win);
	glfwPollEvents();
	return (0);
}

uint8_t			destroy_monitor(t_monitor monitor)
{
	if (monitor.win)
		destroy_glfw_config(&monitor);
	if (monitor.light_trans)
		free(monitor.light_trans);
	if (monitor.light_shader)
		delete_shader(monitor.light_shader);
	if (monitor.obj_shader)
		delete_shader(monitor.obj_shader);
	if (monitor.transformation)
		free(monitor.transformation);
	if (monitor.mesh)
		delete_mesh(monitor.mesh);
	if (monitor.light)
		delete_mesh(monitor.light);
	if (monitor.camera)
		free(monitor.camera);
	return (0);
}
