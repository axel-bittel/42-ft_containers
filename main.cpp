/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 15:45:02 by abittel           #+#    #+#             */
/*   Updated: 2022/06/14 10:00:54 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <map>
#include <list>
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>

//#include <chrono>
#include "map.hpp"

int	main()
{	
	/*std::map<int, int> m;
	std::pair<int, int> test2;
	ft::Tree<int, std::string> t;
	t.insert(3, "10");
	t.insert(5, "20");
	t.insert(4, "30");
	t.insert(1, "40");
	t.insert(-42, "40");
	t.insert(75, "40");
	t.insert(2, "40");
	t.print_tree();
	m.insert(std::make_pair(3, 1));
	m.insert(std::make_pair(5, 2));
	m.insert(std::make_pair(4, 1));
	m.insert(std::make_pair(1, 1));
	m.insert(std::make_pair(-42, 1));
	m.insert(std::make_pair(75, 1));
	m.insert(std::make_pair(75, 2));
	m.insert(std::make_pair(2, 1));
	ft::Tree<int, std::string>::iterator	it;
	it = t.begin();
	it++;
	for (ft::Tree<int, std::string>::iterator it = t.begin(); it != t.end(); it++)
		std::cout << (*it).first << std::endl;
	std::cout << ((((--(m.end())))))->first<< std::endl;
	std::cout << m.size() << std::endl;
	std::cout << m[900] << std::endl;
	std::cout << m.size() << std::endl;
	m[900] = 100;
	std::cout << m.size() << std::endl;
	std::cout << m[900] << std::endl;
	std::cout << m.size() << std::endl;*/
	std::allocator<int>	_alloc;
	int*	one = _alloc.allocate(1);
	_alloc.construct(one, 1);
	int*	two = _alloc.allocate(1);
	_alloc.construct(two, 1);
	std::cout << one << "/" << two << std::endl;
	/*m.insert(std::make_pair(1, 1));
	m.insert(std::make_pair(2, 1));
	m.insert(std::make_pair(2, 2));
	m.insert(std::make_pair(3, 1));
	m.insert(std::make_pair(4, 1));
	m.insert(std::make_pair(5, 1));
	std::cout << (--m.begin())->first << std::endl;
	std::cout << m.at(2) << std::endl;
	std::cout << (*m.end()).first << std::endl;*/
	return (0);
}