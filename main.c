/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 15:13:11 by yer-raki          #+#    #+#             */
/*   Updated: 2021/09/10 16:02:46 by yer-raki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init(t_args *args)
{
	args->nb_ph = 0;
	args->t_die = 0; 
	args->t_eat = 0; 
	args->t_sleep = 0; 
	args->nb_t_eat = 0;
	args->is_nb_t_eat = 0;
	args->end = 0;
	args->start_time = 0;
}

int	check_args_init(int argc, char **argv, t_args *args)
{
	int		i;
	int		j;
	char	*tmp;
	char	*tmp2;

	i = 1;
	j = 0;
	tmp = NULL;
	tmp2 = NULL;
	ft_init(args);
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
		args->is_nb_t_eat = 1;
	return (0);
}


unsigned long	current_time()
{
	struct timeval t;
	
	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000000 + t.tv_usec);
}

void	ft_usleep(unsigned long t)
{
	unsigned long tmp;

	tmp = current_time();
	usleep(t - 10000);
	while (current_time() - tmp < t)
	;
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

void	print_msg(int status, t_philo *ph)
{
	unsigned long time;

	time = (current_time() - ph->args->start_time) / 1000 ;
	pthread_mutex_lock(&ph->args->write);
	if (status == TAKING_FORKS)
		printf("%lu %d has taking a fork\n", time,  ph->id);
	else if (status == EAT)
		printf("%lu %d is eating\n", time, ph->id);
	else if (status == SLEEP)
	{
		printf("%lu %d is sleeping\n", time, ph->id);
		ph->last_meal = time;
	}
	else if (status == THINK)
	{
		printf("%lu %d is thinking\n", time, ph->id);
		ph->next_meal = time;
	}
	else if (status == DIE)
		printf("%lu %d died\n", time, ph->id);
	pthread_mutex_unlock(&ph->args->write);
}

void	take_forks(t_philo *ph)
{
	int id;
	int nb_ph;

	// if (ph->args->end)
	// 	return;
	id = ph->id;
	nb_ph = ph->args->nb_ph;
	pthread_mutex_lock(&ph->args->forks[id]);
	ph->status = TAKING_FORKS;
	print_msg(ph->status, ph);
	pthread_mutex_lock(&ph->args->forks[(id + 1) % nb_ph]);
	print_msg(ph->status, ph);
	
}

void	throw_forks(t_philo *ph)
{
	int id;
	int nb_ph;

	// if (ph->args->end)
	// 	return;
	id = ph->id;
	nb_ph = ph->args->nb_ph;
	pthread_mutex_unlock(&ph->args->forks[id]);
	pthread_mutex_unlock(&ph->args->forks[(id + 1) % nb_ph]);
}

void	eating(t_philo *ph)
{
	// if (ph->args->end)
	// 	return;
	ph->status = EAT;
	print_msg(ph->status, ph);
	ft_usleep(ph->args->t_eat * 1000);
	ph->nb_eat++;
	if (ph->args->is_nb_t_eat && (ph->nb_eat == ph->args->nb_t_eat))
		ph->finish = 1;
}

void	sleeping(t_philo *ph)
{
	// if (ph->args->end)
	// 	return;
	ph->status = SLEEP;
	print_msg(ph->status, ph);
	ft_usleep(ph->args->t_sleep * 1000);
}

void	thinking(t_philo *ph)
{
	// if (ph->args->end)
	// 	return;
	ph->status = THINK;
	print_msg(ph->status, ph);
}

void	detach_mutex(t_args *args)
{
	int i;

	i = -1;
	pthread_mutex_destroy(&args->write);
	while (++i < args->nb_ph)
		pthread_mutex_destroy(&args->forks[i]);
}

int		check_death(t_philo *ph)
{
	// printf ("\n\n last : %lu | next : %lu | die : %d \n\n", ph->last_meal, ph->next_meal, ph->args->t_die);
	int i;

	i = 0;
	// printf("%d\n", ph[i].args->nb_ph);
	while (ph[i].args->nb_ph > i)
	{
		if ((ph[i].next_meal - ph[i].last_meal) >= (unsigned long)(ph[i].args->t_die))
		// if ((current_time() - ph[i].last_meal) >= (unsigned long)(ph[i].args->t_die))
		{
			ph[i].status = DIE;
			print_msg(ph[i].status, &ph[i]);
			return (1);
		}
		// if ()
		i++;
	}
	return (0);
}

void	*fun_thread(void *tmp)
{
	t_philo *ph;
	int i;
	
	i = -1;
	ph = (t_philo *)tmp;
	while (1)
	{
		take_forks(ph);
		eating(ph);
		throw_forks(ph);
		sleeping(ph);
		thinking(ph);
	}
	return (0);
}

void	init_mutex(t_args *args, t_philo *ph)
{
	int i;

	i = -1;
	// pthread_mutex_init(&args->death, NULL);
	args->forks = malloc(sizeof(pthread_mutex_t) * args->nb_ph);
	while (args->nb_ph > ++i)
	{
		ph[i].args = args;
		pthread_mutex_init(&args->forks[i], NULL);
	}
}

void	init_philo(t_philo ph)
{
	ph.finish = 0;
	ph.last_meal = 0;
	ph.nb_eat = 0;
	ph.next_meal = 0;
	ph.status = 0;
	ph.philo = NULL;
}

int		create_threads(t_args *args)
{
	t_philo *ph;
	int i;

	i = -1;
	ph = malloc(sizeof(t_philo) * args->nb_ph);
	init_mutex(args, ph);
	ph->args->start_time = current_time();
	// pthread_mutex_lock(&args->death);
	while (args->nb_ph > ++i && !args->end)
	{
		ph[i].id = i + 1;
		init_philo(ph[i]);
		pthread_create(&ph[i].philo, NULL, &fun_thread, &ph[i]);
		usleep(100);
		// printf ("\n\n %d end = %d \n\n", i + 1, args->end);
	}
	while (1)
	{
		if (check_death(ph) == 1)
			break;
		/* code */
	}
	
	// i = -1;
	// if (args->end)
		// return;
	// while (args->nb_ph > ++i)
	// 	pthread_join(ph[i].philo, NULL);
	i = -1;
	while (args->nb_ph > ++i)
		pthread_mutex_destroy(&args->forks[i]);
	pthread_mutex_destroy(&args->write);
	free(args->forks);
	// free(ph);
	return(0);
}

int	main(int argc, char **argv)
{
	t_args args;
	
	if (check_args_init(argc, argv, &args) || upload_infos(&args, argv) || create_threads(&args))
		return(1);
	return (0);
}