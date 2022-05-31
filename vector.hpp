/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 14:06:13 by abittel           #+#    #+#             */
/*   Updated: 2022/05/22 21:03:08by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iterator.hpp"
#include <stdexcept>
#include <memory>
#include <limits>

namespace ft
{
	template<class T, class Alloc = std::allocator<T> >
	class vector;
	template<class T>
	bool	operator==(const vector<T>& v1, const vector<T>& v2);
	template<class T>
	bool	operator!=(const vector<T>& v1, const vector<T>& v2);
	template<class T>
	bool	operator<(const vector<T>& v1, const vector<T>& v2);
	template<class T>
	bool	operator<=(const vector<T>& v1, const vector<T>& v2);
	template<class T>
	bool	operator>(const vector<T>& v1, const vector<T>& v2);
	template<class T>
	bool	operator>=(const vector<T>& v1, const vector<T>& v2);
	template<class T, class Alloc>
	class vector
	{
		public:
			typedef T 										value_type;
			typedef Alloc 									allocator_type;
			typedef typename allocator_type::reference		reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer 		pointer;	
			typedef const T*								const_pointer;
			typedef random_access_iterator<T>				iterator;
			typedef random_access_iterator<T const>			const_iterator;
			typedef reverse_iterator_type<T>		reverse_iterator;
			typedef reverse_iterator_type<T const>	const_reverse_iterator;
			typedef size_t							size_type;

			vector() : _begin(0), _end(0), _size(0), _size_alloued(0){}
			vector(unsigned int size, const T& value = value_type()) : _size(size), _size_alloued(size)
			{
				if (size > _alloc.max_size())
					throw (std::bad_alloc());
				_begin = _alloc.allocate(size);
				_end = _begin + size;
				for (size_type i = 0; _begin + i != _end; i++)
					_alloc.construct(_begin + i, value);
			}
			vector(iterator const& first, iterator const& last)
			{
				_size = (last - first);
				if (_size > _alloc.max_size())
					throw (std::bad_alloc());
				_begin = _alloc.allocate(_size);
				_end = _begin + _size;
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(_begin + i, *(first + i));
				_size_alloued = _size;
			}
			vector(vector const& cp)
			{
				_size = cp._size;
				_size_alloued = _size;
				_begin = _alloc.allocate(_size);
				_end = _begin + _size;
				for (pointer i = _begin, old = cp._begin; old != cp._end; i++, old++)
					_alloc.construct(i, *old);
			}
			~vector() 
			{
				for (pointer i = _begin; i != _end; i++) 
					_alloc.destroy(i);
				_alloc.deallocate(_begin, _size_alloued); 
			}
			vector& operator= (const vector& x)
			{
				if (x._size > _size_alloued)
					up_size_to(x._size, false);
				for (pointer i = _begin; i != _end; i++)
					_alloc.destroy(i);
				_size = x._size;
				_end  = _begin + _size;
				for (pointer i = _begin, cp = x._begin; i != _end; i++, cp++)
					_alloc.construct(i, *cp);
				return *(this);
			}
			iterator	begin()
			{ 
				iterator	inter(_begin);
				return inter;
			}
			const_iterator	begin() const
			{ 
				return const_iterator(_begin);
			}
			reverse_iterator	rbegin()
			{ 
				reverse_iterator inter(_end - 1);
				return inter;
			}
			const_reverse_iterator	rbegin() const
			{ 
				const_reverse_iterator inter(_end - 1);
				return inter;
			}
			iterator	end() 
			{ 
				iterator inter(_end);
				return (inter);
			}
			const_iterator	end() const
			{ 
				const_iterator	inter(_end);
				return inter;
			}
			reverse_iterator	rend() 
			{ 
				reverse_iterator inter(_begin - 1);
				return inter;
			}
			const_reverse_iterator	rend() const
			{ 
				const_reverse_iterator inter(_begin - 1);
				return inter;
			}
			size_type	size() const { return (_size); }
			size_type	max_size() const { return (_alloc.max_size()); }
			void resize (unsigned int n, T val = value_type())
			{
				if (n < _size)
				{
					_end = _begin + n;
					for (size_type i = 0; i < _size - n; i++)
						_alloc.destroy(_end + i);
					//_alloc.deallocate(_end, 1);
					_size = n;
					return ;
				}	
				else if (n > _size_alloued)
					up_size(n);
				else
					return ;
				size_t i = 0;
				for (pointer it = _end - (_size - n); (size_type)i < _size - n; i++, it++)
					*it = val;	
				_size = n;
				_end = _begin + n;
			}
			unsigned int	capacity() const { return (_size_alloued); }
			bool			empty() const { return (_size == 0 ? true : false); }
			void			reserve(unsigned int n)
			{
				if (n > _size_alloued)
					up_size_to(n);
			}
			reference	operator[](size_type n)
			{
				return (_begin[n]);
			}
			reference	at(size_type n)
			{
				if (n > _size || n < 0)
					throw std::out_of_range("vector:Out of the vector.");
				return (_begin[n]);
			}
			const_reference	at(unsigned int n) const
			{
				if (n > _size || n < 0)
					throw std::out_of_range("vector:Out of the vector.");
				return (_begin[n]);
			}
			reference	front() { return (*_begin); }
			const_reference	front() const { return (*_begin); }
			reference	back() { return (*(_end - 1)); }
			const_reference	back() const { return (*(_end - 1)); }
			void assign (iterator first, iterator last)
			{
				size_type inter_size = (last - first);
				if (inter_size > _alloc.max_size())
					throw (std::bad_alloc());
				if(inter_size > _size_alloued)
					up_size(inter_size);
				else
				{
					_size = inter_size;
					_end = _begin + inter_size;
				}
				for (unsigned int i = 0; first != last; i++)
					_begin[i] = *(first++);
			}
			void assign (size_type n, const T& val)
			{
				if (n > _alloc.max_size())
					throw (std::bad_alloc());
				if (n > _size_alloued)
					up_size(n);
				for (size_type i = 0; i < n; i++)
					_begin[i] = val;
				if (n != _size)
				{
					_size = n;
					_end = _begin + n;
				}
			}
			void push_back(const T& val)
			{
				if (_size >= _size_alloued)
					up_size(_size + 1);
				else
				{
					_size++;
					_end++;	
				}
				_begin[_size - 1] = val;
			}
			void pop_back()
			{
				if (_size > 0)
				{
					_size--;
					_end--;
					_alloc.destroy(_end);
				}
			}

		allocator_type get_allocator() const { return (_alloc); }
		iterator insert (iterator position, const value_type& val)
		{
			unsigned int	pos = position - iterator(_begin);
			pointer			p_pos = &(*position);
			if (_size >= _size_alloued)
			{
				up_size(_size + 1);
				position = iterator(_begin + pos);
				p_pos = &(*position);
			}
			else{
				_end++;
				_size++;
			}
			for (pointer i = _end - 1; i >= p_pos; i--)
				*i = *(i - 1);
			_begin[pos] = val;
			return iterator(_begin + pos);
		}
    	void insert (iterator position, size_type n, const value_type& val)
		{
			unsigned int	pos = position - iterator(_begin);
			if (_size + n > _size_alloued)
			{
				up_size_to(_size + n);
				position = iterator(_begin + pos);
			}
			else{
				_end += n;
				_size += n;
			}
			pointer			p_pos = &(*position) + n;
			for (pointer i = _end - 1; i >= p_pos; i--)
				*i = *(i - n);
			for (unsigned int i = pos; i < pos + n; i++)
				_begin[i] = val;
		}
		//TO CHECK
    	void insert (iterator position, iterator first, iterator last)
		{
			size_type		n = last - first;
			unsigned int	pos = position - iterator(_begin);

			if (_size + n >= _size_alloued)
			{
				up_size_to(_size + n);
				position = iterator(_begin + pos);
			}
			else{
				_end += n;
				_size += n;
			}
			pointer			p_pos = &(*position) + n;
			for (pointer i = _end - 1; i >= p_pos; i--)
				*i = *(i - n);
			for (size_type i = pos; i < pos + n; i++, first++)
				_begin[i] = *first;
		}
		iterator erase (iterator position)
		{
			size_type n = position - iterator(_begin);
			_size--;
			_end--;
			for (pointer i = &(*position); i != _end; i++)
				*(i) = *(i + 1);
			_alloc.destroy(_end);
			return iterator(_begin + n);
		}
		iterator erase (iterator first, iterator last)
		{
			size_type	n = last - first;
			for (pointer i = &(*first); i + n != _end; i++)
				*(i) = *(i + n);
			_size -= n;
			_end -= n;
			for (pointer i = _end; i != _end + n; i++)
				_alloc.destroy(i);
			return iterator(_begin + (first - iterator(_begin)));
		}
		void swap (ft::vector<value_type>& x)
		{
			pointer		old_begin 	= _begin;
			pointer		old_end	  	= _end;
			size_type	size		= _size;
			size_type	size_all	= _size_alloued;

			_begin = x._begin;
			_end = x._end;
			_size = x._size;
			_size_alloued = x._size_alloued;
			x._begin = old_begin;
			x._end = old_end;
			x._size = size;
			x._size_alloued = size_all;
		}
		void clear()
		{
			for (pointer i = _begin; i != _end; i++)
				_alloc.destroy(i);
			_size = 0;
			_end = _begin;
		}
		friend	bool	operator== <> (const vector<T>& v1, const vector<T>&v2);
		friend	bool	operator!= <> (const vector<T>& v1, const vector<T>& v2);
		friend	bool	operator< <> (const vector<T>& v1, const vector<T>& v2);
		friend	bool	operator<= <> (const vector<T>& v1, const vector<T>& v2);
		friend	bool	operator> <> (const vector<T>& v1, const vector<T>& v2);
		friend	bool	operator>= <> (const vector<T>& v1, const vector<T>& v2);
		private:
			void	up_size(unsigned int new_size)
			{
				unsigned int new_size_alloued = _size_alloued == 0 ? 1 : _size_alloued;
				while (new_size_alloued < new_size)
					new_size_alloued = new_size_alloued << 1;
				if (new_size_alloued > _alloc.max_size())
					throw (std::bad_alloc());
				pointer	new_beg = _alloc.allocate(new_size_alloued);
				for (size_type old = 0; _begin + old != _end; old++)
				{
					_alloc.construct(new_beg + old, _begin[old]);
					_alloc.destroy(_begin + old);
				}
				if(_begin)
					_alloc.deallocate(_begin, _size_alloued);
				_begin = new_beg;
				_size_alloued = new_size_alloued;
				_size = new_size;
				_end = new_beg + _size;
			}
			void	up_size_insert(unsigned int new_size, size_type pos, const value_type& val)
			{
				unsigned int new_size_alloued = _size_alloued == 0 ? 1 : _size_alloued;
				while (new_size_alloued < new_size)
					new_size_alloued = new_size_alloued << 1;
				if (new_size_alloued > _alloc.max_size())
					throw (std::bad_alloc());
				pointer	new_beg = _alloc.allocate(new_size_alloued);
				for (size_type old = 0; _begin + old != _end; old++)
				{
					if (old >= pos) 
						_alloc.construct(new_beg + old, _begin[old - 1]);
					else
						_alloc.construct(new_beg + old, _begin[old]);
					_alloc.destroy(_begin + old);
				}
				_alloc.construct(new_beg + pos, val);
				if(_begin)
					_alloc.deallocate(_begin, _size_alloued);
				_begin = new_beg;
				_size_alloued = new_size_alloued;
				_size = new_size;
				_end = new_beg + _size;
			}

			void	up_size_to(unsigned int new_capacity, bool copy_old = true)
			{
				if (new_capacity > _alloc.max_size())
					throw (std::bad_alloc());
				pointer	new_beg = _alloc.allocate(new_capacity);
				if (copy_old)
				{
					for (size_type old = 0; _begin + old != _end; old++)
					{
						_alloc.construct(new_beg + old, _begin[old]);
						_alloc.destroy(_begin + old);
					}
				}
				if (_begin)
					_alloc.deallocate(_begin, _size_alloued);
				_begin = new_beg;
				_size_alloued = new_capacity;
				_size = new_capacity;
				_end = new_beg + _size;
			}
			allocator_type	_alloc;
			pointer			_begin;
			pointer			_end;
			unsigned int 	_size;
			unsigned int	_size_alloued;
	};
	template<class T>
	bool	is_equal(T& a, T&b) { return (a == b); }
	template <class iterator1, class iterator2>
	bool lexicographical_compare (iterator1 first1, iterator1 last1, iterator2 first2, iterator2 last2)
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
	bool	operator==(const vector<T>& v1, const vector<T>& v2)
	{
		if (v1._size != v2._size)
			return (false);
		for (size_t i = 0; i < v1._size; i++)
			if (!is_equal(v1.at(i), v2.at(i)))
				return (false);
		return (true);
	}
	template<class T>
	bool	operator!=(const vector<T>& v1, const vector<T>& v2)
	{
		return (!(v1 == v2));
	}
	template<class T>
	bool	operator<(const vector<T>& v1, const vector<T>& v2)
	{
		return (lexicographical_compare(	random_access_iterator<T>(v1._begin), random_access_iterator<T>(v1._end),\
										 	random_access_iterator<T>(v2._begin), random_access_iterator<T>(v2._end)));
	}
	template<class T>
	bool	operator<=(const vector<T>& v1, const vector<T>& v2)
	{
		return (!(v2 < v1));
	}
	template<class T>
	bool	operator>(const vector<T>& v1, const vector<T>& v2)
	{
		return (v2 < v1);
	}
	template<class T>
	bool	operator>=(const vector<T>& v1, const vector<T>& v2)
	{
		return (!(v1 < v2));
	}
};