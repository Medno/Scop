/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 17:31:40 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/16 17:35:32 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitor.h"

void			edit_light_activation(t_monitor *mon, int key, int act)
{
	if (key == GLFW_KEY_F && act == GLFW_PRESS && mon->mesh->len_normals > 0)
		mon->enable_light ^= 1;
}
