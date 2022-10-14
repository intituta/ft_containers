/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 10:22:05 by kferterb          #+#    #+#             */
/*   Updated: 2022/10/14 10:22:06 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP
# include <iostream>
# include "../other_tools/pair.hpp"
# include "../other_tools/red_black_tree.hpp"
# include "../other_tools/enable_integral.hpp"
# include "../other_tools/lexicographical_compare.hpp"
# include "../other_tools/equal.hpp"
# include "../iterators/node_iterator.hpp"
# include "../iterators/reverse_iterator.hpp"

namespace ft
{
    template <class Key, class T, class Compare = std::less<Key>, class A = std::allocator<pair<const Key, T> > >
    class map
    {
    public:
        typedef Key                                                     key_type;
        typedef T                                                       mapped_type;
        typedef ft::pair<const Key, T>                                  value_type;
        typedef std::size_t                                             size_type;
        typedef std::ptrdiff_t                                          difference_type;
        typedef Compare                                                 key_compare;
        typedef A                                                       allocator_type;
        typedef typename A::reference                                   reference;
        typedef typename A::const_reference                             const_reference;
        typedef typename A::pointer                                     pointer;
        typedef typename A::const_pointer                               const_pointer;
        typedef ft::node_iterator<Node<value_type>*, value_type>        iterator;
        typedef ft::node_iterator<const Node<value_type>*, value_type>  const_iterator;
        typedef ft::reverse_iterator<iterator>                          reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>                    const_reverse_iterator;
        typedef typename A::template rebind<Node<value_type> >::other   allocator_rebind_node;
        typedef typename A::template rebind<Tree<value_type> >::other   allocator_rebind_tree;

        class value_compare : public std::binary_function<value_type, value_type, bool>
        {
        protected:
            key_compare compare;
        public:
            value_compare(key_compare pred) :compare(pred) {}
            bool operator()(const value_type &left, const value_type &right) const
            {
                return compare(left.first, right.first);
            }
        };

    private:
        allocator_type          allocator_pair;
        allocator_rebind_tree   allocator_tree;
        allocator_rebind_node   allocator_node;
        Compare                 compare;
        Tree<value_type>*       tree;

    public:

        /*============================================================================================*/
        /*===================================== MEMBER FUNCTIONS =====================================*/
        /*============================================================================================*/

        explicit map(const Compare &comp = key_compare(), const A &allocator = A())
         : allocator_pair(allocator), compare(comp)
        {
            tree = allocator_tree.allocate(sizeof(Tree<value_type>));
            allocator_tree.construct(tree);
        }

        template <class InputIter>
        map(InputIter first, InputIter last,
            const Compare &comp = Compare(), const A &alloc = A())
             : compare(comp), allocator_pair(alloc)
        {
            tree = allocator_tree.allocate(sizeof(Tree<value_type>));
            allocator_tree.construct(tree);
            for (; first != last; first++)
                insert(ft::make_pair(first->first, first->second));
        }
        map(const map &other) : allocator_pair(other.allocator_pair), compare(other.compare)
        {
            tree = allocator_tree.allocate(sizeof(Tree<value_type>));
            allocator_tree.construct(tree, *(other.tree));
            insert(other.begin(), other.end());
        }
        map &operator=(const map &other)
        {
            if (this != &other)
            {
                clear();
                allocator_tree.destroy(tree);
                allocator_tree.deallocate(tree, sizeof(Tree<value_type>));
                compare = other.compare;
                allocator_pair = other.allocator_pair;
                tree = allocator_tree.allocate(sizeof(Tree<value_type>));
                allocator_tree.construct(tree, *other.tree);
                insert(other.begin(), other.end());
            }
            return *this;
        }
        ~map()
        {
            clear();
            allocator_tree.destroy(tree);
            allocator_tree.deallocate(tree, sizeof(Tree<value_type>));
        }

        /*============================================================================================*/
        /*======================================== ITERATORS =========================================*/
        /*============================================================================================*/

        iterator                begin()         { return tree->first_node(); }
        const_iterator          begin() const   { return tree->first_node(); }
        iterator                end()           { return tree->end_tree(); }
        const_iterator          end() const     { return tree->end_tree(); }
        reverse_iterator        rbegin()        { return reverse_iterator(iterator(tree->last_node())); }
        const_reverse_iterator  rbegin() const  { return const_reverse_iterator(const_iterator(tree->last_node())); }
        reverse_iterator        rend()          { return reverse_iterator(iterator(tree->begin_tree())); }
        const_reverse_iterator  rend() const    { return const_reverse_iterator(const_iterator(tree->begin_tree())); }

        /*============================================================================================*/
        /*======================================== CAPACITY ==========================================*/
        /*============================================================================================*/

        bool empty() const
        {
            return (tree->amount_node == 0);
        }

        size_type size() const
        {
            return tree->amount_node;
        }
//        size_type max_size() const
//        {
//            return (std::numeric_limits<size_type>::max() / sizeof(Node<value_type>));
//        }
//        size_type max_size() const
//        {
//            return (allocator_tree.max_size());
//        }
        size_type max_size() const
        {
            return (get_allocator().max_size()/2);
        }
//        size_type max_size() const
//        {
//            return ((size_type) std::numeric_limits<difference_type>::max()/20);
//        }

        /*============================================================================================*/
        /*====================================== ELEMENT ACCESS ======================================*/
        /*============================================================================================*/

        mapped_type &operator[](const Key &key)
        {
            iterator buf = find(key);
            if (buf == end())
                return insert(ft::make_pair(key, T())).first->second;
            return buf->second;
        }

        mapped_type& at(const Key &key)
        {
            iterator tmp = find(key);
            return (tmp == end() ? throw std::out_of_range("Key don't found.") : tmp->second);
        }

        mapped_type& at(const Key &key)const
        {
            return static_cast<const mapped_type>(at(key));
        }

        /*============================================================================================*/
        /*======================================== MODIFIERS =========================================*/
        /*============================================================================================*/

        ft::pair<iterator, bool> insert(const value_type &value)
        {
            return insertNode(tree->root, value);
        }

        iterator insert(iterator node, const value_type &value)
        {
            if (node == end())
                return insertNode(tree->root, value).first;
            else
            {
                if (node->first > value.first)
                {
                    iterator prev = node;
                    --prev;
                    while (prev != end() && prev->first > value.first)
                    {
                        --prev;
                        --node;
                    }
                }
                else
                {
                    iterator next = node;
                    ++next;
                    while (next != end() && next->first < value.first)
                    {
                        ++node;
                        ++next;
                    }
                }
            }
            return insertNode(node.base(), value).first;
        }

        template <class InputIter>
        void insert(InputIter first, InputIter last)
        {
            for (; first != last; first++)
                insert(ft::make_pair(first->first, first->second));
        }

        void erase(iterator pos)
        {
            tree->deleteNode(pos.base());
        }

        void erase(iterator first, iterator last)
        {
            iterator tmp;
            key_type buf;

            while (first != last)
            {
                tmp = first++;
                buf = first->first;
                tree->deleteNode(tmp.base());
                if (first == last)
                    break;
                first = find(buf);
            }
        }

        size_type erase(const key_type &key)
        {
//            Node<value_type> *current = tree->root;
//            Node<value_type> *buf = NULL;
//
//            while (!current->NIL)
//            {
//                if (key == current->pair->first)
//                {
//                    buf = current;
//                    break;
//                }
//                else
//                    current = compare(key, current->pair->first) ? current->left : current->right;
//            }
//            return tree->deleteNode(buf);
            iterator buf = find(key);
            return tree->deleteNode(buf.base());
        }

        void swap (map &other)
        {
            map buf = *this;
            *this = other;
            other = buf;
        }

        void clear()
        {
            erase(this->begin(), this->end());
        }

        /*============================================================================================*/
        /*======================================== OBSERVERS =========================================*/
        /*============================================================================================*/

        key_compare key_comp() const
        {
            return compare;
        }

        ft::map<Key, T, Compare, A>::value_compare value_comp() const
        {
            return value_compare(key_comp());
        }

        /*============================================================================================*/
        /*======================================= OPERATIONS =========================================*/
        /*============================================================================================*/

        iterator find(const Key &key)
        {
            Node<value_type> *current = tree->root;

            while (!current->NIL)
            {
                if (key == current->pair->first)
                    return iterator(current);
                else
                    current = compare(key, current->pair->first) ? current->left : current->right;
            }
            return end();
        }

        const_iterator find(const Key &key) const
        {
            Node<value_type> *current = tree->root;

            while (!current->NIL)
            {
                if (key == current->pair->first)
                    return (current);
                else
                    current = compare(key, current->pair->first) ? current->left : current->right;
            }
            return end();
        }

        size_type count(const Key &key) const
        {
            return (find(key) == end() ? 0 : 1);
        }

        iterator lower_bound(const Key &key)
        {
            Node<value_type> *current = tree->root;

            while (!current->NIL) {
                if (key == current->pair->first)
                    return iterator(current);
                else {
                    if (compare(key, current->pair->first)) {
                        if (!current->left->NIL)
                            current = current->left;
                        else
                            return iterator(current);
                    }
                    else {
                        if (!current->right->NIL)
                            current = current->right;
                        else
                            return ++iterator(current);
                    }
                }
            }
            return end();
        }
        const_iterator lower_bound(const Key &key) const
        {
            Node<value_type> *current = tree->root;

            while (!current->NIL) {
                if (key == current->pair->first)
                    return const_iterator(current);
                else {
                    if (compare(key, current->pair->first)) {
                        if (!current->left->NIL)
                            current = current->left;
                        else
                            return const_iterator(current);
                    }
                    else {
                        if (!current->right->NIL)
                            current = current->right;
                        else
                            return ++const_iterator(current);
                    }
                }
            }
            return end();
        }
        iterator upper_bound(const Key &key)
        {
            iterator tmp = lower_bound(key);

            return (tmp == end()) ? tmp : (compare(key, tmp->first)) ? tmp : ++tmp;
        }

        const_iterator upper_bound(const Key &key) const
        {
            const_iterator tmp = lower_bound(key);

            return (tmp == end()) ? tmp : (compare(key, tmp->first)) ? tmp : ++tmp;
        }

        ft::pair<iterator, iterator> equal_range(const Key &key)
        {
            return (ft::pair<iterator, iterator>(lower_bound(key), upper_bound(key)));
        }

        ft::pair<const_iterator, const_iterator> equal_range(const Key &key) const
        {
            return (ft::pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key)));
        }

        /*============================================================================================*/
        /*======================================== ALLOCATOR =========================================*/
        /*============================================================================================*/

        allocator_type get_allocator() const
        {
            return allocator_pair;
        }

        /*============================================================================================*/

        friend bool operator== (const map &lhs, const map &rhs) {
            return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
        }

        friend bool operator!= (const map &lhs, const map &rhs) {
            return !(lhs == rhs);
        }

        friend bool operator< (const map &lhs, const map &rhs) {
            return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
        }

        friend bool operator> (const map &lhs, const map &rhs) {
            return (!(lhs < rhs) && !(lhs == rhs));
        }

        friend bool operator>= (const map &lhs, const map &rhs) {
            return !(lhs < rhs);
        }

        friend bool operator<= (const map &lhs, const map &rhs) {
            return (lhs == rhs || lhs < rhs);
        }

    private:
        ft::pair<iterator, bool> insertNode(Node<value_type> *node, const value_type &value)
        {
            Node<value_type> *current, *parent, *new_nod;

            current = node;
            parent = 0;
            while (!current->NIL)
            {
                if (value.first == current->pair->first)
                    return (ft::make_pair(current, false));
                parent = current;
                current = compare(value.first, current->pair->first) ? current->left : current->right;
            }
            new_nod = allocator_node.allocate(sizeof(Node<value_type>));
            allocator_node.construct(new_nod, value);
            new_nod->parent = parent;
            new_nod->begin = 0;
            new_nod->left = &tree->sentinel;
            new_nod->right = &tree->sentinel;
            new_nod->color = 1;
            new_nod->NIL = false;
            tree->amount_node++;
            if (parent)
            {
                if (compare(value.first, parent->pair->first))
                    parent->left = new_nod;
                else
                    parent->right =new_nod;
            }
            else
                tree->root = new_nod;
            tree->balance_insert(new_nod);
            if (new_nod == tree->last_node())
                new_nod->right->parent = new_nod;
            if (new_nod == tree->first_node())
            {
                new_nod->first = true;
                new_nod->left->begin = new_nod;
            }
            return ft::make_pair(new_nod, true);
        }

    };
}

#endif