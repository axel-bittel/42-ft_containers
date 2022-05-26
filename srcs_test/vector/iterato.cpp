/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterato.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:05:07 by abittel           #+#    #+#             */
/*   Updated: 2022/05/26 18:09:55 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iterator.hpp"

namespace ft
{
	template<class T>
	unsigned int	operator-(random_access_iterator<T>& op, random_access_iterator<T>& op2)
	{
		return (op2._data - op._data); 
	}
};