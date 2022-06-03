/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 15:45:02 by abittel           #+#    #+#             */
/*   Updated: 2022/06/04 01:20:48 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <map>
#include <list>
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>

#include "vector.hpp"
//#include <chrono>
#include "RB_tree.hpp"

int	main()
{	
	std::map<int, int> m;
	//std::pair<int, int> test2;
	//ft::Tree<int, std::string> t;
	/*t.insert(3, "10");
	t.insert(5, "20");
	t.insert(4, "30");
	t.insert(1, "40");
	t.insert(6, "40");
	t.insert(-42, "40");
	t.insert(42, "40");
	t.destroy(5);
	t.print_tree();*/
	m.insert(std::make_pair(1, 1));
	m.insert(std::make_pair(2, 1));
	m.insert(std::make_pair(2, 2));
	m.insert(std::make_pair(3, 1));
	m.insert(std::make_pair(4, 1));
	m.insert(std::make_pair(5, 1));
	std::cout << m.at(2) << std::endl;
	std::cout << m.at(2) << std::endl;
	std::cout << (*m.end()).first << std::endl;
	return (0);
}