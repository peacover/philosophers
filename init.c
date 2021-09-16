/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 15:04:17 by yer-raki          #+#    #+#             */
/*   Updated: 2021/09/16 14:30:39 by yer-raki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init(t_args *args, int argc)
{
	args->nb_ph = 0;
	args->t_die = 0;
	args->t_eat = 0;
	args->t_sleep = 0;
	args->nb_t_eat = 0;
	args->end = 0;
	args->count_completed_eat = 0;
	args->start_time = 0;
	if (argc == 6)
		args->is_nb_t_eat = 1;
	if (argc > 6 || argc < 5)
	{
		printf("ERROR ARGS!\n");
		return (1);
	}
	else
		return (0);
}

void	init_mutex(t_args *args, t_philo *ph)
{
	int	i;

	i = -1;
	args->forks = malloc(sizeof(pthread_mutex_t) * args->nb_ph);
	pthread_mutex_init(&args->write, NULL);
	while (args->nb_ph > ++i)
	{
		ph[i].args = args;
		pthread_mutex_init(&args->forks[i], NULL);
	}
}

void	init_philo(t_philo *ph)
{
	ph->last_meal = current_time();
	ph->nb_eat = 0;
	ph->status = 0;
	ph->philo = NULL;
	pthread_mutex_init(&ph->is_eating, NULL);
}
