/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 15:13:11 by yer-raki          #+#    #+#             */
/*   Updated: 2021/07/05 17:42:02 by yer-raki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init(t_infos *info)
{
	info->nb_ph = 0;
	info->t_die = 0; 
	info->t_eat = 0; 
	info->t_sleep = 0; 
	info->nb_t_eat = 0;
	info->is_nb_t_eat = 0;
}

int	check_args_init(int argc, char **argv, t_infos *info)
{
	int		i;
	int		j;
	char	*tmp;
	char	*tmp2;

	i = 1;
	j = 0;
	tmp = NULL;
	tmp2 = NULL;
	ft_init(info);
	if (argc > 6 || argc < 5)
	{
		printf("ERROR ARGS!\n");
		return (1);
	}
	while (argc > i)
	{
		j = 0;
		while (ft_strlen(argv[i]) > 1 && (argv[i][j] == '0'))
			j++;
		tmp = ft_substr(argv[i], j, ft_strlen((argv[i]) - j));
		tmp2 = ft_itoa(ft_atoi(tmp));
		if (ft_strcmp(tmp, tmp2) || (j != 0 && argv[i][j] == '-'))
			printf("ERROR ARGS!\n");
		i++;
		free(tmp);
		free(tmp2);
		tmp = NULL;
		tmp2 = NULL;
	}
	if (argc == 6)
		info->is_nb_t_eat = 1;
	return (0);
}

int	main(int argc, char **argv)
{
	t_infos info;
	if (check_args_init(argc, argv, &info))
		return (1);
}