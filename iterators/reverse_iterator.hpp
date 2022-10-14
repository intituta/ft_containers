/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 10:22:13 by kferterb          #+#    #+#             */
/*   Updated: 2022/10/14 10:22:14 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP
# include "iterators_traits.hpp"
# include "../other_tools/enable_integral.hpp"
# include <memory>

namespace ft
{
    template<class Iterator>
    class reverse_iterator {
    public:
        typedef Iterator												iterator_type;
        typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
        typedef typename iterator_traits<Iterator>::value_type			value_type;
        typedef typename iterator_traits<Iterator>::difference_type		difference_type;
        typedef typename iterator_traits<Iterator>::pointer				pointer;
        typedef typename iterator_traits<Iterator>::reference			reference;

    private:
        iterator_type iter;
    public:

        reverse_iterator() : iter(0) {}
        explicit reverse_iterator(iterator_type iter) : iter(iter) {}

        template<class U>
        reverse_iterator(const reverse_iterator<U>& other) : iter(other.base()) {}
        virtual ~reverse_iterator() {}

        reverse_iterator& operator=(const reverse_iterator& other)
        {
            if (this == &other) {
                return *this;
            }
            this->iter = other.iter;
            return *this;
        }

        iterator_type base() const
        {
            return iter;
        }

        reference operator*() const
        {
            iterator_type tmp = iter;
//            return *--tmp;
             return *tmp;
        }

        pointer operator->() const
        {
            return &operator*();
        }

        reference operator[](difference_type nb) const
        {
            return base()[-nb - 1];
        }

        reverse_iterator& operator++()
        {
            --iter;
            return *this;
        }

        reverse_iterator& operator--()
        {
            ++iter;
            return *this;
        }

        reverse_iterator operator++(int)
        {
            reverse_iterator copy = *this;
            --iter;
            return copy;
        }

        reverse_iterator operator--(int)
        {
            reverse_iterator copy = *this;
            ++iter;
            return copy;
        }

        reverse_iterator& operator+=(difference_type nb)
        {
            iter -= nb;
            return *this;
        }

        reverse_iterator& operator-=(difference_type nb)
        {
            iter += nb;
            return *this;
        }

        reverse_iterator operator+(difference_type nb) const
        {
            return reverse_iterator<Iterator>(iter - nb);
        }

        reverse_iterator operator-(difference_type nb) const
        {
            return reverse_iterator<Iterator>(iter + nb);
        }

        bool operator==(const reverse_iterator& other) const
        {
            return this->base() == other.base();
        }

        bool operator!=(const reverse_iterator& other) const
        {
            return this->base() != other.base();
        }

        bool operator<(const reverse_iterator& other) const
        {
            return this->base() > other.base();
        }

        bool operator<=(const reverse_iterator& other) const
        {
            return this->base() >= other.base();
        }

        bool operator>(const reverse_iterator& other) const
        {
            return this->base() < other.base();
        }

        bool operator>=(const reverse_iterator& other) const
        {
            return this->base() <= other.base();
        }
    };
    template<class Z, class Q>
    bool operator==(reverse_iterator<Z>& _first, reverse_iterator<Q>& _second)
    {
        return _first.base() == _second.base();
    }
    template<class Z, class Q>
    bool operator!=(reverse_iterator<Z>& _first, reverse_iterator<Q>& _second)
    {
        return _first.base() != _second.base();
    }
    template<class Z, class Q>
    bool operator<(reverse_iterator<Z>& _first, reverse_iterator<Q>& _second)
    {
        return _first.base() > _second.base();
    }
    template<class Z, class Q>
    bool operator<=(reverse_iterator<Z>& _first, reverse_iterator<Q>& _second)
    {
        return _first.base() >= _second.base();
    }
    template<class Z, class Q>
    bool operator>(reverse_iterator<Z>& _first, reverse_iterator<Q>& _second)
    {
        return _first.base() < _second.base();
    }
    template<class Z, class Q>
    bool operator>=(reverse_iterator<Z>& _first, reverse_iterator<Q>& _second)
    {
        return _first.base() <= _second.base();
    }
    template<class Iterator>
    reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type nb,
                                         const reverse_iterator<Iterator>& other)
    {
        return other + nb;
    }
    template<class Iterator>
    reverse_iterator<Iterator> operator-(typename reverse_iterator<Iterator>::difference_type nb,
                                         const reverse_iterator<Iterator>& other) {
        return nb - other;
    }
    template<class Z, class Q>
    typename reverse_iterator<Z>::difference_type operator-(reverse_iterator<Z>& _first, reverse_iterator<Q>& _second)
    {
        return _second.base() - _first.base();
    }
}
#endif