/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:43:03 by abittel           #+#    #+#             */
/*   Updated: 2022/06/24 13:17:12 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <limits>
#include <memory>
#include <cstddef>

namespace ft
{
	template<typename _Arg1, typename _Arg2, typename _Result>
    struct binary_function
    {
      /// @c first_argument_type is the type of the first argument
      typedef _Arg1 	first_argument_type; 

      /// @c second_argument_type is the type of the second argument
      typedef _Arg2 	second_argument_type;

      /// @c result_type is the return type
      typedef _Result 	result_type;
    };
	template<typename _Tp>
    struct less : public binary_function<_Tp, _Tp, bool>
    {
      bool operator()(const _Tp& __x, const _Tp& __y) const
      { return __x < __y; }
    };
	struct __true_type { };
 	struct __false_type { };
	 //ENABLE_IF
	template<bool, typename T = void>
    struct enable_if
    {};
  	template<typename T>
    struct enable_if<true, T>
    { typedef T type; };
	//IS_INTEGER
	template<typename _T>
	struct __is_integer
	{
	  enum { __value = 0 };
	  typedef __false_type __type;
	};
	template<>
	struct __is_integer<bool>
	{
	  enum { __value = 1 };
	  typedef __true_type __type;
	};

	template<>
	struct __is_integer<char>
	{
	  enum { __value = 1 };
	  typedef __true_type __type;
	};

	template<>
	struct __is_integer<signed char>
	{
	  enum { __value = 1 };
	  typedef __true_type __type;
	};

	template<>
	struct __is_integer<unsigned char>
	{
	  enum { __value = 1 };
	  typedef __true_type __type;
	};

	template<>
	struct __is_integer<short>
	{
	  enum { __value = 1 };
	  typedef __true_type __type;
	};

	template<>
	struct __is_integer<unsigned short>
	{
	  enum { __value = 1 };
	  typedef __true_type __type;
	};

	template<>
	struct __is_integer<int>
	{
	  enum { __value = 1 };
	  typedef __true_type __type;
	};

	template<>
	struct __is_integer<unsigned int>
	{
	  enum { __value = 1 };
	  typedef __true_type __type;
	};

	template<>
	struct __is_integer<long>
	{
	  enum { __value = 1 };
	  typedef __true_type __type;
	};

	template<>
	struct __is_integer<unsigned long>
	{
	  enum { __value = 1 };
	  typedef __true_type __type;
	};

	template<>
	struct __is_integer<long long>
	{
	  enum { __value = 1 };
	  typedef __true_type __type;
	};

	template<>
	struct __is_integer<unsigned long long>
	{
	  enum { __value = 1 };
	  typedef __true_type __type;
	};
	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };
	template<typename _Category, typename T, typename _Distance = ptrdiff_t,
	       typename _Pointer = T*, typename _Reference = T&>
	struct iterator
	{
	  typedef _Category  iterator_category;
	  typedef T        value_type;
	  typedef _Distance  difference_type;
	  typedef _Pointer   pointer;
	  typedef _Reference reference;
	};
	template<typename _Iterator>
	struct iterator_traits
	{
	  typedef typename _Iterator::iterator_category iterator_category;
	  typedef typename _Iterator::value_type        value_type;
	  typedef typename _Iterator::difference_type   difference_type;
	  typedef typename _Iterator::pointer           pointer;
	  typedef typename _Iterator::reference         reference;
	};
	template<typename T>
	struct iterator_traits<T*>
	{
	  typedef random_access_iterator_tag iterator_category;
	  typedef T                         value_type;
	  typedef ptrdiff_t                   difference_type;
	  typedef T*                        pointer;
	  typedef T&                        reference;
	};
	template<typename T>
	struct iterator_traits<const T*>
	{
	  typedef random_access_iterator_tag iterator_category;
	  typedef T                         value_type;
	  typedef ptrdiff_t                   difference_type;
	  typedef const T*                  pointer;
	  typedef const T&                  reference;
	};
	template<typename _Iter>
	typename iterator_traits<_Iter>::iterator_category
	iterator_category(const _Iter&) { return typename iterator_traits<_Iter>::iterator_category(); }
	template <class iterator1, class iterator2>
	bool _lexicographical_compare (iterator1 first1, iterator1 last1, iterator2 first2, iterator2 last2)
	{
		while (first1!=last1)
		{
			if (first2==last2 || *first2<*first1) return false;
			else if (*first1<*first2) return true;
			++first1; ++first2;
		}
		return (first2!=last2);
	}
	template<class T>
	bool	is_equal(T& a, T&b) { return (a == b); }
	template<class Iterator1>
	bool	equal(Iterator1 b1, Iterator1 e1, Iterator1 b2) 
	{
		for (; b1 != e1; ++b1, ++b2)
			if (!is_equal(b1, b2))
				return (false);
		return (true);
	}
}