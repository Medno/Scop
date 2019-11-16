/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:37:00 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/16 11:16:47 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitor.h"
#include "mesh.h"
#include "vec3.h"
#include "shaders.h"
#include "model.h"

void	display_scop(t_monitor *monitor)
{
	uint8_t	end;
	float	count;
	t_vec3	light_color;

	end = 0;
	count = 0.0f;
	use_shader(monitor->obj_shader);
	light_color = vec3_new(1.0f, 1.0f, 1.0f);
	glUniform3fv(monitor->obj_shader->uniforms[LIGHT_COLOR_U], 1, &light_color.x);
	use_shader(monitor->light_shader);
//	set_light_uniforms(monitor->light_shader);
//Use light monitor->obj_shader iif normal coordinates
	while (!glfwWindowShouldClose(monitor->win))
	{
		clear_window(0.2f, 0.2f, 0.2f, 1.0f);
		update_delta_time(monitor->camera);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, (*monitor->mesh).texture);
		end = update_monitor(monitor);
		count += 0.005f;
	}
}

uint8_t	scop_usage(void)
{
	printf("Wrong number of parameters\n");
	printf("usage: scop file\n");
	return (1);
}

int		main(int ac, char **av)
{
	t_monitor	monitor;

	if (ac != 2)
		return (scop_usage());
	if (!init_monitor(&monitor, av[1]))
		return (1);
	display_scop(&monitor);
	destroy_monitor(monitor);
	return (0);
}
