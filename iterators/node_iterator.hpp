/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 10:22:11 by kferterb          #+#    #+#             */
/*   Updated: 2022/10/14 10:22:12 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_ITERATOR_HPP
#define NODE_ITERATOR_HPP
#include "iterators_traits.hpp"
#include "../other_tools/enable_integral.hpp"

namespace ft
{
    template <class T, class Pair>
    class node_iterator
    {
    public:
        T node;

    public:
        typedef T                                               iterator_type;
        typedef Pair                                            value_type;
        typedef typename iterator_traits<T>::difference_type    difference_type;
        typedef Pair&                                           reference;
        typedef const Pair&                                     const_ref;
        typedef Pair*                                           pointer;
        typedef const Pair*                                     const_pointer;
        typedef typename iterator_traits<T>::iterator_category  iterator_category;

        /*============================================================================================*/
        /*===================================== MEMBER FUNCTIONS =====================================*/
        /*============================================================================================*/

        node_iterator(T value = nullptr) : node(value) {};
        ~node_iterator() {};

        template <typename N1, typename N2>
//        node_iterator(const node_iterator<N1, N2> &other,
//                      typename ft::enable_if<std::is_convertible<N1, N2>::type>::type* = 0)
        node_iterator(const node_iterator<N1, N2> &other)
                       : node(other.node) {};

        iterator_type base() const
        {
            return node;
        }
        node_iterator &operator=(const node_iterator &other)
        {
            if (this != &other)
                node = other.node;
            return *this;
        }
        node_iterator operator++(int)
        {
            node_iterator tmp = *this;
            increment();
            return tmp;
        }
        node_iterator &operator++()
        {
            increment();
            return *this;
        }
        node_iterator operator--(int)
        {
            node_iterator tmp = *this;
            decrement();
            return tmp;
        }
        node_iterator &operator--()
        {
            decrement();
            return *this;
        }
        reference operator*()
        {
            return *(node->pair);
        }
        const_ref operator*() const
        {
            return *(node->pair);
        }
        pointer operator->()
        {
            return (node->pair);
        }
        const_pointer operator->() const
        {
            return (node->pair);
        }
        bool operator==(node_iterator const &other) const
        {
            return node == other.node;
        };
        bool operator!=(node_iterator const &other) const
        {
            return node != other.node;
        };
        bool operator>(node_iterator const &other) const
        {
            return node->pair > other.node->pair;
        };
        bool operator<(node_iterator const &other) const
        {
            return other.node->pair > node->pair;
        };
        bool operator<=(node_iterator const &other) const
        {
            return node->pair <= other.node->pair;
        };
        bool operator>=(node_iterator const &other) const
        {
            return node->pair >= other.node->pair;
        };

        void increment()
        {
            if (node->NIL)
            {
                if (node->begin != 0)
                    node = node->begin;
                return;
            }
            else if (!node->right->NIL)
            {
                node = node->right;
                while (!node->left->NIL)
                    node = node->left;
            }
            else
            {
                T current = node;
                T tmp = node;
                node = node->parent;
                if (!node)
                {
                    node = current->right;
                    return;
                }
                while (node->left != tmp)
                {
                    if (!node->parent)
                    {
                        node = current->right;
                        break;
                    }
                    tmp = node;
                    node = node->parent;
                }
            }
        }
        void decrement()
        {
            if (node->NIL)
            {
                node = node->parent;
                return;
            }
            else if (node->NIL)
                return;
            if (!node->left->NIL)
            {
                node = node->left;
                while (!node->right->NIL)
                    node = node->right;
            }
            else
            {
                T tmp = node;
                if (!node->parent && node->right->NIL && node->left->NIL)
                {
                    node = tmp->left;
                    return;
                }
                if (node->first)
                {
                    *node->left->begin = *node;
                    node = node->left;
                    return;
                }
                node = node->parent;
                while (node->right != tmp)
                {
                    tmp = node;
                    if (!node->parent)
                    {
                        node = tmp->left;
                        break;
                    }
                    node = node->parent;
                }
            }
        }
    };
}

#endif