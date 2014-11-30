/*
  Copyright © 2014 Jesse 'Jeaye' Wilkerson
  See licensing at:
    http://opensource.org/licenses/MIT

  Author: Jesse 'Jeaye' Wilkerson
*/

#pragma once

#include <iterator>

#include <jtl/namespace.hpp>

namespace jtl
{
  namespace iterator
  {
    template <typename C, typename It>
    class insert
      : public std::iterator<std::output_iterator_tag,
          typename std::iterator_traits
          <
            decltype(std::begin(std::declval<C&>()))
          >::value_type>
    {
      public:
        using iterator = decltype(std::begin(std::declval<C&>()));
        using value_type = typename std::iterator_traits<iterator>::value_type;

        insert() = delete;
        insert(C &c, It const it)
          : container_{ c }
          , it_{ it }
        { }

        template <typename T>
        insert& operator =(T &&c)
        {
          it_ = container_.insert(it_, std::forward<T>(c));
          ++it_;
          return *this;
        }

        /* NOP */
        insert& operator *() noexcept
        { return *this; }
        insert& operator ++() noexcept
        { return *this; }
        insert& operator ++(int) noexcept
        { return *this; }

      private:
        C &container_;
        It it_{};
    };

    template <typename C, typename It>
    insert<C, It> inserter(C &c, It const it)
    { return { c, it }; }
  }
}
