/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ualkan <ualkan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 15:52:03 by ualkan            #+#    #+#             */
/*   Updated: 2025/09/14 16:59:07 by ualkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->sim->forks[philo->right_fork_id]);
	pthread_mutex_unlock(&philo->sim->forks[philo->left_fork_id]);
}

void	ft_take_fork(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(&philo->sim->forks[philo->left_fork_id]);
		ft_status(1, philo);
		pthread_mutex_lock(&philo->sim->forks[philo->right_fork_id]);
		ft_status(1, philo);
	}
	else
	{
		pthread_mutex_lock(&philo->sim->forks[philo->right_fork_id]);
		ft_status(1, philo);
		pthread_mutex_lock(&philo->sim->forks[philo->left_fork_id]);
		ft_status(1, philo);
	}
}

void	ft_status(int status, t_philo *philo)
{
	long long	time_offset;

	pthread_mutex_lock(&philo->sim->log_mutex);
	if (check_stop_flag(philo))
		return ;
	time_offset = get_time() - philo->sim->start_time;
	if (status == 1)
		printf("%lld %d has taken a fork\n", time_offset, philo->id);
	else if (status == 2)
		printf("%lld %d is eating\n", time_offset, philo->id);
	else if (status == 3)
		printf("%lld %d is thinking\n", time_offset, philo->id);
	else if (status == 4)
		printf("%lld %d is sleeping\n", time_offset, philo->id);
	pthread_mutex_unlock(&philo->sim->log_mutex);
}
