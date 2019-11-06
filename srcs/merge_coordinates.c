/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_coordinates.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 19:25:08 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/06 14:31:06 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "logger.h"
#include "vec3.h"

float	*merge_coord(t_vec3 v[], float t[], unsigned int lv, unsigned int lt)
{
	float	*merged;
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;

	if (!(merged = (float *)malloc(sizeof(float) * lv * lt * 3)))
		return (NULL);
	i = 0;
	j = 0;
	k = 0;
	while (k < lv)
	{
		merged[i] = v[k].x;
		merged[i + 1] = v[k].y;
		merged[i + 2] = v[k].z;
		merged[i + 3] = t[j];
		merged[i + 4] = t[j + 1];
		i += 5;
		j += 2;
		k += 1;
	}
	return (merged);
}
