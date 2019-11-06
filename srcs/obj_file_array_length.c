/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_file_array_length.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:36:24 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/06 11:46:12 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

uint8_t	check_count_faces(int i, int nb_faces)
{
	if (i == 0/* || i > str[i]*/)
		return (print_parser_error(PARSING_NO_NEWLINE));
	if (nb_faces > 5 || nb_faces < 3)
		return (print_parser_error(PARSING_NB_FACES));
	return (1);
}

uint8_t		count_faces(char *str)
{
	uint8_t	nb_faces;
	int		i;
	char	*get_esp;
	char	*get_nl;

	i = 0;
	nb_faces = 0;
//printf("Starting handling_face\n");
	get_nl = ft_strchr(str, '\n');
	if (get_nl)
		while (str[i] && &str[i] < get_nl) {
//			printf("index: %c\n", str[i]);
			if (!(get_esp = ft_strchr(&str[i], ' ')))
				break ;
			nb_faces++;
			if (nb_faces >= 5)
				break ;
			i += (!get_esp) ? ft_strlen(&str[i]) : get_esp - &str[i];
			if (str[i])
				i++;
		}
//	printf("End of parcing faces, nb : %d\n", nb_faces);
	if (!check_count_faces(i, nb_faces))
		return (0);
//	printf("len_faces : %zu\n", parse->len_faces);
	return (nb_faces == 5 || (!get_esp && nb_faces == 4)) ? 4 : 3;
}
uint8_t	handle_faces(t_parse_obj *parse, char *str)
{
	int	nb_faces;

	nb_faces = count_faces(str);
	if (nb_faces == 0)
		return (0);
	parse->len_faces += nb_faces == 4 ? 6 : 3;
	return (1);
}

uint8_t	get_length_arrays_obj(char *data, t_parse_obj *parse)
{
	size_t	i;
	char	*get_nl;

	i = 0;
	while (data[i])
	{
		if ((get_nl = ft_strchr(&data[i], '\n')) == NULL)
			return (1);
		if (!ft_strncmp(&data[i], "v ", 2))
			parse->len_vertices++;
		else if (!ft_strncmp(&data[i], "vt ", 3))
			parse->len_vertices_texture++;
		else if (!ft_strncmp(&data[i], "vn ", 3))
			parse->len_vertices_normal++;
		else if (!ft_strncmp(&data[i], "f ", 2))
			if (!handle_faces(parse, &data[i]))
				return (0);
		i += get_nl - &data[i];
		i++;
	}
	return (1);
}

