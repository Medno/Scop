/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 17:19:43 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/13 14:32:11 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_vec3	vec3_new(float x, float y, float z)
{
	t_vec3	new_vec3;

	new_vec3.x = x;
	new_vec3.y = y;
	new_vec3.z = z;
	return (new_vec3);
}

float	*vec3_assign_coord(t_vec3 *vec, t_v3_coord coord)
{
	if (coord == COORD_X)
		return (&vec->x);
	else if (coord == COORD_Y)
		return (&vec->y);
	return (&vec->z);
}

t_vec3	*vec3_array(size_t size)
{
	return ((t_vec3 *)malloc(sizeof(t_vec3) * size));
}
