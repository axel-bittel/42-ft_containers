/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 14:06:30 by abittel           #+#    #+#             */
/*   Updated: 2022/07/17 21:59:18 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "utils.hpp"
namespace ft 
{
  	template<typename _Iterator, typename _Container>
    class normal_iterator
    {
    protected:
      _Iterator _val;

      typedef iterator_traits<_Iterator>		traits_type;

    public:
      typedef _Iterator					iterator_type;
      typedef typename traits_type::iterator_category iterator_category;
      typedef typename traits_type::value_type  	value_type;
      typedef typename traits_type::difference_type 	difference_type;
      typedef typename traits_type::reference 	reference;
      typedef typename traits_type::pointer   	pointer;

      normal_iterator() : _val(_Iterator()) { }

      explicit normal_iterator(const _Iterator& i) : _val(i) { }

      template<typename _Iter>
      normal_iterator(const normal_iterator<_Iter, _Container>& i) : _val(i.base()) { }
      reference operator*() const { return *_val; }
      pointer operator->() const { return _val; }
      normal_iterator& operator++() 
      {
		    ++_val;
		    return *this;
      }
      normal_iterator
      operator++(int) 
      { return normal_iterator(_val++); }
      normal_iterator& operator--() 
      {
		    --_val;
		    return *this;
      }
      normal_iterator operator--(int) 
      { return normal_iterator(_val--); }

      reference operator[](difference_type n) const 
      { return _val[n]; }

      normal_iterator& operator+=(difference_type n) 
      { _val += n; return *this; }

      normal_iterator operator+(difference_type n) const 
      { return normal_iterator(_val + n); }

      normal_iterator& operator-=(difference_type n) 
      { _val -= n; return *this; }

      normal_iterator operator-(difference_type n) const 
      { return normal_iterator(_val - n); }

      const _Iterator& base() const 
      { return _val; }
    };
    template<class InputIterator>
		typename ft::iterator_traits<InputIterator>::difference_type distance(InputIterator first, InputIterator last)
		{
			typename ft::iterator_traits<InputIterator>::difference_type n = 0;
			while (first != last)
			{
				++first;
				++n;
			}
			return (n);
		}
    template<typename _IteratorL, typename _IteratorR, typename _Container>
    bool operator==(const normal_iterator<_IteratorL, _Container>& lhs, const normal_iterator<_IteratorR, _Container>& rhs)
    { return lhs.base() == rhs.base(); }
    template<typename _Iterator, typename _Container> 
    bool operator==(const normal_iterator<_Iterator, _Container>& lhs, const normal_iterator<_Iterator, _Container>& rhs)
    { return lhs.base() == rhs.base(); }
    template<typename _Iterator, typename _Container>
     bool operator==(const normal_iterator<_Iterator, _Container>& lhs, const _Iterator& rhs)
    { return lhs.base() == rhs; }
    template<typename _IteratorL, typename _IteratorR, typename _Container> bool
    operator!=(const normal_iterator<_IteratorL, _Container>& lhs, const normal_iterator<_IteratorR, _Container>& rhs)
    { return lhs.base() != rhs.base(); }

  template<typename _Iterator, typename _Container> 
  bool operator!=(const normal_iterator<_Iterator, _Container>& lhs, const normal_iterator<_Iterator, _Container>& rhs)
  { return lhs.base() != rhs.base(); }

  // Random access iterator requirements
  template<typename _IteratorL, typename _IteratorR, typename _Container>
  bool operator<(const normal_iterator<_IteratorL, _Container>& lhs, const normal_iterator<_IteratorR, _Container>& rhs)
  { return lhs.base() < rhs.base(); }

   template<typename _Iterator, typename _Container>
   bool operator<(const normal_iterator<_Iterator, _Container>& lhs, const normal_iterator<_Iterator, _Container>& rhs)
   { return lhs.base() < rhs.base(); }

    template<typename _IteratorL, typename _IteratorR, typename _Container>
    bool operator>(const normal_iterator<_IteratorL, _Container>& lhs, const normal_iterator<_IteratorR, _Container>& rhs)
    { return lhs.base() > rhs.base(); }

    template<typename _Iterator, typename _Container>
    bool operator>(const normal_iterator<_Iterator, _Container>& lhs, const normal_iterator<_Iterator, _Container>& rhs)
    { return lhs.base() > rhs.base(); }

    template<typename _IteratorL, typename _IteratorR, typename _Container>
    bool operator<=(const normal_iterator<_IteratorL, _Container>& lhs, const normal_iterator<_IteratorR, _Container>& rhs)
    { return lhs.base() <= rhs.base(); }

    template<typename _Iterator, typename _Container>
    bool operator<=(const normal_iterator<_Iterator, _Container>& lhs, const normal_iterator<_Iterator, _Container>& rhs)
    { return lhs.base() <= rhs.base(); }
    
    template<typename _IteratorL, typename _IteratorR, typename _Container>
    bool operator>=(const normal_iterator<_IteratorL, _Container>& lhs, const normal_iterator<_IteratorR, _Container>& rhs)    
    { return lhs.base() >= rhs.base(); }

    template<typename _Iterator, typename _Container>
    bool operator>=(const normal_iterator<_Iterator, _Container>& lhs, const normal_iterator<_Iterator, _Container>& rhs)
    { return lhs.base() >= rhs.base(); }
    template<typename _Iterator, typename _Container>
    typename normal_iterator<_Iterator, _Container>::difference_type operator-(const normal_iterator<_Iterator, _Container>& __lhs, const normal_iterator<_Iterator, _Container>& __rhs)
    { return __lhs.base() - __rhs.base(); }

  template<typename _Iterator, typename _Container>
  normal_iterator<_Iterator, _Container> operator+(typename normal_iterator<_Iterator, _Container>::difference_type __n, const normal_iterator<_Iterator, _Container>& __i)
  { return normal_iterator<_Iterator, _Container>(__i.base() + __n); }
  template<typename _IteratorL, typename _IteratorR, typename _Container>
  typename normal_iterator<_IteratorL, _Container>::difference_type operator-(const normal_iterator<_IteratorL, _Container>& __lhs, const normal_iterator<_IteratorR, _Container>& __rhs)
  { return __lhs.base() - __rhs.base(); }


//REVERSE_TERATOR
template<typename _Iterator>
    class _reverse_iterator
    : public iterator<typename iterator_traits<_Iterator>::iterator_category,
		      typename iterator_traits<_Iterator>::value_type,
		      typename iterator_traits<_Iterator>::difference_type,
		      typename iterator_traits<_Iterator>::pointer,
          typename iterator_traits<_Iterator>::reference>
    {
    protected:
      _Iterator current;

      typedef iterator_traits<_Iterator>		traits_type;

    public:
      typedef _Iterator					iterator_type;
      typedef typename traits_type::difference_type	difference_type;
      typedef typename traits_type::pointer		pointer;
      typedef typename traits_type::reference		reference;

      _reverse_iterator() : current() { }
      _reverse_iterator(iterator_type x) : current(x) { }
      _reverse_iterator(const _reverse_iterator& x) : current(x.current) { }

      template<typename _Iter> 
	    _reverse_iterator(const _reverse_iterator<_Iter>& x): current(x.base()) { }
      template<typename _Iter, class Cont> 
	    _reverse_iterator(const normal_iterator<_Iter, Cont>& x): current(x.base()) { }
      iterator_type base() const{ return current; }
      reference operator*() const
      {
		    _Iterator inter = current;
		    return *--inter;
      }
      pointer operator->() const
      {
		    _Iterator inter = current;
		    --inter;
		    return to_pointer(inter);
      }
      _reverse_iterator& operator++()
      {
		    --current;
		    return *this;
      }
      _reverse_iterator operator++(int)
      {
		    _reverse_iterator inter = *this;
		    --current;
		    return inter;
      }
       _reverse_iterator& operator--()
      {
		    ++current;
		    return *this;
      }
      _reverse_iterator operator--(int)
      {
		    _reverse_iterator inter = *this;
		    ++current;
		    return inter;
      }
      _reverse_iterator operator+(difference_type n) const { return _reverse_iterator(current - n); }
      _reverse_iterator& operator+=(difference_type n)
      {
		    current -= n;
		    return *this;
      }
      _reverse_iterator operator-(difference_type n) const { return _reverse_iterator(current + n); }
      _reverse_iterator& operator-=(difference_type n)
      {
		    current += n;
		    return *this;
      }
      reference operator[](difference_type n) const { return *(*this + n); }
    private:
      	template<typename T>
	 	    static  T* to_pointer(T* p) { return p; }
      	template<typename T>
		    static  pointer to_pointer(T t) { return t.operator->(); }
    };
    template<typename _Iterator>
    bool operator==(const _reverse_iterator<_Iterator>& x, const _reverse_iterator<_Iterator>& y)
    { return x.base() == y.base(); }

    template<typename _Iterator>
    bool operator<(const _reverse_iterator<_Iterator>& x, const _reverse_iterator<_Iterator>& y)
    { return y.base() < x.base(); }

    template<typename _Iterator>
    bool operator!=(const _reverse_iterator<_Iterator>& x, const _reverse_iterator<_Iterator>& y)
    { return !(x == y); }

    template<typename _Iterator>
    bool operator>(const _reverse_iterator<_Iterator>& x, const _reverse_iterator<_Iterator>& y)
    { return y < x; }

    template<typename _Iterator>
    bool operator<=(const _reverse_iterator<_Iterator>& x, const _reverse_iterator<_Iterator>& y)
    { return !(y < x); }

    template<typename _Iterator>
    bool operator>=(const _reverse_iterator<_Iterator>& x, const _reverse_iterator<_Iterator>& y)
    { return !(x < y); }
    template<typename _IteratorL, typename _IteratorR>
    bool operator==(const _reverse_iterator<_IteratorL>& x, const _reverse_iterator<_IteratorR>& y)
    { return x.base() == y.base(); }

    template<typename _IteratorL, typename _IteratorR>
    bool operator<(const _reverse_iterator<_IteratorL>& x, const _reverse_iterator<_IteratorR>& y)
    { return y.base() < x.base(); }

    template<typename _IteratorL, typename _IteratorR>
    bool operator!=(const _reverse_iterator<_IteratorL>& x, const _reverse_iterator<_IteratorR>& y)
    { return !(x == y); }

    template<typename _IteratorL, typename _IteratorR>
    bool operator>(const _reverse_iterator<_IteratorL>& x, const _reverse_iterator<_IteratorR>& y)
    { return y < x; }

    template<typename _IteratorL, typename _IteratorR>
    bool operator<=(const _reverse_iterator<_IteratorL>& x, const _reverse_iterator<_IteratorR>& y)
    { return !(y < x); }

    template<typename _IteratorL, typename _IteratorR>
    bool operator>=(const _reverse_iterator<_IteratorL>& x, const _reverse_iterator<_IteratorR>& y)
    { return !(x < y); }
    template<typename _Iterator>
    typename _reverse_iterator<_Iterator>::difference_type operator-(const _reverse_iterator<_Iterator>& __x, const _reverse_iterator<_Iterator>& __y)
    { return __y.base() - __x.base(); }

    template<typename _IteratorL, typename _IteratorR>
    inline typename _reverse_iterator<_IteratorL>::difference_type operator-(const _reverse_iterator<_IteratorL>& __x, const _reverse_iterator<_IteratorR>& __y)
    { return __y.base() - __x.base(); }
    template<typename _Iterator>
    inline _reverse_iterator<_Iterator> operator+(typename _reverse_iterator<_Iterator>::difference_type __n, const _reverse_iterator<_Iterator>& __x)
    { return _reverse_iterator<_Iterator>(__x.base() - __n); }
};