/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 15:14:06 by yer-raki          #+#    #+#             */
/*   Updated: 2021/09/10 10:27:11 by yer-raki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

# define TAKING_FORKS 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DIE 5

typedef struct s_args
{
	int	nb_ph;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	nb_t_eat;
	int	is_nb_t_eat;
	
	unsigned long start_time;
	int	end;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
}				t_args;

typedef struct s_philo
{
	int			id;
	int			status;
	pthread_t	philo;
	int			nb_eat;
	int			finish;
	unsigned long last_meal;
	unsigned long next_meal;
	t_args		*args;	
}				t_philo;

size_t	ft_strlen(const char *s);
char	*ft_itoa(int n);
int		ft_atoi(const char *s);
int		ft_strcmp(char *s1, char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);

# endif