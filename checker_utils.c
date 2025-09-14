/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ualkan <ualkan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:48:43 by ualkan            #+#    #+#             */
/*   Updated: 2025/09/14 00:43:16 by ualkan           ###   ########.fr       */
/*                                     z                                       */
/* ************************************************************************** */

 

static int ft_containalpha(const char *str)
{
	int i;

	i = 0;
	
	while (str[i])
	{
		if (!(47 < str[i] && 58 > str[i]))
			return 1;
		i++;
	}
	return 0;
}

int ft_atoi(const char *str)
{
	int		sign;
	int		result;
	int		i;

	if (ft_containalpha(str))
		return (-42);
	
	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (sign * result);
}