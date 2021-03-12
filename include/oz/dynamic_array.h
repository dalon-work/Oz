#ifndef OZ_DYNAMIC_ARRAY_H
#define OZ_DYNAMIC_ARRAY_H

#include "oz.h"

#include <cstddef>
#include <iterator>
#include <limits>
#include <memory>

BEGIN_NAMESPACE_OZ

template<typename T, typename Allocator = std::allocator<T>>
class dynamic_array : protected Allocator
{
   using value_type = T;
   using allocator_type = Allocator;
   using reference = T&;
   using const_reference = const T&;
   using iterator = T*;
   using const_iterator = const T*;
   using difference_type = typename std::iterator_traits<T*>::difference_type;
   using size_type = std::size_t;

   T * _elems;
   size_type _N;

   public:

   //  -- Done. vector() noexcept(noexcept(Allocator())); (1)
   //  - Default Constructor. Constructs an empty container with a default-constructed allocator.
   // -- Done. explicit vector( const Allocator& alloc ) noexcept; (2)
   //  - Constructs an empty container with the given allocator alloc.
   //
   // vector( size_type count, const T& value, const Allocator& alloc = Allocator()); (3)
   //  - Constructs the container with count copies of elements with value value
   //
   // explicit vector( size_type count, const Allocator& alloc = Allocator()); (4)
   //   - Constructs the container with count default-inserted instances of T. No copies are made.
   //   - This overload zeros out elements of non-class types such as int.
   // template<class InputIt> vector( InputIt first, InputIt last, const Allocator& alloc = Allocator() ); (5)
   //  - Constructs the container with the contents of the range [first, last).
   // vector( const vector& other ); (6)
   // vector( const vector& other, const Allocator& alloc ); (7)
   // vector( vector&& other ) noexcept; (8)
   // vector( vector&& other, const Allocator& alloc); (9)
   // vector( std::initializer_list<T> init, const Allocator& alloc = Allocator() ); (10)
   //
   // ~vector();
   //
   // vector& operator=( const vector& other );
   // vector& operator=( vector&& other ) noexcept(*);
   //   - Replaces the contents with those of other using move semantics
   //     If std::allocator_traits<allocator_type>::propagate_on_container_move_assignment::value
   //     is true, the target allocator is replaced by a copy of the source allocator. 
   //     If it is false and the source and the target allocators do not compare equal,
   //     the target cannot take ownership of the source memory and must move-assign
   //     each element individually, alloacting additional memroy using its own allocator
   //     as needed. In any case, all elements originally present in *this are either
   //     destroyed or replaced by elementwise move-assignment.
   //   - noexcept(std::allocator_traits<Allocator>::propagate_on_container_move_assignment::value || std::allocator_traits<Allocator>::is_always_equal::value)
   // vector& operator=( std::initializer_list<T> ilist );
   //
   // void assign( size_type count, const T& value );
   // template< class InputIt > void assign( InputIt first, InputIt last );
   // void assign( std::initializer_list<T> ilist );
   //
   // allocator_type get_allocator() const noexcept;
   //
   // reference at( size_type pos );
   //   - If pos is not within the range of the container, an exception of type
   //     std::out_of_range is thrown
   //
   // reference operator[] ( size_type pos );
   // const_reference operator [] ( size_type pos) const;
   //   - No bounds checking is performed
   //
   // reference front();
   // const_reference front() const;
   // reference back();
   // const_reference back() const;
   // T* data() noexcept;
   // const T* data() const noexcept;
   //
   // iterator begin() noexcept;
   // const_iterator begin() const noexcept;
   // const_iterator cbegin() const noexcept;
   // iterator end() noexcept;
   // const_iterator end() const noexcept;
   // const_iterator cend() const noexcept;
   // 
   // reverse_iterator rbegin() noexcept;
   // const_reverse_iterator rbegin() const noexcept;
   // const_reverse_iterator crbegin() const noexcept;
   //   - Last element of the non-reversed vector
   //
   // reverse_iterator rend() noexcept;
   // const_reverse_iterator rend() const noexcept;
   // const_reverse_iterator crend() const noexcept;
   //   - element preceding the first element of the non-reversed vector
   //
   // bool empty() const noexcept;
   // size_type size() const noexcept;
   // size_type max_size() const noexcept;
   //   - typically std::numeric_limits<difference_type>::max()
   //
   // void reserve( size_type new_cap );
   //   - does not change the size of the vector
   //   - std::length_error if new_cap > max_size()
   //   - If an exception is thrown, this function has no effect (strong exception guarantee)
   //     If T's move constructor is not noexcept and T is not CopyInsertable into *this, 
   //     vector will use the throwing move constructor. If it throws, the guarantee is
   //     waived and the effects are unspecified.
   //   - Is this function valid for this container?
   //
   // void clear() noexcept;
   //   - erases all elements from the container
   //   - size is 0, capacity is unchanged
   //   - Is this function valid for this container?
   //
   // iterator insert() - Are these functions valid for this container?
   //   - Causes reallocation if the new size() is greater than the old capacity().
   //   - Yes, required for a sequence container
   //
   // template< class... Args> iterator emplace( const_iterator pos, Args&&... args );
   //   - Inserts a new element into the container directly before pos.
   //   - Is this function valid for this container?
   //
   // iterator erase( const_iterator pos );
   //   - Is this function valid for this container?
   //
   // push_back(), emplace_back(), pop_back()
   //   - Are these functions valid for this container?
   //
   // void resize( size_type count );
   // void resize( size_type count, const value_type& value );
   //   - Resizes the container to contain count elements
   //   - If current size is > count, the container is reduced to its first count elements.
   //   - If the current size is less than count, it grows, and additional copies
   //     are inserted.
   //   - Strong exception guarantee
   //   - If value-initialization is undesirable, it can be avoided by providing a
   //     cusom Allocator::construct;
   //
   // void swap( vector& other ) noexcept(*);
   //   - If std::allocator_traits<allocator_type>::propagate_on_container_swap::value 
   //     is true, then the allocators are exchanged using an unqualified call to 
   //     non-member swap. Otherwise, they are not swapped 
   //     (and if get_allocator() != other.get_allocator(), the behavior is undefined). 
   //   - Exceptions: noexcept(std::allocator_traits<Allocator>::propagate_on_container_swap::value || std::allocator_traits<Allocator>::is_always_equal::value)
   //
   // std::swap(std::vector<T,A>) specialization
   //

   // std::array
   //
   // implicit constructor:
   //  - initializes the array following the rules of "aggregate initialization",
   //    which may result in indeterminate values for non-class T.
   //
   // implicit destructor
   //  - destroys every element of the array
   //
   // implicit operator =
   //  - overwrites every element of the array with the corresponding 
   //    element of another array
   //
   // at()
   // operator[]
   // front()
   // back()
   // data()
   // begin()
   // cbegin()
   // end()
   // cend()
   // rbegin()
   // crbegin()
   // rend()
   // crend()
   // empty()
   // size()
   // max_size()
   // fill()
   // swap()
   //
   // operator ==
   // operator !=
   // operator <
   // operator <=
   // operator >
   // operator >=

   dynamic_array() noexcept(noexcept(Allocator())) : Allocator(), _elems{nullptr}, _N{0} {}

   explicit dynamic_array( const Allocator& alloc ) noexcept : Allocator(alloc), _elems{nullptr}, _N{0} {}

   explicit dynamic_array( size_type count, const Allocator& alloc = Allocator()) : Allocator(alloc)
   {
      size_type idx = 0;
      try {
         _elems = std::allocator_traits<Allocator>::allocate(get_allocator(), count);
         for(; idx < count; idx++) {
            std::allocator_traits<Allocator>::construct(get_allocator(), &_elems[idx]);
         }
         _N = count;
      }
      catch (...) {
         for(; idx > 0; idx--) {
            std::allocator_traits<Allocator>::destroy(get_allocator(), &_elems[idx]);
         }

         std::allocator_traits<Allocator>::deallocate(get_allocator(), _elems, _N);
         _N = 0;
         throw;
      }
   }

   // explicit dynamic_array( size_type count, const T& value, const Allocator& alloc = Allocator()) : Allocator(alloc)
   // {
   //    _elems = new T[count](value);
   //    _N = count;
   // }


   // dynamic_array(const dynamic_array& other)
   // {
   //    T * tmp = new T[other.N];
   //    for (size_type i=0; i < other._N; i++) {
   //       tmp[i] = other._elems[i];
   //    }
   //    this->_elems = tmp;
   //    this->_N = other._N;
   // }
   //
   // dynamic_array(dynamic_array&& other) noexcept
   // {
   //    this->_elems = other._elems;
   //    this->_N = other._N;
   //    other._elems = nullptr;
   //    other._N = 0;
   // }
   //
   // dynamic_array& operator = (const dynamic_array& other)
   // {
   //    if ( this != &other ) {
   //       T * tmp = new T[other._N];
   //       for (size_type i=0; i < other._N; i++) {
   //          tmp[i] = other._elems[i];
   //       }
   //       this->~dynamic_array();
   //       this->_elems = tmp;
   //       this->_N = other._N;
   //    }
   //    return *this;
   // }
   //
   // dynamic_array& operator = (dynamic_array&& other) noexcept
   // {
   //    std::swap(this->_elems, other._elems);
   //    std::swap(this->_N, other._N);
   // }
   //
   // ~dynamic_array() noexcept
   // {
   //    if ( this->_elems ) {
   //       delete [] this->_elems;
   //       this->_elems = nullptr;
   //       this->_N = 0;
   //    }
   // }
   //
   // void swap(dynamic_array& other)
   // {
   //    std::swap(this->_N, other._N);
   //    std::swap(this->_elems, other._elems);
   // }
   //
   // void resize(size_type N)
   // {
   //    if (N != this->_N)
   //    {
   //       this->~dynamic_array();
   //       this->_elems = new T[N];
   //       this->_N = N;
   //    }
   // }
   //
   // reference operator [] (size_type idx) noexcept
   // {
   //    return this->_elems[idx];
   // }
   //
   // const_reference operator [] (size_type idx) const noexcept
   // {
   //    return this->_elems[idx];
   // }
   //
   T * data() noexcept
   {
      return this->_elems;
   }
   //
   // const T * data() const noexcept
   // {
   //    return this->_elems;
   // }
   //
   // iterator begin() noexcept
   // {
   //    return this->_elems;
   // }
   //
   // iterator end() noexcept
   // {
   //    return this->_elems + this->_N;
   // }
   //
   // const iterator cbegin() const noexcept
   // {
   //    return this->_elems;
   // }
   //
   // const iterator cend() const noexcept
   // {
   //    return this->_elems + this->_N;
   // }

   size_type size() const noexcept
   {
      return this->_N;
   }

   size_type max_size() const noexcept
   {
      return std::numeric_limits<size_type>::max();
   }

   bool empty() const noexcept
   {
      return this->_elems == nullptr;
   }

   allocator_type& get_allocator() noexcept
   {
      return *this;
   }

   // bool operator == (const dynamic_array& other)
   // {
   //    if ( this->_N == other._N ) {
   //       for(size_type i=0; i < this->_N; i++) {
   //          if ( this->_elems[i] != other._elems[i] ) {
   //             return false;
   //          }
   //       }
   //       return true;
   //    }
   //    else {
   //       return false;
   //    }
   // }
   //
   // bool operator != (const dynamic_array& other)
   // {
   //    return !(this->operator == (other));
   // }




};

template<typename T>
void swap(dynamic_array<T>& a, dynamic_array<T>& b)
{
   a.swap(b);
}

END_NAMESPACE_OZ

#endif

