/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:37:00 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/15 16:31:46 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitor.h"
#include "mesh.h"
#include "vec3.h"
#include "shaders.h"
#include "model.h"

uint8_t	init_mesh_shader(t_monitor *monitor, char *filename, t_shader *shader)
{
	if (!create_mesh(filename, monitor->mesh))
		return (0);
	if (!construct_shader("./res/basicShader", shader))
	{
		delete_mesh(*monitor->mesh);
		return (0);
	}
	return (1);
}

void	display_scop(t_monitor *monitor, char *filename)
{
	uint8_t		end;
	float		count;
	t_shader	shader;

	end = 0;
	count = 0.0f;
	if (!init_mesh_shader(monitor, filename, &shader))
		return ;
	use_shader(shader);
	while (!glfwWindowShouldClose(monitor->win))
	{
		clear_window(0.2f, 0.2f, 0.2f, 1.0f);
		update_delta_time(monitor->camera);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, (*monitor->mesh).texture);
		use_shader(shader);
		update_shader(&shader, monitor);
		draw_mesh(*monitor->mesh);
		end = update_monitor(monitor);
		count += 0.005f;
	}
	delete_shader(shader);
	delete_mesh(*monitor->mesh);
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
	if (!init_monitor(&monitor))
		return (1);
	display_scop(&monitor, av[1]);
	destroy_monitor(monitor);
	return (0);
}
