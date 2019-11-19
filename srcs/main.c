/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:37:00 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/16 18:04:14 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitor.h"

void	display_keys(void)
{
	printf("Input commands:\n");
	printf("- W A S D : Camera movement\n");
	printf("- [ ] : Increase / Decrease camera speed\n");
	printf("- M : Enable / Disable mouse mode\n");
	printf("- Y U : Object movement over X axis\n");
	printf("- H J : Object movement over Y axis\n");
	printf("- B N : Object movement over Z axis\n");
	printf("- P : Change polygon mode (Fill, Line, Point)\n");
	printf("- T : Add texture\n");
	printf("- C : Change color mode (Grey, Normal if available, position)\n");
	printf("- R : Enable / Disable object rotation\n");
	printf("- L : Enable / Disable light if available\n");
	printf("- O : Change object selection (Object / Light if available)\n");
}

uint8_t	launch(const char *filename)
{
	t_monitor	monitor;

	if (!init_monitor(&monitor, filename))
		return (1);
	display_keys();
	use_shader(monitor.obj_shader);
	while (!glfwWindowShouldClose(monitor.win))
	{
		clear_window(0.2f, 0.2f, 0.2f, 1.0f);
		update_delta_time(monitor.camera);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, (*monitor.mesh).texture);
		update_monitor(&monitor);
	}
	destroy_monitor(monitor);
	return (0);
}

uint8_t	scop_usage(void)
{
	printf("Wrong number of parameters\n");
	printf("usage: scop file\n");
	return (1);
}

int		main(int ac, char **av)
{
	uint8_t		exit_code;

	if (ac != 2)
		return (scop_usage());
	exit_code = launch(av[1]);
	return (exit_code);
}
