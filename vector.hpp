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
			typedef Alloc 									allocator_type;
			typedef T 										value_type;
			typedef typename allocator_type::reference		reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer 		pointer;	
			typedef typename allocator_type::const_pointer 		const_pointer;	
			typedef normal_iterator<pointer, vector>				iterator;
			typedef normal_iterator<const_pointer,vector>			const_iterator;
			typedef _reverse_iterator<pointer>				reverse_iterator;
			typedef _reverse_iterator<const_pointer>			const_reverse_iterator;
			typedef size_t									size_type;
			typedef ptrdiff_t								difference_type;

			vector() : _begin(0), _end(0), _size(0), _size_alloued(0){}
			vector(size_t size, const T& value = value_type()) : _size(size), _size_alloued(size)
			{
				if (size > _alloc.max_size())
					throw (std::bad_alloc());
				_begin = _alloc.allocate(size);
				_end = _begin + size;
				for (size_type i = 0; _begin + i != _end; i++)
					_alloc.construct(_begin + i, value);
			}
			template<class InputIterator>
			void vector_init(InputIterator first, InputIterator last, __false_type)
			{
				_size = ft::distance(first, last);
				if (_size > _alloc.max_size())
					throw (std::bad_alloc());
				_begin = _alloc.allocate(_size);
				_end = _begin + _size;
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(_begin + i, *(first++));
				_size_alloued = _size;
			}
			template<class InputIterator>
			vector(InputIterator first, InputIterator last, typename ft::enable_if<!ft::__is_integer<InputIterator>::__value>::type * =  NULL)
			{
				typedef typename ft::__is_integer<InputIterator>::__type _Integral;
	  			vector_init(first, last, _Integral());
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
				reverse_iterator inter(_end);
				return inter;
			}
			const_reverse_iterator	rbegin() const
			{ 
				const_reverse_iterator inter(_end);
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
				reverse_iterator inter(_begin);
				return inter;
			}
			const_reverse_iterator	rend() const
			{ 
				const_reverse_iterator inter(_begin);
				return inter;
			}
			size_type	size() const { return (_size); }
			size_type	max_size() const { return (_alloc.max_size()); }
			void resize (size_type n, T val = value_type())
			{
				size_t	old_size = _size;
				if (n < _size)
				{
					pointer	new_begin = _alloc.allocate(n);
					for (size_type i = 0; i < _size; i++)
					{
						if (i < n)
							new_begin[i] = _begin[i];
						_alloc.destroy(_begin + i);
					}
					_alloc.deallocate(_begin, _size_alloued);
					_size_alloued = n;
					_size = n;
					_begin = new_begin;
					_end = _begin + n;
					return ;
				}	
				if (n > _size_alloued)
					up_size(n);
				for (pointer it = _begin + old_size; it < _begin + n; it++)
					*it = val;	
				_size = n;
				_end = _begin + n;
			}
			size_type capacity() const { return (_size_alloued); }
			bool			empty() const { return (_size == 0 ? true : false); }
			void			reserve(unsigned int n)
			{
				if (n > _size_alloued)
				{
					size_type	old_size = _size;
					up_size_to(n);
					_size = old_size;
					_end = _begin + _size;
				}
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
			template<class InputIterator>
			void _assign (InputIterator first, InputIterator last, __false_type)
			{
				size_type inter_size = ft::distance(first, last);
				if (inter_size > _alloc.max_size())
					throw (std::bad_alloc());
				if(inter_size > _size_alloued)
					up_size(inter_size);
				else
				{
					_size = inter_size;
					_end = _begin + inter_size;
				}
				for (unsigned int i = 0; first != last; i++, first++)
					_begin[i] = *(first);
			}
			template<class InputIterator>
			void assign (InputIterator first, InputIterator last, typename ft::enable_if<!ft::__is_integer<InputIterator>::__value>::type * =  NULL)
			{
				typedef typename ft::__is_integer<InputIterator>::__type _Integral;
	  			_assign(first, last, _Integral());
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
      	template<typename InputIterator>
    	void _insert (iterator position, InputIterator first, InputIterator last, __false_type)
		{
			size_type		n = ft::distance(first, last);
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
      	template<typename InputIterator>
    	void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::__is_integer<InputIterator>::__value>::type * =  NULL)
		{
			typedef typename ft::__is_integer<InputIterator>::__type _Integral;
  			_insert(position, first, last, _Integral());
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
			size_type 	_size;
			size_type	_size_alloued;
	};
	
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
		return (_lexicographical_compare(v1.begin(), v1.end(),v2.begin(), v2.end()));
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