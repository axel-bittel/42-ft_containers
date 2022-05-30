/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 14:06:30 by abittel           #+#    #+#             */
/*   Updated: 2022/05/30 19:30:45 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <memory>
namespace ft 
{

template<class T>
class Iterator
{
protected:
	T*	_data;
public:
	typedef T value_type;
	typedef T& reference; 
	typedef T* pointer;
	typedef std::ptrdiff_t difference_type;

	explicit Iterator<T>() : _data(NULL) {}
	explicit Iterator<T>(T* data) : _data(data) {}
	Iterator<T>(Iterator<T>& cp) : _data(cp._data) {}
	Iterator<T>(Iterator<T> const& cp) : _data(cp._data) {}
	bool	operator==(Iterator<T> const& op) const { return (this->_data == op._data); }	
	bool	operator!=(Iterator<T> const& op) const { return (this->_data != op._data); }	
	bool	operator<=(Iterator<T> const& op) const { return (this->_data <= op._data); }	
	bool	operator<(Iterator<T> const& op)  const { return (this->_data < op._data); }	
	bool	operator>=(Iterator<T> const& op) const { return (this->_data >= op._data); }	
	bool	operator>(Iterator<T> const& op)  const { return (this->_data > op._data); }	
};
template<class T>
class random_access_iterator : public Iterator<T const>
{
		public:
	    typedef T value_type;
	    typedef T& reference; 
		typedef T* pointer;
	    typedef std::ptrdiff_t difference_type;

		explicit random_access_iterator<T>() : Iterator<T const>(){}
		explicit random_access_iterator<T>(T* data) : Iterator<T const>(data){}
		random_access_iterator<T>(random_access_iterator<T>& cp) : Iterator<T const>(cp) {}
		random_access_iterator<T>(const random_access_iterator<T>& cp) : Iterator<T const>(cp) {}
		random_access_iterator<T>&	operator=(random_access_iterator<T>& cp) { this->_data = cp._data; return *(this); }	
		random_access_iterator<T>&	operator=(random_access_iterator<T> const& cp) { this->_data = cp._data; return *(this); }	
		random_access_iterator<T>	operator++(int) { (this->_data) += 1; return (random_access_iterator<T>((T*)this->_data - 1)); }	
		random_access_iterator<T>&	operator++() { (this->_data) += 1; return *(this); }	
		random_access_iterator<T>&	operator--() { (this->_data) -= 1; return *(this); }	
		random_access_iterator<T>	operator--(int) { (this->_data) -= 1; return (random_access_iterator<T>((T*)this->_data + 1)); }	
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
		unsigned int	operator-(random_access_iterator<T>& op) const { 
			return (this->_data - op._data); 
		}
		unsigned int	operator-(random_access_iterator<T> const& op) const { 
			return (this->_data - op._data); 
		}	
		T&	operator[](int idx) { return ((T*)this->_data)[idx]; }	
		T&	operator*() { return *(T*)this->_data; }	
		pointer operator->() { return (T*)(this->_data); }	
		friend random_access_iterator<T> operator+(size_t n,random_access_iterator<T> const &op)
		{
			return (random_access_iterator((T*)op._data + n));
		}
		friend random_access_iterator<T> operator-(size_t n,random_access_iterator<T> const &op)
		{
			return (random_access_iterator((T*)op._data - n));
		}
		operator random_access_iterator<T const>() const { return random_access_iterator<T const>(this->_data);}
};

template<class T>
class reverse_iterator_type : public Iterator<T const>
{
		public:
	    typedef T value_type;
	    typedef T& reference; 
		typedef T* pointer;
	    typedef std::ptrdiff_t difference_type;

		explicit reverse_iterator_type<T>() : Iterator<T const>(){}
		explicit reverse_iterator_type<T>(T* data) : Iterator<T const>(data){}
		reverse_iterator_type<T>(random_access_iterator<T>& cp) : Iterator<T const>(cp) {}
		reverse_iterator_type<T>(const random_access_iterator<T>& cp) : Iterator<T const>(cp) {}
		reverse_iterator_type<T>(reverse_iterator_type<T>& cp) : Iterator<T const>(cp) {}
		reverse_iterator_type<T>(const reverse_iterator_type<T>& cp) : Iterator<T const>(cp) {}
		reverse_iterator_type<T>&	operator=(reverse_iterator_type<T>& cp) { this->_data = cp._data; return *(this); }	
		reverse_iterator_type<T>&	operator=(reverse_iterator_type<T> const& cp) { this->_data = cp._data; return *(this); }	
		reverse_iterator_type<T>	operator++(int) { (this->_data) -= 1; return (reverse_iterator_type<T>((T*)this->_data + 1)); }	
		reverse_iterator_type<T>&	operator++() { (this->_data) -= 1; return *(this); }	
		reverse_iterator_type<T>&	operator--() { (this->_data) += 1; return *(this); }	
		reverse_iterator_type<T>	operator--(int) { (this->_data) += 1; return (reverse_iterator_type<T>((T*)this->_data - 1)); }	
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
		T&	operator[](int idx) { return ((T*)this->_data)[-idx]; }	
		T&	operator*() { return *(T*)this->_data; }	
		pointer operator->() { return (T*)(this->_data); }	
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
			return (random_access_iterator<T>((T*)this->_data));
		}
};
};