/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 01:21:48 by abittel           #+#    #+#             */
/*   Updated: 2022/06/10 21:41:58 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <memory>
#include "tree.hpp"
namespace ft
{

template < class Key, class T,  class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > > 
class map
{
	private:
		Tree<Key, T, Compare>	_tree;
		Compare	_comp;
		Alloc	_alloc;

	public:	
		typedef Key											key_type;
		typedef	T											mapped_type;
		typedef	ft::pair<const key_type, mapped_type>		value_type;
		typedef	Compare										key_compare;
		typedef Alloc										allocator_type;
		typedef	typename allocator_type::reference			reference;
		typedef	typename allocator_type::const_reference	const_reference;
		typedef	typename allocator_type::pointer			pointer;
		typedef	typename allocator_type::const_pointer		const_pointer;
		typedef	Tree<key_type, mapped_type, key_compare>		tree_type;
		typedef	typename tree_type::iterator				iterator;	
		typedef	typename tree_type::const_iterator			const_iterator;	
		typedef	typename tree_type::difference_type			difference_type;
		typedef	typename tree_type::size_type				size_type;
		typedef map<Key, T,  Compare>						map_type;
//reverse_iterator	reverse_iterator<iterator>	
//const_reverse_iterator	reverse_iterator<const_iterator>	
		map (const key_compare& comp = key_compare(),
	         const allocator_type& alloc = allocator_type()) : _tree(), _comp(comp), _alloc(alloc)
		{}
		template <class InputIterator>
	  	map (InputIterator first, InputIterator last,
	       const key_compare& comp = key_compare(),
	       const allocator_type& alloc = allocator_type()) : _tree(), _comp(comp), _alloc(alloc)
		{
			for (; first != last; first++)
				_tree->insert(first->first, first->second);
		}
		map (const map& x) { *this = x; }
		~map(){}
    	iterator begin() { return (_tree.begin()); }
		const_iterator begin() const { return (_tree.begin());}
	    iterator end() { return (_tree.end()); }
		const_iterator end() const { return (_tree.end()); }
		bool empty() const { return (_tree.size() == 0); }
		size_type size() const { return (_tree.size()); }
		size_type max_size() const { return (_alloc.max_size()); }
		mapped_type& operator[] (const key_type& k)
		{
			if (_tree.search(k) == _tree._nullNode)
			{
				iterator it(_tree.insert(k, mapped_type()));
				return (it->second);
			}
			return (_tree.search(k)->_value.second);
		}
		ft::pair<iterator,bool> insert (const value_type& val)
		{
			ft::pair<iterator,bool>	res;
			if (_tree._root == _tree._nullNode || _tree.search(val.first) == _tree._nullNode)
			{
				res.first = _tree.insert(val.first, val.second);
				res.second = true;
				return (res);
			}
			res.first = iterator(_tree.search(val.first), &_tree);
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
				if (_tree._root == _tree._nullNode || _tree.search(first->first) == _tree._nullNode)
					_tree.insert(first->first, first->second);
			}
		}
     	void erase (iterator position)
		{	_tree.destroy(position->first);	}
		size_type erase (const key_type& k)
		{	_tree.destroy(k);	}
     	void erase (iterator first, iterator last)
		{
			for (; first != last; first++)
				_tree.destroy(first->first);
		}

		void clear()
		{
			_tree.clear();
		}
		map_type&	operator=(const map_type&	cp)
		{	
			_tree = cp._tree;	
			_alloc = cp._alloc;
			_comp = cp._comp;
			return *(this);	
		}	
};

}