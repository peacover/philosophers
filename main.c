/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 15:13:11 by yer-raki          #+#    #+#             */
/*   Updated: 2021/09/07 18:39:56 by yer-raki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init(t_infos *infos)
{
	infos->args.nb_ph = 0;
	infos->args.t_die = 0; 
	infos->args.t_eat = 0; 
	infos->args.t_sleep = 0; 
	infos->args.nb_t_eat = 0;
	infos->args.is_nb_t_eat = 0;
}

int	check_args_init(int argc, char **argv, t_infos *infos)
{
	int		i;
	int		j;
	char	*tmp;
	char	*tmp2;

	i = 1;
	j = 0;
	tmp = NULL;
	tmp2 = NULL;
	ft_init(infos);
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
		{
			printf("ERROR ARGS!\n");
			return (1);
		}
		i++;
		free(tmp);
		free(tmp2);
		tmp = NULL;
		tmp2 = NULL;
	}
	if (argc == 6)
		infos->args.is_nb_t_eat = 1;
	return (0);
}

int	upload_infos(t_infos *infos, char **argv)
{
	infos->args.nb_ph = ft_atoi(argv[1]);
	infos->args.t_die = ft_atoi(argv[2]);
	infos->args.t_eat = ft_atoi(argv[3]);
	infos->args.t_sleep = ft_atoi(argv[4]);
	if (infos->args.is_nb_t_eat)
		infos->args.nb_t_eat = ft_atoi(argv[5]);
	return (0);
}

void	*fun_thread(void *tmp)
{
	int i;
	t_philo *t;

	i = 0;
	t = (t_philo *)tmp;
	while (1) // is_alive()
	{
		printf("\nhello %d \n", t->id);
		// take_fork();// take forks
		// eat
		// sleep
		// think
	}
}

// void	init_mutex(t_infos *infos)
// {
// 	int i;

// 	i = -1;
// 	while (infos->args.nb_ph > ++i)
// 		pthread_mutex_init(&infos->infos.forks[i], NULL);
// }
int		create_threads(t_infos *infos)
{
	int i;

	i = -1;
	infos->ph = malloc(sizeof(t_philo) * infos->args.nb_ph);
	// init_mutex(infos);
	while (infos->args.nb_ph > ++i)
	{
		infos->ph[i].id = i + 1;
		pthread_create(&infos->ph[i].philo, NULL, &fun_thread, &infos->ph[i]);
	}

	return(0);
}

int	main(int argc, char **argv)
{
	t_infos infos;
	
	if (check_args_init(argc, argv, &infos) || upload_infos(&infos, argv) || create_threads(&infos))
		return(1);
	return (0);
}