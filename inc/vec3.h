/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 19:19:16 by pchadeni          #+#    #+#             */
/*   Updated: 2019/10/08 19:19:24 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

typedef struct	s_vec3
{
	float	x;
	float	y;
	float	z;
}				t_vec3;

t_vec3			create_vec3(float x, float y, float z);
t_vec3			add_vec3(t_vec3 first, t_vec3 second);
t_vec3			sub_vec3(t_vec3 first, t_vec3 second);
float			mul_vec3(t_vec3 first, t_vec3 second);

#endif
