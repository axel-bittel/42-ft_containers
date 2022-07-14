/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stack.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 20:27:36 by abittel           #+#    #+#             */
/*   Updated: 2022/07/14 20:12:58 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.hpp"
#include <stack>
#include <iostream>
#include <string>

#include <chrono>
int main()
{
    auto begin = std::chrono::high_resolution_clock::now();
    ft::stack<std::string>   map_ft;

    for (int i = 1; i < 1000000 ;i++)
    {
      map_ft.push(std::to_string(i));
      map_ft.pop();
      map_ft.push(std::to_string(i));
      map_ft.size();
      map_ft.empty();
    }
    auto end = std::chrono::high_resolution_clock::now();
        
    auto begin2 = std::chrono::high_resolution_clock::now();
    std::stack<std::string>  map_std;
    std::stack<std::string>  map_std2;
    for (int i = 1; i < 1000000; i++)
    {
      map_std.push(std::to_string(i));
      map_std.pop();
      map_std.push(std::to_string(i));
      map_std.size();
    }
    auto end2 = std::chrono::high_resolution_clock::now();
    auto res1 =std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    auto res2 =std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - begin2);
    std::cout << res1.count() << "/" << res2.count() << " : " << (float)res1.count() / (float)res2.count() << std::endl;
}