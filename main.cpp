/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 15:45:02 by abittel           #+#    #+#             */
/*   Updated: 2022/05/21 21:09:27 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <iostream>
#include <iterator>
#include <string>

#include "vector.hpp"

int	main()
{	
	std::vector<int> nv;
	nv.push_back(1);
	nv.push_back(2);
	nv.push_back(3);
	nv.push_back(4);
	nv.push_back(5);
	std::cout << *(nv.rend() - 1) << "/" << *(nv.begin()) << std::endl;
	std::cout << nv.capacity() << std::endl;
	std::cout << nv.capacity() << std::endl;
	for (int i = 0; i < 10; i ++)
		std::cout << nv[i] << std::endl;
	std::cout << nv.capacity() << std::endl;
	std::cout << nv.size() << std::endl;
	return (0);
}