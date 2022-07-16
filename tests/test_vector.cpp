/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 20:27:36 by abittel           #+#    #+#             */
/*   Updated: 2022/07/16 16:32:33 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include <vector>
#include <iostream>
#include <string>

#include <ctime>
#include <sys/time.h>

int main()
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    long int begin = tp.tv_sec * 1000 + tp.tv_usec / 1000; 
    ft::vector<std::string>   map_ft;
    ft::vector<std::string>   map_ft2;

    for (int i = 1; i < 30000 ;i++)
    {
        map_ft.insert(map_ft.begin(), std::to_string(i));
        map_ft.back();
        map_ft.capacity();
        map_ft.empty();
        map_ft.front();
        map_ft.erase(map_ft.begin());
        map_ft.push_back(std::to_string(i));
        map_ft.pop_back();
        map_ft.push_back(std::to_string(i));
        map_ft.size();
        map_ft.swap(map_ft2);
        map_ft2.swap(map_ft);
    }
    map_ft.erase(map_ft.begin(), map_ft.end());
    gettimeofday(&tp, NULL);
    long int end = tp.tv_sec * 1000 + tp.tv_usec / 1000; 
        
    gettimeofday(&tp, NULL);
    long int begin2 = tp.tv_sec * 1000 + tp.tv_usec / 1000; 
     
    std::vector<std::string>  map_std;
    std::vector<std::string>  map_std2;
    for (int i = 1; i < 30000; i++)
    {
        map_std.insert(map_std.begin(), std::to_string(i));
        map_std.back();
        map_std.capacity();
        map_std.empty();
        map_std.front();
        map_std.erase(map_std.begin());
        map_std.push_back(std::to_string(i));
        map_std.pop_back();
        map_std.push_back(std::to_string(i));
        map_std.size();
        map_std.swap(map_std2);
        map_std2.swap(map_std);
    }
    map_std.erase(map_std.begin(), map_std.end());
    gettimeofday(&tp, NULL);
    long int end2 = tp.tv_sec * 1000 + tp.tv_usec / 1000; 
     
    unsigned int res1 = (end - begin);
    unsigned int res2 = (end2 - begin2);
    std::cout << res1 << "/" << res2 << " : " << (float)res1/(float)res2 << std::endl;

}