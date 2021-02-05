#ifndef OZ_DYNAMIC_ARRAY_H
#define OZ_DYNAMIC_ARRAY_H

#include "oz.h"

#include <cstddef>
#include <iterator>
#include <limits>

BEGIN_NAMESPACE_OZ

template<typename T>
class dynamic_array
{
   using value_type = T;
   using reference = T&;
   using const_reference = const T&;
   using iterator = T*;
   using const_iterator = const T*;
   using difference_type = typename std::iterator_traits<T*>::difference_type;
   using size_type = std::size_t;

   T * _elems;
   size_type _N;

   public:

   dynamic_array() noexcept : _elems{nullptr}, _N{0} {}

   explicit dynamic_array(size_type N, T val = T()) 
   {
      _elems = new T[N](val);
      _N = N;
   }

   dynamic_array(const dynamic_array& other)
   {
      T * tmp = new T[other.N];
      for (size_type i=0; i < other._N; i++) {
         tmp[i] = other._elems[i];
      }
      this->_elems = tmp;
      this->_N = other._N;
   }

   dynamic_array(dynamic_array&& other) noexcept
   {
      this->_elems = other._elems;
      this->_N = other._N;
      other._elems = nullptr;
      other._N = 0;
   }

   dynamic_array& operator = (const dynamic_array& other)
   {
      if ( this != &other ) {
         T * tmp = new T[other._N];
         for (size_type i=0; i < other._N; i++) {
            tmp[i] = other._elems[i];
         }
         this->~dynamic_array();
         this->_elems = tmp;
         this->_N = other._N;
      }
      return *this;
   }

   dynamic_array& operator = (dynamic_array&& other) noexcept
   {
      std::swap(this->_elems, other._elems);
      std::swap(this->_N, other._N);
   }

   ~dynamic_array() noexcept
   {
      if ( this->_elems ) {
         delete [] this->_elems;
         this->_elems = nullptr;
         this->_N = 0;
      }
   }

   void swap(dynamic_array& other)
   {
      std::swap(this->_N, other._N);
      std::swap(this->_elems, other._elems);
   }

   void resize(size_type N, T val = T())
   {
      if (N != this->_N)
      {
         this->~dynamic_array();
         this->_elems = new T[N](val);
         this->_N = N;
      }
   }

   reference operator [] (size_type idx) noexcept
   {
      return this->_elems[idx];
   }

   const_reference operator [] (size_type idx) const noexcept
   {
      return this->_elems[idx];
   }

   T * data() noexcept
   {
      return this->_elems;
   }

   const T * data() const noexcept
   {
      return this->_elems;
   }

   iterator begin() noexcept
   {
      return this->_elems;
   }

   iterator end() noexcept
   {
      return this->_elems + this->_N;
   }

   const iterator cbegin() const noexcept
   {
      return this->_elems;
   }

   const iterator cend() const noexcept
   {
      return this->_elems + this->_N;
   }

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

   bool operator == (const dynamic_array& other)
   {
      if ( this->_N == other._N ) {
         for(size_type i=0; i < this->_N; i++) {
            if ( this->_elems[i] != other._elems[i] ) {
               return false;
            }
         }
         return true;
      }
      else {
         return false;
      }
   }

   bool operator != (const dynamic_array& other)
   {
      return !(this->operator == (other));
   }




};

template<typename T>
void swap(dynamic_array<T>& a, dynamic_array<T>& b)
{
   a.swap(b);
}

END_NAMESPACE_OZ

#endif

