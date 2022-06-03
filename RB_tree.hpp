/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RB_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 00:09:49 by abittel           #+#    #+#             */
/*   Updated: 2022/06/04 01:33:16 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace ft
{
	#define	BLACK	0
	#define	RED		1
	#include "pair.hpp"
	#include <memory>

	template<class T>
	class	Node
	{
		public:
			typedef	T	value_type;
			Node(value_type val = value_type(), Node* parent = NULL, Node* left = NULL, Node* right = NULL, int color = BLACK) : _value(val), _parent(parent), _left(left), _right(right), _color(color) 
			{}
			Node(Node& cp) : _value(cp._val), _parent(cp._parent), _left(cp._left), _right(cp._right), _color(cp._color) 
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
			Node<ft::pair<Key, T> >*	_root;
			Node<ft::pair<Key, T> >*	_nullNode;
			size_t						_size;

			Node<ft::pair<Key, T> >*	get_NullNode()
			{
				Node<ft::pair<Key, T> >*	res = new Node<ft::pair<Key, T> >;

				res->_value = ft::make_pair(Key(), T());
				res->_left = res->_right = res->_parent = NULL;
				res->_color = BLACK;
				return (res);
			}
			Node<ft::pair<Key, T> >*	minTree(Node<ft::pair<Key, T> >* node)
			{
				while (node->_left != this->_nullNode)
					node = node->_left;
				return(node);
			}	
			Node<ft::pair<Key, T> >*	maxTree(Node<ft::pair<Key, T> >* node)
			{
				while (node->right != this->_nullNode)
					node = node->right;
				return(node);
			}	
			Node<ft::pair<Key, T> >* _searchTree(Node<ft::pair<Key, T> >* node, Key key) 
			{
				if (node == this->_nullNode || key == node->_value.first)
				{
					return node;
				}
				if (_comp(key, node->value.first))
					return (searchTree(node->left, key));
				return (searchTree(node->right, key));
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
				if (y->_right != _nullNode) {
					y->_right->_parent = x;
				}
				y->_parent = x->_parent;
				if (x->_parent == NULL) {
					this->_root = y;
				} else if (x == x->_parent->_right) {
					x->_parent->_right = y;
				} else {
					x->_parent->_left = y;
				}
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
			void	_insert(Node<ft::pair<Key, T> >*	node)
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
					return ;
				}
				if (node->_parent->_parent == NULL)
					return ;
				insertFixUp(node);
			}
			void	fixDelete(Node<ft::pair<Key, T>>*	node)
			{
				Node<ft::pair<Key, T>>*	s;
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
							s->_parent = node->_parent->_right;
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
							s->_color = node->_parent->_right->_color;
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
							s->_parent = node->_parent->_left;
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
							s->_color = node->_parent->_left->_color;
							node->_parent->_color = BLACK;
							s->_left->_color = BLACK;
							rightRotate(node->_parent);
							node = this->_root;
						}
					}
				}
				node->_color = BLACK;
			}
			void	change_parents(Node<ft::pair<Key, T>>* change, Node<ft::pair<Key, T>>* cmp)
			{
				if (change->_parent == NULL)
					this->_root = cmp;
				else if (change == change->_parent->_left)
					change->_parent->_left = cmp;
				else
					change->_parent->_right = cmp;
				cmp->_parent = change->_parent;
			}
			void	_delete(Node<ft::pair<Key, T>>*	node, Key keyDelete)
			{
				Node<ft::pair<Key, T>>* find = _nullNode;
				Node<ft::pair<Key, T>>* x;
				Node<ft::pair<Key, T>>* y;
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
				delete find;
				if (y_base_color == BLACK)
					fixDelete(x);
			}
			void	freeTree(Node<ft::pair<Key, T> >* node)
			{
				if (node->_left != nullptr)
					freeTree(node->_left);
				if (node->_right != nullptr)
					freeTree(node->_right);
				if (node != _nullNode)
					delete node;
			}
		public:
			Tree() : _nullNode(get_NullNode()), _size(0) 
			{ _root = _nullNode; }
			~Tree()
			{
				freeTree(this->_root); 
				delete _nullNode;
			}
			//BASE OPERATION
			Node<ft::pair<Key, T> >*	search(Key key)
			{ return (_searchTree(this->_root, key)); }
			Key&	search_key(Key key)
			{ return (_searchTree(this->_root, key))->_value.first; }
			T&	search_value(Key key)
			{ return (_searchTree(this->_root, key))->_value.second; }
			void	insert(Key key, T value)
			{
				Node<ft::pair<Key, T> >*	node = new Node<ft::pair<Key, T> >;
				node->_left = _nullNode;
				node->_right = _nullNode;
				node->_parent = NULL;
				node->_color = RED;
				node->_value = ft::make_pair(key, value);
				_insert(node);
				_size++;
			}
			void	destroy(Key key)
			{
				_delete(this->_root, key);
				_size--;
			}
			//NEW OPERATION
			size_t	size()
			{	return (_size);	}
			size_t	count(const Key& key)
			{	return (_count(key, this->_root));	}
			void	clear()
			{
				freeTree();
				this->_root = _nullNode;
				this->_size = 0;
			}
			void	print_tree(Node<ft::pair<Key, T> >*	node = NULL, int num = 0)
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