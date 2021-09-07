/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 15:14:06 by yer-raki          #+#    #+#             */
/*   Updated: 2021/09/07 18:33:44 by yer-raki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_args
{
	int	nb_ph;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	nb_t_eat;
	int	is_nb_t_eat;
	
	
	//mutex write
	//mutex *forks
}				t_args;

typedef struct s_philo
{
	int			id;
	pthread_t	philo;
	char		status;
	int			nb_eat;
	int			finish;  //1 when = nb_t_eat
	pthread_mutex_t	*forks;
}				t_philo;

typedef struct	s_infos
{
	t_philo *ph;
	t_args	args;
}				t_infos;

size_t	ft_strlen(const char *s);
char	*ft_itoa(int n);
int		ft_atoi(const char *s);
int		ft_strcmp(char *s1, char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);

# endif