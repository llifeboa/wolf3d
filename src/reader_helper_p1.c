/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_helper_p1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlayna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 02:11:28 by nlayna            #+#    #+#             */
/*   Updated: 2020/03/12 02:11:29 by nlayna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void			map_validation(t_map *map, int check)
{
	if (map->height < 3 || map->width < 3 || check == 0)
		exit_with_error("error: invalid map!\n");
}

void			free_split(char **split)
{
	int i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

t_vec3			get_pos(t_map *map, char *line)
{
	t_vec3	pos;
	char	**find_player;
	int		x;

	find_player = ft_strsplit(line, ' ');
	x = 0;
	while (find_player[x])
	{
		if (find_player[x][0] == 'p')
			break ;
		x++;
	}
	pos.x = 64 * x + 32;
	pos.y = 32;
	pos.z = 64 * (map->height - 1) + 32;
	free_split(find_player);
	return (pos);
}

/*
**	int check_elem(char *s, int wc)
**	s - current elem
**	wc - elements count
*/

int				check_elem(char *s, int wc)
{
	char	**elem;
	int		i;
	int		value;
	int		check;

	malloc_check((elem = ft_strsplit(s, ',')));
	i = 0;
	check = 1;
	if (wc == 1)
	{
		if (elem[i][0] != 'p')
			value = ft_atoi_with_non_digit_error(elem[i]);
		if (!(value >= 0 && value <= 10) || !(value != 112))
			check = 0;
	}
	else
		while (i < wc)
		{
			value = ft_atoi_with_non_digit_error(elem[i]);
			if (!(value > 0 && value <= 10))
				check = 0;
			i++;
		}
	free_split(elem);
	return (check);
}

/*
**	int check_line(char **str, int flag, int w_count)
**		str - array from split
**		flag - option for start/middle/end line
**	 		1 = start/end
**			2 = middle
**		w_count - count of elements
*/

int				check_line(char **str, int flag, int w_count)
{
	int i;

	i = 0;
	if (flag == 1)
		while (str[i])
		{
			if (ft_atoi_with_non_digit_error(str[i]) == 0 || str[i][0] == 'p')
				return (0);
			i++;
		}
	else if (flag == 2)
		if (ft_atoi_with_non_digit_error(str[i]) == 0 ||
			ft_atoi_with_non_digit_error(str[w_count - 1]) == 0 ||
			str[i][0] == 'p' || str[w_count - 1][0] == 'p')
			return (0);
	return (1);
}
