/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ualkan <ualkan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 00:43:26 by ualkan            #+#    #+#             */
/*   Updated: 2025/09/14 15:58:49 by ualkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_checker(int ac, char **av, t_sim *f)
{
	if (ac != 5 && ac != 6)
		return (-1);
	f->philo_count = ft_atoi(av[1]);
	f->time_to_die = ft_atoi(av[2]);
	f->time_to_eat = ft_atoi(av[3]);
	f->time_to_sleep = ft_atoi(av[4]);
	f->must_eat_count = -1;
	if (ac == 6)
		f->must_eat_count = ft_atoi(av[5]);
	if (f->philo_count == -42 || f->time_to_die == -42
		|| f->time_to_eat == -42 || f->time_to_sleep == -42
		|| (ac == 6 && f->must_eat_count == -42))
		return (-1);
	if (f->philo_count < 1 || f->philo_count >= 200
		|| f->time_to_die <= 0 || f->time_to_eat <= 0 || f->time_to_sleep <= 0
		|| f->time_to_eat >= f->time_to_die
		|| f->time_to_sleep >= f->time_to_die
		|| (ac == 6 && f->must_eat_count <= 0))
		return (-1);
	return (0);
}

int	check_stop_flag(t_philo *philo)
{
	int	should_stop;

	pthread_mutex_lock(&philo->sim->stop_mutex);
	should_stop = philo->sim->stop_flag;
	pthread_mutex_unlock(&philo->sim->stop_mutex);
	return (should_stop);
}
