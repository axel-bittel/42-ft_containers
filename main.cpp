/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 15:45:02 by abittel           #+#    #+#             */
/*   Updated: 2022/05/23 00:42:57 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>

#include "Vector.hpp"
#include <chrono>

int	main()
{	
	std::ofstream fd ;
	fd.open ("test1");
	auto begin1 = std::chrono::high_resolution_clock::now();
	const ft::vector<int> v(1,2);
	ft::vector<int>::const_iterator t = v.begin();
	for (int i = 0; i < 10000; i++)
	{
		//fd << v.size() << "/" << v.capacity() << std::endl;
		//v.insert(v.begin(), i);
	}
	for (int i = 0; i < 10000; i++)
	{
		//fd << v[i] << std::endl;
	}
	auto end1 = std::chrono::high_resolution_clock::now();
	fd.close();
	fd.open("test2");
	auto begin2 = std::chrono::high_resolution_clock::now();
		std::vector<int> v2(1,2);
		for (int i = 0; i < 10000; i++)
		{
			//fd << v2.size() << "/" << v2.capacity() << std::endl;
			//v2.insert(v2.begin(), i);
		}
		for (int i = 0; i < 10000; i++)
		{
			//fd << v2[i] << std::endl;
		}
	auto end2 = std::chrono::high_resolution_clock::now();
	fd.close();
	std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - begin1).count() << std::endl;
	std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - begin2).count() << std::endl;
	std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - begin1).count()  / std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - begin2).count() << std::endl;
	return (0);
}