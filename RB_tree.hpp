/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RB_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 00:09:49 by abittel           #+#    #+#             */
/*   Updated: 2022/06/03 01:48:26 by abittel          ###   ########.fr       */
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
				this->_color = this->_color;
			}
		private:
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
			Node*	_root;
			Node	_nullNode;

			Node	get_NullNode()
			{
				Node	res;

				res._value = ft::make_pair(Key(), T());
				res._left = res._right = res._parent = NULL;
				res._color = BLACK;
			}
			Node*	minTree(Node* node)
			{
				while (node->left != this->_nullNode)
					node = node->left;
				return(node);
			}	
			Node*	maxTree(Node* node)
			{
				while (node->right != this->_nullNode)
					node = node->right;
				return(node);
			}	
			Node* _searchTree(Node* node, Key key) 
			{
				if (*node == this->_nullNode || key == node->_value.first)
				{
					return node;
				}
				if (less(key, node->value.first))
					return (searchTree(node->left, key));
				return (searchTree(node->right, key));
			}
			void leftRotate(Node* x) 
			{
				NodePtr y = x->right;
				x->right = y->left;
				if (y->left != _nullNode) {
					y->left->parent = x;
				}
				y->parent = x->parent;
				if (x->parent == NULL) {
					this->root = y;
				} else if (x == x->parent->left) {
					x->parent->left = y;
				} else {
					x->parent->right = y;
				}
				y->left = x;
				x->parent = y;
			}
			void rightRotate(Node* x) 
			{
				NodePtr y = x->left;
				x->left = y->right;
				if (y->right != TNULL) {
					y->right->parent = x;
				}
				y->parent = x->parent;
				if (x->parent == NULL) {
					this->root = y;
				} else if (x == x->parent->right) {
					x->parent->right = y;
				} else {
					x->parent->left = y;
				}
				y->right = x;
				x->parent = y;
			}
			void	insertFixUP(Node*	node)
			{

			}
			void	insert(Node*	node)
			{
				Node*	y = NULL;
				Node*	x = this->_root;	
				while (x != _nullNode)
				{
					y = x;
					if (less(node->_value.first, x->_value.first))
						x = x->left;
					else
						x = x->right;
				}
				node->_parent = y;
				if (y == NULL)
					this->_root = node;
				else if (less(node->_value.first, y->_value.first))
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
				
			}
		public:
			Tree() : _root(get_NullNode()), _nullNode(get_NullNode()) {}
			~Tree();
			Node*	search(Key key)
			{ return (_searchTree(this->_root, key)); }
			Key&	search(Key key)
			{ return (_searchTree(this->_root, key))->_value.first; }
			T&	search(Key key)
			{ return (_searchTree(this->_root, key))->_value.second; }

	};	
}