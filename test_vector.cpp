/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 20:27:36 by abittel           #+#    #+#             */
/*   Updated: 2022/07/13 00:22:00 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include <vector>
#include <iostream>
#include <string>

#include <chrono>
int main()
{
    auto begin = std::chrono::high_resolution_clock::now();
    ft::vector<std::string>   map_ft;
    ft::vector<std::string>   map_ft2;

    for (int i = 1; i < 1000000; i++)
    {
        std::cout << "t:" << i << std::endl;
        map_ft.insert(map_ft.begin(), std::to_string(i));
        std::cout << "u:" << i << std::endl;
        /*map_ft.back();
        map_ft.capacity();
        map_ft.empty();
        map_ft.front();
        map_ft.erase(map_ft.begin());
        map_ft.push_back(std::to_string(i));
        map_ft.pop_back();
        map_ft.push_back(std::to_string(i));
        map_ft.size();
        map_ft.swap(map_ft2);
        map_ft2.swap(map_ft);*/
        std::cout << "t:" << i << std::endl;
    }
    std::cout << "bite" << std::endl;
    map_ft.erase(map_ft.begin(), map_ft.end());
    auto end = std::chrono::high_resolution_clock::now();
        
    auto begin2 = std::chrono::high_resolution_clock::now();
    std::vector<std::string>  map_std;
    std::vector<std::string>  map_std2;
    for (int i = 1; i < 1000000; i++)
    {
        map_std.insert(map_std.begin(), std::to_string(i));
        map_std.back();
        map_std.capacity();
        map_std.empty();
        map_std.erase(map_std.begin());
        map_std.front();
        map_std.pop_back();
        map_std.push_back(std::to_string(i));
        map_std.size();
        map_std.swap(map_std2);
        map_std2.swap(map_std);
    }
    map_std.erase(map_std.begin(), map_std.end());
    auto end2 = std::chrono::high_resolution_clock::now();
    auto res1 =std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    auto res2 =std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - begin2);
    std::cout << res1.count() << "/" << res2.count() << " : " << (float)res1.count() / (float)res2.count() << std::endl;

}