/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 17:31:40 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/16 19:01:19 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitor.h"

void	edit_light_activation(t_monitor *mon, int key, int act)
{
	if (key == GLFW_KEY_L && act == GLFW_PRESS && mon->mesh->len_normals > 0)
		mon->enable_light ^= 1;
}

void	edit_mode(t_monitor *mon, int key, int act)
{
	if (key == GLFW_KEY_O && act == GLFW_PRESS && mon->mesh->len_normals > 0
		&& mon->light && mon->light_trans && mon->mode == OBJ_MODE)
	{
		mon->mode = LIGHT_MODE;
	}
	else if (key == GLFW_KEY_O && act == GLFW_PRESS
		&& mon->mesh->len_normals > 0
		&& mon->mesh && mon->transformation && mon->mode == LIGHT_MODE)
	{
		mon->mode = OBJ_MODE;
	}
	else if (mon->mode == LIGHT_MODE && mon->enable_light == 0)
		mon->mode = OBJ_MODE;
}
