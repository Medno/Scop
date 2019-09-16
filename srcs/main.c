/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:37:00 by pchadeni          #+#    #+#             */
/*   Updated: 2019/09/10 18:44:55 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define GL3_PROTOTYPES 1
#define GL_SILENCE_DEPRECATION

#include "monitor.h"
#include "mesh.h"
#include "vec3.h"
#include "shaders.h"
#include "transform.h"
#include <OpenGL/gl.h>

void	display_scop(t_monitor monitor)
{
	uint8_t		end;
/*
	float vertices[] = {
		-0.5, 0.0, 0.0,
		0.5, 0.0, 0.0,
		0.0, -1.0, 0.0,
		-0.5, 0.0, 0.0,
		0.5, 0.0, 0.0,
		0.0, 1.0, 0.0
	};
	*/
	t_vec3 vertices[] = {
		create_vec3(-0.5, -0.5, 0.0),
		create_vec3(0.5, -0.5, 0.0),
		create_vec3(0.0, 0.5, 0.0)
//		create_vec3(-0.5, 0.0, 0.0),
//		create_vec3(0.5, 0.0, 0.0),
//		create_vec3(0.0, 1.0, 0.0)
	};
	t_shader	shader;
	t_mesh		mesh;
	t_transform	transform;
	float		count;

	end = 0;
	count = 0.0f;
	mesh = create_mesh(vertices, sizeof(vertices)/sizeof(vertices[0]));
	if (!construct_shader("./res/basicShader", &shader))
		return ;
	transform = create_transform();
	while (!end)
	{
		/*
		// Gestion des évènements
		SDL_WaitEvent(&monitor.event);
		if (monitor.event.window.event == SDL_WINDOWEVENT_CLOSE)
			end = 1;
*/
		clear_window(0.91f, 0.86f, 0.79f, 1.0f);
		transform.position.x = sinf(count);
		transform.rotation.z = count;
	dprintf(2, "Position: %f, %f, %f\n", transform.position.x, transform.position.y, transform.position.z);
		transform.scale = create_vec3(cosf(count), cosf(count), cosf(count));

		bind_shader(shader);
		update_shader(shader, transform);

		draw_mesh(mesh);
/*
		// On remplie puis on active le tableau Vertex Attrib 0
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices);
		glEnableVertexAttribArray(0);
		// On affiche le triangle
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// On désactive le tableau Vertex Attrib puisque l'on n'en a plus besoin
		glDisableVertexAttribArray(0);
*/		
		end = update_monitor(monitor);
		count += 0.01f;
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
	display_scop(monitor);
	destroy_monitor(&monitor);
	return (0);
}
