/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_file_array_length.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:36:24 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/07 10:40:32 by pchadeni         ###   ########.fr       */
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

uint8_t	count_faces(char *str)
{
	uint8_t	nb_faces;
	int		i;
	char	*get_esp;
	char	*get_nl;

	i = 0;
	nb_faces = 0;
	get_nl = ft_strchr(str, '\n');
	if (!get_nl)
		get_nl = str + ft_strlen(str);
	while (str[i] && &str[i] < get_nl)
	{
		if (!(get_esp = ft_strchr(&str[i], ' ')))
			break ;
		nb_faces++;
		if (nb_faces >= 5)
			break ;
		i += (!get_esp) ? ft_strlen(&str[i]) : get_esp - &str[i];
		if (str[i])
			i++;
	}
	if (!check_count_faces(i, nb_faces))
		return (0);
	return (nb_faces == 5 || (!get_esp && nb_faces == 4)) ? 4 : 3;
}

uint8_t	handle_faces(t_parser_obj *parser, char *str)
{
	int	nb_faces;

	nb_faces = count_faces(str);
	if (nb_faces == 0)
		return (0);
	parser->len_faces += nb_faces == 4 ? 6 : 3;
	return (1);
}

uint8_t	get_length_arrays_obj(char *data, t_parser_obj *parser)
{
	long	i;
	char	*get_nl;

	i = 0;
	while (i < parser->obj_size)
	{
		get_nl = ft_strchr(&data[i], '\n');
		if (get_nl == NULL)
			get_nl = data + parser->obj_size;
		if (!ft_strncmp(&data[i], "v ", 2))
			parser->len_vertices++;
		else if (!ft_strncmp(&data[i], "vt ", 3))
			parser->len_vertices_texture++;
		else if (!ft_strncmp(&data[i], "vn ", 3))
			parser->len_vertices_normal++;
		else if (!ft_strncmp(&data[i], "f ", 2))
			if (!handle_faces(parser, &data[i]))
				return (0);
		i += get_nl - &data[i];
		i++;
	}
	return (1);
}
