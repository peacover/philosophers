/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 15:14:06 by yer-raki          #+#    #+#             */
/*   Updated: 2021/09/16 14:36:48 by yer-raki         ###   ########.fr       */
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
	int				nb_ph;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				nb_t_eat;
	int				is_nb_t_eat;
	int				count_completed_eat;
	int				end;
	unsigned int	start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
}				t_args;

typedef struct s_philo
{
	int				id;
	int				status;
	pthread_t		philo;
	int				nb_eat;
	unsigned int	last_meal;
	pthread_mutex_t	is_eating;
	t_args			*args;	
}				t_philo;

size_t			ft_strlen(const char *s);
char			*ft_itoa(int n);
int				ft_atoi(const char *s);
int				ft_strcmp(char *s1, char *s2);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strdup(const char *s1);
int				ft_init(t_args *args, int argc);
void			init_mutex(t_args *args, t_philo *ph);
void			init_philo(t_philo *ph);
void			take_forks(t_philo *ph);
void			throw_forks(t_philo *ph);
void			eating(t_philo *ph);
void			sleeping(t_philo *ph);
void			thinking(t_philo *ph);
int				check_args_init(int argc, char **argv, t_args *args);
int				upload_infos(t_args *args, char **argv);
unsigned int	current_time(void);
void			ft_usleep(unsigned int t);
void			print_msg(int status, t_philo *ph);
int				check_death(t_philo *ph);
#endif