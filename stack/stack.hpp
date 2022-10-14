/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 10:21:35 by kferterb          #+#    #+#             */
/*   Updated: 2022/10/14 10:21:36 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP
# include "../vector/vector.hpp"

namespace ft
{
    template <class T, class Container = ft::vector<T> >
    class stack
    {
    public:
        typedef Container                               container_type;
        typedef typename container_type::value_type     value_type;
        typedef typename container_type::size_type      size_type;

    protected:
        container_type ctnr;
    public:
        /*==================== MEMBER FUNCTIONS ====================*/
        /*============== CONSTRUCTORS AND DESTRUCTOR ===============*/
        explicit stack(const container_type &ctnr = container_type()) : ctnr(ctnr) {}

        stack(const stack &other) : ctnr(other.ctnr) {}
        ~stack() {}

        stack &operator=(const stack & other)
        {
            if (this != &other)
                ctnr = other.ctnr;
            return *this;
        }
        /*==================== MEMBER FUNCTIONS ====================*/

        bool            empty() const                   {return ctnr.empty();}
        size_type       size() const                    {return ctnr.size();}
        value_type&     top()                           {return ctnr.back();}
        const value_type&     top() const               {return ctnr.back();}
        void            push(const value_type &value)   {return ctnr.push_back(value);}
        void            pop()                           {return ctnr.pop_back();}

        template<class T1, class Container1>
        friend bool operator==(const ft::stack<T1, Container1>& first, const ft::stack<T1, Container1>& second);

        template<class T1, class Container1>
        friend bool operator!=(const ft::stack<T1, Container1>& first, const ft::stack<T1, Container1>& second);

        template<class T1, class Container1>
        friend bool operator<(const ft::stack<T1, Container1>& first, const ft::stack<T1, Container1>& second);

        template<class T1, class Container1>
        friend bool operator>(const ft::stack<T1, Container1>& first, const ft::stack<T1, Container1>& second);

        template<class T1, class Container1>
        friend bool operator<=(const ft::stack<T1, Container1>& first, const ft::stack<T1, Container1>& second);

        template<class T1, class Container1>
        friend bool operator>=(const ft::stack<T1, Container1>& first, const ft::stack<T1, Container1>& second);

    };
    /*==================== NON-MEMBER FUNCTIONS ====================*/

    template<class T, class Container>
    bool operator==(const ft::stack<T, Container>& first, const ft::stack<T, Container>& second)
    {
        return first.ctnr == second.ctnr;
    }

    template<class T, class Container>
    bool operator!=(const ft::stack<T, Container>& first, const ft::stack<T, Container>& second)
    {
        return first.ctnr != second.ctnr;
    }

    template<class T, class Container>
    bool operator<(const ft::stack<T, Container>& first, const ft::stack<T, Container>& second)
    {
        return first.ctnr < second.ctnr;
    }

    template<class T, class Container>
    bool operator>(const ft::stack<T, Container>& first, const ft::stack<T, Container>& second)
    {
        return first.ctnr > second.ctnr;
    }

    template<class T, class Container>
    bool operator<=(const ft::stack<T, Container>& first, const ft::stack<T, Container>& second)
    {
        return first.ctnr <= second.ctnr;
    }

    template<class T, class Container>
    bool operator>=(const ft::stack<T, Container>& first, const ft::stack<T, Container>& second)
    {
        return first.ctnr >= second.ctnr;
    }
}

#endif