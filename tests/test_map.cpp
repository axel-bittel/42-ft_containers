/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 20:27:36 by abittel           #+#    #+#             */
/*   Updated: 2022/07/16 16:57:12 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.hpp"
#include <map>
#include <iostream>
#include <string>

#include <chrono>
#include <sys/time.h>
int main()
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    long int begin = tp.tv_sec * 1000 + tp.tv_usec / 1000; 
     
    ft::map<std::string, int>   map_ft;
    ft::map<std::string, int>   map_ft2;

    for (int i = 1; i < 30000; i++)
    {
        map_ft.insert(ft::make_pair<std::string>(std::to_string(i), i));
        map_ft.find(std::to_string(i));
        map_ft.count(std::to_string(i));
        map_ft.empty();
        map_ft.size();
        map_ft.begin(); map_ft.end();
        map_ft.erase(std::to_string(i));
        map_ft.insert(ft::make_pair<std::string>(std::to_string(i), i));
        map_ft.swap(map_ft2);
        map_ft2.swap(map_ft);
    }
    map_ft.erase(map_ft.begin(), map_ft.end());
    gettimeofday(&tp, NULL);
    long int end = tp.tv_sec * 1000 + tp.tv_usec / 1000; 
     
        
    gettimeofday(&tp, NULL);
    long int begin2 = tp.tv_sec * 1000 + tp.tv_usec / 1000; 
    std::map<std::string, int>  map_std;
    std::map<std::string, int>  map_std2;
    for (int i = 1; i < 30000; i++)
    {
        map_std.insert(std::make_pair<std::string>(std::to_string(i), i));
        map_std.find(std::to_string(i));
        map_std.count(std::to_string(i));
        map_std.empty();
        map_std.size();
        map_std.begin(); map_std.end();
        map_std.erase(std::to_string(i));
        map_std.insert(std::make_pair<std::string>(std::to_string(i), i));
        map_std.swap(map_std2);
        map_std2.swap(map_std2);
    }
    map_std.erase(map_std.begin(), map_std.end());
    gettimeofday(&tp, NULL);
    long int end2 = tp.tv_sec * 1000 + tp.tv_usec / 1000; 
    unsigned int res1 = (end - begin);
    unsigned int res2 = (end2 - begin2);
    std::cout << res1 << "/" << res2 << " : " << (float)res1/(float)res2 << std::endl;
}