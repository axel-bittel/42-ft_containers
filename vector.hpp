/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 14:06:13 by abittel           #+#    #+#             */
/*   Updated: 2022/05/21 21:34:36 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iterator.hpp"
#include <memory>

namespace ft
{
	template<class T, class Alloc = std::allocator<T>>
	class vector
	{
		typedef	random_access_iterator<T> iterator_type;
		public:
			vector() : _begin(NULL), _end(NULL), _size(0), _size_alloued(0){}
			vector(unsigned int size, const T& value) : _size(size), _size_alloued(0)
			{
				if (size > _alloc.max_size())
					throw (std::bad_alloc());
				_begin = _alloc.allocate(size);
				_end = _begin + size;
				for (iterator_type i = _begin; i != _end; i++)
					_alloc.construct(i, value);
			}
			vector(iterator_type& first, iterator_type& last)
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
				for (iterator_type i = _begin, old = cp._begin; i != end; i++, old++)
					*i = *old;
			}
			~vector() { _alloc.deallocate(_begin, _size_alloued); }
			iterator_type	begin() { return (_begin);}
			reverse_iterator_type	rbegin() { return (_begin);}
			iterator_type	end() { return (_end);}
			reverseiterator_type	rend() { return (_end);}
			unsigned int	size() { return (_size); }
			unsigned int	max_size() { return (_alloc.max_size()); }
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
					up_size();
				for (iterator_type it = _end, i = 0; i < _size - n; i++, it++)
					*it = val;	
				_size = n;
				_end = _begin + n;
			}
			unsigned int	capacity() { return (_size_alloued); }
			bool			empty() { return (size == 0); }
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
				if (n > _size)
					trow (std::out_of_range());
				return (_begin[n]);
			}
			T&	front() { return (*_begin); }
			T&	back() { return (*_end); }
			void assign (iterator_type first, iterator_type last)
			{
				int	inter_size = last - first;
				if (inter_size > _alloc.max_size())
					throw (std::bad_alloc());
				if (inter_size > _size_alloued)
					up_size();
				for (unsigned int i = 0; first != last; i++)
					_begin[i] = *(first++);
			}
			void assign (unsigned int n, const T& val)
			{
				if (n > _alloc.max_size())
					throw (std::bad_alloc());
				if (n > _size_alloued)
					up_size();
				for (unsigned int i = 0; i < n; i++)
					_begin[i] = val;
			}
			void push_back(const T& val)
			{
				if (_begin + _size == _end)
					up_size();
				_begin[_size] = val;
				_end++;	
			}
			void pop_back()
			{
				_size--;
				_end--;
				_alloc.deallocate(_end, 1);
			}

		Alloc get_allocator() const { return (_alloc); }
		private:
			void	up_size(bool copy_old = true)
			{
				if (_size_alloued * 2 > _alloc.max_size())
					throw (std::bad_alloc());
				iterator_type	new_beg = _alloc.allocate(_size_alloued * 2 == 0 ? 1 : _size_alloued * 2);
				if (copy_old)
					for (iterator_type old = _begin, newv = new_beg; old != _end; old++, newv++)
						_alloc.construct(newv, *old);
				_alloc.deallocate(_begin, _size_alloued);
				_begin = new_beg;
				_end = new_beg + _size;
				_size_alloued = _size_alloued * 2 == 0 ? 1 : _size_alloued * 2;
			}
			void	up_size_to(unsigned int new_capacity, bool copy_old = true)
			{
				if (new_capacity > _alloc.max_size())
					throw (std::bad_alloc());
				iterator_type	new_beg = _alloc.allocate(new_capacity);
				if (copy_old)
					for (iterator_type old = _begin, newv = new_beg; old != _end; old++, newv++)
						_alloc.construct(newv, *old);
				_alloc.deallocate(_begin, _size_alloued);
				_begin = new_beg;
				_end = new_beg + _size;
				_size_alloued = new_capacity;
			}
			Alloc			_alloc;
			iterator_type	_begin;
			iterator_type	_end;
			unsigned int 	_size;
			unsigned int	_size_alloued;
	};
};