/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 10:22:16 by kferterb          #+#    #+#             */
/*   Updated: 2022/10/14 10:22:17 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP
# include "../other_tools/enable_integral.hpp"
# include <memory>

namespace ft
{
    template<class T>
    class vector_iterator {
    public:
        typedef std::ptrdiff_t						difference_type;
        typedef T									value_type;
        typedef value_type*							pointer;
        typedef const value_type*					const_pointer;
        typedef value_type&							reference;
        typedef const value_type&					const_reference;
        typedef std::random_access_iterator_tag		iterator_category;

    private:
        pointer ptr;
    public:

        vector_iterator() : ptr(0) {}
        explicit vector_iterator(pointer ptr) : ptr(ptr) {}

        vector_iterator(const vector_iterator& other) : ptr(other.ptr) {}
        virtual ~vector_iterator() {}

        vector_iterator& operator=(const vector_iterator& other)
        {
            if (this == &other) {
                return *this;
            }
            this->ptr = other.ptr;
            return *this;
        }

        operator vector_iterator<const value_type>() const
        {
            return vector_iterator<const value_type>(ptr);
        }

        reference operator*()
        {
            return *ptr;
        }

        const_reference operator*() const
        {
            return *ptr;
        }

        pointer operator->()
        {
            return ptr;
        }

        const_pointer operator->() const
        {
            return ptr;
        }

        reference operator[](difference_type n)
        {
            return *(ptr + n);
        }

        const_reference operator[](difference_type n) const
        {
            return *(ptr + n);
        }

        pointer base(void) const
        {
            return ptr;
        }

        vector_iterator& operator++()
        {
            ++ptr;
            return *this;
        }

        vector_iterator& operator--()
        {
            --ptr;
            return *this;
        }

        vector_iterator operator++(int)
        {
            vector_iterator copy = *this;
            ++ptr;
            return copy;
        }

        vector_iterator operator--(int)
        {
            vector_iterator copy = *this;
            --ptr;
            return copy;
        }

        vector_iterator& operator+=(difference_type n)
        {
            ptr += n;
            return *this;
        }

        vector_iterator& operator-=(difference_type n)
        {
            ptr -= n;
            return *this;
        }

        vector_iterator operator+(difference_type n) const
        {
            return vector_iterator<T>(ptr + n);
        }

        vector_iterator operator-(difference_type n) const
        {
            return vector_iterator<T>(ptr - n);
        }

        difference_type operator+(const vector_iterator& other) const
        {
            return base() + other.base();
        }

        difference_type operator-(const vector_iterator& other) const
        {
            return base() - other.base();
        }

        bool operator==(const vector_iterator& other) const
        {
            return base() == other.base();
        }

        bool operator!=(const vector_iterator& other) const
        {
            return base() != other.base();
        }

        bool operator<(const vector_iterator& other) const
        {
            return base() < other.base();
        }

        bool operator<=(const vector_iterator& other) const
        {
            return base() <= other.base();
        }

        bool operator>(const vector_iterator& other) const
        {
            return base() > other.base();
        }

        bool operator>=(const vector_iterator& other) const
        {
            return base() >= other.base();
        }
    };

    template<class T, class V>
    bool operator==(vector_iterator<T>& first, vector_iterator<V>& second)
    {
        return first.base() == second.base();
    }

    template<class T, class V>
    bool operator!=(vector_iterator<T>& first, vector_iterator<V>& second)
    {
        return first.base() != second.base();
    }

    template<class T, class V>
    bool operator<(vector_iterator<T>& first, vector_iterator<V>& second)
    {
        return first.base() < second.base();
    }

    template<class T, class V>
    bool operator<=(vector_iterator<T>& first, vector_iterator<V>& second)
    {
        return first.base() <= second.base();
    }

    template<class T, class V>
    bool operator>(vector_iterator<T>& first, vector_iterator<V>& second)
    {
        return first.base() > second.base();
    }

    template<class T, class V>
    bool operator>=(vector_iterator<T>& first, vector_iterator<V>& second)
    {
        return first.base() >= second.base();
    }

    template<class T>
    vector_iterator<T> operator+(typename ft::vector_iterator<T>::difference_type n,
                                        const vector_iterator<T>& other)
    {
        return (other + n);
    }
}
#endif