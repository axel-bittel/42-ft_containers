/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 15:45:02 by abittel           #+#    #+#             */
/*   Updated: 2022/05/26 17:53:50 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>

#include "vector.hpp"
#include <chrono>

class A
{
private:
	int	test;
public:
	A(int val) : test(val) {}
	~A(){};
	bool	operator==(A& op) { return (test == op.test);}
	bool	operator<(A& op) { return (test < op.test);}
	friend std::ostream& operator<<(std::ostream& os, A& a);
};
std::ostream& operator<<(std::ostream& os, A& a) { os << a.test << std::endl; return (os); }


int	main()
{	
	std::ofstream fd ;
	fd.open ("test1");
	ft::vector<A> v(2, A(5));
	//int begin1 = std::chrono::high_resolution_clock::now();
		fd << v.size() << "/" << v.capacity() << std::endl;
		for (int i = 0; i < 2; i++)
		{
			fd << v[i] << std::endl;
		}
		
	//int end1 = std::chrono::high_resolution_clock::now();
	fd.close();
	fd.open("test2");
	//int begin2 = std::chrono::high_resolution_clock::now();
		std::vector<int> v1(3, 1);
		std::vector<int> v2(10000, 2);
		std::cout << v1.size() << "/" << v1.capacity() << &(*v1.begin()) << std::endl;
		std::cout << v2.size() << "/" << v2.capacity() << &(*v2.begin()) << std::endl;
		v2 = v1;
		std::cout << v1.size() << "/" << v1.capacity() << &(*v1.begin()) << std::endl;
		std::cout << v2.size() << "/" << v2.capacity() << &(*v2.begin()) << std::endl;
		/*for (int i = 0; i < 1; i++)
		{
			std::vector<int> v2(2,2);
			v2.insert(v2.begin() + 1, 10000, i);
			fd << v2.size() << "/" << v2.capacity() << std::endl;
			for (int i = 0; i < v2.size();i++)
				fd << v2[i] << std::endl;
		}*/
	//int end2 = std::chrono::high_resolution_clock::now();
	fd.close();
	//std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - begin1).count() << std::endl;
	//std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - begin2).count() << std::endl;
	//std::cout << (float)std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - begin1).count()  / (float)std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - begin2).count() << std::endl;
	return (0);
}