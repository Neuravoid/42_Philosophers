/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ualkan <ualkan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:04:20 by ualkan            #+#    #+#             */
/*   Updated: 2025/09/14 11:53:21 by ualkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef	pthread_mutex_t mutex_t;

typedef struct s_sim
{
	int				philo_count;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				must_eat_count;
	long long		start_time;
	int				stop_flag;
	pthread_mutex_t	*forks;
	pthread_mutex_t	log_mutex;
	pthread_mutex_t	stop_mutex;
	pthread_t		monitor_handle;
	struct s_philo	*philos;
}	t_sim;

typedef struct s_philo
{
	int				id;
	int				left_fork_id;
	int				right_fork_id;
	long long		last_meal_eaten;
	int				meals_eaten;
	pthread_t		thread_handle;
	pthread_mutex_t	meal_mutex;
	t_sim			*sim;
}	t_philo;

int			ft_atoi(const char *str);
long long	get_time(void);
int			ft_checker(int ac, char **av, t_sim *simulation);
t_sim		*init_simulation(int ac, char **av, t_sim *simulation);
void		handle_routine(t_philo *philo);
void		start_simulation(t_sim *sim);
void		*start_monitor(void *arg);
void		spend_time(long long ms);
int			check_stop_flag(t_philo *philo);
void		clean_resources(t_sim *sim);

#endif