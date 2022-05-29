/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 14:06:30 by abittel           #+#    #+#             */
/*   Updated: 2022/05/30 00:26:43 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace ft 
{

template<class T>
class random_access_iterator
{
	private :
		T*	_data;
	public:
	    typedef T value_type;
	    typedef T& reference; 
		typedef T* pointer;
	    typedef std::ptrdiff_t difference_type;

		explicit random_access_iterator() : _data(NULL) {}
		explicit random_access_iterator(T* data) : _data(data) {}
		random_access_iterator(random_access_iterator<T>& cp) : _data(cp._data) {}
		random_access_iterator(random_access_iterator<T> const& cp) : _data(cp._data) {}
		random_access_iterator&	operator=(random_access_iterator<T>& cp) { this->_data = cp._data; return *(this); }	
		random_access_iterator&	operator=(random_access_iterator<T> const& cp) { this->_data = cp._data; return *(this); }	
		random_access_iterator	operator++(int) { this->_data++; return (random_access_iterator<T>(this->_data - 1)); }	
		random_access_iterator&	operator++() { this->_data++; return *(this); }	
		random_access_iterator&	operator--() { this->_data--; return *(this); }	
		random_access_iterator	operator--(int) { this->_data--; return (random_access_iterator<T>(this->_data + 1)); }	
		random_access_iterator	operator+=(std::ptrdiff_t n) { 
			_data += n; 
			return *(this); 
		}
		random_access_iterator	operator-=(std::ptrdiff_t n) { 
			_data += n; 
			return *(this); 
		}
		random_access_iterator	operator+(std::ptrdiff_t n) const { 
			random_access_iterator<T> inter(*this);
			inter._data += n; 
			return inter; 
		}	
		random_access_iterator	operator-(std::ptrdiff_t n) const { 
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
		T&	operator[](int idx) { return this->_data[idx]; }	
		T&	operator*() { return *this->_data; }	
		bool	operator==(random_access_iterator const& op) const { return (this->_data == op._data); }	
		bool	operator!=(const random_access_iterator& op) const { return (this->_data != op._data); }	
		bool	operator<=(random_access_iterator& op) const { return (this->_data <= op._data); }	
		bool	operator<(random_access_iterator& op)  const { return (this->_data < op._data); }	
		bool	operator>=(random_access_iterator& op) const { return (this->_data >= op._data); }	
		bool	operator>(random_access_iterator& op)  const { return (this->_data > op._data); }	
		operator random_access_iterator<T const>() const { return *(this);}
};

template<class T>
class reverse_iterator_type
{
	private :
		T*	_data;
	public:
	    typedef T value_type;
	    typedef T& reference; 
		typedef T* pointer;
	    typedef std::ptrdiff_t difference_type;

		explicit reverse_iterator_type() : _data(NULL) {}
		explicit reverse_iterator_type(T* data) : _data(data) {}
		reverse_iterator_type(reverse_iterator_type<T>& cp) : _data(cp._data) {}
		reverse_iterator_type(reverse_iterator_type<T> const& cp) : _data(cp._data) {}
		reverse_iterator_type&	operator=(reverse_iterator_type<T>& cp) { this->_data = cp._data; return *(this); }	
		reverse_iterator_type&	operator=(reverse_iterator_type<T> const& cp) { this->_data = cp._data; return *(this); }	
		reverse_iterator_type	operator++(int) { this->_data--; return (reverse_iterator_type<T>(this->_data + 1)); }	
		reverse_iterator_type&	operator++() { this->_data--; return *(this); }	
		reverse_iterator_type&	operator--() { this->_data++; return *(this); }	
		reverse_iterator_type&	operator--(int) { this->_data++; return (reverse_iterator_type<T>(this->_data - 1)); }	
		reverse_iterator_type	operator+(std::ptrdiff_t n) const { 
			reverse_iterator_type<T> inter(*this);
			inter._data -= n; 
			return inter; 
		}	
		reverse_iterator_type	operator-(std::ptrdiff_t n) { 
			reverse_iterator_type<T> inter(*this);
			inter._data += n; 
			return inter; 
		}
		unsigned int	operator-(reverse_iterator_type<T>& op) const { 
			return (this->_data - op._data); 
		}
		unsigned int	operator-(reverse_iterator_type<T> const& op) const { 
			return (this->_data - op._data); 
		}	
		T&	operator[](int idx) { return this->_data[idx]; }	
		T&	operator*() { return *this->_data; }	
		bool	operator==(reverse_iterator_type& op) const { return (this->_data == op._data); }	
		bool	operator!=(const reverse_iterator_type& op) const { return (this->_data != op._data); }	
		bool	operator<=(reverse_iterator_type& op) const { return (this->_data <= op._data); }	
		bool	operator<(reverse_iterator_type& op)  const { return (this->_data < op._data); }	
		bool	operator>=(reverse_iterator_type& op) const { return (this->_data >= op._data); }	
		bool	operator>(reverse_iterator_type& op)  const { return (this->_data > op._data); }	
		operator reverse_iterator_type<T const>() const;

};
};