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

uint8_t	launch(const char *filename)
{
	t_monitor	monitor;
	uint8_t	end;
	float	count;

	if (!init_monitor(&monitor, filename))
		return (1);
	end = 0;
	count = 0.0f;
	use_shader(monitor.obj_shader);
	while (!glfwWindowShouldClose(monitor.win))
	{
		clear_window(0.2f, 0.2f, 0.2f, 1.0f);
		update_delta_time(monitor.camera);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, (*monitor.mesh).texture);
		end = update_monitor(&monitor);
		count += 0.005f;
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

int		main(int ac, char **av)
{
	uint8_t		exit_code;

	if (ac != 2)
		return (scop_usage());
	display_keys();
	exit_code = launch(av[1]);
	return (exit_code);
}
