/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_integral.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 10:21:53 by kferterb          #+#    #+#             */
/*   Updated: 2022/10/14 10:21:54 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENABLE_IF_HPP
# define ENABLE_IF_HPP
# include <limits>

namespace ft
{
    /*============================ ENABLE_IF ============================*/
    template <bool Cond, typename T = void>
    struct enable_if {};

    template <typename T>
    struct enable_if<true, T>
    {typedef T type;};

    /*=========================== IS_INTEGRAL ============================*/
    template <class T, T v>
    struct integral_constant
    {
        typedef T value_type;
        typedef integral_constant<T, v> type;

        static const value_type value = v;

        operator value_type() const
        {
            return value;
        }
    };

    template<class T> struct is_integral : ft::integral_constant<bool, false> {};
    template<> struct is_integral<bool> : ft::integral_constant<bool, true> {};
    template<> struct is_integral<char> : ft::integral_constant<bool, true> {};
    template<> struct is_integral<char16_t> : ft::integral_constant<bool, true> {};
    template<> struct is_integral<char32_t> : ft::integral_constant<bool, true> {};
    template<> struct is_integral<wchar_t> : ft::integral_constant<bool, true> {};
    template<> struct is_integral<short> : ft::integral_constant<bool, true> {};
    template<> struct is_integral<int> : ft::integral_constant<bool, true> {};
    template<> struct is_integral<long> : ft::integral_constant<bool, true> {};
    template<> struct is_integral<long long> : ft::integral_constant<bool, true> {};
    template<> struct is_integral<unsigned long> : ft::integral_constant<bool, true> {};
    template<> struct is_integral<unsigned char> : ft::integral_constant<bool, true> {};
    template<> struct is_integral<unsigned short> : ft::integral_constant<bool, true> {};
    template<> struct is_integral<unsigned int> : ft::integral_constant<bool, true> {};
    template<> struct is_integral<unsigned long long> : ft::integral_constant<bool, true> {};
}

#endif
