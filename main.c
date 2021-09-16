/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 15:13:11 by yer-raki          #+#    #+#             */
/*   Updated: 2021/09/16 15:42:26 by yer-raki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_msg(int status, t_philo *ph)
{
	int		time;
	t_args	*args;

	args = ph->args;
	time = (current_time() - ph->args->start_time);
	pthread_mutex_lock(&args->write);
	if (status == TAKING_FORKS)
		printf("%d %d has taking a fork\n", time, ph->id);
	else if (status == EAT)
		printf("%d %d is eating\n", time, ph->id);
	else if (status == SLEEP)
		printf("%d %d is sleeping\n", time, ph->id);
	else if (status == THINK)
		printf("%d %d is thinking\n", time, ph->id);
	else if (status == DIE)
	{
		printf("%d %d died\n", time, ph->id);
		return ;
	}
	pthread_mutex_unlock(&args->write);
}

int	check_death(t_philo *ph)
{
	int	i;
	int	t;

	i = -1;
	t = 0;
	while (++i < ph->args->nb_ph && !ph->args->end)
	{
		if (ph[i].status != EAT)
		{
			pthread_mutex_lock(&ph->is_eating);
			if ((current_time() - ph[i].last_meal)
				>= (unsigned int)(ph[i].args->t_die))
			{
				ph[i].status = DIE;
				print_msg(ph[i].status, &ph[i]);
				free(ph->args->forks);
				return (1);
			}
			pthread_mutex_unlock(&ph->is_eating);
		}
	}
	return (0);
}

void	*fun_thread(void *tmp)
{
	t_philo	*ph;

	ph = (t_philo *)tmp;
	while (!ph->args->end)
	{
		take_forks(ph);
		eating(ph);
		throw_forks(ph);
		sleeping(ph);
		thinking(ph);
	}
	return (0);
}

int	create_threads(t_args *args, t_philo *ph)
{
	int	i;

	i = -1;
	ph = malloc(sizeof(t_philo) * args->nb_ph);
	init_mutex(args, ph);
	args->start_time = current_time();
	args->count_completed_eat = 0;
	while (args->nb_ph > ++i)
	{
		ph[i].id = i + 1;
		init_philo(&ph[i]);
		pthread_create(&ph[i].philo, NULL, &fun_thread, &ph[i]);
		usleep(200);
	}
	while (1)
	{
		if (check_death(ph))
			return (1);
		else if (ph->args->end)
			return (1);
		usleep(200);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_args	args;
	t_philo	ph;

	if (check_args_init(argc, argv, &args)
		|| upload_infos(&args, argv) || create_threads(&args, &ph))
		return (1);
	return (0);
}
