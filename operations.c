/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 15:03:22 by yer-raki          #+#    #+#             */
/*   Updated: 2021/09/16 14:32:05 by yer-raki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *ph)
{
	int	id;
	int	nb_ph;

	if (ph->args->end)
		return ;
	id = ph->id - 1;
	nb_ph = ph->args->nb_ph;
	pthread_mutex_lock(&ph->args->forks[id]);
	ph->status = TAKING_FORKS;
	print_msg(ph->status, ph);
	pthread_mutex_lock(&ph->args->forks[(id + 1) % nb_ph]);
	print_msg(ph->status, ph);
}

void	throw_forks(t_philo *ph)
{
	int	id;
	int	nb_ph;

	if (ph->args->end)
		return ;
	id = ph->id - 1;
	nb_ph = ph->args->nb_ph;
	pthread_mutex_unlock(&ph->args->forks[id]);
	pthread_mutex_unlock(&ph->args->forks[(id + 1) % nb_ph]);
}

void	eating(t_philo *ph)
{
	if (ph->args->end)
		return ;
	ph->status = EAT;
	pthread_mutex_lock(&ph->is_eating);
	ph->last_meal = current_time();
	print_msg(ph->status, ph);
	ft_usleep(ph->args->t_eat);
	ph->nb_eat++;
	if (ph->args->is_nb_t_eat && ph->nb_eat >= ph->args->nb_t_eat)
	{
		ph->args->count_completed_eat++;
		if (ph->args->count_completed_eat == ph->args->nb_t_eat)
			ph->args->end = 1;
	}
	pthread_mutex_unlock(&ph->is_eating);
}

void	sleeping(t_philo *ph)
{
	if (ph->args->end)
		return ;
	ph->status = SLEEP;
	print_msg(ph->status, ph);
	ft_usleep(ph->args->t_sleep);
}

void	thinking(t_philo *ph)
{
	if (ph->args->end)
		return ;
	ph->status = THINK;
	print_msg(ph->status, ph);
}
