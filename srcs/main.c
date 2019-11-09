/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:37:00 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/09 13:16:30 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define GLFW_INCLUDE_GLCOREARB
# define GL_SILENCE_DEPRECATION

#include "monitor.h"
#include "mesh.h"
#include "vec3.h"
#include "shaders.h"
#include "model.h"
#include "logger.h"

void	display_scop(t_monitor *monitor, const char *filename)
{
	uint8_t		end;
	/*
	float	textures[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f
	};
	t_vec3 vertices[] = {
		vec3_new(-0.5f, -0.5f, -0.5f),
		vec3_new( 0.5f, -0.5f, -0.5f),
		vec3_new( 0.5f,  0.5f, -0.5f),
		vec3_new( 0.5f,  0.5f, -0.5f),
		vec3_new(-0.5f,  0.5f, -0.5f),
		vec3_new(-0.5f, -0.5f, -0.5f),

		vec3_new(-0.5f, -0.5f,  0.5f),
		vec3_new( 0.5f, -0.5f,  0.5f),
		vec3_new( 0.5f,  0.5f,  0.5f),
		vec3_new( 0.5f,  0.5f,  0.5f),
		vec3_new(-0.5f,  0.5f,  0.5f),
		vec3_new(-0.5f, -0.5f,  0.5f),

		vec3_new(-0.5f,  0.5f,  0.5f),
		vec3_new(-0.5f,  0.5f, -0.5f),
		vec3_new(-0.5f, -0.5f, -0.5f),
		vec3_new(-0.5f, -0.5f, -0.5f),
		vec3_new(-0.5f, -0.5f,  0.5f),
		vec3_new(-0.5f,  0.5f,  0.5f),

		vec3_new( 0.5f,  0.5f,  0.5f),
		vec3_new( 0.5f,  0.5f, -0.5f),
		vec3_new( 0.5f, -0.5f, -0.5f),
		vec3_new( 0.5f, -0.5f, -0.5f),
		vec3_new( 0.5f, -0.5f,  0.5f),
		vec3_new( 0.5f,  0.5f,  0.5f),

		vec3_new(-0.5f, -0.5f, -0.5f),
		vec3_new( 0.5f, -0.5f, -0.5f),
		vec3_new( 0.5f, -0.5f,  0.5f),
		vec3_new( 0.5f, -0.5f,  0.5f),
		vec3_new(-0.5f, -0.5f,  0.5f),
		vec3_new(-0.5f, -0.5f, -0.5f),

		vec3_new(-0.5f,  0.5f, -0.5f),
		vec3_new( 0.5f,  0.5f, -0.5f),
		vec3_new( 0.5f,  0.5f,  0.5f),
		vec3_new( 0.5f,  0.5f,  0.5f),
		vec3_new(-0.5f,  0.5f,  0.5f),
		vec3_new(-0.5f,  0.5f, -0.5f)
    };
*/
	t_shader	shader;
	t_mesh		mesh;
	t_transform	transform;
	float		count;

	end = 0;
	count = 0.0f;

	if (!create_mesh(filename, &mesh))
		return ;
	if (!construct_shader("./res/basicShader", &shader))
		return ;
	transform = create_transform();
	monitor->transformation = &transform;
	monitor->mesh = &mesh;
	use_shader(shader);

	while (!glfwWindowShouldClose(monitor->win))
	{
		clear_window(0.91f, 0.86f, 0.79f, 1.0f);
		update_delta_time(monitor->camera);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh.texture);

		use_shader(shader);
		update_shader(&shader, monitor);

		draw_mesh(mesh);
		end = update_monitor(monitor);
		count += 0.005f;
	}
	delete_shader(shader);
	delete_mesh(mesh);
}

//TODO : Center object with center of window 
int main(int ac, char **av)
{
	init_logger();
	t_monitor	monitor;

	if (ac != 2)
		return (1); // Usage
	if (!init_monitor(&monitor))
		return (1);
	display_scop(&monitor, av[1]);
	destroy_monitor(monitor);
	quit_logger();
	return (0);
}
