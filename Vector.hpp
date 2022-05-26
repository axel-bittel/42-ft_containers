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

namespace ft
{
	template<class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef T 										value_type;
			typedef Alloc 									allocator_type;
			typedef T&										reference;
			typedef const T&								const_reference;
			typedef T*	 									pointer;	
			typedef const T*								const_pointer;
			typedef random_access_iterator<T>				iterator;
			typedef random_access_iterator<const T>			const_iterator;
			typedef reverse_random_access_iterator<T>		reverse_iterator;
			typedef reverse_random_access_iterator<const T>	const_reverse_iterator;
			typedef size_t							size_type;

			vector() : _begin(0), _end(0), _size(0), _size_alloued(0){}
			vector(unsigned int size, const T& value = size_type()) : _size(size), _size_alloued(0)
			{
				if (size > _alloc.max_size())
					throw (std::bad_alloc());
				_begin = _alloc.allocate(size);
				_end = _begin + size;
				for (size_type i = 0; _begin + i != _end; i++)
					_alloc.construct(_begin + i, value);
			}
			vector(iterator& first, iterator& last)
			{
				_size = last - first;
				if (last - first > _alloc.max_size())
					throw (std::bad_alloc());
				_begin = _alloc.allocate(_size);
				_end = _begin + _size;
				_size_alloued = _size;
			}
			vector(vector& cp)
			{
				_size = cp._size;
				_size_alloued = _size;
				_begin = _alloc.allocate(_size);
				_end = _begin + _size;
				for (iterator i = _begin, old = cp._begin; i != _end; i++, old++)
					*i = *old;
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
				for (pointer i = _begin, cp = x.begin; i != _end; i++, cp++)
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
				const_iterator	inter(_begin);
				return inter;
			}
			reverse_iterator	rbegin() 
			{ 
				reverse_iterator inter(_end - 1);
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
			unsigned int	size() const { return (_size); }
			unsigned int	max_size() const { return (_alloc.max_size()); }
			void resize (unsigned int n, T val)
			{
				if (n < _size)
				{
					_size = n;
					_end = _begin + n;
					_alloc.deallocate(_end, _size - n);
					return ;
				}	
				if (n > _size_alloued)
					up_size(n);
				for (iterator it = _end, i = 0; i < _size - n; i++, it++)
					*it = val;	
				_size = n;
				_end = _begin + n;
			}
			unsigned int	capacity() const { return (_size_alloued); }
			bool			empty() { return (_size == 0 ? true : false); }
			void			reserve(unsigned int n)
			{
				if (n > _size_alloued)
					up_size_to(n);
			}
			T&	operator[](unsigned int n)
			{
				return (_begin[n]);
			}
			T&	at(unsigned int n)
			{
				if (n > _size){}
				return (_begin[n]);
			}
			T&	front() { return (*_begin); }
			T&	back() { return (*(_end - 1)); }
			void assign (iterator first, iterator last)
			{
				size_type inter_size = last - first;
				if (inter_size > _alloc.max_size())
					throw (std::bad_alloc());
				while (inter_size > _size_alloued)
					up_size(inter_size);
				for (unsigned int i = 0; first != last; i++)
					_begin[i] = *(first++);
			}
			void assign (unsigned int n, const T& val)
			{
				if (n > _alloc.max_size())
					throw (std::bad_alloc());
				while (n > _size_alloued)
					up_size(n);
				for (unsigned int i = 0; i < n; i++)
					_begin[i] = val;
			}
			void push_back(const T& val)
			{
				if (_size >= _size_alloued)
					up_size(_size + 1);
				_begin[_size] = val;
				_end++;	
			}
			void pop_back()
			{
				_size--;
				_end--;
				_alloc.deallocate(_end, 1);
			}

		allocator_type get_allocator() const { return (_alloc); }
		iterator insert (iterator position, const value_type& val)
		{
			unsigned int	pos = position - iterator(_begin);
			pointer			p_pos = &(*position);
			if (_size >= _size_alloued)
			{
				up_size_insert(_size + 1, pos, val);
				return iterator(_begin + pos);
			}
			else{
				_end++;
				_size++;
			}
			for (pointer i = _end - 1; i > p_pos; i--)
				*i = *(i - 1);
			_begin[pos] = val;
			return iterator(_begin + pos);
		}
    	void insert (iterator position, size_type n, const value_type& val)
		{
			unsigned int	pos = position - iterator(_begin);
			pointer			p_pos = &(*position) + n;
			if (_size + n >= _size_alloued)
				up_size_to(_size + n);
			else{
				_end += n;
				_size += n;
			}
			for (pointer i = _end - 1; i > p_pos; i--)
				*i = *(i - n);
			for (int i = pos + n - 1; i >= (int)pos; i--)
				_begin[i] = val;
		}
		//TO CHECK
    	void insert (iterator position, iterator first, iterator last)
		{
			size_type		n = last - first;
			unsigned int	pos = position - iterator(_begin);
			pointer			p_pos = &(*position) + n;
			if (_size + n >= _size_alloued)
				up_size_to(_size + n);
			else{
				_end += n;
				_size += n;
			}
			for (pointer i = _end - 1; i > p_pos; i--)
				*i = *(i - n);
			for (int i = pos + n - 1; i >= (int)pos; i--, last--)
				_begin[i] = *last;
		}
		iterator erase (iterator position)
		{
			_size--;
			_end--;
			for (pointer i = &(*position); i != _end; i++)
				*(i) = *(i + 1);
			_alloc.destroy(_end);
		}
		iterator erase (iterator first, iterator last)
		{
			size_type	n = last - first;
			_size -= n;
			_end -= n;
			for (pointer i = &(*first); i != &(last) + 1; i++)
				*(i) = *(i + n);
			for (pointer i = _end; i != _end + n; i++)
				_alloc.destroy(i);
		}
		void swap (ft::vector<value_type>& x)
		{
			pointer		old_begin 	= _begin;
			pointer		old_end	  	= _end;
			size_type	size		= _size;
			size_type	size_all	= _size_alloued;

			_begin = x.begin;
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
		friend	bool	operator==(vector& v1, vector&v2);
		friend	bool	operator!=(vector<T>& v1, vector<T>& v2);
		friend	bool	operator<(vector<T>& v1, vector<T>& v2);
		friend	bool	operator<=(vector<T>& v1, vector<T>& v2);
		friend	bool	operator>(vector<T>& v1, vector<T>& v2);
		friend	bool	operator>=(vector<T>& v1, vector<T>& v2);
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
					if (old > pos)
						_alloc.construct(new_beg + old, _begin[old - 1]);
					else
						_alloc.construct(new_beg + old, _begin[old]);
					_alloc.destroy(_begin + old);
				}
				new_beg[pos] = val;
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
	bool	operator==(vector<T>& v1, vector<T>& v2)
	{
		if (v1._size != v2._size)
			return (false);
		for (size_t i = 0; i < v1._size; i++)
			if (!is_equal(v1[i], v2[i]))
				return (false);
		return (true);
	}
	template<class T>
	bool	operator!=(vector<T>& v1, vector<T>& v2)
	{
		return (!(v1 == v2));
	}
	template<class T>
	bool	operator<(vector<T>& v1, vector<T>& v2)
	{
		return (lexicographical_compare(iterator(v1._begin), *iterator(v1._end), itarator(v2._begin), iterator(v2._end)));
	}
	template<class T>
	bool	operator<=(vector<T>& v1, vector<T>& v2)
	{
		return (!(v2 < v1));
	}
	template<class T>
	bool	operator>(vector<T>& v1, vector<T>& v2)
	{
		return (v2 < v1);
	}
	template<class T>
	bool	operator>=(vector<T>& v1, vector<T>& v2)
	{
		return (!(v1 < v2));
	}
};