/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 10:22:00 by kferterb          #+#    #+#             */
/*   Updated: 2022/10/14 10:22:01 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
#define PAIR_HPP
# include <iostream>

namespace ft
{
    template <class T1, class T2>
    struct pair
    {
        typedef T1 first_type;
        typedef T2 second_type;

        first_type  first;
        second_type second;

        pair(const first_type &x = first_type(), const second_type &y = second_type()) : first(x), second(y) {}

        template <class P1, class P2>
        pair(const pair<P1, P2> &other) : first(other.first), second(other.second) {}

        pair &operator=(const pair &other)
        {
            if (this != &other)
            {
                first = other.first;
                second = other.second;
            }
            return *this;
        }
    };

    template <class P1, class P2>
    pair<P1, P2> make_pair(P1 x, P2 y)
    {
        return pair<P1, P2>(x, y);
    }

    template <class P1, class P2>
    bool operator==(const pair<P1, P2> &x, const pair<P1, P2> &y)
    {
        return (x.first == y.first && x.second == y.second);
    }

    template <class P1, class P2>
    bool operator!=(const pair<P1, P2> &x, const pair<P1, P2> &y)
    {
        return (x.first != y.first || x.second != y.second);
    }

    template <class P1, class P2>
    bool operator<(const pair<P1, P2> &x, const pair<P1, P2> &y)
    {
        return (x.first < y.first || (!(x.first < y.first) && x.second < y.second));
    }

    template <class P1, class P2>
    bool operator<=(const pair<P1, P2> &x, const pair<P1, P2> &y)
    {
        return !(y < x);
    }

    template <class P1, class P2>
    bool operator>(const pair<P1, P2> &x, const pair<P1, P2> &y)
    {
        return (y < x);
    }

    template <class P1, class P2>
    bool operator>=(const pair<P1, P2> &x, const pair<P1, P2> &y)
    {
        return !(x < y);
    }
}

#endif