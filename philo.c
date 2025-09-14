/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ualkan <ualkan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 00:45:02 by ualkan            #+#    #+#             */
/*   Updated: 2025/09/14 14:34:46 by ualkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_status(int status, t_philo *philo)
{
	long long	time_offset;

	if (check_stop_flag(philo))
		return ;

	pthread_mutex_lock(&philo->sim->log_mutex);
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

void	ft_one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->forks[philo->left_fork_id]);
	ft_status(1, philo);
	spend_time_interruptible(philo->sim->time_to_die, philo);
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


void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_eaten = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	
	ft_status(2, philo);
	
	spend_time_interruptible(philo->sim->time_to_eat, philo);
	
	pthread_mutex_unlock(&philo->sim->forks[philo->right_fork_id]);
	pthread_mutex_unlock(&philo->sim->forks[philo->left_fork_id]);
}

void	ft_sleep(t_philo *philo)
{
	ft_status(4, philo);
	spend_time_interruptible(philo->sim->time_to_sleep, philo);
}

void	ft_think(t_philo *philo)
{
	long long	think_time;
	long long	time_since_last_meal;
	long long	current_time;

	ft_status(3, philo);
	
	pthread_mutex_lock(&philo->meal_mutex);
	current_time = get_time();
	time_since_last_meal = current_time - philo->last_meal_eaten;
	
	think_time = (philo->sim->time_to_die - time_since_last_meal - philo->sim->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->meal_mutex);
	
	if (think_time < 0)
		think_time = 0;
	if (think_time == 0)
		think_time = 1;
	if (think_time > 600)
		think_time = 200;
	else if (think_time > 50 && think_time < 100)
		think_time = 75;
	spend_time_interruptible(think_time, philo);
}

int	check_stop_flag(t_philo *philo)
{
	int	should_stop;

	pthread_mutex_lock(&philo->sim->stop_mutex);
	should_stop = philo->sim->stop_flag;
	pthread_mutex_unlock(&philo->sim->stop_mutex);
	return (should_stop);
}

void	ft_release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->sim->forks[philo->right_fork_id]);
	pthread_mutex_unlock(&philo->sim->forks[philo->left_fork_id]);
}

void handle_routine(t_philo *philo)
{
	if (philo->sim->philo_count == 1)
	{
		ft_one_philo(philo);
		return ;
	}
	if (philo->id % 2 == 0)
	{
		long long stagger_delay = (philo->sim->philo_count / 2) + (philo->id / 2);
		if (stagger_delay > 15)
			stagger_delay = 15;
		spend_time_interruptible(stagger_delay, philo);
	}

	while (!check_stop_flag(philo))
	{
		ft_take_fork(philo);
		if (check_stop_flag(philo))
		{
			ft_release_forks(philo);
			break ;
		}		
		ft_eat(philo);		
		if (check_stop_flag(philo))
			break ;
		ft_sleep(philo);
		if (check_stop_flag(philo))
			break ;
		ft_think(philo);
	}
}



