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
#include <OpenGL/gl.h>
#include "monitor.h"

void	display_scop(t_monitor monitor)
{
	uint8_t		end;
	float vertices[] = {
		-0.5, 0.0,
		0.5, 0.0,
		0.0, -1.0,
		-0.5, 0.0,
		0.5, 0.0,
		0.0, 1.0
	};

	end = 0;
	while (!end)
	{
		// Gestion des évènements
		SDL_WaitEvent(&monitor.event);
		if (monitor.event.window.event == SDL_WINDOWEVENT_CLOSE)
			end = 1;
		// Nettoyage de l'écran
		glClear(GL_COLOR_BUFFER_BIT);
		// On remplie puis on active le tableau Vertex Attrib 0
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vertices);
		glEnableVertexAttribArray(0);
		// On affiche le triangle
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// On désactive le tableau Vertex Attrib puisque l'on n'en a plus besoin
		glDisableVertexAttribArray(0);
		// Actualisation de la fenêtre
		SDL_GL_SwapWindow(monitor.win);
	}
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
	return 0;
}
