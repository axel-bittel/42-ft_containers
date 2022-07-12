/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 20:27:36 by abittel           #+#    #+#             */
/*   Updated: 2022/07/12 20:44:51 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.hpp"
#include <map>
#include <iostream>
#include <string>

#include <chrono>
int main()
{
    auto begin = std::chrono::high_resolution_clock::now();
    ft::map<std::string, int>   map_ft;
    ft::map<std::string, int>   map_ft2;

    for (int i = 1; i < 1000000; i++)
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
    auto end = std::chrono::high_resolution_clock::now();
        
    auto begin2 = std::chrono::high_resolution_clock::now();
    std::map<std::string, int>  map_std;
    std::map<std::string, int>  map_std2;
    for (int i = 1; i < 1000000; i++)
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
    auto end2 = std::chrono::high_resolution_clock::now();
    auto res1 =std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    auto res2 =std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - begin2);
    std::cout << res1.count() << "/" << res2.count() << " : " << (float)res1.count() / (float)res2.count() << std::endl;

}