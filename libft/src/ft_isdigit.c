/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 15:29:49 by aihya             #+#    #+#             */
/*   Updated: 2019/12/22 16:58:48 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_isdigit(char c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}
