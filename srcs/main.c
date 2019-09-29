/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:37:00 by pchadeni          #+#    #+#             */
/*   Updated: 2019/09/17 19:01:44 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define GLFW_INCLUDE_GLCOREARB
# define GL_SILENCE_DEPRECATION

#include "monitor.h"
#include "mesh.h"
#include "vec3.h"
#include "shaders.h"
#include "transform.h"

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
/*	t_vec3 vertices[] = {
		create_vec3(-0.5, -0.5, 0.5), //FRONT_LEFT
		create_vec3(0.5, -0.5, 0.5), //RIGHT_LEFT
		create_vec3(0.0, sqrt(3.0)/3.0, 0.0), //MIDDLE

		create_vec3(-0.5, -0.5, 0.5), //FRONT_LEFT
		create_vec3(0.5, -0.5, 0.5), //RIGHT_LEFT
		create_vec3(0.0, -0.5, -0.5), //BACK

		create_vec3(-0.5, -0.5 , 0.5), //FRONT_LEFT
		create_vec3(0.0, sqrt(3.0)/3.0, 0.0), //MIDDLE
		create_vec3(0.0, -0.5, -0.5), //BACK

		create_vec3(0.5, -0.5, 0.5), //RIGHT_LEFT
		create_vec3(0.0, sqrt(3.0)/3.0, 0.0),
		create_vec3(0.0, -0.5, -0.5) //BACK
	};
	*/
	t_shader	shader;
	t_mesh		mesh;
	t_transform	transform;
	float		count;

	end = 0;
	count = 0.0f;
	mesh = create_mesh(vertices, sizeof(vertices)/sizeof(vertices[0]), textures, sizeof(textures)/sizeof(textures[0]));
	if (!construct_shader("./res/basicShader", &shader))
		return ;
	transform = create_transform();
	monitor->transformation = &transform;
	while (!glfwWindowShouldClose(monitor->win))
	{
		clear_window(0.91f, 0.86f, 0.79f, 1.0f);
//		transform.position.x = sinf(count);
//		transform.rotation.z = count;
//		transform.rotation.y = count;
//	dprintf(2, "Position: %f, %f, %f\n", transform.position.x, transform.position.y, transform.position.z);
//	transform.scale = create_vec3(cosf(count), cosf(count), cosf(count));

		bind_shader(shader);
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
	(void)ac;
	(void)av;
	t_monitor	monitor;

	if (!init_monitor(&monitor))
		return (1);
	display_scop(&monitor);
	destroy_monitor(&monitor);
	return (0);
}
