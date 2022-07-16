/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stack.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 20:27:36 by abittel           #+#    #+#             */
/*   Updated: 2022/07/16 16:58:43 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.hpp"
#include <stack>
#include <iostream>
#include <string>

#include <chrono>
#include <sys/time.h>
int main()
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    long int begin = tp.tv_sec * 1000 + tp.tv_usec / 1000; 
    ft::stack<std::string>   map_ft;

    for (int i = 1; i < 1000000 ;i++)
    {
      map_ft.push(std::to_string(i));
      map_ft.pop();
      map_ft.push(std::to_string(i));
      map_ft.size();
      map_ft.empty();
    }
    gettimeofday(&tp, NULL);
    long int end = tp.tv_sec * 1000 + tp.tv_usec / 1000; 
   
    gettimeofday(&tp, NULL);
    long int begin2 = tp.tv_sec * 1000 + tp.tv_usec / 1000; 
    std::stack<std::string>  map_std;
    std::stack<std::string>  map_std2;
    for (int i = 1; i < 1000000; i++)
    {
      map_std.push(std::to_string(i));
      map_std.pop();
      map_std.push(std::to_string(i));
      map_std.size();
    }
    gettimeofday(&tp, NULL);
    long int end2 = tp.tv_sec * 1000 + tp.tv_usec / 1000; 
    unsigned int res1 = (end - begin);
    unsigned int res2 = (end2 - begin2);
    std::cout << res1 << "/" << res2 << " : " << (float)res1/(float)res2 << std::endl;

}