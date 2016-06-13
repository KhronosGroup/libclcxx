//
// Copyright (c) 2015-2016 The Khronos Group Inc.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and/or associated documentation files (the
// "Materials"), to deal in the Materials without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Materials, and to
// permit persons to whom the Materials are furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Materials.
//
// THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// MATERIALS OR THE USE OR OTHER DEALINGS IN THE MATERIALS.
//

#pragma once
#define Region 1
#include <opencl_type_traits>
#include <opencl_functional>

namespace cl
{

#if Region | general_iterators

/// \brief type used to define iterator category for input iterators
///
struct input_iterator_tag { };

/// \brief type used to define iterator category for output iterators
///
struct output_iterator_tag { };

/// \brief type used to define iterator category for forward iterators
///
struct forward_iterator_tag : input_iterator_tag { };

/// \brief type used to define iterator category for bidirectional iterators
///
struct bidirectional_iterator_tag : forward_iterator_tag { };

/// \brief type used to define iterator category for random access iterators
///
struct random_access_iterator_tag : bidirectional_iterator_tag { };

namespace __details
{

#define _CHECK_IF_HAS_TYPEDEF(typedef_name) \
template <class T> struct __has_##typedef_name{ \
template <typename U> static true_type helper(remove_reference_t<typename U::typedef_name>*); \
template <typename> static false_type helper(...); \
static constexpr bool value = decltype(helper<T>(nullptr))::value; };

_CHECK_IF_HAS_TYPEDEF(difference_type)
_CHECK_IF_HAS_TYPEDEF(value_type)
_CHECK_IF_HAS_TYPEDEF(pointer)
_CHECK_IF_HAS_TYPEDEF(reference)
_CHECK_IF_HAS_TYPEDEF(iterator_category)

/// \brief Helper class determining if Iterator has proper typedefs
///
template <class It>
struct __iterator_validate : integral_constant<bool, __all<__has_difference_type<It>::value, __has_value_type<It>::value,
                                __has_pointer<It>::value, __has_reference<It>::value, __has_iterator_category<It>::value>::value> { };

#undef _CHECK_IF_HAS_TYPEDEF

template <class It, bool = __iterator_validate<It>::value>
struct __iterator_traits_helper { };

/// \brief iterator_traits helper specialization for valid iterator types
///
template <class Iterator>
struct __iterator_traits_helper<Iterator, true>
{
    using difference_type = typename Iterator::difference_type;
    using value_type = typename Iterator::value_type;
    using pointer = typename Iterator::pointer;
    using reference = typename Iterator::reference;
    using iterator_category = typename Iterator::iterator_category;
};

/// \brief iterator_traits helper specialization for pointers
///
template <class T>
struct __iterator_traits_helper<T*, false>
{
    using difference_type = ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using iterator_category = random_access_iterator_tag;
};

/// \brief iterator_traits helper specialization for const pointers
///
template<class T>
struct __iterator_traits_helper<const T*, false>
{
    using difference_type = ptrdiff_t;
    using value_type = T;
    using pointer = const T*;
    using reference = const T&;
    using iterator_category = random_access_iterator_tag;
};

}

/// \brief iterator_traits
///
template <class Iterator>
struct iterator_traits : __details::__iterator_traits_helper<Iterator> { };

/// \brief base class for iterators used to simplify iterator definition
///
template<class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
struct iterator
{
    static_assert(__details::__is_one_of<remove_cv_t<Category>, input_iterator_tag,
                                        output_iterator_tag,
                                        forward_iterator_tag,
                                        bidirectional_iterator_tag,
                                        random_access_iterator_tag>::value, "Category must be a valid iterator tag");
    using value_type = T;
    using difference_type = Distance;
    using pointer = Pointer;
    using reference = Reference;
    using iterator_category = Category;
};

#endif

#if Region | reverse_iterator

/// \brief reverse iterator adapter
///
/// this iterator operates on inverted sequence that is also shifted by one so that
/// reverse_iterator(c.begin()) is invalid, as c.end() would and also
/// reverse_iterator(c.end()) is valid, in the same way as c.begin()
template< class Iterator >
class reverse_iterator : public iterator<typename iterator_traits<Iterator>::iterator_category,
                                         typename iterator_traits<Iterator>::value_type,
                                         typename iterator_traits<Iterator>::difference_type,
                                         typename iterator_traits<Iterator>::pointer,
                                         typename iterator_traits<Iterator>::reference>
{
protected:
    /// \brief member holding adapted iterator
    ///
    Iterator current;

public:
    template <class U>
    friend class reverse_iterator;

    using iterator_category = typename iterator_traits<Iterator>::iterator_category;
    using value_type        = typename iterator_traits<Iterator>::value_type;
    using difference_type   = typename iterator_traits<Iterator>::difference_type;
    using pointer           = typename iterator_traits<Iterator>::pointer;
    using reference         = typename iterator_traits<Iterator>::reference;

    static_assert(__details::__is_one_of<iterator_category, bidirectional_iterator_tag, random_access_iterator_tag>::value,
                                                                    "Reverse iterator tag should be at least bidirectional");

    /// \brief default reverse iterator constructor
    ///
    reverse_iterator( ) __NOEXCEPT = default;

    /// \brief constructs reverse iterator from iterator v
    ///
    explicit reverse_iterator(Iterator value) __NOEXCEPT : current{ value } { }

    /// \brief template copy constructor that just copies current iterator
    ///
    template <class U>
    reverse_iterator(const reverse_iterator<U>& other) __NOEXCEPT : current{ other.current } { }

    /// \brief template copy assignment operator that just copies current iterator
    ///
    template <class U>
    __ALWAYS_INLINE reverse_iterator& operator=(const reverse_iterator<U>& other) __NOEXCEPT { current(other.current); return *this; }

    /// \brief returns current
    ///
    __ALWAYS_INLINE Iterator base( ) const __NOEXCEPT{ return current; }

    /// \brief returns value prior to current iterator
    ///
    __ALWAYS_INLINE reference operator*( ) const __NOEXCEPT
    {
        Iterator tmp = current;
        return *--tmp;
    }

    /// \brief returns iterator prior to current iterator
    ///
    __ALWAYS_INLINE pointer operator->( ) const __NOEXCEPT
    {
        return addressof(operator*());
    }

    /// \brief returns value one prior to n in reversed sequence
    ///
    __ALWAYS_INLINE reference operator[ ](difference_type n) __NOEXCEPT { return current[-n - 1]; }

    /// \brief decrements current, which advances the reverse iterator
    ///
    __ALWAYS_INLINE reverse_iterator& operator++( ) __NOEXCEPT
    {
        --current;
        return *this;
    }

    /// \brief increments current, which decreases the reverse iterator
    ///
    __ALWAYS_INLINE reverse_iterator& operator--( ) __NOEXCEPT
    {
        ++current;
        return *this;
    }

    /// \brief decrements current, which advances the reverse iterator
    ///
    __ALWAYS_INLINE reverse_iterator operator++(int) __NOEXCEPT
    {
        reverse_iterator tmp = *this;
        --current;
        return tmp;
    }

    /// \brief increments current, which decreases the reverse iterator
    ///
    __ALWAYS_INLINE reverse_iterator operator--(int) __NOEXCEPT
    {
        reverse_iterator tmp = *this;
        ++current;
        return tmp;
    }

    /// \brief decrements current by n, which advances the reverse iterator by n
    ///
    __ALWAYS_INLINE reverse_iterator& operator+=(difference_type n) __NOEXCEPT
    {
        current -= n;
        return *this;
    }

    /// \brief increments current by n, which decreases the reverse iterator by n
    ///
    __ALWAYS_INLINE reverse_iterator& operator-=(difference_type n) __NOEXCEPT
    {
        current += n;
        return *this;
    }

    /// \brief returns reverse iterator increased by n, which means that current is actually decreased
    ///
    __ALWAYS_INLINE reverse_iterator operator+(difference_type n) const __NOEXCEPT
    {
        reverse_iterator tmp = *this;
        return tmp -= n;
    }

    /// \brief returns reverse iterator decreased by n, which means that current is actually increased
    ///
    __ALWAYS_INLINE reverse_iterator operator-(difference_type n) const __NOEXCEPT
    {
        reverse_iterator tmp = *this;
        return tmp += n;
    }
};

/// \brief returns lhs.base( ) == rhs.base( )
///
template< class Lhs, class Rhs >
__ALWAYS_INLINE bool operator==(const reverse_iterator<Lhs>& lhs, const reverse_iterator<Rhs>& rhs) __NOEXCEPT
{
    return lhs.base( ) == rhs.base( );
}

/// \brief returns lhs.base( ) != rhs.base( )
///
template< class Lhs, class Rhs >
__ALWAYS_INLINE bool operator!=(const reverse_iterator<Lhs>& lhs, const reverse_iterator<Rhs>& rhs) __NOEXCEPT
{
    return lhs.base( ) != rhs.base( );
}

/// \brief returns lhs.base( ) > rhs.base( )
///
template< class Lhs, class Rhs >
__ALWAYS_INLINE bool operator<(const reverse_iterator<Lhs>& lhs, const reverse_iterator<Rhs>& rhs) __NOEXCEPT
{
    return lhs.base( ) > rhs.base( );
}

/// \brief returns lhs.base( ) >= rhs.base( )
///
template< class Lhs, class Rhs >
__ALWAYS_INLINE bool operator<=(const reverse_iterator<Lhs>& lhs, const reverse_iterator<Rhs>& rhs) __NOEXCEPT
{
    return lhs.base( ) >= rhs.base( );
}

/// \brief returns lhs.base( ) < rhs.base( )
///
template< class Lhs, class Rhs >
__ALWAYS_INLINE bool operator>(const reverse_iterator<Lhs>& lhs, const reverse_iterator<Rhs>& rhs) __NOEXCEPT
{
    return lhs.base( ) < rhs.base( );
}

/// \brief returns lhs.base( ) <= rhs.base( )
///
template< class Lhs, class Rhs >
__ALWAYS_INLINE bool operator>=(const reverse_iterator<Lhs>& lhs, const reverse_iterator<Rhs>& rhs) __NOEXCEPT
{
    return lhs.base( ) <= rhs.base( );
}

/// \brief returns it - n
///
template< class Iterator >
__ALWAYS_INLINE reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& it) __NOEXCEPT
{
    return it - n;
}

/// \brief returns rhs.base( ) + lhs.base( )
///
template< class Lhs, class Rhs >
__ALWAYS_INLINE auto operator-(const reverse_iterator<Lhs>& lhs, const reverse_iterator<Rhs>& rhs) __NOEXCEPT -> decltype(rhs.base( ) - lhs.base( ))
{
    return rhs.base( ) - lhs.base( );
}

/// \brief returns reverse iterator constructed from i with deduced type of Iterator
///
template <class Iterator>
__ALWAYS_INLINE reverse_iterator<Iterator> make_reverse_iterator(Iterator i) __NOEXCEPT { return reverse_iterator<Iterator>(i); }

#endif

#if Region | move_iterator

/// \brief move iterator adapter
///
/// all operations on references returned by this adapter convert this references to rvalue references
template< class Iterator >
class move_iterator : public iterator<typename iterator_traits<Iterator>::iterator_category,
                                      typename iterator_traits<Iterator>::value_type,
                                      typename iterator_traits<Iterator>::difference_type,
                                      typename iterator_traits<Iterator>::pointer,
                                      typename iterator_traits<Iterator>::value_type&&>
{
protected:
    /// \brief member holding adapted iterator
    ///
    Iterator current;

public:
    template <class U>
    friend class move_iterator;

    using iterator_category = typename iterator_traits<Iterator>::iterator_category;
    using value_type        = typename iterator_traits<Iterator>::value_type;
    using difference_type   = typename iterator_traits<Iterator>::difference_type;
    using pointer           = typename iterator_traits<Iterator>::pointer;
    using reference         = typename iterator_traits<Iterator>::value_type&&;

    /// \brief default constructor
    ///
    move_iterator( ) __NOEXCEPT = default;

    /// \brief constructs adapter from value
    ///
    explicit move_iterator(Iterator value) __NOEXCEPT : current{ value } { }

    /// \brief template copy constructor
    ///
    template <class U>
    move_iterator(const move_iterator<U>& other) __NOEXCEPT : current{ other.current } { }

    /// \brief template copy assignment operator
    ///
    template <class U>
    __ALWAYS_INLINE move_iterator& operator=(const move_iterator<U>& other) __NOEXCEPT{ current(other.current); return *this; }

    /// \brief returns current
    ///
    __ALWAYS_INLINE Iterator base( ) const __NOEXCEPT { return current; }

    /// \brief returns rvalue reference to value pointed by current
    ///
    __ALWAYS_INLINE reference operator*() const __NOEXCEPT { return move(*current); }

    /// \brief returns current
    ///
    __ALWAYS_INLINE pointer operator->()  const __NOEXCEPT
    {
        return current;
    }

    /// \brief returns rvalue reference to current[n]
    ///
    __ALWAYS_INLINE reference operator[ ](difference_type n) __NOEXCEPT{ return move(current[n]); }

    /// \brief advances iterator
    ///
    __ALWAYS_INLINE move_iterator& operator++( ) __NOEXCEPT
    {
        ++current;
        return *this;
    }

    /// \brief decrements iterator
    ///
    __ALWAYS_INLINE move_iterator& operator--( ) __NOEXCEPT
    {
        --current;
        return *this;
    }

    /// \brief advances iterator
    ///
    __ALWAYS_INLINE move_iterator operator++(int) __NOEXCEPT
    {
        move_iterator tmp = *this;
        ++current;
        return tmp;
    }

    /// \brief decrements iterator
    ///
    __ALWAYS_INLINE move_iterator operator--(int) __NOEXCEPT
    {
        move_iterator tmp = *this;
        --current;
        return tmp;
    }

    /// \brief advances iterator by n
    ///
    __ALWAYS_INLINE move_iterator& operator+=(difference_type n) __NOEXCEPT
    {
        current += n;
        return *this;
    }

    /// \brief decrements iterator by n
    ///
    __ALWAYS_INLINE move_iterator& operator-=(difference_type n) __NOEXCEPT
    {
        current -= n;
        return *this;
    }

    /// \brief returns iterator advanced by n
    ///
    __ALWAYS_INLINE move_iterator operator+(difference_type n) const __NOEXCEPT
    {
        move_iterator tmp = *this;
        return tmp += n;
    }

    /// \brief returns iterator decremented by n
    ///
    __ALWAYS_INLINE move_iterator operator-(difference_type n) const __NOEXCEPT
    {
        move_iterator tmp = *this;
        return tmp -= n;
    }
};

/// \brief returns lhs.base( ) == rhs.base( )
///
template< class Lhs, class Rhs >
__ALWAYS_INLINE bool operator==(const move_iterator<Lhs>& lhs, const move_iterator<Rhs>& rhs) __NOEXCEPT
{
    return lhs.base( ) == rhs.base( );
}

/// \brief returns lhs.base( ) != rhs.base( )
///
template< class Lhs, class Rhs >
__ALWAYS_INLINE bool operator!=(const move_iterator<Lhs>& lhs, const move_iterator<Rhs>& rhs) __NOEXCEPT
{
    return lhs.base( ) != rhs.base( );
}

/// \brief returns lhs.base( ) < rhs.base( )
///
template< class Lhs, class Rhs >
__ALWAYS_INLINE bool operator<(const move_iterator<Lhs>& lhs, const move_iterator<Rhs>& rhs) __NOEXCEPT
{
    return lhs.base( ) < rhs.base( );
}

/// \brief returns lhs.base( ) <= rhs.base( )
///
template< class Lhs, class Rhs >
__ALWAYS_INLINE bool operator<=(const move_iterator<Lhs>& lhs, const move_iterator<Rhs>& rhs) __NOEXCEPT
{
    return lhs.base( ) <= rhs.base( );
}

/// \brief returns lhs.base( ) > rhs.base( )
///
template< class Lhs, class Rhs >
__ALWAYS_INLINE bool operator>(const move_iterator<Lhs>& lhs, const move_iterator<Rhs>& rhs) __NOEXCEPT
{
    return lhs.base( ) > rhs.base( );
}

/// \brief returns lhs.base( ) >= rhs.base( )
///
template< class Lhs, class Rhs >
__ALWAYS_INLINE bool operator>=(const move_iterator<Lhs>& lhs, const move_iterator<Rhs>& rhs) __NOEXCEPT
{
    return lhs.base( ) >= rhs.base( );
}

/// \brief returns it + n
///
template< class Iterator >
__ALWAYS_INLINE move_iterator<Iterator> operator+(typename move_iterator<Iterator>::difference_type n, const move_iterator<Iterator>& it) __NOEXCEPT
{
    return it + n;
}

/// \brief returns rhs.base( ) - lhs.base( )
///
template< class Lhs, class Rhs >
__ALWAYS_INLINE auto operator-(const move_iterator<Lhs>& lhs, const move_iterator<Rhs>& rhs) __NOEXCEPT -> decltype(rhs.base( ) - lhs.base( ))
{
    return rhs.base( ) - lhs.base( );
}

/// \brief returns move iterator adapter constructed from i with deduced Iterator type
///
template <class Iterator>
__ALWAYS_INLINE move_iterator<Iterator> make_move_iterator(Iterator i) __NOEXCEPT { return move_iterator<Iterator>(i); }

#endif

#if Region | back_insert_iterator

/// \brief back insert iterator
///
template <class Container>
class back_insert_iterator : public cl::iterator<output_iterator_tag, void, void, void, void>
{
public:
    /// \brief constructs back insert iterator for container c
    ///
    explicit back_insert_iterator(Container& c) __NOEXCEPT : container{ addressof(c) } { }

    /// \brief performs push_back(value) on stored container
    ///
    __ALWAYS_INLINE back_insert_iterator<Container> & operator=(const typename Container::value_type& value) __NOEXCEPT
    {
        container->push_back(value);
        return *this;
    }

    /// \brief performs push_back(move(value)) on stored container
    ///
    __ALWAYS_INLINE back_insert_iterator<Container> & operator=(typename Container::value_type&& value) __NOEXCEPT
    {
        container->push_back(move(value));
        return *this;
    }

    /// \brief no op
    ///
    __ALWAYS_INLINE back_insert_iterator& operator*( ) __NOEXCEPT { return *this; }

    /// \brief no op
    ///
    __ALWAYS_INLINE back_insert_iterator& operator++( ) __NOEXCEPT { return *this; }

    /// \brief no op
    ///
    __ALWAYS_INLINE back_insert_iterator& operator++(int) __NOEXCEPT { return *this; }

protected:
    /// \brief stored container
    ///
    Container * container;
};

/// \brief returns back_insert_iterator constructed from container correctly deducing container type
///
template <class Container>
__ALWAYS_INLINE back_insert_iterator<Container> back_inserter(Container& c) __NOEXCEPT
{
    return back_insert_iterator<Container>(c);
}

#endif

#if Region | front_insert_iterator

/// \brief front insert iterator
///
template <class Container>
class front_insert_iterator : public cl::iterator<output_iterator_tag, void, void, void, void>
{
public:
    /// \brief constructs front insert iterator for container c
    ///
    explicit front_insert_iterator(Container& c) __NOEXCEPT : container{ addressof(c) } { }

    /// \brief performs push_front(value) on stored container
    ///
    __ALWAYS_INLINE front_insert_iterator<Container> & operator=(const typename Container::value_type& value) __NOEXCEPT
    {
        container->push_front(value);
        return *this;
    }

    /// \brief performs push_front(move(value)) on stored container
    ///
    __ALWAYS_INLINE front_insert_iterator<Container> & operator=(typename Container::value_type&& value) __NOEXCEPT
    {
        container->push_front(move(value));
        return *this;
    }

    /// \brief no op
    ///
    __ALWAYS_INLINE front_insert_iterator& operator*( ) __NOEXCEPT { return *this; }

    /// \brief no op
    ///
    __ALWAYS_INLINE front_insert_iterator& operator++( ) __NOEXCEPT { return *this; }

    /// \brief no op
    ///
    __ALWAYS_INLINE front_insert_iterator& operator++(int) __NOEXCEPT { return *this; }

protected:
    /// \brief stored container
    ///
    Container * container;
};

/// \brief returns front_insert_iterator constructed from container correctly deducing container type
///
template <class Container>
__ALWAYS_INLINE front_insert_iterator<Container> front_inserter(Container& c) __NOEXCEPT
{
    return front_insert_iterator<Container>(c);
}

#endif

#if Region | insert_iterator

/// \brief insert iterator
///
template <class Container>
class insert_iterator : public cl::iterator<output_iterator_tag, void, void, void, void>
{
protected:
    /// \brief stored container
    ///
    Container * container;

    /// \brief stored iterator
    ///
    typename Container::iterator iter;

public:
    /// \brief constructs insert_iterator from container and iterator to that container
    ///
    explicit insert_iterator(Container& c, typename Container::iterator i) __NOEXCEPT : container{ addressof(c) }, iter{ i }{}

    /// \brief inserts value into the container at the position pointed by iterator and increments iterator
    ///
    __ALWAYS_INLINE insert_iterator<Container> & operator=(const typename Container::value_type& value) __NOEXCEPT
    {
        iter = container->insert(iter, value);
        ++iter;
        return *this;
    }

    /// \brief inserts value, converted into rvalue reference, into the container at the position pointed by iterator and increments iterator
    ///
    __ALWAYS_INLINE insert_iterator<Container> & operator=(typename Container::value_type&& value) __NOEXCEPT
    {
        iter = container->insert(iter, move(value));
        ++iter;
        return *this;
    }

    /// \brief no op
    ///
    __ALWAYS_INLINE insert_iterator& operator*( ) __NOEXCEPT { return *this; }

    /// \brief no op
    ///
    __ALWAYS_INLINE insert_iterator& operator++( ) __NOEXCEPT { return *this; }

    /// \brief no op
    ///
    insert_iterator& operator++(int) __NOEXCEPT { return *this; }
};

/// \brief returns insert_iterator constructed from container correctly deducing container type
///
template <class Container>
insert_iterator<Container> inserter(Container& c, typename Container::iterator i) __NOEXCEPT
{
    return insert_iterator<Container>(c, i);
}

#endif

#if Region | iterator_operations

/// \brief Advances the iterator forward if the distance is positive, otherwise recedes iterator backwards
///
template <class Iterator, class Distance>
__ALWAYS_INLINE void advance(Iterator& it, Distance n) __NOEXCEPT
{
    if (is_same<typename Iterator::iterator_category, random_access_iterator_tag>::value)
    {
        if (n < Distance{ }) // is distance negative
        {
            it -= -n;
        }
        else
        {
            it += n;
        }
    }
    else
    {
        if (n < Distance{ }) // is distance negative
        {
            for (Distance i = Distance{ }; i < n; i++) { --it; }
        }
        else
        {
            for (Distance i = Distance{ }; i < n; i++) { ++it; }
        }
    }
}

/// \brief Calculates the distance between two iterators, if last cannot be reached from first by incrementing first the behavior is undefined
///
template <class Iterator>
__ALWAYS_INLINE typename iterator_traits<Iterator>::difference_type distance(Iterator first, Iterator last) __NOEXCEPT
{
//##todo - type czy category? category -> porownujemy tagi
    if (is_same<typename Iterator::iterator_category, random_access_iterator_tag>::value)
    {
        return last - first;
    }
    else
    {
        typename iterator_traits<Iterator>::difference_type diff = typename iterator_traits<Iterator>::difference_type{ };
        while (first != last) { ++first; ++diff; }
        return diff;
    }
}

/// \brief Returns iterator following it by n
///
template <class Iterator>
__ALWAYS_INLINE Iterator next(Iterator it, typename iterator_traits<Iterator>::difference_type n = 1) __NOEXCEPT
{
    advance(it, n);
    return it;
}

/// \brief Returns iterator preceding it by n
///
template <class Iterator>
__ALWAYS_INLINE Iterator prev(Iterator it, typename iterator_traits<Iterator>::difference_type n = 1) __NOEXCEPT
{
    advance(it, -n);
    return it;
}

#endif

#if Region | range_access

/// \brief Returns iterator to the beginning of the container or a pointer to begin of a bound array
///
template <class Container>
__ALWAYS_INLINE auto begin(Container& container) __NOEXCEPT -> decltype(container.begin( )) { return container.begin( ); }

/// \brief Returns iterator to the beginning of the container or a pointer to begin of a bound array
///
template <class Container>
__ALWAYS_INLINE auto begin(const Container& container) __NOEXCEPT -> decltype(container.begin( )) { return container.begin( ); }

/// \brief Returns iterator to the beginning of the container or a pointer to begin of a bound array
///
template <class T, size_t N>
__ALWAYS_INLINE constexpr T* begin(T (&arr)[N]) __NOEXCEPT { return addressof(arr); }

/// \brief Returns const iterator to the beginning of the container or a const pointer to begin of a bound array
///
template <class Container>
__ALWAYS_INLINE constexpr auto cbegin( const Container& container ) __NOEXCEPT -> decltype(begin(container)) { return begin(container); }

/// \brief Returns iterator to the end of the container or a pointer to end of a bound array
///
template <class Container>
__ALWAYS_INLINE auto end(Container& container) __NOEXCEPT -> decltype(container.end( )) { return container.end( ); }

/// \brief Returns iterator to the end of the container or a pointer to end of a bound array
///
template <class Container>
__ALWAYS_INLINE auto end(const Container& container) __NOEXCEPT -> decltype(container.end( )) { return container.end( ); }

/// \brief Returns iterator to the end of the container or a pointer to end of a bound array
///
template <class T, size_t N>
__ALWAYS_INLINE constexpr T* end(T (&arr)[N]) __NOEXCEPT { return addressof(arr) + N; }

/// \brief Returns const iterator to the end of the container or a const pointer to end of a bound array
///
template <class Container>
__ALWAYS_INLINE constexpr auto cend(const Container& container) __NOEXCEPT -> decltype(end(container)) { return end(container); }

/// \brief Returns reverse iterator to the beginning of the container or a pointer to end - 1 of a bound array
///
template <class Container>
__ALWAYS_INLINE auto rbegin(Container& container) __NOEXCEPT -> decltype(container.rbegin( )) { return container.rbegin( ); }

/// \brief Returns reverse iterator to the beginning of the container or a pointer to end - 1 of a bound array
///
template <class Container>
__ALWAYS_INLINE auto rbegin(const Container& container) __NOEXCEPT -> decltype(container.rbegin( )) { return container.rbegin( ); }

/// \brief Returns reverse iterator to the beginning of the container or a pointer to end - 1 of a bound array
///
template <class T, size_t N>
__ALWAYS_INLINE reverse_iterator<T*> rbegin(T (&arr)[N]) __NOEXCEPT { return reverse_iterator<T*>(end(arr)); }

/// \brief Returns const reverse iterator to the beginning of the container or a const pointer to end - 1 of a bound array
///
template <class Container>
__ALWAYS_INLINE auto crbegin(const Container& container) __NOEXCEPT -> decltype(rbegin(container)) { return rbegin(container); }

/// \brief Returns reverse iterator to the end of the container or a pointer to begin of a bound array
///
template <class Container>
__ALWAYS_INLINE auto rend(Container& container) __NOEXCEPT -> decltype(container.rend( )) { return container.rend( ); }

/// \brief Returns reverse iterator to the end of the container or a pointer to begin of a bound array
///
template <class Container>
__ALWAYS_INLINE auto rend(const Container& container) __NOEXCEPT -> decltype(container.rend( )) { return container.rend( ); }

/// \brief Returns reverse iterator to the end of the container or a pointer to begin of a bound array
///
template <class T, size_t N>
__ALWAYS_INLINE reverse_iterator<T*> rend(T (&arr)[N]) __NOEXCEPT { return reverse_iterator<T*>(begin(arr)); }

/// \brief Returns const reverse iterator to the end of the container or a const pointer to begin of a bound array
///
template <class Container>
__ALWAYS_INLINE auto crend(const Container& container) __NOEXCEPT -> decltype(rend(container)) { return rend(container); }

#endif

}

#undef Region