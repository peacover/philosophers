/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 15:06:23 by yer-raki          #+#    #+#             */
/*   Updated: 2021/09/16 15:41:43 by yer-raki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_args(int argc, t_args *args)
{
	if (ft_init(args, argc))
		return (1);
	if (argc > 6 || argc < 5)
	{
		printf("ERROR ARGS!\n");
		return (1);
	}
	return (0);
}

int	check_args_init(int argc, char **argv, t_args *args)
{
	int		i;
	int		j;
	char	*tmp;
	char	*tmp2;

	i = 0;
	j = 0;
	if (init_args(argc, args))
		return (1);
	while (argc > ++i)
	{
		j = 0;
		while (ft_strlen(argv[i]) > 1 && (argv[i][j] == '0'))
			j++;
		tmp = ft_substr(argv[i], j, ft_strlen((argv[i]) - j));
		tmp2 = ft_itoa(ft_atoi(tmp));
		if (ft_strcmp(tmp, tmp2) || (j != 0 && argv[i][j] == '-'))
		{
			printf("ERROR ARGS!\n");
			return (1);
		}
		free(tmp);
		free(tmp2);
	}
	return (0);
}

int	upload_infos(t_args *args, char **argv)
{
	args->nb_ph = ft_atoi(argv[1]);
	args->t_die = ft_atoi(argv[2]);
	args->t_eat = ft_atoi(argv[3]);
	args->t_sleep = ft_atoi(argv[4]);
	if (args->is_nb_t_eat)
		args->nb_t_eat = ft_atoi(argv[5]);
	return (0);
}
