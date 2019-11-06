/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_basic_operations.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 13:37:53 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/06 13:37:54 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_vec3	vec3_add(t_vec3 first, t_vec3 second)
{
	return (vec3_new(first.x + second.x, first.y + second.y,
		first.z + second.z));
}

t_vec3	vec3_sub(t_vec3 first, t_vec3 second)
{
	return (vec3_new(first.x - second.x, first.y - second.y,
		first.z - second.z));
}

t_vec3	vec3_mul_scalar(t_vec3 vect, float scalar)
{
	return (vec3_new(vect.x * scalar, vect.y * scalar, vect.z * scalar));
}
