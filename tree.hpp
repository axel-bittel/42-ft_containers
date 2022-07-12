/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 00:09:49 by abittel           #+#    #+#             */
/*   Updated: 2022/07/12 19:51:41 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "iterator.hpp"
#include "pair.hpp"
#include <memory>

namespace ft
{
	#define	BLACK	0
	#define	RED		1
	
	template<class Key, class T,  class Compare = ft::less<Key> >
	class Tree;

	template<class T>
	class	Node;

	template<class T>
	class RBIterator
	{
		public:
		typedef T 	value_type;
		typedef	T&	reference;
		typedef T* 	pointer;
		typedef	bidirectional_iterator_tag iterator_category;
		typedef	ptrdiff_t	difference_type;
		typedef	size_t		size_type;
		typedef	RBIterator<T>	_Self;
		typedef	Node<T>*		_Base_ptr;

		RBIterator() : _node() {}
		explicit	RBIterator(_Base_ptr x) : _node(x) {}

		reference 	operator*()
		{	return (_node)->_value;	}
		pointer 	operator->() const
		{	return &(_node)->_value;	}
		_Self&	operator++()
		{
			_node =	NodeIncrement(_node);
			return *(this); 
		}
		_Self	operator++(int)
		{
			_Self inter = *this;
			_node = NodeIncrement(_node);
			return (inter);
		}
		_Self&	operator--()
		{
			_node =	NodeDecrement(_node);
			return *(this); 
		}
		_Self	operator--(int)
		{
			_Self inter = *this;
			_node = NodeDecrement(_node);
			return (inter);
		}
		friend	bool operator==(const _Self& x, const _Self y)
		{	return (*x._node == *y._node);	}
		friend	bool operator!=(const _Self& x, const _Self y)
		{	return (*x._node != *y._node);	}
		_Base_ptr	_node;
	};
	template<class T>
	class const_RBIterator
	{
		public:
		typedef T 	value_type;
		typedef	const T&	reference;
		typedef const T* 	pointer;
		typedef	bidirectional_iterator_tag iterator_category;
		typedef	ptrdiff_t	difference_type;
		typedef	size_t		size_type;
		typedef	const_RBIterator<T>	_Self;
		typedef	const Node<T>*		_Base_ptr;

		const_RBIterator() : _node() {}
		explicit	const_RBIterator(_Base_ptr x) : _node(x) {}
		const_RBIterator(const RBIterator<T>& x) : _node(x._node) {}
		RBIterator<T>	_const_cast() const 
      	{ return RBIterator<T>(const_cast<Node<T>*>(_node)); }

		reference 	operator*() const
		{	return (_node->_value);	}
		pointer 	operator->() const
		{	return &(_node->_value);	}
		_Self&	operator++()
		{
			_node =	NodeIncrement(_node);
			return *(this); 
		}
		_Self	operator++(int)
		{
			_Self inter = *this;
			_node = NodeIncrement(_node);
			return (inter);
		}
		_Self&	operator--()
		{
			_node =	NodeDecrement(_node);
			return *(this); 
		}
		_Self	operator--(int)
		{
			_Self inter = *this;
			_node = NodeDecrement(_node);
			return (inter);
		}
		friend	bool operator==(const _Self& x, const _Self y)
		{	return (*x._node == *y._node);	}
		friend	bool operator!=(const _Self& x, const _Self y)
		{	return (x._node != y._node);	}
		_Base_ptr	_node;
	};
	//NEXT AND PREVIOUS NODE
	template <class T>
	Node<T>*	_NodeIncrement(Node<T>* node)
	{
		Node<T>*	null = node->_nullNode;
		if (node == *node->_max)
			return (null);
		if (node == null)
			return *(node->_min);
		if (node->_right != null)
	    {
	        node = node->_right;
	        while (node->_left != null)
	          node = node->_left;
	    }
	    else
	    {
	        Node<T>* inter = node->_parent;
	        while (inter && node == inter->_right)
	        {
	            node = inter;
	           	inter = inter->_parent;
	        }
	        if (node->_right != inter)
	          node = inter;
	    }
		if (node)
	    	return (node);
		else
			return (null);
	}
	template <class T>
	Node<T>*	NodeIncrement(Node<T>* node)
	{	return (_NodeIncrement(node));	}
	template <class T>
	const Node<T>*	NodeIncrement(const Node<T>* node)
	{	return (_NodeIncrement(const_cast<Node<T>*>(node)));	}
	template <class T>
	Node<T>*	_NodeDecrement(Node<T>* node)
	{
		Node<T>*	null = node->_nullNode;
		if (node == *node->_min || node == null)
			return *(node->_max);
		if(node->_color == RED && node->_parent->_parent == node)
	      node = node->_right;
	    else if (node->_left != null)
	    {
	        Node<T>* inter = node->_left;
	        while (inter->_right != node->_nullNode)
	          inter = inter->_right;
	        node = inter;
	    }
	    else
	    {
	        Node<T>* inter = node->_parent;
	        while (inter && node == inter->_left)
	          {
	            node = inter;
	            inter = inter->_parent;
	          }
	        node = inter;
	    }
		if (node)
	    	return node;
		else 
			return (null);
	}
	template <class T>
	Node<T>*	NodeDecrement(Node<T>* node)
	{	return (_NodeDecrement(node));}
	template <class T>
	const Node<T>*	NodeDecrement(const Node<T>* node)
	{	return (_NodeDecrement(const_cast<Node<T>*>(node)));}
	template<class T>
	class	Node
	{
		public:

			typedef	T	value_type;
			Node(value_type val = value_type(), Node* nullNode = NULL, Node* parent = NULL, Node* left = NULL, Node* right = NULL, int color = BLACK) : _value(val), _nullNode(nullNode), _parent(parent), _left(left), _right(right), _color(color) 
			{}
			Node(const Node& cp) : _value(cp._value), _nullNode(cp._nullNode), _parent(cp._parent), _left(cp._left), _right(cp._right), _color(cp._color) 
			{}

			Node&	operator=(Node& cp)
			{
				this->_value = cp._value;
				this->_left = cp._left;
				this->_right = cp._right;
				this->_parent = cp._parent;
				this->_color = cp._color;
			}
			bool	operator==(Node& nd)
			{
				if (this->_value == nd._value) 
				/*&& 	this->_left == nd._left \
				&& 	this->_right == nd._righ \
				&& 	this->_parent == nd._parent \
				&& 	this->_color == nd._color)*/
					return (true);
				return (false);
			}
			bool	operator!=(Node& nd)
			{ return (!((*this) == nd)); }
			friend	bool	operator==(const Node& n1, const Node& n2)
			{	return (n1._value == n2._value);	}
			T		_value;
			Node	*_nullNode;
			Node	**_min;
			Node	**_max;
			Node	*_parent;
			Node	*_left;
			Node	*_right;	
			int		_color;
	};
	template<class Key, class T,  class Compare >
	class Tree
	{
		private:
			Compare						_comp;
			size_t						_size;
			Node<ft::pair<Key, T> >*		_max;
			Node<ft::pair<Key, T> >*		_min;

			std::allocator<Node<ft::pair<Key, T> > >	_alloc;

			Node<ft::pair<Key, T> >*	get_NullNode()
			{
				//Node<ft::pair<Key, T> >*	res = new Node<ft::pair<Key, T> >;
				Node<ft::pair<Key, T> >*	res = _alloc.allocate(1);
				_alloc.construct(res, Node<ft::pair<Key, T> >());

				res->_value = ft::make_pair(Key(), T());
				res->_left = res->_right = res->_parent = NULL;
				res->_color = BLACK;
				res->_parent = _root;
				res->_max = &_max;
				res->_min = &_min;
				res->_nullNode = res;
				return (res);
			}
				
			Node<ft::pair<Key, T> >* _searchTree(Node<ft::pair<Key, T> >* node, Key key) const
			{
				if (node == this->_nullNode || key == node->_value.first)
				{
					return node;
				}
				if (_comp(key, node->_value.first))
					return (_searchTree(node->_left, key));
				return (_searchTree(node->_right, key));
			}
			size_t	_count(Key&	key, Node<ft::pair<Key, T> >* node)
			{
				if (node == _nullNode)
					return (0);
				return ((node->_value.first == key) + _count(key, node->_left) + _count(key, node->_right));
			}
			void leftRotate(Node<ft::pair<Key, T> >* x) 
			{
				Node<ft::pair<Key, T> >* y = x->_right;
				x->_right = y->_left;
				if (y->_left != _nullNode)
					y->_left->_parent = x;
				y->_parent = x->_parent;
				if (x->_parent == NULL)
					this->_root = y;
				else if (x == x->_parent->_left)
					x->_parent->_left = y;
				else
					x->_parent->_right = y;
				y->_left = x;
				x->_parent = y;
			}
			void rightRotate(Node<ft::pair<Key, T> >* x) 
			{
				Node<ft::pair<Key, T> >* y = x->_left;
				x->_left = y->_right;
				if (y->_right != _nullNode) 
					y->_right->_parent = x;
				y->_parent = x->_parent;
				if (x->_parent == NULL) 
					this->_root = y;
				else if (x == x->_parent->_right)
					x->_parent->_right = y;
				else
					x->_parent->_left = y;
				y->_right = x;
				x->_parent = y;
			}
			void	insertFixUp(Node<ft::pair<Key, T> >*	node)
			{
				Node<ft::pair<Key, T> >*	u;
				while (node->_parent->_color == RED)			
				{
					if (node->_parent == node->_parent->_parent->_right)
					{
						u = node->_parent->_parent->_left;
						if (u->_color == RED)
						{
							u->_color = BLACK;
							node->_parent->_color = BLACK;
							node->_parent->_parent->_color = RED;
							node = node->_parent->_parent;
						}
						else 
						{
							if (node == node->_parent->_left)
							{
								node = node->_parent;
								rightRotate(node);
							}
							node->_parent->_color = BLACK;
							node->_parent->_parent->_color = RED;
							leftRotate(node->_parent->_parent);
						}
					}
					else
					{
						u = node->_parent->_parent->_right;
						if (u->_color == RED)
						{
							u->_color = BLACK;
							node->_parent->_color = BLACK;
							node->_parent->_parent->_color = RED;
							node = node->_parent->_parent;
						}
						else 
						{
							if (node == node->_parent->_right)
							{
								node = node->_parent;
								leftRotate(node);
							}
							node->_parent->_color = BLACK;
							node->_parent->_parent->_color = RED;
							rightRotate(node->_parent->_parent);
						}
					}
					if (node == _root)
						break ;
				}
				this->_root->_color = BLACK;
			}
			Node<ft::pair<Key, T> >*	_insert(Node<ft::pair<Key, T> >*	node)
			{
				Node<ft::pair<Key, T> >*	y = NULL;
				Node<ft::pair<Key, T> >*	x = this->_root;	
				while (x != _nullNode)
				{
					y = x;
					if (_comp(node->_value.first, x->_value.first))
						x = x->_left;
					else
						x = x->_right;
				}
				node->_parent = y;
				if (y == NULL)
					this->_root = node;
				else if (_comp(node->_value.first, y->_value.first))
					y->_left = node;
				else
					y->_right = node;
				if (node->_parent == NULL)
				{
					node->_color = BLACK;
					return (node);
				}
				if (node->_parent->_parent == NULL)
					return (node);
				insertFixUp(node);
				return (node);
			}
			void	fixDelete(Node<ft::pair<Key, T> >*	node)
			{
				Node<ft::pair<Key, T> >*	s;
				while (node != this->_root && node->_color == BLACK)
				{
					if (node == node->_parent->_left)
					{
						s = node->_parent->_right;
						if (s->_color == RED)
						{
							s->_color = BLACK;
							node->_parent->_color = RED;
							leftRotate(node->_parent);
							s = node->_parent->_right;
						}
						if (s->_left->_color == BLACK && s->_right->_color == BLACK)
						{
							s->_color = RED;
							node = node->_parent;
						}
						else
						{
							if (s->_right->_color == BLACK)
							{
								s->_left->_color = BLACK;
								s->_color = RED;
								rightRotate(s);
								s = node->_parent->_right;
							}
							s->_color = node->_parent->_color;
							node->_parent->_color = BLACK;
							s->_right->_color = BLACK;
							leftRotate(node->_parent);
							node = this->_root;
						}
					}
					else
					{
						s = node->_parent->_left;
						if (s->_color == RED)
						{
							s->_color = BLACK;
							node->_parent->_color = RED;
							rightRotate(node->_parent);
							s = node->_parent->_left;
						}
						if (s->_left->_color == BLACK && s->_right->_color == BLACK)
						{
							s->_color = RED;
							node = node->_parent;
						}
						else
						{
							if (s->_left->_color == BLACK)
							{
								s->_right->_color = BLACK;
								s->_color = RED;
								leftRotate(s);
								s = node->_parent->_left;
							}
							s->_color = node->_parent->_color;
							node->_parent->_color = BLACK;
							s->_left->_color = BLACK;
							rightRotate(node->_parent);
							node = this->_root;
						}
					}
				}
				node->_color = BLACK;
			}
			void	change_parents(Node<ft::pair<Key, T> >* change, Node<ft::pair<Key, T> >* cmp)
			{
				if (change->_parent == NULL)
					this->_root = cmp;
				else if (change == change->_parent->_left)
					change->_parent->_left = cmp;
				else
					change->_parent->_right = cmp;
				cmp->_parent = change->_parent;
			}
			void	_delete(Node<ft::pair<Key, T> >*	node, Key keyDelete)
			{
				Node<ft::pair<Key, T> >* find = _nullNode;
				Node<ft::pair<Key, T> >* x;
				Node<ft::pair<Key, T> >* y;
				while (node != _nullNode)
				{
					if (node->_value.first == keyDelete)
						find = node;
					if (_comp(node->_value.first, keyDelete) || 
						node->_value.first == keyDelete)
						node = node->_right;
					else
						node = node->_left;
				}
				if (find == _nullNode)
					return ;
				y = find;
				int	y_base_color = y->_color;
				if (find->_left == _nullNode)
				{
					x = find->_right;
					change_parents(find, find->_right);
				}
				else if (find->_right == _nullNode)
				{
					x = find->_left;
					change_parents(find, find->_left);
				}
				else
				{
					y = minTree(find->_right);
					y_base_color = y->_color;
					x = y->_right;
					if (y->_parent == find)
						x->_parent = y;
					else
					{
						change_parents(y, y->_right);
						y->_right = find->_right;
						y->_right->_parent = y;
					}
					change_parents(find,y);
					y->_left = find->_left;
					y->_left->_parent = y;
					y->_color = find->_color;
				}
				_alloc.destroy(find);
				_alloc.deallocate(find, 1);
				if (y_base_color == BLACK)
					fixDelete(x);
			}
			void	freeTree(Node<ft::pair<Key, T> >* node)
			{
				if (node->_left != _nullNode)
					freeTree(node->_left);
				if (node->_right != _nullNode)
					freeTree(node->_right);
				if (node != _nullNode)
				{
					_alloc.destroy(node);
					_alloc.deallocate(node, 1);
				}
			}
		public:
			Node<ft::pair<Key, T> >*	_root;
			Node<ft::pair<Key, T> >*	_nullNode;
			typedef	RBIterator<ft::pair<Key, T> >				iterator;
			typedef	const_RBIterator<ft::pair<Key, T> >		const_iterator;

			typedef	_reverse_iterator<iterator>										reverse_iterator;
			typedef	_reverse_iterator<const_iterator>									const_reverse_iterator;
			typedef	size_t															size_type;
			typedef	ptrdiff_t														difference_type;
			typedef	Compare															comp_type;

			Tree() : _size(0), _nullNode(get_NullNode())
			{ _root = _nullNode; }
			Tree(const Tree&	cp)
			{
				_nullNode = get_NullNode();
				_root = _nullNode;
				*this = cp;
			}
			~Tree()
			{
				if (_size)
					clear();
				_alloc.destroy(_nullNode);
				_alloc.deallocate(_nullNode, 1);
			}
			Tree*	operator->()
			{	return this;	}
			//BASE OPERATION
			size_t	max_size()
			{	return (_alloc.max_size());	}
			Node<ft::pair<Key, T> >*	search(Key key) const
			{ return (_searchTree(this->_root, key)); }
			iterator insert(Key key, T value)
			{
				Node<ft::pair<Key, T> >*	node = _alloc.allocate(1);
				_alloc.construct(node, Node<ft::pair<Key, T> >());
				if (_root == _nullNode || _comp(_max->_value.first, key))
					_max = node;
				if (_root == _nullNode || _comp(key, _min->_value.first))
					_min = node;
				node->_nullNode = _nullNode;
				node->_left = _nullNode;
				node->_right = _nullNode;
				node->_parent = NULL;
				node->_color = RED;
				node->_value = ft::make_pair(key, value);
				node->_max = &_max;
				node->_min = &_min;
				iterator	it(_insert(node));
				_size++;
				//_nullNode->_value.first = _size;
				return (it);
			}
			void	destroy(Key key)
			{
				if (_max->_value.first == key)
					_max = previous(_max); 
				if (_min->_value.first == key)
					_min = next(_min);
				_delete(this->_root, key);
				_size--;
				//_nullNode->_value.first = _size;
			}
			//NEW OPERATION
			size_t	size() const
			{	return (_size);	}
			size_t	count(const Key& key) const
			{	return (_count(key, this->_root));	}
			void	clear()
			{
				if (this->_root == _nullNode || this->_root == NULL)
					return ;
				freeTree(this->_root);
				this->_root = _nullNode;
				//_nullNode->_value.first = 0;
				this->_size = 0;
			}
			Node<ft::pair<Key, T> >*	minTree(Node<ft::pair<Key, T> >* node) const
			{
				if (!_size)
					return (_nullNode);
				while (node->_left != this->_nullNode)
					node = node->_left;
				return(node);
			}	
			Node<ft::pair<Key, T> >*	maxTree(Node<ft::pair<Key, T> >* node) const
			{
				if (!_size)
					return (_nullNode);
				while (node->_right != this->_nullNode)
					node = node->_right;
				return(node);
			}
			template<class _T>
			_T*		next(_T* act) const
			{
				if (_root == _nullNode)
					return	(_nullNode);
				if (act == _nullNode)
					return (maxTree(this->_root));
				if (act->_right != _nullNode)
					return (minTree(act->_right));
				_T*	y = act->_parent;
				while (y != NULL && act == y->_right) {
					act = y;
					y = y->_parent;
				}
				if (y == NULL)
					return (_nullNode);
				return y;
			}
			template<class _T>
			_T*		previous(_T* act) const 
			{
				if (_root == _nullNode)
					return	(_nullNode);
				if (act == _nullNode)
					return (maxTree(this->_root));
				if (act->_left != _nullNode)
					return (maxTree(act->_left));
				_T*	y = act->_parent;
				while (y != NULL && act == y->_left) {
					act	= y;
					y 	= y->_parent;
				}
				if (y == NULL)
					return (_nullNode);
				return y;
			}
			iterator	begin()
			{
				iterator it = iterator(minTree(this->_root));
				return (it);
			}
			const_iterator	begin() const
			{
				const_iterator	it = const_iterator(minTree(this->_root));
				return (it);
			}
			iterator	end()
			{
				iterator	it = iterator(_nullNode);
				return (it);
			}
			const_iterator	end() const
			{
				const_iterator	it = const_iterator(_nullNode);
				return (it);
			}
			
			reverse_iterator	rbegin()
			{
				reverse_iterator	it((end()));
				return (it);
			}
			const_iterator	rbegin() const
			{
				const_reverse_iterator	it((end()));
				return (it);
			}
			reverse_iterator	rend()
			{
				reverse_iterator	it((begin()));
				return (it);
			}
			const_reverse_iterator	rend() const
			{
				const_reverse_iterator it((begin()));
				return (it);
			}
			Node<ft::pair<Key, T> >*	_copyNode(Node<ft::pair<Key, T> >* node, Node<ft::pair<Key, T> >* null, Node<ft::pair<Key, T> >* _currentNode)
			{
				if (node == null)
					return node;
				Node<ft::pair<Key, T> >*	nNode = _alloc.allocate(1);

				//Insert new values
				if (_currentNode == _root)
				{
					_root = nNode;
					_currentNode = _root;
				}
				else
					_currentNode = nNode;
				if (node->_left != null)
				{
					_currentNode->_left = _copyNode(node->_left, null, _currentNode->_left);
					_currentNode->_left->_parent = _currentNode;
				}
				else
					_currentNode->_left = _nullNode;
				if (node->_right != null)
				{
					_currentNode->_right = _copyNode(node->_right, null, _currentNode->_right);
					_currentNode->_right->_parent = _currentNode;
				}
				else
					_currentNode->_right = _nullNode;
				_currentNode->_color = node->_color;
				_currentNode->_value = node->_value;
				_currentNode->_nullNode = _nullNode;
				_currentNode->_max = &_max;
				_currentNode->_min = &_min;
				return _currentNode;
			}
			Tree&	operator=(const Tree&	cp)
			{
				if (_size)
					clear();
				this->_size = cp._size;
				_copyNode(cp._root, cp._nullNode, this->_root);	
				_max = maxTree(_root);
				_min = minTree(_root);
				return (*this);
			}
			/*void	print_tree(Node<ft::pair<Key, T> >*	node = NULL, int num = 0) const
			{
				if (node == NULL)
					node = this->_root;
				if (node != _nullNode)
				{
					std::cout << "[" << num << ", <" << node->_value.first << ", " << node->_value.second << ">, " << node->_color << "] " << std::endl;
					print_tree(node->_left, num + 1);
					print_tree(node->_right, num + 1);
				}
			}*/
		friend bool	operator==(Tree& t1, Tree& t2)
 	   {	
			return 	t1.size() == t2.size()	&& 
				ft::equal(t1.begin(), t1.end(), t2.begin());
 	   }
	};	
	template<class Key, class T,  class Compare>
	bool	operator<(const Tree<Key, T, Compare>& t1, const Tree<Key, T, Compare>& t2)
	{	return (ft::_lexicographical_compare(t1.begin(), t1.end(), t2.begin(), t2.end()));	}
}