/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 15:45:02 by abittel           #+#    #+#             */
/*   Updated: 2022/06/24 13:15:25 by abittel          ###   ########.fr       */
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

class A
{
	public:
	A() : test(0), test2(1) {}
	A(int _t) : test(_t), test2(1) {}
	A(const A& cp) : test(cp.test), test2(cp.test2) {}
	~A(){}
	friend std::ostream& operator<<(std::ostream& os, const A& t)
	{
		os << t.test << "/" << t.test2;
		return (os);
	}
	bool operator<(const A& t) const
	{	return (test < t.test);	}
	int test;
	int test2;
};

int	main()
{	
	std::map<A, int> m;
	std::map<int, int>::reverse_iterator r;
	std::pair<int, int> test2;
	ft::Tree<int, std::string> t;
	t.insert(3, "10");
	t.insert(5, "20");
	t.insert(4, "30");
	t.insert(1, "40");
	t.insert(-42, "40");
	t.insert(75, "40");
	t.insert(2, "40");
	//t.print_tree();
	/*m.insert(std::make_pair("3", 1));
	m.insert(std::make_pair("5", 2));
	m.insert(std::make_pair("4", 1));
	m.insert(std::make_pair("1", 1));
	m.insert(std::make_pair("-42", 1));
	m.insert(std::make_pair("75", 1));
	m.insert(std::make_pair("75", 2));
	m.insert(std::make_pair("2", 1));*/
	m.insert(std::make_pair(A(3), 1));
	m.insert(std::make_pair(A(5), 2));
	m.insert(std::make_pair(A(4), 1));
	m.insert(std::make_pair(A(1), 1));
	m.insert(std::make_pair(A(-42), 1));
	m.insert(std::make_pair(A(75), 1));
	m.insert(std::make_pair(A(75), 2));
	m.insert(std::make_pair(A(2), 1));
	for (std::map<A, int>::iterator it = m.begin(); it != m.end(); it++)
		std::cout << it->first << std::endl;
	std::cout << m.end()->first  << "|" << m.end()->second << std::endl;
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