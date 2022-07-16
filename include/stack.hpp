/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 22:56:54 by abittel           #+#    #+#             */
/*   Updated: 2022/06/02 01:08:48 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
namespace ft
{
template<class T, class Cont = vector<T> >
class stack 
{
	protected:
		Cont	_cont;
	public:
		typedef	typename Cont::size_type	size_type;
		typedef	typename Cont::value_type		value_type;
		typedef Cont	container_type;
		stack (const container_type& ctnr = container_type()) : _cont(ctnr){}
		bool empty() const
		{
			return (_cont.empty());
		}
		size_type size() const
		{
			return (_cont.size());
		}
	    value_type& top()
		{
			return (_cont.back());
		}
		const value_type& top() const	
		{
			return (_cont.back());
		}
		void push (const value_type& val)
		{
			_cont.push_back(val);
		}
		void pop ()
		{
			_cont.pop_back();
		}
		template<class _T, class _Container>
		friend bool operator== (const stack<_T, _Container>& lhs, const stack<_T,_Container>& rhs)
		{
			return (lhs._cont == rhs._cont);
		}
		template<class _T, class _Container>
		friend bool operator!= (const stack<_T,_Container>& lhs, const stack<_T,_Container>& rhs)
		{
			return (lhs._cont != rhs._cont);
		}
		template<class _T, class _Container>
		friend bool operator<  (const stack<_T,_Container>& lhs, const stack<_T,_Container>& rhs)
		{
			return (lhs._cont < rhs._cont);
		}
		template<class _T, class _Container>
		friend bool operator<= (const stack<_T,_Container>& lhs, const stack<_T,_Container>& rhs)
		{
			return (lhs._cont <= rhs._cont);
		}
		template<class _T, class _Container>
		friend bool operator> (const stack<_T,_Container>& lhs, const stack<_T,_Container>& rhs)
		{
			return (lhs._cont > rhs._cont);
		}
		template<class _T, class _Container>
		friend bool operator>= (const stack<_T,_Container>& lhs, const stack<_T,_Container>& rhs)
		{
			return (lhs._cont >= rhs._cont);
		}
};

}