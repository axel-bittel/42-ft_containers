/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 01:21:48 by abittel           #+#    #+#             */
/*   Updated: 2022/07/17 23:16:49 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <memory>
#include "tree.hpp"
namespace ft
{

template < class Key, class T,  class Compare = ft::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > > 
class map
{
	
	public:	
		typedef Key											key_type;
		typedef	T											mapped_type;
		typedef	ft::pair<const key_type, mapped_type>		value_type;
		class value_compare : public ft::binary_function<value_type, value_type,bool>
		{   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
		 	friend class map;
			protected:
			  Compare comp;
			  value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
			public:
			  typedef bool result_type;
			  typedef value_type first_argument_type;
			  typedef value_type second_argument_type;
			  bool operator() (const value_type& x, const value_type& y) const
			  {
			    return comp(x.first, y.first);
			  }
		};
		typedef	Compare										key_compare;
		typedef Alloc										allocator_type;
		typedef	typename allocator_type::reference			reference;
		typedef	typename allocator_type::const_reference	const_reference;
		typedef	typename allocator_type::pointer			pointer;
		typedef	typename allocator_type::const_pointer		const_pointer;
		typedef	Tree<key_type, mapped_type, key_compare>	tree_type;
		typedef	typename tree_type::iterator				iterator;	
		typedef	typename tree_type::const_iterator			const_iterator;	
		typedef	typename tree_type::difference_type			difference_type;
		typedef	typename tree_type::size_type				size_type;
		typedef map<Key, T,  Compare>						map_type;
		typedef	typename tree_type::reverse_iterator		reverse_iterator;
		typedef	typename tree_type::const_reverse_iterator	const_reverse_iterator;	

		map (const key_compare& comp = key_compare(),
	         const allocator_type& alloc = allocator_type()) : _comp(comp), _alloc(alloc)
		{
			_tree = _alloc_tree.allocate(1);
			_alloc_tree.construct(_tree, tree_type());
		}
		template <class InputIterator>
	  	map (InputIterator first, InputIterator last,
	       const key_compare& comp = key_compare(),
	       const allocator_type& alloc = allocator_type()) : _comp(comp), _alloc(alloc)
		{
			_tree = _alloc_tree.allocate(1);
			_alloc_tree.construct(_tree, tree_type());
			for (; first != last; first++)
			{
				if (_tree->_root == _tree->_nullNode || _tree->search(first->first) == _tree->_nullNode)
					_tree->insert(first->first, first->second);
			}
		}
		map (const map& x) 
		{ 
			_tree = _alloc_tree.allocate(1);
			_alloc_tree.construct(_tree, tree_type());
			*this = x; 
		}
		~map()
		{
			_alloc_tree.destroy(_tree);
			_alloc_tree.deallocate(_tree, 1);
		}
    	iterator begin() { return (_tree->begin()); }
		const_iterator begin() const { return (_tree->begin());}
	    iterator end() { return (_tree->end()); }
		const_iterator end() const { return (_tree->end()); }

		reverse_iterator rbegin() { return (_tree->rbegin()); }
		const_reverse_iterator rbegin() const { return (_tree->rbegin());}
	    reverse_iterator rend() { return (_tree->rend()); }
		const_reverse_iterator rend() const { return (_tree->rend()); }

		bool empty() const { return (_tree->size() == 0); }
		size_type size() const { return (_tree->size()); }
		size_type max_size() const { return (_alloc_node.max_size()); }
		mapped_type& operator[] (const key_type& k)
		{
			if (_tree->search(k) == _tree->_nullNode)
			{
				iterator it(_tree->insert(k, mapped_type()));
				return (it->second);
			}
			return (_tree->search(k)->_value.second);
		}
		ft::pair<iterator,bool> insert (const value_type& val)
		{
			ft::pair<iterator,bool>	res;
			if (_tree->_root == _tree->_nullNode || _tree->search(val.first) == _tree->_nullNode)
			{
				res.first = _tree->insert(val.first, val.second);
				res.second = true;
				return (res);
			}
			res.first = iterator(_tree->search(val.first));
			res.second = false;
			return (res);
		}
		iterator insert (iterator position, const value_type& val)
		{
			(void)position;
			return (insert(val).first);
		}
		template <class InputIterator>
		void insert (InputIterator first, InputIterator last)
		{
			for (; first != last; first++)
			{
				if (_tree->_root == _tree->_nullNode || _tree->search(first->first) == _tree->_nullNode)
					_tree->insert(first->first, first->second);
			}
		}
     	void erase (iterator position)
		{	_tree->destroy(position->first);	}
		size_type erase (const key_type& k)
		{	
			int res = 0;
			if (_tree->search(k) != _tree->_nullNode)
			{
				res = 1;
				_tree->destroy(k);	
			}			
			return (res);	
		}
     	void erase (iterator first, iterator last)
		{
			for (; first != last;)
			{
				key_type	k = first->first;
				++first;
				_tree->destroy(k);
			}
		}
		void swap (map& x)
		{
			tree_type*	inter;
			inter = this->_tree;
			_tree = x._tree;
			x._tree = inter;
		}
		void clear()
		{	_tree->clear();	}
		key_compare key_comp() const
		{	return (this->_comp);	}
		value_compare	value_comp (void) const
		{	return (value_compare(_comp));	}
	    iterator find (const key_type& k)
		{	return	(iterator(_tree->search(k)));	}
		const_iterator find (const key_type& k) const
		{	return	(const_iterator(_tree->search(k)));	}
		size_type count (const key_type& k) const
		{
			if (_tree->search(k) == _tree->_nullNode)
				return (0);
			return (1);
		}
		map_type&	operator=(const map_type&	cp)
		{	
			*_tree = *cp._tree;	
			_alloc = cp._alloc;
			_comp = cp._comp;
			return *(this);	
		}	
    	iterator lower_bound (const key_type& k)
		{
			iterator	it(_tree->begin()), ite(_tree->end());
			for (; it != ite; it++)
			{
				if (it->first >= k)
					break;
			}
			return (it);
		}
		const_iterator lower_bound (const key_type& k) const
		{
			const_iterator	it(_tree->begin()), ite(_tree->end());
			for (; it != ite; it++)
			{
				if (it->first >= k)
					break;
			}
			return (it);
		}
		iterator upper_bound (const key_type& k)
		{
			iterator	it(_tree->begin()), ite(_tree->end());
			for (; it != ite; it++)
			{
				if (it->first > k)
					break;
			}
			return	(it);
	
		}
		const_iterator upper_bound (const key_type& k) const
		{
			const_iterator	it(_tree->begin()), ite(_tree->end());
			for (; it != ite; it++)
			{
				if (it->first > k)
					break;
			}
			return	(it);
	
		}
		pair<iterator,iterator>             equal_range (const key_type& k)
		{
			ft::pair<iterator, iterator>	res;

			res.first = lower_bound(k);
			res.second = upper_bound(k);
			return (res);
		}
		pair<const_iterator,const_iterator> equal_range (const key_type& k) const
		{
			ft::pair<const_iterator, const_iterator>	res;

			res.first = lower_bound(k);
			res.second = upper_bound(k);
			return (res);
	
		}
		allocator_type get_allocator() const
		{	return (_alloc);	}

	friend bool	operator==(const map<Key, T, Compare, Alloc>& m1, const map<Key, T, Compare, Alloc>& m2)
	{	return (*m1._tree == *m2._tree);	}
	friend bool	operator!=(const map<Key, T, Compare, Alloc>& m1, const map<Key, T, Compare, Alloc>& m2)
	{	return (!(m1 == m2));	}
	friend bool	operator<(const map<Key, T, Compare, Alloc>& m1, const map<Key, T, Compare, Alloc>& m2)
	{	return (*m1._tree < *m2._tree);	}
	friend bool	operator>(const map<Key, T, Compare, Alloc>& m1, const map<Key, T, Compare, Alloc>& m2)
	{	return (m2 < m1);	}
	friend bool	operator>=(const map<Key, T, Compare, Alloc>& m1, const map<Key, T, Compare, Alloc>& m2)
	{	return !(m1 < m2);	}
	friend bool	operator<=(const map<Key, T, Compare, Alloc>& m1, const map<Key, T, Compare, Alloc>& m2)
	{	return !(m2 < m1);	}

	private:
		Tree<Key, T, Compare>*	_tree;
		typename allocator_type::template rebind<tree_type >::other	_alloc_tree;
		typename allocator_type::template rebind<Node<T> >::other	_alloc_node;
		Compare	_comp;
		Alloc	_alloc;
};
	
}