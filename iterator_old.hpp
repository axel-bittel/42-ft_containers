/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 14:06:30 by abittel           #+#    #+#             */
/*   Updated: 2022/06/01 13:06:11 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits>
#include <memory>
#include <cstddef>
namespace ft 
{
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	template<class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
		struct iterator
		{
			typedef Category	iterator_category;
			typedef T			value_type;
			typedef Distance	difference_type;
			typedef Pointer		pointer;
			typedef Reference	reference;
		};

	template<class T>
		struct iterator_traits
		{
			typedef typename T::iterator_category	iterator_category;
			typedef typename T::value_type			value_type;
			typedef typename T::difference_type		difference_type;
			typedef typename T::pointer				pointer;
			typedef typename T::reference			reference;
		};

	template<class T>
	struct iterator_traits<T*>
	{
		typedef random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef ptrdiff_t					difference_type;
		typedef T*						pointer;
		typedef T&						reference;
	};

	template<class T>
	struct iterator_traits<T* const>
	{
		typedef random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef ptrdiff_t					difference_type;
		typedef const T*					pointer;
		typedef const T&					reference;
	};

template<class T, class _Container >
class Iterator 
{
protected:
	typedef	iterator_traits<T>	it_type;
	T	_data;
public:
	typedef typename it_type::iterator_category iterator_category;
	typedef typename it_type::value_type value_type;
	typedef typename it_type::reference reference; 
	typedef typename it_type::pointer pointer;
	typedef typename it_type::difference_type difference_type;

	Iterator<T, _Ca>() : _data(T()) {}
	Iterator<T>(const T& data) : _data(data) {}
	bool	operator==(Iterator<T> const& op) const { return (this->_data == op._data); }	
	bool	operator!=(Iterator<T> const& op) const { return (this->_data != op._data); }	
	bool	operator<=(Iterator<T> const& op) const { return (this->_data <= op._data); }	
	bool	operator<(Iterator<T> const& op)  const { return (this->_data < op._data); }	
	bool	operator>=(Iterator<T> const& op) const { return (this->_data >= op._data); }	
	bool	operator>(Iterator<T> const& op)  const { return (this->_data > op._data); }	
};
template<class T, class Container>
class random_access_iterator : public Iterator<T>
{
		private:
			typedef	iterator_traits<T>	it_type;
		public:
			typedef typename it_type::iterator_category iterator_category;
			typedef typename it_type::value_type value_type;
			typedef typename it_type::reference reference; 
			typedef typename it_type::pointer pointer;
			typedef typename it_type::difference_type difference_type;

		random_access_iterator<T>() : Iterator<T>(){}
		random_access_iterator<T>(const T& data) : Iterator<T>(data){}
		random_access_iterator<T>&	operator=(random_access_iterator<T>& cp) { this->_data = cp._data; return *(this); }	
		random_access_iterator<T>&	operator=(random_access_iterator<T> const& cp) { this->_data = cp._data; return *(this); }	
		random_access_iterator<T>	operator++(int) { (this->_data) += 1; return (random_access_iterator<T>(this->_data - 1)); }	
		random_access_iterator<T>&	operator++() { (this->_data) += 1; return *(this); }	
		random_access_iterator<T>&	operator--() { (this->_data) -= 1; return *(this); }	
		random_access_iterator<T>	operator--(int) { (this->_data) -= 1; return (random_access_iterator<T>(this->_data + 1)); }	
		random_access_iterator<T>	operator+=(std::ptrdiff_t n) { 
			this->_data += n; 
			return *(this); 
		}
		random_access_iterator<T>	operator-=(std::ptrdiff_t n) { 
			this->_data -= n; 
			return *(this); 
		}
		random_access_iterator<T>	operator+(std::ptrdiff_t n) const { 
			random_access_iterator<T> inter(*this);
			inter._data += n; 
			return inter; 
		}	
		random_access_iterator<T>	operator-(std::ptrdiff_t n) const { 
			random_access_iterator<T> inter(*this);
			inter._data -= n; 
			return inter; 
		}
		int operator-(random_access_iterator<T>& op) const { 
			return (this->_data - op._data); 
		}
		int operator-(random_access_iterator<T> const& op) const { 
			return (this->_data - op._data); 
		}	
		reference	operator[](int idx) { return (this->_data)[idx]; }	
		reference operator*() { return *this->_data; }	
		pointer operator->() { return (this->_data); }	
		friend random_access_iterator<T> operator+(size_t n,random_access_iterator<T> const &op)
		{
			return (random_access_iterator(op._data + n));
		}
		friend random_access_iterator<T> operator-(size_t n,random_access_iterator<T> const &op)
		{
			return (random_access_iterator(op._data - n));
		}
		//operator random_access_iterator<T>() { return random_access_iterator<T>(this->_data);}
		operator random_access_iterator<T const>() { return random_access_iterator<T const>((T const)this->_data);}
};

template<class T>
class reverse_iterator_type : public Iterator<T>, public iterator<typename ft::iterator_traits<T>::iterator_category,
						typename ft::iterator_traits<T>::value_type,
						typename ft::iterator_traits<T>::difference_type,
						typename ft::iterator_traits<T>::pointer,
						typename ft::iterator_traits<T>::reference>
{
		private:
			typedef	iterator_traits<T>	it_type;
		public:
			typedef typename it_type::iterator_category iterator_category;
			typedef typename it_type::value_type value_type;
			typedef typename it_type::reference reference; 
			typedef typename it_type::pointer pointer;
			typedef typename it_type::difference_type difference_type;

		explicit reverse_iterator_type<T>() : Iterator<T const>(){}
		explicit reverse_iterator_type<T>(T* data) : Iterator<T const>(data){}
		reverse_iterator_type<T>(random_access_iterator<T>& cp) : Iterator<T const>(cp) { }
		reverse_iterator_type<T>(const random_access_iterator<T>& cp) : Iterator<T const>(cp) {}
		reverse_iterator_type<T>(reverse_iterator_type<T>& cp) : Iterator<T const>(cp) {}
		reverse_iterator_type<T>(const reverse_iterator_type<T>& cp) : Iterator<T const>(cp) {}
		reverse_iterator_type<T>&	operator=(reverse_iterator_type<T>& cp) { this->_data = cp._data; return *(this); }	
		reverse_iterator_type<T>&	operator=(reverse_iterator_type<T> const& cp) { this->_data = cp._data; return *(this); }	
		reverse_iterator_type<T>	operator++(int) { (this->_data) -= 1; return (reverse_iterator_type<T>(this->_data + 1)); }	
		reverse_iterator_type<T>&	operator++() { (this->_data) -= 1; return *(this); }	
		reverse_iterator_type<T>&	operator--() { (this->_data) += 1; return *(this); }	
		reverse_iterator_type<T>	operator--(int) { (this->_data) += 1; return (reverse_iterator_type<T>(this->_data - 1)); }	
		reverse_iterator_type<T>	operator+=(std::ptrdiff_t n) { 
			this->_data -= n; 
			return *(this); 
		}
		reverse_iterator_type<T>	operator-=(std::ptrdiff_t n) { 
			this->_data += n; 
			return *(this); 
		}
		reverse_iterator_type<T>	operator+(std::ptrdiff_t n) const { 
			reverse_iterator_type<T> inter(*this);
			inter._data -= n; 
			return inter; 
		}	
		reverse_iterator_type<T>	operator-(std::ptrdiff_t n) const { 
			reverse_iterator_type<T> inter(*this);
			inter._data += n; 
			return inter; 
		}
		long	operator-(reverse_iterator_type<T>& op) const { 
			return -(this->_data - op._data); 
		}
		long operator-(reverse_iterator_type<T> const& op) const { 
			return -(this->_data - op._data); 
		}	
		reference	operator[](int idx) { return ((T*)this->_data)[-idx-1]; }	
		reference	operator*() { return *((T*)this->_data - 1); }	
		pointer operator->() { return (T*)(this->_data - 1); }	
		friend reverse_iterator_type<T> operator+(size_t n,reverse_iterator_type<T> const &op)
		{
			return (reverse_iterator_type((T*)op._data - n));
		}
		friend reverse_iterator_type<T> operator-(size_t n,reverse_iterator_type<T> const &op)
		{
			return (reverse_iterator_type(n - (T*)op._data));
		}
		operator reverse_iterator_type<T const>() const { return reverse_iterator_type<T const>(this->_data);}
		random_access_iterator<T>	base() const
		{
			T* inter = (T*)this->_data;
			return (random_access_iterator<T>(inter));
		}
};
};