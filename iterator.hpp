/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 14:06:30 by abittel           #+#    #+#             */
/*   Updated: 2022/05/21 21:58:48 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

template<class T>
class Iiterator
{
	public:
		Iiterator(): _data(NULL){}
		Iiterator(T* data) : _data(data) {}
		Iiterator(Iiterator& cp) : _data(cp._data){}
	private:
		T*	_data;
};
template<class T>
class random_access_iterator : public Iiterator<T>
{
	public:
		random_access_iterator&	operator=(random_access_iterator& cp) { this->_data = cp->_data; return *(this); }	
		random_access_iterator&	operator++(int) { this->_data++; return (random_access_iterator<T>(this->_data - 1)); }	
		random_access_iterator&	operator++() { this->_data++; return *(this); }	
		random_access_iterator&	operator--() { this->_data--; return *(this); }	
		random_access_iterator&	operator--(int) { this->_data--; return (random_access_iterator<T>(this->_data + 1)); }	
		T&	operator[](int idx) { return this->_data[idx]; }	
		T&	operator*() { return *this->_data; }	
		operator unsigned int() { return (reinterpret_cast<unsigned long>(this->_data));}
};
template<class T>
class reverse_iterator : public Iiterator<T>
{
	public:
		reverse_iterator&	operator=(reverse_iterator& cp) { this->_data = cp->_data; return *(this); }	
		reverse_iterator&	operator++(int) { this->_data--; return (reverse_iterator<T>(this->_data + 1)); }	
		reverse_iterator&	operator++() { this->_data--; return *(this); }	
		reverse_iterator&	operator--() { this->_data++; return *(this); }	
		reverse_iterator&	operator--(int) { this->_data++; return (reverse_iterator<T>(this->_data - 1); }	
		T&	operator[](int idx) { return this->_data[idx]; }	
		T&	operator*() { return *this->_data; }	
		operator unsigned int() { return (reinterpret_cast<unsigned long>(this->_data));}
};