/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parse_float.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:31:26 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/06 14:32:09 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	main()
{
	char	*tests[] = {
		"1.0", "2.", "2.0402095308520457248082",
		"55555555555555555555555555555555555555",
		"55555555555555555555555555555555555555333333333333333333333333333.0",
		"55555555555555555555555555555555555555.0",
		"abc", "a.0", "1a.0", "1.a0",
		"1..0", ".10", "2.2.4", "1.3f", "1.4 ", "2",
		"-2", "-2.0"
	};
	size_t	len = sizeof(tests) / sizeof(tests[0]);
	uint8_t	isfloat;
	float	fl;

	for (size_t i = 0; i < len; i++) {
		printf("Test for : |%s|\n", tests[i]);
		isfloat = check_float(tests[i], &fl);
		if (isfloat)
			printf("Is a float\n");
		else
			printf("Is not a float\n");
	}
	return (0);
}
