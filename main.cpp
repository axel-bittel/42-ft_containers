/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 15:45:02 by abittel           #+#    #+#             */
/*   Updated: 2022/06/03 02:03:27 by abittel          ###   ########.fr       */
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

int	main()
{	
	/*std::ofstream fd ;
	fd.open ("test1");
		ft::vector<int> v1(3, 1);
		ft::vector<int> v2(v1.begin(), --v1.end());
		ft::vector<int>::iterator c1 = v1.begin();
		ft::vector<int>::const_iterator c = v2.begin();
		if (c1 == c)
			return (1);
		std::cout << v1.size() << "/" << v1.capacity() << &(*v1.begin()) << std::endl;
		std::cout << v2.size() << "/" << v2.capacity() << &(*v2.begin()) << std::endl;
*/
	//auto begin1 = std::chrono::high_resolution_clock::now();
		/*for (int i = 0; i < 1; i++)
		{
			ft::vector<int> v(2,2);
			v.insert(v.begin() + 1, 10000 , i);
			fd << v.size() << "/" << v.capacity() << std::endl;
			for (int i = 0; i < v.size();i++)
				fd << v[i] << std::endl;
		}*/
		
	//auto end1 = std::chrono::high_resolution_clock::now();
	//fd.close();
	//fd.open("test2");
	//auto begin2 = std::chrono::high_resolution_clock::now();
		std::vector<int> v1(3, 1);
		std::vector<int>::iterator test = v1.begin();
		std::vector<int>::reverse_iterator test2(v1);
		std::map<int, int> test;
		std::list<int>::iterator test;
		std::cout << v1.size() << "/" << v1.capacity() << &(*v1.begin()) << std::endl;
		std::cout << v1.size() << "/" << v1.capacity() << &(*v1.begin()) << std::endl;
		/*for (int i = 0; i < 1; i++)
		{
			std::vector<int> v2(2,2);
			v2.insert(v2.begin() + 1, 10000, i);
			fd << v2.size() << "/" << v2.capacity() << std::endl;
			for (int i = 0; i < v2.size();i++)
				fd << v2[i] << std::endl;
		}
	//auto end2 = std::chrono::high_resolution_clock::now();
	fd.close();
//	std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - begin1).count() << std::endl;
//	std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - begin2).count() << std::endl;
//	std::cout << (float)std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - begin1).count()  / (float)std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - begin2).count() << std::endl;
*/
	return (0);
}