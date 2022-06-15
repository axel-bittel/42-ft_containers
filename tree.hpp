/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 00:09:49 by abittel           #+#    #+#             */
/*   Updated: 2022/06/15 21:25:56 by abittel          ###   ########.fr       */
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
	
	template<class Tree, class T, class Key, class Value>
	class RBIterator;
	template<class Tree, class T, class Key, class Value>
	class Rev_RBIterator
	{
		protected:
			T	_current;
			const Tree*	_tree;
		public:
			typedef T 												iterator_type;
			typedef	typename iterator_traits<T>::reference			reference;
			typedef	typename iterator_traits<T>::pointer			pointer;
			typedef	typename iterator_traits<T>::value_type			value_type;
			typedef	bidirectional_iterator_tag						iterator_category;

			Rev_RBIterator() : _current(T()), _tree(NULL) {}
			explicit	Rev_RBIterator(const T val, const Tree* tree = NULL) : _current(val), _tree(tree){}
			Rev_RBIterator(const Rev_RBIterator<Tree, T, Key, Value>& cp) : _current(cp._current), _tree(cp._tree) {}
			template<class _T>
			Rev_RBIterator(const Rev_RBIterator<Tree, _T, Key, Value>& cp) : _current(cp.get_current()), _tree(cp.get_tree()) {}
			template<class it>
			Rev_RBIterator(const it& cp) : _current(cp.get_current()), _tree(cp.get_tree()) 
			{}
			const	ft::pair<Key, Value>&	operator*() const
			{	return (this->_current->_value);}
			ft::pair<Key, Value>*	operator->() const
			{
				RBIterator<Tree, T, Key, Value>	it(_current, _tree);
				//--it;
				return const_cast<ft::pair<Key, Value>* >(&(it.get_current()->_value));
			}
			const Rev_RBIterator<Tree, T, Key, Value>&	operator=(const Rev_RBIterator<Tree, T, Key, Value>& cp)
			{	this->_current = cp._current; this->_tree = cp._tree; return *(this); }
			bool	operator==(const Rev_RBIterator&	cp) const
			{ return (_current == cp._current);}
			bool	operator!=(const Rev_RBIterator&	cp) const
			{ return !(_current == cp._current);}
			Rev_RBIterator&	operator--()
			{
				if (this->_current == _tree->maxTree(_tree->_root)) 
					_current = _tree->minTree(_tree->_root);
				else
					_current = _tree->next(_current); 
				return *(this); 
			}
			Rev_RBIterator	operator--(int)
			{ 	
				Rev_RBIterator inter (*this);
				if (this->_current == _tree->maxTree(_tree->_root))
					_current = _tree->minTree(_tree->_root);
				else
					_current = _tree->next(_current); 
				return (inter); 
			}
			Rev_RBIterator&	operator++()
			{ 
				if (this->_current == _tree->minTree(_tree->_root))
					_current = _tree->_nullNode;
				else if (this->_current == _tree->_nullNode)
					_current = _tree->maxTree(_tree->_root);
				else
					_current = (_tree->previous(_current)); 
				return *(this); 
			}
			Rev_RBIterator	operator++(int)
			{ 
				Rev_RBIterator inter (*this);
				if (this->_current == _tree->minTree(_tree->_root))
					_current = _tree->_nullNode;
				else if (this->_current == _tree->_nullNode)
					_current = _tree->maxTree(_tree->_root);
				else
					_current = (_tree->previous(_current)); 
				return (inter); 
			}
			RBIterator<Tree, T, Key, Value> base() const
			{	
				RBIterator<Tree, T, Key, Value> it(this->get_current(), this->_tree);
				return (it);	
			}
			const T&	get_current() const {	return (_current); }
			const	Tree*	get_tree() const {	return (_tree);	}
	};
	template<class Tree, class T, class Key, class Value>
	class RBIterator
	{
		protected:
			T	_current;
			const Tree*	_tree;
		public:
			typedef T 												iterator_type;
			typedef	typename iterator_traits<T>::reference			reference;
			typedef	typename iterator_traits<T>::pointer			pointer;
			typedef	typename iterator_traits<T>::value_type			value_type;
			typedef	bidirectional_iterator_tag						iterator_category;

			RBIterator() : _current(T()), _tree(NULL) {}
			explicit	RBIterator(const T val, const Tree* tree = NULL) : _current(val), _tree(tree){}
			RBIterator(const RBIterator<Tree, T, Key, Value>& cp) : _current(cp._current), _tree(cp._tree) {}
			template<class _T>
			RBIterator(const RBIterator<Tree, _T, Key, Value>& cp) : _current(cp.get_current()), _tree(cp.get_tree()) {}
			const	ft::pair<Key, Value>&	operator*() const
			{	return (this->_current->_value);}
			ft::pair<Key, Value>*	operator->() const
			{	return const_cast<ft::pair<Key, Value>* >(&(_current->_value));}
			const RBIterator<Tree, T, Key, Value>&	operator=(const RBIterator<Tree, T, Key, Value>& cp)
			{	this->_current = cp._current; this->_tree = cp._tree; return *(this); }
			bool	operator==(const RBIterator&	cp) const
			{ return (_current == cp._current);}
			bool	operator!=(const RBIterator&	cp) const
			{ return !(_current == cp._current);}
			RBIterator&	operator++()
			{
				if (this->_current == _tree->_nullNode) 
					_current = _tree->maxTree(_tree->_root);
				else
					_current = _tree->next(_current); 
				return *(this); 
			}
			RBIterator	operator++(int)
			{ 	
				RBIterator inter (*this);
				if (this->_current == _tree->_nullNode)
					_current = _tree->maxTree(_tree->_root);
				else
					_current = _tree->next(_current); 
				return (inter); 
			}
			RBIterator&	operator--()
			{ 
				if (this->_current == _tree->minTree(_tree->_root))
					_current = _tree->_nullNode;
				else
					_current = (_tree->previous(_current)); 
				return *(this); 
			}
			RBIterator	operator--(int)
			{ 
				RBIterator inter (*this);
				if (this->_current == _tree->minTree(_tree->_root))
					_current = _tree->_nullNode;
				else
					_current = (_tree->previous(_current)); 
				return (inter); 
			}
			RBIterator&	base()
			{	
				RBIterator<Tree, T, Key, Value> it(this->get_current(), this->_tree);
				return *(this);	
			}
			const T&	get_current() const {	return (_current); }
			const	Tree*	get_tree() const {	return (_tree);	}

	};
	/*template<class Tree, class T, class Key, class Value>
	bool operator==(RBIterator<Tree, T, Key, Value>&	it, RBIterator<Tree, T, Key, Value>* v)
	{	return (it.get_current() == v->get_current());	}
	template<class Tree, class T, class Key, class Value>
	bool operator==(Rev_RBIterator<Tree, T, Key, Value>&	it, RBIterator<Tree, T, Key, Value>* v)
	{	return (it.get_current() == v->get_current());	}
	template<class Tree, class T, class Key, class Value>
	bool operator==(RBIterator<Tree, T, Key, Value>&	it, Rev_RBIterator<Tree, T, Key, Value>* v)
	{	return (it.get_current() == v->get_current());	}*/
	template<class IT1, class IT2>
	bool	operator==(IT1& it_one, IT2&	it_two)
	{	return (&it_one.get_current()->_value == &it_two.get_current()->_value);	}
	template<class T>
	class	Node
	{
		public:
			typedef	T	value_type;
			Node(value_type val = value_type(), Node* parent = NULL, Node* left = NULL, Node* right = NULL, int color = BLACK) : _value(val), _parent(parent), _left(left), _right(right), _color(color) 
			{}
			Node(const Node& cp) : _value(cp._value), _parent(cp._parent), _left(cp._left), _right(cp._right), _color(cp._color) 
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
				if (this->_value == nd._value \
				&& 	this->_left == nd._left \
				&& 	this->_right == nd._righ \
				&& 	this->_parent == nd._parent \
				&& 	this->_color == nd._color)
					return (true);
				return (false);
			}
			bool	operator!=(Node& nd)
			{ return (!((*this) == nd)); }
			T		_value;
			Node	*_parent;
			Node	*_left;
			Node	*_right;	
			int		_color;
	};
	template<class Key, class T,  class Compare = std::less<Key> >
	class Tree
	{
		private:
			Compare						_comp;
			size_t						_size;
			std::allocator<Node<ft::pair<Key, T> > >	_alloc;

			Node<ft::pair<Key, T> >*	get_NullNode()
			{
				//Node<ft::pair<Key, T> >*	res = new Node<ft::pair<Key, T> >;
				Node<ft::pair<Key, T> >*	res = _alloc.allocate(1);
				_alloc.construct(res, Node<ft::pair<Key, T> >());

				res->_value = ft::make_pair(Key(), T());
				res->_left = res->_right = res->_parent = NULL;
				res->_color = BLACK;
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
			typedef	RBIterator<Tree, Node<ft::pair<Key, T> >*, Key, T>				iterator;
			typedef	RBIterator<Tree, const Node<ft::pair<Key, T> >*, Key, T>		const_iterator;
			typedef	Rev_RBIterator<Tree, Node<ft::pair<Key, T> >*, Key, T>			reverse_iterator;
			typedef	Rev_RBIterator<Tree, const Node<ft::pair<Key, T> >*, Key, T>	const_reverse_iterator;
			typedef	size_t															size_type;
			typedef	ptrdiff_t														difference_type;
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
			Node<ft::pair<Key, T> >*	search(Key key) const
			{ return (_searchTree(this->_root, key)); }
			iterator insert(Key key, T value)
			{
				//Node<ft::pair<Key, T> >*	node = new Node<ft::pair<Key, T> >;
				Node<ft::pair<Key, T> >*	node = _alloc.allocate(1);
				_alloc.construct(node, Node<ft::pair<Key, T> >());
				node->_left = _nullNode;
				node->_right = _nullNode;
				node->_parent = NULL;
				node->_color = RED;
				node->_value = ft::make_pair(key, value);
				iterator	it(_insert(node), this);
				_nullNode->_value.first = ++_size;
				return (it);
			}
			void	destroy(Key key)
			{
				_delete(this->_root, key);
				_size--;
				_nullNode->_value.first = _size;
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
				_nullNode->_value.first = 0;
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
				iterator it = iterator(minTree(this->_root), this);
				return (it);
			}
			const_iterator	begin() const
			{
				const_iterator	it = const_iterator(minTree(this->_root), this);
				return (it);
			}
			iterator	end()
			{
				iterator	it = iterator(_nullNode, this);
				return (it);
			}
			const_iterator	end() const
			{
				const_iterator	it = const_iterator(_nullNode, this);
				return (it);
			}
			
			reverse_iterator	rbegin()
			{
				reverse_iterator	it(maxTree(_root), this);
				return (it);
			}
			const_iterator	rbegin() const
			{
				const reverse_iterator	it(maxTree(_root), this);
				return (it);
			}
			reverse_iterator	rend()
			{
				const reverse_iterator	it(_nullNode, this);
				return (it);
			}
			const_reverse_iterator	rend() const
			{
				const_reverse_iterator it(_nullNode, this);
				return (it);
			}
			Node<ft::pair<Key, T> >*	_copyNode(Node<ft::pair<Key, T> >* node, Node<ft::pair<Key, T> >* null, Node<ft::pair<Key, T> >* _currentNode)
			{
				if (node == null)
					return node;
				//Node<ft::pair<Key, T> >*	nNode = new Node<ft::pair<Key, T> >;	
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
				return _currentNode;
			}
			Tree&	operator=(const Tree&	cp)
			{
				if (_size)
					clear();
				this->_size = cp._size;
				_copyNode(cp._root, cp._nullNode, this->_root);	
				return (*this);
			}
			void	print_tree(Node<ft::pair<Key, T> >*	node = NULL, int num = 0) const
			{
				if (node == NULL)
					node = this->_root;
				if (node != _nullNode)
				{
					std::cout << "[" << num << ", <" << node->_value.first << ", " << node->_value.second << ">, " << node->_color << "] " << std::endl;
					print_tree(node->_left, num + 1);
					print_tree(node->_right, num + 1);
				}
			}
	};	
}