/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 14:06:30 by abittel           #+#    #+#             */
/*   Updated: 2022/05/26 18:09:02 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

namespace ft
{
template<class T>
class Iiterator
{
	public:
		explicit Iiterator(): _data(0){}
		explicit Iiterator(T* data) : _data(data) {}
		Iiterator(const Iiterator& cp) : _data(cp._data){}
		virtual unsigned int	operator-(Iiterator<T>& op) const { 
			return (this->_data - op._data); 
		}
	
	protected:
		T*	_data;
};
template<class T>
class random_access_iterator : public Iiterator<T>
{
	public:
		explicit random_access_iterator() : Iiterator<T>() {}
		explicit random_access_iterator(T* data) : Iiterator<T>(data) {}
		random_access_iterator(const random_access_iterator<T>& cp) : Iiterator<T>(cp) {}
		random_access_iterator&	operator=(random_access_iterator<T>& cp) { this->_data = cp._data; return *(this); }	
		random_access_iterator&	operator=(random_access_iterator<T> cp) { this->_data = cp._data; return *(this); }	
		random_access_iterator	operator++(int) { this->_data++; return (random_access_iterator<T>(this->_data - 1)); }	
		random_access_iterator&	operator++() { this->_data++; return *(this); }	
		random_access_iterator&	operator--() { this->_data--; return *(this); }	
		random_access_iterator&	operator--(int) { this->_data--; return (random_access_iterator<T>(this->_data + 1)); }	
		random_access_iterator	operator+(std::ptrdiff_t n) const { 
			random_access_iterator<T> inter(*this);
			inter._data += n; 
			return inter; 
		}	
		random_access_iterator	operator-(std::ptrdiff_t n)
		 { 
			random_access_iterator<T> inter(*this);
			inter._data -= n; 
			return inter; 
		}
		friend unsigned int	operator-(random_access_iterator<T>& op, random_access_iterator<T>& op2);
		T&	operator[](int idx) { return this->_data[idx]; }	
		T&	operator*() { return *this->_data; }	
		bool	operator==(random_access_iterator& op) const { return (this->_data == op._data); }	
		bool	operator!=(const random_access_iterator& op) const { return (this->_data != op._data); }	
		bool	operator<=(random_access_iterator& op) const { return (this->_data <= op._data); }	
		bool	operator<(random_access_iterator& op)  const { return (this->_data < op._data); }	
		bool	operator>=(random_access_iterator& op) const { return (this->_data >= op._data); }	
		bool	operator>(random_access_iterator& op)  const { return (this->_data > op._data); }	
		//operator unsigned int() { return (reinterpret_cast<unsigned long>(this->_data));}
};
template<class T>
class reverse_random_access_iterator : public Iiterator<T>
{
	public:
		reverse_random_access_iterator&	operator=(reverse_random_access_iterator& cp) { this->_data = cp->_data; return *(this); }	
		reverse_random_access_iterator&	operator++(int) { this->_data--; return (reverse_random_access_iterator<T>(this->_data + 1)); }	
		reverse_random_access_iterator&	operator++() { this->_data--; return *(this); }	
		reverse_random_access_iterator&	operator--() { this->_data++; return *(this); }	
		reverse_random_access_iterator&	operator--(int) { this->_data++; return (reverse_random_access_iterator<T>(this->_data - 1)); }	
		T&	operator[](int idx) { return this->_data[idx]; }	
		T&	operator*() { return *this->_data; }	
		//operator unsigned int() { return (reinterpret_cast<unsigned long>(this->_data));}
};

};