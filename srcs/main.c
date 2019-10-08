/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:37:00 by pchadeni          #+#    #+#             */
/*   Updated: 2019/10/08 13:52:50 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define GLFW_INCLUDE_GLCOREARB
# define GL_SILENCE_DEPRECATION

#include "monitor.h"
#include "mesh.h"
#include "vec3.h"
#include "shaders.h"
#include "transform.h"
#include "logger.h"

void	display_scop(t_monitor *monitor)
{
	uint8_t		end;
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
		create_vec3(-0.5f, -0.5f, -0.5f),
		create_vec3( 0.5f, -0.5f, -0.5f),
		create_vec3( 0.5f,  0.5f, -0.5f),
		create_vec3( 0.5f,  0.5f, -0.5f),
		create_vec3(-0.5f,  0.5f, -0.5f),
		create_vec3(-0.5f, -0.5f, -0.5f),

		create_vec3(-0.5f, -0.5f,  0.5f),
		create_vec3( 0.5f, -0.5f,  0.5f),
		create_vec3( 0.5f,  0.5f,  0.5f),
		create_vec3( 0.5f,  0.5f,  0.5f),
		create_vec3(-0.5f,  0.5f,  0.5f),
		create_vec3(-0.5f, -0.5f,  0.5f),

		create_vec3(-0.5f,  0.5f,  0.5f),
		create_vec3(-0.5f,  0.5f, -0.5f),
		create_vec3(-0.5f, -0.5f, -0.5f),
		create_vec3(-0.5f, -0.5f, -0.5f),
		create_vec3(-0.5f, -0.5f,  0.5f),
		create_vec3(-0.5f,  0.5f,  0.5f),

		create_vec3( 0.5f,  0.5f,  0.5f),
		create_vec3( 0.5f,  0.5f, -0.5f),
		create_vec3( 0.5f, -0.5f, -0.5f),
		create_vec3( 0.5f, -0.5f, -0.5f),
		create_vec3( 0.5f, -0.5f,  0.5f),
		create_vec3( 0.5f,  0.5f,  0.5f),

		create_vec3(-0.5f, -0.5f, -0.5f),
		create_vec3( 0.5f, -0.5f, -0.5f),
		create_vec3( 0.5f, -0.5f,  0.5f),
		create_vec3( 0.5f, -0.5f,  0.5f),
		create_vec3(-0.5f, -0.5f,  0.5f),
		create_vec3(-0.5f, -0.5f, -0.5f),

		create_vec3(-0.5f,  0.5f, -0.5f),
		create_vec3( 0.5f,  0.5f, -0.5f),
		create_vec3( 0.5f,  0.5f,  0.5f),
		create_vec3( 0.5f,  0.5f,  0.5f),
		create_vec3(-0.5f,  0.5f,  0.5f),
		create_vec3(-0.5f,  0.5f, -0.5f)
    };

	t_shader	shader;
	t_mesh		mesh;
	t_transform	transform;
	float		count;

	end = 0;
	count = 0.0f;

	mesh = create_mesh(vertices, sizeof(vertices)/sizeof(vertices[0]),
			textures, sizeof(textures)/sizeof(textures[0]));
	if (!construct_shader("./res/basicShader", &shader))
		return ;
	transform = create_transform();
	monitor->transformation = &transform;
	use_shader(shader);

	while (!glfwWindowShouldClose(monitor->win))
	{
		clear_window(0.91f, 0.86f, 0.79f, 1.0f);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh.texture);

		use_shader(shader);
		update_shader(shader, *(monitor->transformation));

		draw_mesh(mesh);
		end = update_monitor(monitor);
		count += 0.005f;
	}
	delete_shader(shader);
	delete_mesh(mesh);
}

int main(int ac, char **av)
{
	init_logger();
	(void)ac;
	(void)av;
	t_monitor	monitor;

	if (!init_monitor(&monitor))
		return (1);
	display_scop(&monitor);
	destroy_monitor(monitor);
	quit_logger();
	return (0);
}
