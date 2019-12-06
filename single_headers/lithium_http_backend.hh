// Author: Matthieu Garrigues matthieu.garrigues@gmail.com
//
// Single header version the lithium_http_backend library.
// https://github.com/matt-42/lithium
//
// This file is generated do not edit it.

#pragma once

#include <cstring>
#include <sstream>
#include <variant>
#include <microhttpd.h>
#include <string>
#include <tuple>
#include <random>
#include <fstream>
#include <map>
#include <vector>
#include <set>
#include <sys/stat.h>
#include <boost/lexical_cast.hpp>
#include <stdio.h>
#include <utility>
#include <iostream>
#include <string.h>
#include <functional>
#include <memory>
#include <unordered_map>
#include <thread>
#include <string_view>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <mutex>
#include <cassert>
#include <optional>
#include <cmath>

#if defined(_MSC_VER)
#include <io.h>
#include <windows.h>
#include <ciso646>
#endif // _MSC_VER


#ifndef LITHIUM_SINGLE_HEADER_GUARD_LI_HTTP_BACKEND_HTTP_BACKEND
#define LITHIUM_SINGLE_HEADER_GUARD_LI_HTTP_BACKEND_HTTP_BACKEND

#ifndef LITHIUM_SINGLE_HEADER_GUARD_LI_SQL_SQL_COMMON
#define LITHIUM_SINGLE_HEADER_GUARD_LI_SQL_SQL_COMMON


namespace li
{
  struct sql_blob : public std::string {
    using std::string::string;
    using std::string::operator=;

    sql_blob() : std::string() {}
  };

  struct sql_null_t {};
  static sql_null_t null;

  template <unsigned SIZE>
  struct sql_varchar : public std::string {
    using std::string::string;
    using std::string::operator=;

    sql_varchar() : std::string() {}
  };
}
#endif // LITHIUM_SINGLE_HEADER_GUARD_LI_SQL_SQL_COMMON

#ifndef LITHIUM_SINGLE_HEADER_GUARD_LI_SQL_SQL_ORM
#define LITHIUM_SINGLE_HEADER_GUARD_LI_SQL_SQL_ORM

#ifndef LITHIUM_SINGLE_HEADER_GUARD_LI_METAMAP_METAMAP
#define LITHIUM_SINGLE_HEADER_GUARD_LI_METAMAP_METAMAP


namespace li {

  namespace internal
  {
    struct {
      template <typename A, typename... B>
      constexpr auto operator()(A&& a, B&&... b)
      {
        auto result = a;
        using expand_variadic_pack  = int[];
        (void)expand_variadic_pack{0, ((result += b), 0)... };
        return result;
      }
    } reduce_add;

  }

  
  template <typename... Ms>
  struct metamap;
  
  template <typename F, typename... M>
  decltype(auto) find_first(metamap<M...>&& map, F fun);

  template <typename ...Ms>
  struct metamap;

  template <typename M1, typename ...Ms>
  struct metamap<M1, Ms...> : public M1, public Ms...
  {
    typedef metamap<M1, Ms...> self;
    // Constructors.
    inline metamap() = default;
    //inline metamap(self&&) = default;
    inline metamap(const self&) = default;
    self& operator=(const self&) = default;

    //metamap(self& other)
    //  : metamap(const_cast<const self&>(other)) {}

    inline metamap(M1&& m1, Ms&&... members) : M1(m1), Ms(std::forward<Ms>(members))... {}
    inline metamap(const M1& m1, const Ms&... members) : M1(m1), Ms((members))... {}

    // Assignemnt ?

    // Retrive a value.
    template <typename K>
    decltype(auto) operator[](K k)
    {
      return symbol_member_access(*this, k);
    }

    template <typename K>
    decltype(auto) operator[](K k) const
    {
      return symbol_member_access(*this, k);
    }

  };

  template <>
  struct metamap<>
  {
    typedef metamap<> self;
    // Constructors.
    inline metamap() = default;
    //inline metamap(self&&) = default;
    inline metamap(const self&) = default;
    //self& operator=(const self&) = default;

    //metamap(self& other)
    //  : metamap(const_cast<const self&>(other)) {}

    // Assignemnt ?

    // Retrive a value.
    template <typename K>
    decltype(auto) operator[](K k)
    {
      return symbol_member_access(*this, k);
    }

    template <typename K>
    decltype(auto) operator[](K k) const
    {
      return symbol_member_access(*this, k);
    }

  };

  template <typename... Ms>
  constexpr auto size(metamap<Ms...>)
  {
    return sizeof...(Ms);
  }
  
  template <typename M>
  struct metamap_size_t
  {
  };
  template <typename... Ms>
  struct metamap_size_t<metamap<Ms...>>
  {
    enum { value = sizeof...(Ms) };
  };
  template <typename M>
  constexpr int metamap_size()
  {
    return metamap_size_t<std::decay_t<M>>::value;
  }

  template <typename... Ks>
  decltype(auto) metamap_values(const metamap<Ks...>& map)
  {
    return std::forward_as_tuple(map[typename Ks::_iod_symbol_type()]...);
  }

  template <typename K, typename M>
  constexpr auto has_key(M&& map, K k)
  {
    return decltype(has_member(map, k)){};
  }

  template <typename M, typename K>
  constexpr auto has_key(K k)
  {
    return decltype(has_member(std::declval<M>(), std::declval<K>())){};
  }

  template <typename M, typename K>
  constexpr auto has_key()
  {
    return decltype(has_member(std::declval<M>(), std::declval<K>())){};
  }

  template <typename K, typename M, typename O>
  constexpr auto get_or(M&& map, K k, O default_)
  {
    if constexpr(has_key<M, decltype(k)>()) {
        return map[k];
      }
    else
      return default_;
  }
  
  template <typename X>
  struct is_metamap { enum { ret = false }; };
  template <typename... M>
  struct is_metamap<metamap<M...>> { enum { ret = true }; };
  
}

#ifndef LITHIUM_SINGLE_HEADER_GUARD_LI_METAMAP_MAKE
#define LITHIUM_SINGLE_HEADER_GUARD_LI_METAMAP_MAKE

#ifndef LITHIUM_SINGLE_HEADER_GUARD_LI_SYMBOL_SYMBOL
#define LITHIUM_SINGLE_HEADER_GUARD_LI_SYMBOL_SYMBOL

#ifndef LITHIUM_SINGLE_HEADER_GUARD_LI_SYMBOL_AST
#define LITHIUM_SINGLE_HEADER_GUARD_LI_SYMBOL_AST


namespace li {

  template <typename E>
  struct Exp {};

  template <typename E>
  struct array_subscriptable;

  template <typename E>
  struct callable;

  template <typename E>
  struct assignable;

  template <typename E>
  struct array_subscriptable;


  template <typename M, typename... A>
  struct function_call_exp :
    public array_subscriptable<function_call_exp<M, A...>>,
    public callable<function_call_exp<M, A...>>,
    public assignable<function_call_exp<M, A...>>,
    public Exp<function_call_exp<M, A...>>
  {
    using assignable<function_call_exp<M, A...>>::operator=;

    function_call_exp(const M& m, A&&... a)
      : method(m), args(std::forward<A>(a)...) {}

    M method;
    std::tuple<A...> args;
  };

  template <typename O, typename M>
  struct array_subscript_exp :
    public array_subscriptable<array_subscript_exp<O, M>>,
    public callable<array_subscript_exp<O, M>>,
    public assignable<array_subscript_exp<O, M>>,
    public Exp<array_subscript_exp<O, M>>
  {
    using assignable<array_subscript_exp<O, M>>::operator=;

    array_subscript_exp(const O& o, const M& m) : object(o), member(m) {}
    
    O object;
    M member;
  };

  template <typename L, typename R>
  struct assign_exp : public Exp<assign_exp<L, R>>
  {
    typedef L left_t;
    typedef R right_t;

    //template <typename V>
    //assign_exp(L l, V&& r) : left(l), right(std::forward<V>(r)) {}
    //template <typename V>
    inline assign_exp(L l, R r) : left(l), right(r) {}
    //template <typename V>
    //inline assign_exp(L l, const V& r) : left(l), right(r) {}
 
    L left;
    R right;
  };
  
  template <typename E>
  struct array_subscriptable
  {
  public:
    // Member accessor
    template <typename S>
    constexpr auto operator[](S&& s) const
    {
      return array_subscript_exp<E, S>(*static_cast<const E*>(this), std::forward<S>(s));
    }

  };

  template <typename E>
  struct callable
  {
  public:
    // Direct call.
    template <typename... A>
    constexpr auto operator()(A&&... args) const
    {
      return function_call_exp<E, A...>(*static_cast<const E*>(this),
                                        std::forward<A>(args)...);
    }

  };
 
  template <typename E>
  struct assignable
  {
  public:

    template <typename L>
    auto operator=(L&& l) const
    {
      return assign_exp<E, L>(static_cast<const E&>(*this), std::forward<L>(l));
    }

    template <typename L>
    auto operator=(L&& l)
    {
      return assign_exp<E, L>(static_cast<E&>(*this), std::forward<L>(l));
    }
    
    template <typename T>
    auto operator=(const std::initializer_list<T>& l) const
    {
      return assign_exp<E, std::vector<T>>(static_cast<const E&>(*this), std::vector<T>(l));
    }

  };

#define iod_query_declare_binary_op(OP, NAME)                           \
  template <typename A, typename B>                                     \
  struct NAME##_exp :                                                   \
   public assignable<NAME##_exp<A, B>>,                                 \
  public Exp<NAME##_exp<A, B>>                                          \
  {                                                                     \
    using assignable<NAME##_exp<A, B>>::operator=; \
    NAME##_exp()  {}                                                    \
    NAME##_exp(A&& a, B&& b) : lhs(std::forward<A>(a)), rhs(std::forward<B>(b)) {} \
    typedef A lhs_type;                                                 \
    typedef B rhs_type;                                                 \
    lhs_type lhs;                                                       \
    rhs_type rhs;                                                       \
  };                                                                    \
  template <typename A, typename B>                                     \
  inline                                                                \
  std::enable_if_t<std::is_base_of<Exp<A>, A>::value || \
                   std::is_base_of<Exp<B>, B>::value,\
                   NAME##_exp<A, B >>                                                    \
  operator OP (const A& b, const B& a)                                \
  { return NAME##_exp<std::decay_t<A>, std::decay_t<B>>{b, a}; }

  iod_query_declare_binary_op(+, plus);
  iod_query_declare_binary_op(-, minus);
  iod_query_declare_binary_op(*, mult);
  iod_query_declare_binary_op(/, div);
  iod_query_declare_binary_op(<<, shiftl);
  iod_query_declare_binary_op(>>, shiftr);
  iod_query_declare_binary_op(<, inf);
  iod_query_declare_binary_op(<=, inf_eq);
  iod_query_declare_binary_op(>, sup);
  iod_query_declare_binary_op(>=, sup_eq);
  iod_query_declare_binary_op(==, eq);
  iod_query_declare_binary_op(!=, neq);
  iod_query_declare_binary_op(&, logical_and);
  iod_query_declare_binary_op(^, logical_xor);
  iod_query_declare_binary_op(|, logical_or);
  iod_query_declare_binary_op(&&, and);
  iod_query_declare_binary_op(||, or);

# undef iod_query_declare_binary_op

}

#endif // LITHIUM_SINGLE_HEADER_GUARD_LI_SYMBOL_AST


namespace li {

  template <typename S>
  class symbol : public assignable<S>,
                 public array_subscriptable<S>,
                 public callable<S>,
                 public Exp<S>
  {};
}

#ifdef LI_SYMBOL
# undef LI_SYMBOL
#endif

#define LI_SYMBOL(NAME)                                                \
namespace s {                                                           \
struct NAME##_t : li::symbol<NAME##_t> {                         \
                                                                        \
using assignable<NAME##_t>::operator=;                               \
                                                                        \
inline constexpr bool operator==(NAME##_t) { return true; }          \
  template <typename T>                                                 \
  inline constexpr bool operator==(T) { return false; }                 \
                                                                        \
template <typename V>                                                   \
  struct variable_t {                                                   \
    typedef NAME##_t _iod_symbol_type;                            \
    typedef V _iod_value_type;                                          \
    V NAME;                                                             \
  };                                                                   \
                                                                        \
  template <typename T, typename... A>                                  \
  static inline decltype(auto) symbol_method_call(T&& o, A... args) { return o.NAME(args...); } \
  template <typename T, typename... A>                                  \
  static inline auto& symbol_member_access(T&& o) { return o.NAME; } \
  template <typename T>                                                \
  static constexpr auto has_getter(int) -> decltype(std::declval<T>().NAME(), std::true_type{}) { return {}; } \
  template <typename T>                                                \
  static constexpr auto has_getter(long) { return std::false_type{}; }     \
  template <typename T>                                                \
  static constexpr auto has_member(int) -> decltype(std::declval<T>().NAME, std::true_type{}) { return {}; } \
  template <typename T>                                                \
  static constexpr auto has_member(long) { return std::false_type{}; }        \
                                                                        \
  static inline auto symbol_string()                                    \
  {                                                                     \
    return #NAME;                                                       \
  }                                                                     \
                                                                        \
};                                                                      \
static constexpr  NAME##_t NAME;                                    \
}


namespace li {

  template <typename S>
  inline decltype(auto) make_variable(S s, char const v[])
  {
    typedef typename S::template variable_t<const char*> ret;
    return ret{v};
  }

  template <typename V, typename S>
  inline decltype(auto) make_variable(S s, V v)
  {
    typedef typename S::template variable_t<std::remove_const_t<std::remove_reference_t<V>>> ret;
    return ret{v};
  }
  
  template <typename K, typename V>
  inline decltype(auto) make_variable_reference(K s, V&& v)
  {
    typedef typename K::template variable_t<V> ret;
    return ret{v};
  }

  template <typename T, typename S, typename... A>
  static inline decltype(auto) symbol_method_call(T&& o, S, A... args)
  {
    return S::symbol_method_call(o, std::forward<A>(args)...);
  }

  template <typename T, typename S>
  static inline decltype(auto) symbol_member_access(T&& o, S)
  {
    return S::symbol_member_access(o);
  }
  
  template <typename T, typename S>
  constexpr auto has_member(T&& o, S) { return S::template has_member<T>(0); }
  template <typename T, typename S>
  constexpr auto has_member() { return S::template has_member<T>(0); }

  template <typename T, typename S>
  constexpr auto has_getter(T&& o, S) { return decltype(S::template has_getter<T>(0)){}; }
  template <typename T, typename S>
  constexpr auto has_getter() { return decltype(S::template has_getter<T>(0)){}; }
  
  template <typename S, typename T>
  struct CANNOT_FIND_REQUESTED_MEMBER_IN_TYPE {};
  
  template <typename T, typename S>
  decltype(auto) symbol_member_or_getter_access(T&&o, S)
  {
    if constexpr(has_getter<T, S>()) {
        return symbol_method_call(o, S{});
      }
    else if constexpr(has_member<T, S>()) {
        return symbol_member_access(o, S{});
      }
    else
    {
      return CANNOT_FIND_REQUESTED_MEMBER_IN_TYPE<S, T>::error;
    }
                   
  }
  
  template <typename S>
  auto symbol_string(symbol<S> v)
  {
    return S::symbol_string();
  }

  template <typename V>
  auto symbol_string(V v, typename V::_iod_symbol_type* = 0)
  {
    return V::_iod_symbol_type::symbol_string();
  }
}


#endif // LITHIUM_SINGLE_HEADER_GUARD_LI_SYMBOL_SYMBOL


namespace li {

  
  template <typename ...Ms>
  struct metamap;

  namespace internal
  {
    
    template <typename S, typename V>
    decltype(auto) exp_to_variable_ref(const assign_exp<S, V>& e)
    {
      return make_variable_reference(S{}, e.right);
    }

    template <typename S, typename V>
    decltype(auto) exp_to_variable(const assign_exp<S, V>& e)
    {
      typedef std::remove_const_t<std::remove_reference_t<V>> vtype;
      return make_variable(S{}, e.right);
    }

    template <typename S>
    decltype(auto) exp_to_variable(const symbol<S>& e)
    {
      return exp_to_variable(S() = int());
    }
    
    template <typename ...T>
    inline decltype(auto) make_metamap_helper(T&&... args)
    {
      return metamap<T...>(std::forward<T>(args)...);
    }
    
  }
  
  // Store copies of values in the map
  static struct {
    template <typename ...T>
    inline decltype(auto) operator()(T&&... args) const
    {
      // Copy values.
      return internal::make_metamap_helper(internal::exp_to_variable(std::forward<T>(args))...);
    }
  } mmm;
  
  // Store references of values in the map
  template <typename ...T>
  inline decltype(auto) make_metamap_reference(T&&... args)
  {
    // Keep references.
    return internal::make_metamap_helper(internal::exp_to_variable_ref(std::forward<T>(args))...);
  }
  
}

#endif // LITHIUM_SINGLE_HEADER_GUARD_LI_METAMAP_MAKE

#ifndef LITHIUM_SINGLE_HEADER_GUARD_LI_METAMAP_ALGORITHMS_MAP_REDUCE
#define LITHIUM_SINGLE_HEADER_GUARD_LI_METAMAP_ALGORITHMS_MAP_REDUCE

#ifndef LITHIUM_SINGLE_HEADER_GUARD_LI_METAMAP_ALGORITHMS_TUPLE_UTILS
#define LITHIUM_SINGLE_HEADER_GUARD_LI_METAMAP_ALGORITHMS_TUPLE_UTILS


namespace li {


  template <typename... E, typename F>
  void apply_each(F&& f, E&&... e)
  {
    (void)std::initializer_list<int>{
      ((void)f(std::forward<E>(e)), 0)...};
  }

  template <typename... E, typename F, typename R>
  auto tuple_map_reduce_impl(F&& f, R&& reduce, E&&... e)
  {
    return reduce(f(std::forward<E>(e))...);
  }

  template <typename T, typename F>
  void tuple_map(T&& t, F&& f)
  {
    return std::apply([&] (auto&&... e) { apply_each(f, std::forward<decltype(e)>(e)...); },
                                    std::forward<T>(t));
  }

  template <typename T, typename F>
  auto tuple_reduce(T&& t, F&& f)
  {
    return std::apply(std::forward<F>(f), std::forward<T>(t));
  }

  template <typename T, typename F, typename R>
  decltype(auto) tuple_map_reduce(T&& m, F map, R reduce)
  {
    auto fun = [&] (auto... e) {
      return tuple_map_reduce_impl(map, reduce, e...);
    };
    return std::apply(fun, m);
  }

  template <typename F>
  inline std::tuple<> tuple_filter_impl() { return std::make_tuple(); }

  template <typename F, typename... M, typename M1>
  auto tuple_filter_impl(M1 m1, M... m) {
    if constexpr (std::is_same<M1, F>::value)
      return tuple_filter_impl<F>(m...);
    else
      return std::tuple_cat(std::make_tuple(m1), tuple_filter_impl<F>(m...));
  }

  template <typename F, typename... M>
  auto tuple_filter(const std::tuple<M...>& m) {

    auto fun = [] (auto... e) { return tuple_filter_impl<F>(e...); };
    return std::apply(fun, m);
  
  }
  
}
#endif // LITHIUM_SINGLE_HEADER_GUARD_LI_METAMAP_ALGORITHMS_TUPLE_UTILS


namespace li {

  // Map a function(key, value) on all kv pair
  template <typename... M, typename F>
  void map(const metamap<M...>& m, F fun)
  {
    auto apply = [&] (auto key) -> decltype(auto)
      {
        return fun(key, m[key]);
      };

    apply_each(apply, typename M::_iod_symbol_type{}...);
  }

  // Map a function(key, value) on all kv pair. Ensure that the calling order
  // is kept.
  // template <typename O, typename F>
  // void map_sequential2(F fun, O& obj)
  // {}
  // template <typename O, typename M1, typename... M, typename F>
  // void map_sequential2(F fun, O& obj, M1 m1, M... ms)
  // {
  //   auto apply = [&] (auto key) -> decltype(auto)
  //     {
  //       return fun(key, obj[key]);
  //     };

  //   apply(m1);
  //   map_sequential2(fun, obj, ms...);
  // }
  // template <typename... M, typename F>
  // void map_sequential(const metamap<M...>& m, F fun)
  // {
  //   auto apply = [&] (auto key) -> decltype(auto)
  //     {
  //       return fun(key, m[key]);
  //     };

  //   map_sequential2(fun, m, typename M::_iod_symbol_type{}...);
  // }

  // Map a function(key, value) on all kv pair (non const).
  template <typename... M, typename F>
  void map(metamap<M...>& m, F fun)
  {
    auto apply = [&] (auto key) -> decltype(auto)
      {
        return fun(key, m[key]);
      };

    apply_each(apply, typename M::_iod_symbol_type{}...);
  }

  template <typename... E, typename F, typename R>
  auto apply_each2(F&& f, R&& r, E&&... e)
  {
    return r(f(std::forward<E>(e))...);
    //(void)std::initializer_list<int>{
    //  ((void)f(std::forward<E>(e)), 0)...};
  }

  // Map a function(key, value) on all kv pair an reduce
  // all the results value with the reduce(r1, r2, ...) function.
  template <typename... M, typename F, typename R>
  decltype(auto) map_reduce(const metamap<M...>& m, F map, R reduce)
  {
    auto apply = [&] (auto key) -> decltype(auto)
      {
        //return map(key, std::forward<decltype(m[key])>(m[key]));
        return map(key, m[key]);
      };

    return apply_each2(apply, reduce, typename M::_iod_symbol_type{}...);
    //return reduce(apply(typename M::_iod_symbol_type{})...);
  }

  // Map a function(key, value) on all kv pair an reduce
  // all the results value with the reduce(r1, r2, ...) function.
  template <typename... M, typename R>
  decltype(auto) reduce(const metamap<M...>& m, R reduce)
  {
    return reduce(m[typename M::_iod_symbol_type{}]...);
  }

}

#endif // LITHIUM_SINGLE_HEADER_GUARD_LI_METAMAP_ALGORITHMS_MAP_REDUCE

#ifndef LITHIUM_SINGLE_HEADER_GUARD_LI_METAMAP_ALGORITHMS_INTERSECTION
#define LITHIUM_SINGLE_HEADER_GUARD_LI_METAMAP_ALGORITHMS_INTERSECTION

#ifndef LITHIUM_SINGLE_HEADER_GUARD_LI_METAMAP_ALGORITHMS_MAKE_METAMAP_SKIP
#define LITHIUM_SINGLE_HEADER_GUARD_LI_METAMAP_ALGORITHMS_MAKE_METAMAP_SKIP

#ifndef LITHIUM_SINGLE_HEADER_GUARD_LI_METAMAP_ALGORITHMS_CAT
#define LITHIUM_SINGLE_HEADER_GUARD_LI_METAMAP_ALGORITHMS_CAT


namespace li {


  template <typename ...T, typename ...U>
  inline decltype(auto) cat(const metamap<T...>& a,
                            const metamap<U...>& b)
  {
    return metamap<T..., U...>(*static_cast<const T*>(&a)...,
                               *static_cast<const U*>(&b)...);
  }
  
}

#endif // LITHIUM_SINGLE_HEADER_GUARD_LI_METAMAP_ALGORITHMS_CAT


namespace li {

  
  struct skip {};
  static struct {

    template <typename... M, typename ...T>
    inline decltype(auto) run(metamap<M...> map, skip, T&&... args) const
    {
      return run(map, std::forward<T>(args)...);
    }
    
    template <typename T1, typename... M, typename ...T>
    inline decltype(auto) run(metamap<M...> map, T1&& a, T&&... args) const
    {
      return run(cat(map,
                     internal::make_metamap_helper(internal::exp_to_variable(std::forward<T1>(a)))),
                 std::forward<T>(args)...);
    }

    template <typename... M>
    inline decltype(auto) run(metamap<M...> map) const { return map; }
    
    template <typename... T>
    inline decltype(auto) operator()(T&&... args) const
    {
      // Copy values.
      return run(metamap<>{}, std::forward<T>(args)...);
    }

  } make_metamap_skip;

}

#endif // LITHIUM_SINGLE_HEADER_GUARD_LI_METAMAP_ALGORITHMS_MAKE_METAMAP_SKIP


namespace li {

  template <typename ...T, typename ...U>
  inline decltype(auto) intersection(const metamap<T...>& a,
                           const metamap<U...>& b)
  {
    return map_reduce(a, [&] (auto k, auto&& v) -> decltype(auto) {
        if constexpr(has_key<metamap<U...>, decltype(k)>()) {
            return k = std::forward<decltype(v)>(v);
          }
        else return skip{}; }, make_metamap_skip);
  }

}

#endif // LITHIUM_SINGLE_HEADER_GUARD_LI_METAMAP_ALGORITHMS_INTERSECTION

#ifndef LITHIUM_SINGLE_HEADER_GUARD_LI_METAMAP_ALGORITHMS_SUBSTRACT
#define LITHIUM_SINGLE_HEADER_GUARD_LI_METAMAP_ALGORITHMS_SUBSTRACT


namespace li {

  template <typename ...T, typename ...U>
  inline auto substract(const metamap<T...>& a,
                        const metamap<U...>& b)
  {
    return map_reduce(a, [&] (auto k, auto&& v) {
        if constexpr(!has_key<metamap<U...>, decltype(k)>()) {
            return k = std::forward<decltype(v)>(v);
          }
        else return skip{}; }, make_metamap_skip);
  }

}

#endif // LITHIUM_SINGLE_HEADER_GUARD_LI_METAMAP_ALGORITHMS_SUBSTRACT


#endif // LITHIUM_SINGLE_HEADER_GUARD_LI_METAMAP_METAMAP

#ifndef LITHIUM_SINGLE_HEADER_GUARD_LI_HTTP_BACKEND_SYMBOLS
#define LITHIUM_SINGLE_HEADER_GUARD_LI_HTTP_BACKEND_SYMBOLS

#ifndef LI_SYMBOL_blocking
#define LI_SYMBOL_blocking
    LI_SYMBOL(blocking)
#endif

#ifndef LI_SYMBOL_create_secret_key
#define LI_SYMBOL_create_secret_key
    LI_SYMBOL(create_secret_key)
#endif

#ifndef LI_SYMBOL_hash_password
#define LI_SYMBOL_hash_password
    LI_SYMBOL(hash_password)
#endif

#ifndef LI_SYMBOL_https_cert
#define LI_SYMBOL_https_cert
    LI_SYMBOL(https_cert)
#endif

#ifndef LI_SYMBOL_https_key
#define LI_SYMBOL_https_key
    LI_SYMBOL(https_key)
#endif

#ifndef LI_SYMBOL_id
#define LI_SYMBOL_id
    LI_SYMBOL(id)
#endif

#ifndef LI_SYMBOL_linux_epoll
#define LI_SYMBOL_linux_epoll
    LI_SYMBOL(linux_epoll)
#endif

#ifndef LI_SYMBOL_name
#define LI_SYMBOL_name
    LI_SYMBOL(name)
#endif

#ifndef LI_SYMBOL_non_blocking
#define LI_SYMBOL_non_blocking
    LI_SYMBOL(non_blocking)
#endif

#ifndef LI_SYMBOL_nthreads
#define LI_SYMBOL_nthreads
    LI_SYMBOL(nthreads)
#endif

#ifndef LI_SYMBOL_one_thread_per_connection
#define LI_SYMBOL_one_thread_per_connection
    LI_SYMBOL(one_thread_per_connection)
#endif

#ifndef LI_SYMBOL_path
#define LI_SYMBOL_path
    LI_SYMBOL(path)
#endif

#ifndef LI_SYMBOL_primary_key
#define LI_SYMBOL_primary_key
    LI_SYMBOL(primary_key)
#endif

#ifndef LI_SYMBOL_read_only
#define LI_SYMBOL_read_only
    LI_SYMBOL(read_only)
#endif

#ifndef LI_SYMBOL_select
#define LI_SYMBOL_select
    LI_SYMBOL(select)
#endif

#ifndef LI_SYMBOL_session_id
#define LI_SYMBOL_session_id
    LI_SYMBOL(session_id)
#endif

#ifndef LI_SYMBOL_update_secret_key
#define LI_SYMBOL_update_secret_key
    LI_SYMBOL(update_secret_key)
#endif

#ifndef LI_SYMBOL_user_id
#define LI_SYMBOL_user_id
    LI_SYMBOL(user_id)
#endif


#endif // LITHIUM_SINGLE_HEADER_GUARD_LI_HTTP_BACKEND_SYMBOLS


#ifndef LITHIUM_SINGLE_HEADER_GUARD_LI_SQL_SYMBOLS
#define LITHIUM_SINGLE_HEADER_GUARD_LI_SQL_SYMBOLS

#ifndef LI_SYMBOL_after_insert
#define LI_SYMBOL_after_insert
    LI_SYMBOL(after_insert)
#endif

#ifndef LI_SYMBOL_after_remove
#define LI_SYMBOL_after_remove
    LI_SYMBOL(after_remove)
#endif

#ifndef LI_SYMBOL_after_update
#define LI_SYMBOL_after_update
    LI_SYMBOL(after_update)
#endif

#ifndef LI_SYMBOL_auto_increment
#define LI_SYMBOL_auto_increment
    LI_SYMBOL(auto_increment)
#endif

#ifndef LI_SYMBOL_before_insert
#define LI_SYMBOL_before_insert
    LI_SYMBOL(before_insert)
#endif

#ifndef LI_SYMBOL_before_remove
#define LI_SYMBOL_before_remove
    LI_SYMBOL(before_remove)
#endif

#ifndef LI_SYMBOL_before_update
#define LI_SYMBOL_before_update
    LI_SYMBOL(before_update)
#endif

#ifndef LI_SYMBOL_charset
#define LI_SYMBOL_charset
    LI_SYMBOL(charset)
#endif

#ifndef LI_SYMBOL_computed
#define LI_SYMBOL_computed
    LI_SYMBOL(computed)
#endif

#ifndef LI_SYMBOL_database
#define LI_SYMBOL_database
    LI_SYMBOL(database)
#endif

#ifndef LI_SYMBOL_host
#define LI_SYMBOL_host
    LI_SYMBOL(host)
#endif

#ifndef LI_SYMBOL_password
#define LI_SYMBOL_password
    LI_SYMBOL(password)
#endif

#ifndef LI_SYMBOL_port
#define LI_SYMBOL_port
    LI_SYMBOL(port)
#endif

#ifndef LI_SYMBOL_primary_key
#define LI_SYMBOL_primary_key
    LI_SYMBOL(primary_key)
#endif

#ifndef LI_SYMBOL_read_access
#define LI_SYMBOL_read_access
    LI_SYMBOL(read_access)
#endif

#ifndef LI_SYMBOL_read_only
#define LI_SYMBOL_read_only
    LI_SYMBOL(read_only)
#endif

#ifndef LI_SYMBOL_synchronous
#define LI_SYMBOL_synchronous
    LI_SYMBOL(synchronous)
#endif

#ifndef LI_SYMBOL_user
#define LI_SYMBOL_user
    LI_SYMBOL(user)
#endif

#ifndef LI_SYMBOL_validate
#define LI_SYMBOL_validate
    LI_SYMBOL(validate)
#endif

#ifndef LI_SYMBOL_write_access
#define LI_SYMBOL_write_access
    LI_SYMBOL(write_access)
#endif


#endif // LITHIUM_SINGLE_HEADER_GUARD_LI_SQL_SYMBOLS


namespace li {

struct sqlite_connection;
struct mysql_connection;

using s::auto_increment;
using s::primary_key;
using s::read_only;

template <typename SCHEMA, typename C> struct sql_orm {

  typedef decltype(std::declval<SCHEMA>().all_fields()) O;
  typedef O object_type;

  sql_orm(SCHEMA& schema, C con) : schema_(schema), con_(con) {}

  template <typename S, typename... A> void call_callback(S s, A&&... args) {
    if constexpr(has_key<decltype(schema_.get_callbacks())>(S{}))
      return schema_.get_callbacks()[s](args...);
  }

  inline auto drop_table_if_exists() {
    con_(std::string("DROP TABLE IF EXISTS ") + schema_.table_name());
    return *this;
  }

  inline auto create_table_if_not_exists() {
    std::stringstream ss;
    ss << "CREATE TABLE if not exists " << schema_.table_name() << " (";

    bool first = true;
    li::tuple_map(schema_.all_info(), [&](auto f) {
      auto f2 = schema_.get_field(f);
      typedef decltype(f) F;
      typedef decltype(f2) F2;
      typedef typename F2::left_t K;
      typedef typename F2::right_t V;

      bool auto_increment = SCHEMA::template is_auto_increment<F>::value;
      bool primary_key = SCHEMA::template is_primary_key<F>::value;
      K k{};
      V v{};

      if (!first)
        ss << ", ";
      ss << li::symbol_string(k) << " " << con_.type_to_string(v);

      if (std::is_same<C, sqlite_connection>::value) {
        if (auto_increment || primary_key)
          ss << " PRIMARY KEY ";
      }

      if (std::is_same<C, mysql_connection>::value) {
        if (auto_increment)
          ss << " AUTO_INCREMENT NOT NULL";
        if (primary_key)
          ss << " PRIMARY KEY ";
      }

      // To activate when pgsql_connection is implemented.
      // if (std::is_same<C, pgsql_connection>::value and
      //     m.attributes().has(s::auto_increment))
      //   ss << " SERIAL ";

      first = false;
    });
    ss << ");";
    try {
      con_(ss.str())();
    } catch (std::exception e) {
      std::cerr << "Warning: Silicon could not create the " << schema_.table_name() << " sql table."
                << std::endl
                << "You can ignore this message if the table already exists."
                << "The sql error is: " << e.what() << std::endl;
    }
    return *this;
  }

  template <typename W>
  void where_clause(W&& cond, std::stringstream& ss)
  {
    ss << " WHERE ";
    bool first = true;
    map(cond, [&](auto k, auto v) {
      if (!first)
        ss << " and ";
      first = false;
      ss << li::symbol_string(k) << " = ? ";
    });
    ss << " ";
  }

  template <typename... W, typename... A> auto find_one(metamap<W...> where, A&&... cb_args) {
    std::stringstream ss;
    O o;
    ss << "SELECT ";
    bool first = true;
    li::map(o, [&](auto k, auto v) {
      if (!first)
        ss << ",";
      first = false;
      ss << li::symbol_string(k);
    });

    ss << " FROM " << schema_.table_name();
    where_clause(where, ss);
    ss << "LIMIT 1";
    auto stmt = con_.prepare(ss.str());

    auto res = li::tuple_reduce(metamap_values(where), stmt).template read_optional<O>();
    if (res)
      call_callback(s::read_access, o, cb_args...);
    return res;
  }

  template <typename A, typename B, typename... O, typename... W>
  auto find_one(metamap<O...>&& o, assign_exp<A, B> w1, W... ws) {
    return find_one(cat(o, mmm(w1)), ws...);
  }
  template <typename A, typename B, typename... W>
  auto find_one(assign_exp<A, B> w1, W... ws) {
    return find_one(mmm(w1), ws...);
  }

  template <typename W>
  bool exists(W&& cond)
  {
    std::stringstream ss;
    O o;
    ss << "SELECT count(*) FROM " << schema_.table_name();
    where_clause(cond, ss);
    ss << "LIMIT 1";

    auto stmt = con_.prepare(ss.str());

    return li::tuple_reduce(metamap_values(cond), stmt).template read<int>();
  }

  template <typename A, typename B, typename... W>
  auto exists(assign_exp<A, B> w1, W... ws) {
    return exists(mmm(w1, ws...));
  }
  // Save a ll fields except auto increment.
  // The db will automatically fill auto increment keys.
  template <typename N, typename... A> long long int insert(N&& o, A&&... cb_args) {
    std::stringstream ss;
    std::stringstream vs;

    auto values = schema_.without_auto_increment();
    map(o, [&](auto k, auto& v) { values[k] = o[k]; });
    // auto values = intersection(o, schema_.without_auto_increment());
    
    call_callback(s::validate, values, cb_args...);
    call_callback(s::before_insert, values, cb_args...);
    ss << "INSERT into " << schema_.table_name() << "(";

    bool first = true;
    li::map(values, [&](auto k, auto v) {
      if (!first) {
        ss << ",";
        vs << ",";
      }
      first = false;
      ss << li::symbol_string(k);
      vs << "?";
    });


    ss << ") VALUES (" << vs.str() << ")";
    auto req = con_.prepare(ss.str());
    li::reduce(values, req);

    call_callback(s::after_insert, o, cb_args...);

    return req.last_insert_id();
  };
  template <typename A, typename B, typename... O, typename... W>
  long long int insert(metamap<O...>&& o, assign_exp<A, B> w1, W... ws) {
    return insert(cat(o, mmm(w1)), ws...);
  }
  template <typename A, typename B, typename... W>
  long long int insert(assign_exp<A, B> w1, W... ws) {
    return insert(mmm(w1), ws...);
  }

  // template <typename S, typename V, typename... A>
  // long long int insert(const assign_exp<S, V>& a, A&&... tail) {
  //   auto m = mmm(a, tail...);
  //   return insert(m);
  // }

  // Iterate on all the rows of the table.
  template <typename F> void forall(F f) {
    std::stringstream ss;
    ss << "SELECT * from " << schema_.table_name();
    con_(ss.str()).map([&](decltype(schema_.all_fields()) o) { f(o); });
  }

  // Update N's members except auto increment members.
  // N must have at least one primary key.
  template <typename N, typename... CB> void update(const N& o, CB&&... args) {
    // check if N has at least one member of PKS.

    call_callback(s::validate, o, args...);
    call_callback(s::write_access, o, args...);
    call_callback(s::before_update, o, args...);

    // static_assert(metamap_size<decltype(intersect(o, schema_.read_only()))>(),
    //"You cannot give read only fields to the orm update method.");

    auto pk = intersection(o, schema_.primary_key());
    static_assert(metamap_size<decltype(pk)>() > 0,
                  "You must provide at least one primary key to update an object.");
    std::stringstream ss;
    ss << "UPDATE " << schema_.table_name() << " SET ";

    bool first = true;
    auto to_update = substract(o, schema_.read_only());

    map(to_update, [&](auto k, auto v) {
      if (!first)
        ss << ",";
      first = false;
      ss << li::symbol_string(k) << " = ?";
    });

    where_clause(pk, ss);

    auto stmt = con_.prepare(ss.str());
    li::tuple_reduce(std::tuple_cat(metamap_values(to_update), metamap_values(pk)), stmt);

    call_callback(s::after_update, o, args...);
  }

  template <typename A, typename B, typename... O, typename... W>
  void update(metamap<O...>&& o, assign_exp<A, B> w1, W... ws) {
    return update(cat(o, mmm(w1)), ws...);
  }
  template <typename A, typename B, typename... W>
  void update(assign_exp<A, B> w1, W... ws) {
    return update(mmm(w1), ws...);
  }

  inline int count() {
    return con_(std::string("SELECT count(*) from ") + schema_.table_name()).template read<int>();
  }

  template <typename N, typename... CB> void remove(const N& o, CB&&... args) {

    call_callback(s::before_remove, o, args...);

    std::stringstream ss;
    ss << "DELETE from " << schema_.table_name() << " WHERE ";

    bool first = true;
    map(schema_.primary_key(), [&](auto k, auto v) {
      if (!first)
        ss << " and ";
      first = false;
      ss << li::symbol_string(k) << " = ? ";
    });

    auto pks = intersection(o, schema_.primary_key());
    li::reduce(pks, con_.prepare(ss.str()));

    call_callback(s::after_remove, o, args...);
  }
  template <typename A, typename B, typename... O, typename... W>
  void remove(metamap<O...>&& o, assign_exp<A, B> w1, W... ws) {
    return remove(cat(o, mmm(w1)), ws...);
  }
  template <typename A, typename B, typename... W>
  void remove(assign_exp<A, B> w1, W... ws) {
    return remove(mmm(w1), ws...);
  }

  auto& schema() { return schema_; }

  SCHEMA schema_;
  C con_;
};

template <typename... F> struct orm_fields {

  orm_fields(F... fields) : fields_(fields...) {
    static_assert(sizeof...(F) == 0 || metamap_size<decltype(this->primary_key())>() != 0,
                  "You must give at least one primary key to the ORM. Use "
                  "s::your_field_name(s::primary_key) to add a primary_key");
  }

  // Field extractor.
  template <typename M> auto get_field(M m) { return m; }
  template <typename M, typename T> 
  auto get_field(assign_exp<M, T> e) { return e; }
  template <typename M, typename T, typename... A> 
  auto get_field(assign_exp<function_call_exp<M, A...>, T> e) { return assign_exp<M, T>{M{}, e.right}; }

  // template <typename M> struct get_field { typedef M ret; };
  // template <typename M, typename T> struct get_field<assign_exp<M, T>> {
  //   typedef assign_exp<M, T> ret;
  //   static auto ctor() { return assign_exp<M, T>{M{}, T()}; }
  // };
  // template <typename M, typename T, typename... A>
  // struct get_field<assign_exp<function_call_exp<M, A...>, T>> : public get_field<assign_exp<M, T>> {
  // };

//get_field<E>::ctor();
// field attributes checks.
#define CHECK_FIELD_ATTR(ATTR)                                                                     \
  template <typename M> struct is_##ATTR : std::false_type {};                                     \
  template <typename M, typename T, typename... A>                                                 \
  struct is_##ATTR<assign_exp<function_call_exp<M, A...>, T>>                                      \
      : std::disjunction<std::is_same<std::decay_t<A>, s::ATTR##_t>...> {};                        \
                                                                                                   \
  auto ATTR() {                                                                                    \
    return tuple_map_reduce(fields_,                                                               \
                            [this](auto e) {                                                           \
                              typedef std::remove_reference_t<decltype(e)> E;                      \
                              if constexpr (is_##ATTR<E>::value)                                   \
                                return get_field(e);                                       \
                              else                                                                 \
                                return skip{};                                                     \
                            },                                                                     \
                            make_metamap_skip);                                                    \
  }

  CHECK_FIELD_ATTR(primary_key); 
  CHECK_FIELD_ATTR(read_only);
  CHECK_FIELD_ATTR(auto_increment);
  CHECK_FIELD_ATTR(computed);
#undef CHECK_FIELD_ATTR

  // Do not remove this comment, this is used by the symbol generation.
  // s::primary_key s::read_only s::auto_increment s::computed 

  auto all_info() { return fields_; }

  auto all_fields() {

    return tuple_map_reduce(fields_,
                            [this](auto e) {
                              //typedef std::remove_reference_t<decltype(e)> E;
                              return get_field(e);
                            },
                            [](auto... e) { return mmm(e...); });
  }

  auto without_auto_increment() { return substract(all_fields(), auto_increment()); }
  auto all_fields_except_computed() { return substract(substract(all_fields(), computed()),
                                                       auto_increment()); }

  std::tuple<F...> fields_;
};

template <typename DB, typename MD = orm_fields<>, typename CB = decltype(mmm())>
struct sql_orm_schema : public MD {

  sql_orm_schema(DB& db, const std::string& table_name, CB cb = CB(), MD md = MD())
      : MD(md), database_(db), table_name_(table_name), callbacks_(cb) {}

  inline auto connect() { return sql_orm(*this, database_.connect()); }

  const std::string& table_name() const { return table_name_; }
  auto get_callbacks() const { return callbacks_; }

  template <typename... P> auto callbacks(P... params_list) const {
    auto cbs = mmm(params_list...);
    auto allowed_callbacks = mmm(s::before_insert, s::before_remove, s::before_update,
                                 s::after_insert, s::after_remove, s::after_update, s::validate);

    static_assert(metamap_size<decltype(substract(cbs, allowed_callbacks))>() == 0, 
    "The only supported callbacks are: s::before_insert, s::before_remove, s::before_update,"
    " s::after_insert, s::after_remove, s::after_update, s::validate");
    return sql_orm_schema<DB, MD, decltype(cbs)>(database_, table_name_, cbs, *static_cast<const MD*>(this));
  }

  template <typename... P> auto fields(P... p) const {
    return sql_orm_schema<DB, orm_fields<P...>, CB>(database_, table_name_, callbacks_, orm_fields<P...>(p...));
  }

  DB& database_;
  std::string table_name_;
  CB callbacks_;
};

}; // namespace li

#endif // LITHIUM_SINGLE_HEADER_GUARD_LI_SQL_SQL_ORM

#ifndef LITHIUM_SINGLE_HEADER_GUARD_LI_JSON_JSON
#define LITHIUM_SINGLE_HEADER_GUARD_LI_JSON_JSON


#ifndef LITHIUM_SINGLE_HEADER_GUARD_LI_JSON_DECODER
#define LITHIUM_SINGLE_HEADER_GUARD_LI_JSON_DECODER

#ifndef LITHIUM_SINGLE_HEADER_GUARD_LI_JSON_UTILS
#define LITHIUM_SINGLE_HEADER_GUARD_LI_JSON_UTILS


#ifndef LITHIUM_SINGLE_HEADER_GUARD_LI_JSON_SYMBOLS
#define LITHIUM_SINGLE_HEADER_GUARD_LI_JSON_SYMBOLS

#ifndef LI_SYMBOL_append
#define LI_SYMBOL_append
    LI_SYMBOL(append)
#endif

#ifndef LI_SYMBOL_json_key
#define LI_SYMBOL_json_key
    LI_SYMBOL(json_key)
#endif

#ifndef LI_SYMBOL_name
#define LI_SYMBOL_name
    LI_SYMBOL(name)
#endif

#ifndef LI_SYMBOL_type
#define LI_SYMBOL_type
    LI_SYMBOL(type)
#endif


#endif // LITHIUM_SINGLE_HEADER_GUARD_LI_JSON_SYMBOLS


namespace li {


  
  
  
  
  
  template <typename T>
  struct json_object_base;
  
  template <typename T>    struct json_object_;
  template <typename T>    struct json_vector_;
  template <typename V>    struct json_value_;
  template <typename... T> struct json_tuple_;
  struct json_key;
  
  namespace impl
  {
    template <typename S, typename... A>
    auto make_json_object_member(const function_call_exp<S, A...>& e);
    template <typename S>
    auto make_json_object_member(const li::symbol<S>&);

    template <typename S, typename T>
    auto make_json_object_member(const assign_exp<S, T>& e)
    {
      return cat(make_json_object_member(e.left),
                 mmm(s::type = e.right));
    }

    template <typename S>
    auto make_json_object_member(const li::symbol<S>&)
    {
      return mmm(s::name = S{});
    }

    template <typename V>
    auto to_json_schema(V v)
    {
      return json_value_<V>{};
    }

    template <typename... M>
    auto to_json_schema(const metamap<M...>& m);
    
    template <typename V>
    auto to_json_schema(const std::vector<V>& arr)
    {
      auto elt = to_json_schema(decltype(arr[0]){});
      return json_vector_<decltype(elt)>{elt};
    }
    
    template <typename... V>
    auto to_json_schema(const std::tuple<V...>& arr)
    {
      return json_tuple_<decltype(to_json_schema(V{}))...>(to_json_schema(V{})...);
    }

    template <typename... M>
    auto to_json_schema(const metamap<M...>& m)
    {
      auto tuple_maker = [] (auto&&... t) { return std::make_tuple(std::forward<decltype(t)>(t)...); };

      auto entities = map_reduce(m, [] (auto k, auto v) {
          return mmm(s::name = k, s::type = to_json_schema(v));
        }, tuple_maker);


      return json_object_<decltype(entities)>(entities);
    }

    
    template <typename... E>
    auto json_object_to_metamap(const json_object_<std::tuple<E...>>& s)
    {
      auto make_kvs = [] (auto... elt)
        {
          return std::make_tuple((elt.name = elt.type)...);
        };

      auto kvs = std::apply(make_kvs, s.entities);
      return std::apply(mmm, kvs);
    }

    template <typename S, typename... A>
    auto make_json_object_member(const function_call_exp<S, A...>& e)
    {
      auto res = mmm(s::name = e.method, s::json_key = symbol_string(e.method));

      auto parse = [&] (auto a)
        {
          if constexpr(std::is_same<decltype(a), json_key>::value) {
              res.json_key = a.key;
            }
        };

      ::li::tuple_map(e.args, parse);
      return res;
    }
    
  }

  template <typename T>
  struct json_object_;

  template <typename O>
  struct json_vector_;
  

  template <typename E> constexpr auto json_is_vector(json_vector_<E>) ->  std::true_type { return {}; }
  template <typename E> constexpr auto json_is_vector(E) ->  std::false_type { return {}; }

  template <typename... E> constexpr auto json_is_tuple(json_tuple_<E...>) ->  std::true_type { return {}; }
  template <typename E> constexpr auto json_is_tuple(E) ->  std::false_type { return {}; }
  
  template <typename E> constexpr auto json_is_object(json_object_<E>) ->  std::true_type { return {}; }
  template <typename E> constexpr auto json_is_object(E) ->  std::false_type { return {}; }

  template <typename E> constexpr auto json_is_value(json_object_<E>) ->  std::false_type { return {}; }
  template <typename E> constexpr auto json_is_value(json_vector_<E>) ->  std::false_type { return {}; }
  template <typename... E> constexpr auto json_is_value(json_tuple_<E...>) ->  std::false_type { return {}; }
  template <typename E> constexpr auto json_is_value(E) ->  std::true_type { return {}; }


  template <typename T>
  constexpr auto is_std_optional(std::optional<T>) -> std::true_type;
  template <typename T>
  constexpr auto is_std_optional(T) -> std::false_type;
  
}

#endif // LITHIUM_SINGLE_HEADER_GUARD_LI_JSON_UTILS

#ifndef LITHIUM_SINGLE_HEADER_GUARD_LI_JSON_UNICODE
#define LITHIUM_SINGLE_HEADER_GUARD_LI_JSON_UNICODE



#ifndef LITHIUM_SINGLE_HEADER_GUARD_LI_JSON_DECODE_STRINGSTREAM
#define LITHIUM_SINGLE_HEADER_GUARD_LI_JSON_DECODE_STRINGSTREAM


namespace li {

  using std::string_view;
  
  namespace internal
  {
    template <typename I>
    void parse_uint(I* val_, const char* str, const char** end)
    {
      I& val = *val_;
      val = 0;
      int i = 0;
      while (i < 40)
      {
        char c = *str;
        if (c < '0' or c > '9') break;
        val = val * 10 + c - '0';
        str++;
        i++;
      }
      if (end)
        *end = str;
    }

    template <typename I>
    void parse_int(I* val, const char* str, const char** end)
    {
      bool neg = false;

      if (str[0] == '-')
      {
        neg = true;
        str++;
      }
      parse_uint(val, str, end);
      if constexpr (!std::is_same<I, bool>::value)
      {
        if (neg)
          *val = -(*val);
      }
    }

    inline unsigned long long pow10(unsigned int e)
    {
      unsigned long long pows[] = {
        1,
        10,
        100,
        1000,
        10000,
        100000,
        1000000,
        10000000,
        100000000,
        1000000000,
        10000000000,
        100000000000,
        1000000000000,
        10000000000000,
        100000000000000,
        1000000000000000,
        10000000000000000,
        100000000000000000
      };

      if (e < 18)
        return pows[e];
      else
        return 0;
    }
    
    template <typename F>
    void parse_float(F* f, const char* str, const char** end)
    {
      // 1.234e-10
      // [sign][int][decimal_part][exp]

      const char* it = str;
      int integer_part;
      parse_int(&integer_part, it, &it);
      int sign = integer_part >= 0 ? 1 : -1;
      *f = integer_part;
      if (*it == '.')
      {
        it++;
        unsigned long long decimal_part;
        const char* dec_end;
        parse_uint(&decimal_part, it, &dec_end);

        if (dec_end > it)
          *f += (F(decimal_part) / pow10(dec_end - it)) * sign;

        it = dec_end;
      }

      if (*it == 'e' || *it == 'E')
      {
        it++;
        bool neg = false;
        if (*it == '-')
        {
          neg = true;
          it++;
        }

        unsigned int exp = 0;
        parse_uint(&exp, it, &it);
        if (neg)
          *f = *f / pow10(exp);
        else
          *f = *f * pow10(exp);
      }
      
      if (end)
        *end = it;

    }
    
  }

  class decode_stringstream
  {
  public:

    inline decode_stringstream(string_view buffer_)
      : cur(buffer_.data()),
        bad_(false),
        buffer(buffer_) {}
    
    inline bool eof() const { return cur >= &buffer.back(); }
    inline const char peek() const { return *cur; }
    inline int get()        { return *(cur++); }
    inline int bad() const  { return bad_; }

    template <typename T>
    void operator>>(T& value)
      {
        eat_spaces();
        if constexpr(std::is_floating_point<T>::value) {
            // Decode floating point.
            eat_spaces();
            const char* end = nullptr;
            internal::parse_float(&value, cur, &end);
            if (end == cur)
              bad_ = true;
            cur = end;
          }
        else if constexpr (std::is_integral<T>::value) {
            // Decode integer.
            const char* end = nullptr;
            internal::parse_int(&value, cur, &end);
            if (end == cur)
              bad_ = true;
            cur = end;
          }
        else if constexpr (std::is_same<T, std::string>::value) {
            // Decode UTF8 string.
            json_to_utf8(*this, value);
          }
        else if constexpr (std::is_same<T, string_view>::value) {
            // Decoding to stringview does not decode utf8.

            if (get() != '"')
            {
              bad_ = true;
              return;
            }

            const char* start = cur;
            bool escaped = false;
            
            while (peek() != '\0' and (escaped or peek() != '"'))
            {
              int nb = 0;
              while (peek() == '\\')
                nb++;

              escaped = nb % 2;
              cur++;
            }
            const char* end = cur;
            value = string_view(start, end - start);

            if (get() != '"')
            {
              bad_ = true;
              return;
            }
            
          }
      }

  private:

    inline void eat_spaces()
      {
        while (peek() < 33) ++cur;
      }
    
    int bad_;
    const char* cur;
    string_view buffer; //
  };

}

#endif // LITHIUM_SINGLE_HEADER_GUARD_LI_JSON_DECODE_STRINGSTREAM


#ifndef LITHIUM_SINGLE_HEADER_GUARD_LI_JSON_ERROR
#define LITHIUM_SINGLE_HEADER_GUARD_LI_JSON_ERROR


namespace li {


  enum json_error_code
  {
    JSON_OK = 0,
    JSON_KO = 1
  };
    
  struct json_error
  {
    json_error& operator=(const json_error&) = default;
    operator bool() { return code != 0; }
    bool good() { return code == 0; }
    bool bad() { return code != 0; }
    int code;
    std::string what;
  };

  int make_json_error(const char* what) { return 1; }
  int json_no_error() { return 0; }

  static int json_ok = json_no_error();

}

#endif // LITHIUM_SINGLE_HEADER_GUARD_LI_JSON_ERROR


namespace li {

  
  
  template <typename O>
  inline decltype(auto) wrap_json_output_stream(O&& s)
  {
    return mmm(s::append = [&s] (char c) { s << c; });
  }
  
  inline decltype(auto) wrap_json_output_stream(std::stringstream& s)
  {
    return mmm(s::append = [&s] (char c) { s << c; });
  }

  inline decltype(auto) wrap_json_output_stream(std::string& s)
  {
    return mmm(s::append = [&s] (char c) { s.append(1, c); });
  }

  inline decltype(auto)
  wrap_json_input_stream(std::stringstream& s) { return s; }
  inline decltype(auto)
  wrap_json_input_stream(decode_stringstream& s) { return s; }
  inline decltype(auto)
  wrap_json_input_stream(const std::string& s) { return std::stringstream(s); }
  inline decltype(auto)
  wrap_json_input_stream(const char* s) { return std::stringstream(std::string(s)); }
  inline decltype(auto)
  wrap_json_input_stream(const std::string_view& s) { return std::stringstream(std::string(s)); }

  namespace unicode_impl
  {
    template <typename S, typename T>
    auto json_to_utf8(S&& s, T&& o);

    template <typename S, typename T>
    auto utf8_to_json(S&& s, T&& o);
  }
  
  template <typename I, typename O>
  auto json_to_utf8(I&& i, O&& o)
  {
    return unicode_impl::json_to_utf8(wrap_json_input_stream(std::forward<I>(i)),
                                      wrap_json_output_stream(std::forward<O>(o)));
  }

  template <typename I, typename O>
  auto utf8_to_json(I&& i, O&& o)
  {
    return unicode_impl::utf8_to_json(wrap_json_input_stream(std::forward<I>(i)),
                              wrap_json_output_stream(std::forward<O>(o)));
  }
  
  enum json_encodings
    {
      UTF32BE,
      UTF32LE,
      UTF16BE,
      UTF16LE,
      UTF8
    };

  // Detection of encoding depending on the pattern of the
  // first fourth characters.
  auto detect_encoding(char a, char b, char c, char d)
  {
    // 00 00 00 xx  UTF-32BE
    // xx 00 00 00  UTF-32LE
    // 00 xx 00 xx  UTF-16BE
    // xx 00 xx 00  UTF-16LE
    // xx xx xx xx  UTF-8

    if (a == 0 and b == 0) return UTF32BE;
    else if (c == 0 and d == 0) return UTF32LE;
    else if (a == 0) return UTF16BE;
    else if (b == 0) return UTF16LE;
    else return UTF8;
  }

  // The JSON RFC escapes character codepoints prefixed with a \uXXXX (7-11 bits codepoints)
  // or \uXXXX\uXXXX (20 bits codepoints)

  // uft8 string have 4 kinds of character representation encoding the codepoint of the character.
    
  // 1 byte : 0xxxxxxx  -> 7 bits codepoint ASCII chars from 0x00 to 0x7F
  // 2 bytes: 110xxxxx 10xxxxxx -> 11 bits codepoint
  // 3 bytes: 1110xxxx 10xxxxxx 10xxxxxx -> 11 bits codepoint

  // 1 and 3 bytes representation are escaped as \uXXXX with X a char in the 0-9A-F range. It
  // is possible since the codepoint is less than 16 bits.

  // the 4 bytes representation uses the UTF-16 surrogate pair (high and low surrogate).

  // The high surrogate is in the 0xD800..0xDBFF range (HR) and
  // the low surrogate is in the 0xDC00..0xDFFF range (LR).

  // to encode a given 20bits codepoint c to the surrogate pair.
  //  - substract 0x10000 to c
  //  - separate the result in a high (first 10 bits) and low (last 10bits) surrogate.
  //  - Add 0xD800 to the high surrogate
  //  - Add 0xDC00 to the low surrogate
  //  - the 32 bits code is (high << 16) + low.

  // and to json-escape the high-low(H-L) surrogates representation (16+16bits):
  //  - Check that H and L are respectively in the HR and LR ranges.
  //  - add to H-L 0x0001_0000 - 0xD800_DC00 to get the 20bits codepoint c.
  //  - Encode the codepoint in a string of \uXXXX\uYYYY with X and Y the respective hex digits
  //    of the high and low sequence of 10 bits.
    
  // In addition to utf8, JSON escape characters ( " \ / ) with a backslash and translate
  // \n \r \t \b \r in their matching two characters string, for example '\n' to  '\' followed by 'n'.

  namespace unicode_impl
  {
    template <typename S, typename T>
    auto json_to_utf8(S&& s, T&& o)
    {
      // Convert a JSON string into an UTF-8 string.
      if (s.get() != '"')
        return JSON_KO;//make_json_error("json_to_utf8: JSON strings should start with a double quote.");
      
      while (true)
      {
        // Copy until we find the escaping backslash or the end of the string (double quote).
        while (s.peek() != EOF and s.peek() != '"' and s.peek() != '\\')
          o.append(s.get());

        // If eof found before the end of the string, return an error.
        if (s.eof()) return JSON_KO;// make_json_error("json_to_utf8: Unexpected end of string when parsing a string.");

        // If end of json string, return
        if (s.peek() == '"')
        {
          break;
          return JSON_OK;
        }

        // Get the '\'.
        assert(s.peek() ==  '\\');
        s.get();

        switch (s.get())
        {
          // List of escaped char from http://www.json.org/ 
        default:
          return JSON_KO;//make_json_error("json_to_utf8: Bad JSON escaped character.");
        case '"': o.append('"'); break;
        case '\\': o.append('\\'); break;
        case '/': o.append('/'); break;
        case 'n': o.append('\n'); break;
        case 'r': o.append('\r'); break;
        case 't': o.append('\t'); break;
        case 'b': o.append('\b'); break;
        case 'f': o.append('\f'); break;
        case 'u':
          char a,b,c,d;

          a = s.get();
          b = s.get();
          c = s.get();
          d = s.get();

          if (s.eof())
            return JSON_KO;//make_json_error("json_to_utf8: Unexpected end of string when decoding an utf8 character");

          auto decode_hex_c = [] (char c) {
            if (c >= '0' and c <= '9') return c - '0';
            else return (10 + std::toupper(c) - 'A');
          };
              
          uint16_t x =
            (decode_hex_c(a) << 12) +
            (decode_hex_c(b) << 8) +
            (decode_hex_c(c) << 4) +
            decode_hex_c(d);

          // If x in the  0xD800..0xDBFF range -> decode a surrogate pair \uXXXX\uYYYY -> 20 bits codepoint.
          if (x >= 0xD800 and x <= 0xDBFF)
          {
            if (s.get() != '\\' or s.get() != 'u')
              return JSON_KO;//make_json_error("json_to_utf8: Missing low surrogate.");
          
            uint16_t y =
              (decode_hex_c(s.get()) << 12) +
              (decode_hex_c(s.get()) << 8) +
              (decode_hex_c(s.get()) << 4) +
              decode_hex_c(s.get());

            if (s.eof())
              return JSON_KO;//make_json_error("json_to_utf8: Unexpected end of string when decoding an utf8 character");

            x -= 0xD800;
            y -= 0xDC00;

            int cp = (x << 10) + y + 0x10000;

            o.append(0b11110000 | (cp >> 18));
            o.append(0b10000000 | ((cp & 0x3F000) >> 12));
            o.append(0b10000000 | ((cp & 0x00FC0) >> 6));
            o.append(0b10000000 | (cp & 0x003F));
          
          }
          // else encode the codepoint with the 1-2, or 3 bytes utf8 representation.
          else
          {
            if (x <= 0x007F) // 7bits codepoints, ASCII 0xxxxxxx.
            {
              o.append(uint8_t(x));
            }
            else if (x >= 0x0080 and x <= 0x07FF) // 11bits codepoint -> 110xxxxx 10xxxxxx
            {
              o.append(0b11000000 | (x >> 6));
              o.append(0b10000000 | (x & 0x003F));
            }
            else if (x >= 0x0800 and x <= 0xFFFF) //16bits codepoint -> 1110xxxx 10xxxxxx 10xxxxxx
            {
              o.append(0b11100000 | (x >> 12));
              o.append(0b10000000 | ((x & 0x0FC0) >> 6));
              o.append(0b10000000 | (x & 0x003F));
            }
            else
              return JSON_KO;//make_json_error("json_to_utf8: Bad UTF8 codepoint.");            
          }
          break;
        }
      }

      if (s.get() != '"')
        return JSON_KO;//make_json_error("JSON strings must end with a double quote.");
    
      return JSON_OK;//json_no_error();
    }

    template <typename S, typename T>
    auto utf8_to_json(S&& s, T&& o)
    {
      o.append('"');

      auto encode_16bits = [&] (uint16_t b)
        {
          const char lt[] = "0123456789ABCDEF";
          o.append(lt[b >> 12]);
          o.append(lt[(b & 0x0F00) >> 8]);
          o.append(lt[(b & 0x00F0) >> 4]);
          o.append(lt[b & 0x000F]);
        };

      while (!s.eof())
      {
        // 7-bits codepoint
        while (s.good() and s.peek() <= 0x7F and s.peek() != EOF)
        {
          switch (s.peek())
          {
          case '"': o.append('\\'); o.append('"'); break;
          case '\\': o.append('\\'); o.append('\\'); break;
            //case '/': o.append('/'); break; Do not escape /
          case '\n': o.append('\\'); o.append('n'); break;
          case '\r': o.append('\\'); o.append('r'); break;
          case '\t': o.append('\\'); o.append('t'); break;
          case '\b': o.append('\\'); o.append('b'); break;
          case '\f': o.append('\\'); o.append('f'); break;
          default:
            o.append(s.peek());
          }
          s.get();
        }
      
        if (s.eof()) break;

        // uft8 prefix \u.
        o.append('\\');
        o.append('u');

        uint8_t c1 = s.get();
        uint8_t c2 = s.get();
        {        
          // extract codepoints.
          if (c1 < 0b11100000) // 11bits - 2 char: 110xxxxx	10xxxxxx
          {
            uint16_t cp = ((c1 & 0b00011111) << 6) +
              (c2 & 0b00111111);
            if (cp >= 0x0080 and cp <= 0x07FF)
              encode_16bits(cp);
            else
              return JSON_KO;//make_json_error("utf8_to_json: Bad UTF8 codepoint.");
          }
          else if (c1 < 0b11110000) // 16 bits - 3 char: 1110xxxx	10xxxxxx	10xxxxxx
          {
            uint16_t cp = ((c1 & 0b00001111) << 12) +
              ((c2 & 0b00111111) << 6) +
              (s.get() & 0b00111111);

            if (cp >= 0x0800 and cp <= 0xFFFF)
              encode_16bits(cp);
            else
              return JSON_KO;//make_json_error("utf8_to_json: Bad UTF8 codepoint.");          
          }
          else // 21 bits - 4 chars: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
          {
            int cp =
              ((c1 & 0b00000111) << 18) +
              ((c2 & 0b00111111) << 12) +
              ((s.get() & 0b00111111) << 6) +
              (s.get() & 0b00111111);

            cp -= 0x10000;

            uint16_t H = (cp >> 10) + 0xD800;
            uint16_t L = (cp & 0x03FF) + 0xDC00;

            // check if we are in the right range.
            // The high surrogate is in the 0xD800..0xDBFF range (HR) and
            // the low surrogate is in the 0xDC00..0xDFFF range (LR).
            assert(H >= 0xD800 and H <= 0xDBFF and
                   L >= 0xDC00 and L <= 0xDFFF);

            encode_16bits(H);
            o.append('\\');
            o.append('u');
            encode_16bits(L);
          }
          
        }
      }
      o.append('"');
      return JSON_OK;
    }
  }
}

#endif // LITHIUM_SINGLE_HEADER_GUARD_LI_JSON_UNICODE


namespace li {

  namespace impl
  {

    template <typename S>
    struct json_parser
    {
      inline json_parser(S&& s) : ss(s) {}
      inline json_parser(S& s) : ss(s) {}

      inline decltype(auto) peek() {
        return ss.peek();
      }
      inline decltype(auto) get() {
        return ss.get();
      }


      inline void skip_one() {
        ss.get();
      }
      
      inline bool eof() { return ss.eof(); }
      inline json_error_code eat(char c, bool skip_spaces = true) {
        if (skip_spaces)
          eat_spaces();

        char g = ss.get();
        if (g != c)
          return make_json_error("Unexpected char. Got '", char(g), "' expected ", c);
        return JSON_OK;
      }

      inline json_error_code eat(const char* str, bool skip_spaces = true) {
        if (skip_spaces)
          eat_spaces();

        const char* str_it = str;
        while (*str_it)
        {
          char g = ss.get();
          if (g != *str_it)
            return make_json_error("Unexpected char. Got '", char(g), "' expected '",
                                   *str_it, "' when parsing string ", str);
          str_it++;
        }
        return JSON_OK;
      }
      
      template <typename... T>
      inline json_error_code make_json_error(T&&... t)
      {
        if (!error_stream)
          error_stream = new std::stringstream();
        *error_stream << "json error: ";
        auto add = [this] (auto w) { *error_stream << w; };
        apply_each(add, t...);
        return JSON_KO;
      }
      inline void eat_spaces()
      {
        while (ss.peek() >= 0 and ss.peek() < 33) ss.get();
      }

      template <typename X>
      struct JSON_INVALID_TYPE;

      // Integers and floating points.
      template <typename T>
      json_error_code fill(T& t) {

        if constexpr(std::is_floating_point<T>::value or
                     std::is_integral<T>::value or
                     std::is_same<T, std::string_view>::value
          ) {
            ss >> t;
            if (ss.bad())
              return make_json_error("Ill-formated value.");
            return JSON_OK;
          }
        else
          // The JSON decoder only parses floating-point, integral and string types.
          return JSON_INVALID_TYPE<T>::error;
      }

      // Strings
      inline json_error_code fill(std::string& str)
      {
        eat_spaces();
        str.clear();
        return json_to_utf8(ss, str);
      }

      template <typename T>
      inline json_error_code fill(std::optional<T>& opt)
      {
        opt.emplace();
        return fill(opt.value());
      }

      template <typename... T>
      inline json_error_code fill(std::variant<T...>& v)
      {
        if (auto err = eat('{')) return err;
        if (auto err = eat("\"idx\"")) return err;
        if (auto err = eat(':')) return err;

        int idx = 0;
        fill(idx);
        if (auto err = eat(',')) return err;
        if (auto err = eat("\"value\"")) return err;
        if (auto err = eat(':')) return err;

        int cpt = 0;
        apply_each([&] (auto* x) {
            if (cpt == idx)
            {
              std::remove_pointer_t<decltype(x)> value{};
              fill(value);
              v = std::move(value);
            }
            cpt++;
          },
          (T*)nullptr...);

        if (auto err = eat('}')) return err;
        return JSON_OK;
      }
      
      S& ss;
      std::stringstream* error_stream = nullptr;
    };

    template <typename P, typename O, typename S>
    json_error_code json_decode2(P& p, O& obj, S)
    {
      auto err = p.fill(obj);
      if (err) return err;
      else
        return JSON_OK;
    }
    
    template <typename P, typename O, typename S>
    json_error_code json_decode2(P& p, O& obj, json_vector_<S> schema)
    {
      obj.clear();
      bool first = true;
      auto err = p.eat('[');
      if (err) return err;

      p.eat_spaces();
      while (p.peek() != ']')
      {
        if (!first)
        {
          if ((err = p.eat(','))) return err;
        }
        first = false;

        obj.resize(obj.size() + 1);
        if ((err = json_decode2(p, obj.back(), S{}))) return err;
        p.eat_spaces();
      }
      
      if ((err = p.eat(']'))) return err;
      else
        return JSON_OK;
    }

    template <typename F, typename... E, typename... T, std::size_t... I>
    inline void json_decode_tuple_elements(F& decode_fun,
                                           std::tuple<T...>& tu,
                                           const std::tuple<E...>& schema,
                                           std::index_sequence<I...>)
    {
      (void)std::initializer_list<int>{
        ((void)decode_fun(std::get<I>(tu), std::get<I>(schema)), 0)...};
    }
    
    template <typename P, typename... O, typename... S>
    json_error_code json_decode2(P& p, std::tuple<O...>& tu, json_tuple_<S...> schema)
    {
      bool first = true;
      auto err = p.eat('[');
      if (err) return err;

      auto decode_one_element = [&first,&p,&err] (auto& value, auto value_schema) {
        if (!first)
        {
          if ((err = p.eat(','))) return err;
        }
        first = false;
        if ((err = json_decode2(p, value, value_schema))) return err;
        p.eat_spaces();
        return JSON_OK;
      };
      
      json_decode_tuple_elements(decode_one_element, tu, schema.elements, std::make_index_sequence<sizeof...(O)>{});

      if ((err = p.eat(']'))) return err;
      else
        return JSON_OK;
    }
    
    template <typename P, typename O, typename S>
    json_error_code json_decode2(P& p, O& obj, json_object_<S> schema)
    {
      json_error_code err;
      if ((err = p.eat('{'))) return err;

      struct attr_info { bool filled; bool required; const char* name; int name_len; std::function<json_error_code(P&)> parse_value; };
      constexpr int n_members = std::tuple_size<decltype(schema.schema)>();
      attr_info A[n_members];
      int i = 0;
      auto prepare = [&] (auto m) {
        A[i].filled = false;
        A[i].required = true;
        A[i].name = symbol_string(m.name);
        A[i].name_len = strlen(symbol_string(m.name));

        if constexpr(has_key(m, s::json_key)) {
            A[i].name = m.json_key;
          }

        if constexpr(decltype(is_std_optional(symbol_member_or_getter_access(obj, m.name))){}) {
            A[i].required = false;
          }

        A[i].parse_value = [m,&obj] (P& p) {
          
          using V = decltype(symbol_member_or_getter_access(obj, m.name));
          using VS = decltype(get_or(m, s::type, json_value_<V>{}));
          
          if constexpr(decltype(json_is_value(VS{})){}) {
            if (auto err = p.fill(symbol_member_or_getter_access(obj, m.name))) return err;
            else return JSON_OK;
            }
          else {
              if (auto err = json_decode2(p, symbol_member_or_getter_access(obj, m.name), m.type)) return err;
              else return JSON_OK;
          }
        };

        i++;
      };

      std::apply([&] (auto... m) { apply_each(prepare, m...); },
                               schema.schema);

      while (p.peek() != '}')
      {

        bool found = false;
        if ((err = p.eat('"'))) return err;
        char symbol[50];
        int symbol_size = 0;
        while (!p.eof() and p.peek() != '"' and symbol_size < 50)
          symbol[symbol_size++] = p.get();
        symbol[symbol_size] = 0;
        if ((err = p.eat('"', false))) return err;
  
        for (int i = 0; i < n_members; i++)
        {
          int len = A[i].name_len;
          if (!strncmp(symbol, A[i].name, len))
          {
            if ((err = p.eat(':'))) return err;
            if (A[i].filled)
              return p.make_json_error("Duplicate json key: ", A[i].name);
            
            if ((err = A[i].parse_value(p))) return err;
            A[i].filled = true;
            found = true;
            break;
          }
        }
        
        if (!found)
          return p.make_json_error("Unknown json key");
        p.eat_spaces();
        if (p.peek() == ',')
        {
          if ((err = p.eat(','))) return err;
        }
      }
      if ((err = p.eat('}'))) return err;

      for (int i = 0; i < n_members; i++)
      {
        if (A[i].required and !A[i].filled)
          return p.make_json_error("Missing json key ", A[i].name);
      }
      return JSON_OK;
    }

    template <typename C, typename O, typename S>
    json_error json_decode(C& input, O& obj, S schema)
    {
      auto stream = decode_stringstream(input);
      json_parser<decode_stringstream> p(stream);
      if (json_decode2(p, obj, schema))
        return json_error{1, p.error_stream ? p.error_stream->str() : "Json error"};
      else
        return json_error{0};
    }

  }

}


#endif // LITHIUM_SINGLE_HEADER_GUARD_LI_JSON_DECODER

#ifndef LITHIUM_SINGLE_HEADER_GUARD_LI_JSON_ENCODER
#define LITHIUM_SINGLE_HEADER_GUARD_LI_JSON_ENCODER


namespace li {

  using std::string_view;

  template <typename... T>
  struct json_tuple_;
  template <typename T>
  struct json_object_;
  
  namespace impl
  {

    // Json encoder.
    // =============================================

    template <typename C, typename O, typename E>
    inline void json_encode(C& ss, O obj, const json_object_<E>& schema);
    template <typename C, typename... E, typename... T>
    inline void json_encode(C& ss, const std::tuple<T...>& tu, const json_tuple_<E...>& schema);
    template <typename T, typename C, typename E>
    inline void json_encode(C& ss, const T& value, const E& schema);
    template <typename T, typename C, typename E>
    inline void json_encode(C& ss, const std::vector<T>& array, const json_vector_<E>& schema);


    template <typename T, typename C>
    inline void json_encode_value(C& ss, const T& t) { ss << t; }
    
    template <typename C>
    inline void json_encode_value(C& ss, const char* s) { utf8_to_json(s, ss); }

    template <typename C>
    inline void json_encode_value(C& ss, const string_view& s) { utf8_to_json(s, ss); }
    
    template <typename C>
    inline void json_encode_value(C& ss, const std::string& s) { utf8_to_json(s, ss); }

    template <typename C, typename... T>
    inline void json_encode_value(C& ss, const metamap<T...>& s) { json_encode(ss, s, to_json_schema(s)); }

    template <typename T, typename C>
    inline void json_encode_value(C& ss, const std::optional<T>& t) {
      if (t.has_value())
        json_encode_value(ss, t.value());
    }

    template <typename C, typename... T>
    inline void json_encode_value(C& ss, const std::variant<T...>& t) {
      ss << "{\"idx\":" << t.index() << ",\"value\":";
      std::visit([&] (auto&& value) { json_encode_value(ss, value); },
                 t);      
      ss << '}';
    }
    
    template <typename C, typename O, typename E>
    inline void json_encode(C& ss, O obj, const json_object_<E>& schema);

    template <typename T, typename C, typename E>
    inline void json_encode(C& ss, const T& value, const E& schema)
    {
      json_encode_value(ss, value);
    }
    
    template <typename T, typename C, typename E>
    inline void json_encode(C& ss, const std::vector<T>& array, const json_vector_<E>& schema)
    {
      ss << '[';
      for (const auto& t : array)
      {
        if constexpr(decltype(json_is_vector(E{})){} or decltype(json_is_object(E{})){}) {
            json_encode(ss, t, schema.schema);
          }
        else
          json_encode_value(ss, t);
          
        if (&t != &array.back())
          ss << ',';
      }
      ss << ']';
    }

    template <typename F, typename... E, typename... T, std::size_t... I>
    inline void json_encode_tuple_elements(F& encode_fun,
                                           const std::tuple<T...>& tu,
                                           const std::tuple<E...>& schema,
                                           std::index_sequence<I...>)
    {
      (void)std::initializer_list<int>{
        ((void)encode_fun(std::get<I>(tu), std::get<I>(schema)), 0)...};
    }

    template <typename C, typename... E, typename... T>
    inline void json_encode(C& ss, const std::tuple<T...>& tu, const json_tuple_<E...>& schema)
    {
      ss << '[';
      bool first = true;
      auto encode_one_element = [&first,&ss] (auto value, auto value_schema) {
        if (!first)
          ss << ',';
        first = false;
        if constexpr(decltype(json_is_value(value_schema)){}) {
            json_encode_value(ss, value);
          }
        else
          json_encode(ss, value, value_schema);
      };

      json_encode_tuple_elements(encode_one_element, tu, schema.elements, std::make_index_sequence<sizeof...(T)>{});
      ss << ']';
    }
    
    template <typename C, typename O, typename E>
    inline void json_encode(C& ss, O obj, const json_object_<E>& schema)
    {
      ss << '{';
      bool first = true;

      auto encode_one_entity = [&] (auto e)
        {

          if constexpr(decltype(is_std_optional(symbol_member_or_getter_access(obj, e.name))){}) {
              if (!symbol_member_or_getter_access(obj, e.name).has_value()) return;
            }

          if (!first) { ss << ','; }
          first = false; 
          if constexpr(has_key(e, s::json_key)) {
              json_encode_value(ss, e.json_key);
            }
          else
            json_encode_value(ss, symbol_string(e.name));
          ss << ':';

          if constexpr(has_key(e, s::type)) {
              if constexpr(decltype(json_is_vector(e.type)){} or decltype(json_is_object(e.type)){}) {
                  return json_encode(ss, symbol_member_or_getter_access(obj, e.name), e.type);
                }
              else
                json_encode_value(ss, symbol_member_or_getter_access(obj, e.name));
            }
          else
            json_encode_value(ss, symbol_member_or_getter_access(obj, e.name));
        };

      tuple_map(schema.schema, encode_one_entity);
      ss << '}';
    }
  }

}

#endif // LITHIUM_SINGLE_HEADER_GUARD_LI_JSON_ENCODER


namespace li {



template <typename T> struct json_object_base {

public:
  inline auto downcast() const { return static_cast<const T*>(this); }

  template <typename C, typename O> void encode(C& output, O&& obj) const {
    return impl::json_encode(output, std::forward<O>(obj), *downcast());
  }

  template <typename C, typename... M>
  void encode(C& output, const metamap<M...>& obj) const {
    return impl::json_encode(output, obj, *downcast());
  }

  template <typename O> std::string encode(O obj) const {
    std::stringstream ss;
    impl::json_encode(ss, std::forward<O>(obj), *downcast());
    return ss.str();
  }

  template <typename... M> std::string encode(const metamap<M...>& obj) const {
    std::stringstream ss;
    impl::json_encode(ss, obj, *downcast());
    return ss.str();
  }

  template <typename C, typename O> json_error decode(C& input, O& obj) const {
    return impl::json_decode(input, obj, *downcast());
  }

  template <typename C, typename... M> auto decode(C& input) const {
    auto map = impl::json_object_to_metamap(*downcast());
    impl::json_decode(input, map, *downcast());
    return map;
  }
};

template <typename T>
struct json_object_ : public json_object_base<json_object_<T>> {
  json_object_() = default;
  json_object_(const T& s) : schema(s) {}
  T schema;
};

template <typename... S> auto json_object(S&&... s) {
  auto members =
      std::make_tuple(impl::make_json_object_member(std::forward<S>(s))...);
  return json_object_<decltype(members)>{members};
}

template <typename V>
struct json_value_ : public json_object_base<json_value_<V>> {
  json_value_() = default;
};

template <typename V> auto json_value(V&& v) { return json_value_<V>{}; }

template <typename T>
struct json_vector_ : public json_object_base<json_vector_<T>> {
  json_vector_() = default;
  json_vector_(const T& s) : schema(s) {}
  T schema;
};

template <typename... S> auto json_vector(S&&... s) {
  auto obj = json_object(std::forward<S>(s)...);
  return json_vector_<decltype(obj)>{obj};
}

template <typename... T>
struct json_tuple_ : public json_object_base<json_tuple_<T...>> {
  json_tuple_() = default;
  json_tuple_(const T&... s) : elements(s...) {}
  std::tuple<T...> elements;
};

template <typename... S> auto json_tuple(S&&... s) {
  return json_tuple_<S...>{s...};
}

struct json_key {
  inline json_key(const char* c) : key(c) {}
  const char* key;
};

template <typename C, typename M> auto json_decode(C& input, M& obj) {
  return impl::to_json_schema(obj).decode(input, obj);
}

template <typename C, typename M> auto json_encode(C& output, const M& obj) {
  impl::to_json_schema(obj).encode(output, obj);
}

template <typename M> auto json_encode(const M& obj) {
  return impl::to_json_schema(obj).encode(obj);
}

template <typename A, typename B, typename... C> auto json_encode(const assign_exp<A, B>& exp, C... c) {
  auto obj = mmm(exp, c...);
  return impl::to_json_schema(obj).encode(obj);
}

} // namespace li

#endif // LITHIUM_SINGLE_HEADER_GUARD_LI_JSON_JSON



#ifndef LITHIUM_SINGLE_HEADER_GUARD_LI_HTTP_BACKEND_API
#define LITHIUM_SINGLE_HEADER_GUARD_LI_HTTP_BACKEND_API

#ifndef LITHIUM_SINGLE_HEADER_GUARD_LI_HTTP_BACKEND_DYNAMIC_ROUTING_TABLE
#define LITHIUM_SINGLE_HEADER_GUARD_LI_HTTP_BACKEND_DYNAMIC_ROUTING_TABLE


namespace li {

  namespace internal
  {

    template <typename V>
    struct drt_node
    {

      drt_node() : v{0, nullptr} {}
      struct iterator
      {
        drt_node<V>* ptr;
        std::string_view first;
        V second;

        auto operator->(){ return this; }
        bool operator==(const iterator& b) { return this->ptr == b.ptr; }
        bool operator!=(const iterator& b) { return this->ptr != b.ptr; }
      };

      auto end() { return iterator{nullptr, std::string_view(), V()}; }
      
      auto& find_or_create(std::string_view r, unsigned int c)
      {
        if (c == r.size())
          return v;

        if (r[c] == '/')
          c++; // skip the /
        int s = c;
        while (c < r.size() and r[c] != '/') c++;
        std::string_view k = r.substr(s, c - s);

        auto& v = childs[k].find_or_create(r, c);

        return v;
      }

      template <typename F>
      void for_all_routes(F f, std::string prefix = "") const
      {
        if (childs.size() == 0)
          f(prefix, v);
        else
        {
          if (prefix.size() && prefix.back() != '/')
            prefix += '/';
          for (auto it : childs)
            it.second.for_all_routes(f, prefix + std::string(it.first));
        }
      } 
      iterator find(const std::string_view& r, unsigned int c)
      {
        // We found the route r.
        if ((c == r.size() and v.handler != nullptr) or
            (childs.size() == 0))
          return iterator{this, r, v};

        // r does not match any route.
        if (c == r.size() and v.handler == nullptr)
          return iterator{nullptr, r, v};

        if (r[c] == '/')
          c++; // skip the first /

        // Find the next /.
        int s = c;
        while (c < r.size() and r[c] != '/') c++;

        // k is the string between the 2 /.
        std::string_view k(&r[s], c - s);
        
        // look for k in the childs.
        auto it = childs.find(k);
        if (it != childs.end())
        {
          auto it2 = it->second.find(r, c); // search in the corresponding child.
          if (it2 != it->second.end()) return it2;
        }


        {
          // if one child is a url param {{param_name}}, choose it
          for (auto& kv : childs)
          {
            auto name = kv.first;
            if (name.size() > 4 and 
                name[0] == '{' and
                name[1] == '{' and
                name[name.size() -2] == '}' and
                name[name.size() -1] == '}')
              return kv.second.find(r, c);                
          }
          return end();
        }
      }

      V v;
      std::map<std::string_view, drt_node> childs;
    };
  }
  
  template <typename V>
  struct dynamic_routing_table
  {

    // Find a route and return reference to a procedure.
    auto& operator[](const std::string_view& r)
    {
      strings.push_back(std::shared_ptr<std::string>(new std::string(r)));
      std::string_view r2(*strings.back());
      return root.find_or_create(r2, 0);
    }
    auto& operator[](const std::string& r)
    {
      strings.push_back(std::shared_ptr<std::string>(new std::string(r)));
      std::string_view r2(*strings.back());
      return root.find_or_create(r2, 0);
    }

    // Find a route and return an iterator.
    auto find(const std::string_view& r)
    {
      return root.find(r, 0);
    }


    template <typename F>
    void for_all_routes(F f) const
    {
      root.for_all_routes(f);
    } 
    auto end() { return root.end(); }

    std::vector<std::shared_ptr<std::string>> strings;
    internal::drt_node<V> root;
  };

}

#endif // LITHIUM_SINGLE_HEADER_GUARD_LI_HTTP_BACKEND_DYNAMIC_ROUTING_TABLE

#ifndef LITHIUM_SINGLE_HEADER_GUARD_LI_HTTP_BACKEND_ERROR
#define LITHIUM_SINGLE_HEADER_GUARD_LI_HTTP_BACKEND_ERROR


namespace li {

template <typename E> inline void format_error_(E&) {}

template <typename E, typename T1, typename... T>
inline void format_error_(E& err, T1 a, T... args) {
  err << a;
  format_error_(err, std::forward<T>(args)...);
}

template <typename... T> inline std::string format_error(T&&... args) {
  std::stringstream ss;
  format_error_(ss, std::forward<T>(args)...);
  return ss.str();
}

struct http_error {
public:
  http_error(int status, const std::string& what) : status_(status), what_(what) {}
  http_error(int status, const char* what) : status_(status), what_(what) {}
  auto status() const { return status_; }
  auto what() const { return what_; }


#define LI_HTTP_ERROR(CODE, ERR)                                          \
  template <typename... A> static auto ERR(A&&... m) {                                \
    return http_error(CODE, format_error(m...));                                    \
  }                                                                            \
  static auto ERR(const char* w) { return http_error(CODE, w); }

LI_HTTP_ERROR(400, bad_request)
LI_HTTP_ERROR(401, unauthorized)
LI_HTTP_ERROR(403, forbidden)
LI_HTTP_ERROR(404, not_found)

LI_HTTP_ERROR(500, internal_server_error)
LI_HTTP_ERROR(501, not_implemented)

#undef LI_HTTP_ERROR


private:
  int status_;
  std::string what_;
};

} // namespace li

#endif // LITHIUM_SINGLE_HEADER_GUARD_LI_HTTP_BACKEND_ERROR


namespace li {

enum { ANY, GET, POST, PUT, HTTP_DELETE };

template <typename T, typename F> struct delayed_assignator {
  delayed_assignator(T& t, F f = [](T& t, auto u) { t = u; })
      : t(t), f(f) {}

  template <typename U> auto operator=(U&& u) { return f(t, u); }

  T& t;
  F& f;
};

template <typename Req, typename Resp> struct api {

  typedef api<Req, Resp> self;

  using H = std::function<void(Req&, Resp&)>;
  struct VH {
    int verb = ANY;
    H handler;
    std::string url_spec;
  };

  H& operator()(const std::string_view& r) 
  { 
    auto& vh = routes_map_[r];
    vh.verb = ANY;
    vh.url_spec = r;
    return vh.handler;
  }

  H& operator()(int verb, std::string_view r) {
    auto& vh = routes_map_[r];
    vh.verb = verb;
    vh.url_spec = r;
    return vh.handler;
  }
  H& get(std::string_view r) { return this->operator()(GET, r); }
  H& post(std::string_view r) { return this->operator()(POST, r); }
  H& put(std::string_view r) { return this->operator()(PUT, r); }
  H& delete_(std::string_view r) { return this->operator()(HTTP_DELETE , r); }

  int parse_verb(std::string_view method)
  {
    if (method == "GET") return GET;
    if (method == "PUT") return PUT;
    if (method == "POST") return POST;
    if (method == "HTTP_DELETE") return HTTP_DELETE;
    return ANY;
  }

  void add_subapi(std::string prefix, const self& subapi)
  {
    subapi.routes_map_.for_all_routes([this, prefix] (auto r, VH h) {
      if (r.back() == '/')
        h.url_spec = prefix + r;
      else
        h.url_spec = prefix + "/" + r;

      this->routes_map_[h.url_spec] = h;

    });

  }

  void print_routes()
  {
    std::cout << "=====================" << std::endl;
    routes_map_.for_all_routes([this] (auto r, auto h) {
      std::cout << r << std::endl;
    });
    std::cout << "=====================" << std::endl;
  }
  auto call(const char* method, std::string route, Req& request,
            Resp& response) {
    // skip the last / of the url.
    std::string_view route2(route);
    if (route2.size() != 0 and route2[route2.size() - 1] == '/')
      route2 = route2.substr(0, route2.size() - 1);

    auto it = routes_map_.find(route2);
    if (it != routes_map_.end()) {
      if (it->second.verb == ANY or parse_verb(method) == it->second.verb)
      {
        request.url_spec = it->second.url_spec;
        it->second.handler(request, response);
      }
      else
        throw http_error::not_found("Method ", method, " not implemented on route ",
                               route2);
    } else
      throw http_error::not_found("Route ", route2, " does not exist.");
  }

  dynamic_routing_table<VH> routes_map_;
};

} // namespace li

#endif // LITHIUM_SINGLE_HEADER_GUARD_LI_HTTP_BACKEND_API

#ifndef LITHIUM_SINGLE_HEADER_GUARD_LI_HTTP_BACKEND_REQUEST
#define LITHIUM_SINGLE_HEADER_GUARD_LI_HTTP_BACKEND_REQUEST


#ifndef LITHIUM_SINGLE_HEADER_GUARD_LI_HTTP_BACKEND_URL_DECODE
#define LITHIUM_SINGLE_HEADER_GUARD_LI_HTTP_BACKEND_URL_DECODE

#if defined(_MSC_VER)
#endif


namespace li
{
  // Decode a plain value.
  template <typename O>
  std::string_view url_decode2(std::set<void*>& found, std::string_view str, O& obj)
  {
    if (str.size() == 0)
      throw std::runtime_error(format_error("url_decode error: expected key end"));

    if (str[0] != '=')
      throw std::runtime_error(format_error("url_decode error: expected =, got ", str[0]));

    int start = 1;
    int end = 1;
    
    while (str.size() != end && str[end] != '&') end++;

    if (start != end)
    {
      std::string content(str.substr(start, end - start));
      // Url escape.
      content.resize(MHD_http_unescape(&content[0]));
      obj = boost::lexical_cast<O>(content);
      found.insert(&obj);
    }
    if (end == str.size())
      return str.substr(end, 0);
    else
      return str.substr(end + 1, str.size() - end - 1);
  }

  template <typename O>
  std::string_view url_decode2(std::set<void*>& found, std::string_view str, std::optional<O>& obj)
  {
    O o;
    auto ret = url_decode2(found, str, o);
    obj = o;
    return ret;
  }

  template <typename... O>
  std::string_view url_decode2(std::set<void*>& found, std::string_view str, metamap<O...>& obj, bool root = false);
  
  // Decode an array element.
  template <typename O>
  std::string_view url_decode2(std::set<void*>& found, std::string_view str, std::vector<O>& obj)
  {
    if (str.size() == 0)
      throw std::runtime_error(format_error("url_decode error: expected key end", str[0]));

    if (str[0] != '[')
      throw std::runtime_error(format_error("url_decode error: expected [, got ", str[0]));

    // Get the index substring.
    int index_start = 1;
    int index_end = 1;
    
    while (str.size() != index_end and str[index_end] != ']') index_end++;

    if (str.size() == 0)
      throw std::runtime_error(format_error("url_decode error: expected key end", str[0]));
    
    auto next_str = str.substr(index_end + 1, str.size() - index_end - 1);

    if (index_end == index_start) // [] syntax, push back a value.
    {
      O x;
      auto ret = url_decode2(found, next_str, x);
      obj.push_back(x);
      return ret;
    }
    else // [idx] set index idx.
    {
      int idx = std::strtol(str.data() + index_start, nullptr, 10);
      if (idx >= 0 and idx <= 9999)
      {
        if (int(obj.size()) <= idx)
          obj.resize(idx + 1);
        return url_decode2(found, next_str, obj[idx]);
      }
      else
        throw std::runtime_error(format_error("url_decode error: out of bound array subscript."));
    }
    
  }

  // Decode an object member.
  template <typename... O>
  std::string_view url_decode2(std::set<void*>& found, std::string_view str, metamap<O...>& obj, bool root)
  {
    if (str.size() == 0)
      throw http_error::bad_request("url_decode error: expected key end", str[0]);
      
    int key_start = 0;
    int key_end = key_start + 1;

    int next = 0;

    if (!root)
    {
      if (str[0] != '[')
        throw std::runtime_error(format_error("url_decode error: expected [, got ", str[0]));
        
      key_start = 1;
      while (key_end != str.size() && str[key_end] != ']' && str[key_end] != '=') key_end++;

      if (key_end == str.size())
        throw std::runtime_error("url_decode error: unexpected end.");
      next = key_end + 1; // skip the ]
    }
    else
    {
      while (key_end != str.size() && str[key_end] != '[' && str[key_end] != '=') key_end++;
      next = key_end;
    }

    auto key = str.substr(key_start, key_end - key_start);
    auto next_str = str.substr(next, str.size() - next);

    std::string_view ret;
    map(obj, [&] (auto k, auto& v)
    {
      if (li::symbol_string(k) == key)
      {
      try{
        ret = url_decode2(found, next_str, v);
      }
      catch(std::exception e)
      {
        throw std::runtime_error(format_error("url_decode error: cannot decode parameter ", 
                                  li::symbol_string(k)));
      }
      }
    });
    return ret;
  }

  template <typename O>
  std::string url_decode_check_missing_fields(const std::set<void*>& found, std::optional<O>& obj)
  {
    return std::string();
  }

  template <typename O>
  std::string url_decode_check_missing_fields(const std::set<void*>& found, O& obj)
  {
    if (found.find(&obj) == found.end())
      return " ";
    else
      return std::string();
  }

  template <typename O>
  std::string url_decode_check_missing_fields(const std::set<void*>& found, std::vector<O>& obj)
  {
    // Fixme : implement missing fields checking in std::vector<metamap<O...>>
    // for (int i = 0; i < obj.size(); i++)
    // {
    //   std::string missing = url_decode_check_missing_fields(found, obj[i]);
    //   if (missing.size())
    //   {
    //     std::stringstream ss;
    //     ss << '[' << i << "]" << missing;
    //     return ss.str();
    //   }
    // }
    return std::string();
  }
  
  template <typename... O>
  std::string url_decode_check_missing_fields(const std::set<void*>& found, metamap<O...>& obj, bool root = false)
  {
    std::string missing;
    map(obj, [&] (auto k, auto& v)
    {
      if (missing.size()) return;
      missing = url_decode_check_missing_fields(found, v);
      if (missing.size())
        missing = (root ? "" : ".") + std::string(li::symbol_string(k)) + missing;
    });
    return missing;
  }

  template <typename S, typename... O>
  std::string url_decode_check_missing_fields_on_subset(const std::set<void*>& found, metamap<O...>& obj, bool root = false)
  {
    std::string missing;
    map(S(), [&] (auto k, auto)
    {
      if (missing.size()) return;
      auto& v = obj[k];
      missing = url_decode_check_missing_fields(found, v);
      if (missing.size())
        missing = (root ? "" : ".") + std::string(li::symbol_string(k)) + missing;
    });
    return missing;
  }
  
  // Frontend.
  template <typename O>
  void url_decode(std::string_view str, O& obj)
  {
    std::set<void*> found;

    // Parse the urlencoded string
    while (str.size() > 0)
      str = url_decode2(found, str, obj, true);

    // Check for missing fields.
    std::string missing = url_decode_check_missing_fields(found, obj, true);
    if (missing.size())
      throw std::runtime_error(format_error("Missing argument ", missing));
  }

}

#endif // LITHIUM_SINGLE_HEADER_GUARD_LI_HTTP_BACKEND_URL_DECODE


namespace li {

struct http_request {

  inline const char* header(const char* k) const;
  inline const char* cookie(const char* k) const;

  // With list of parameters: s::id = int(), s::name = string(), ...
  template <typename S, typename V, typename... T>
  auto url_parameters(assign_exp<S, V> e, T... tail) const;
  template <typename S, typename V, typename... T>
  auto get_parameters(assign_exp<S, V> e, T... tail) const;
  template <typename S, typename V, typename... T>
  auto post_parameters(assign_exp<S, V> e, T... tail) const;

  // Const wrapper.
  template <typename O> auto url_parameters(const O& res) const;
  template <typename O> auto get_parameters(const O& res) const;
  template <typename O> auto post_parameters(const O& res) const;

  // With a metamap.
  template <typename O> auto url_parameters(O& res) const;
  template <typename O> auto get_parameters(O& res) const;
  template <typename O> auto post_parameters(O& res) const;

  MHD_Connection* mhd_connection;

  std::string body;
  std::string url;
  std::string url_spec;
};

template <typename F>
int mhd_keyvalue_iterator(void* cls, enum MHD_ValueKind kind, const char* key, const char* value) {
  F& f = *(F*)cls;
  if (key and value and *key and *value) {
    f(key, value);
    return MHD_YES;
  }
  // else return MHD_NO;
  return MHD_YES;
}

struct url_parser_info_node { int slash_pos; bool is_path; };
using url_parser_info = std::unordered_map<std::string, url_parser_info_node>;

auto make_url_parser_info(const std::string_view url) {

  url_parser_info info;

  auto check_pattern = [](const char* s, char a) { return *s == a and *(s + 1) == a; };

  int slash_pos = -1;
  for (int i = 0; i < int(url.size()); i++) {
    if (url[i] == '/')
      slash_pos++;
    // param must start with {{
    if (check_pattern(url.data() + i, '{')) {
      const char* param_name_start = url.data() + i + 2;
      const char* param_name_end = param_name_start;
      // param must end with }}
      while (!check_pattern(param_name_end, '}'))
        param_name_end++;

      if (param_name_end != param_name_start and check_pattern(param_name_end, '}')) {
        int size = param_name_end - param_name_start;
        bool is_path = false;
        if (size > 3 and param_name_end[-1] == '.' and param_name_end[-2] == '.' and param_name_end[-3] == '.')
        {
          is_path = true;
          param_name_end -= 3;
        }
        std::string_view param_name(param_name_start, param_name_end - param_name_start);
        info.emplace(param_name, url_parser_info_node{slash_pos, is_path});
      }
    }
  }
  return info;
}

template <typename O>
auto parse_url_parameters(const url_parser_info& fmt, const std::string_view url, O& obj) {
  // get the indexes of the slashes in url.
  std::vector<int> slashes;
  for (int i = 0; i < int(url.size()); i++) {
    if (url[i] == '/')
      slashes.push_back(i);
  }

  // For each field in O...
  //  find the location of the field in the url thanks to fmt.
  //  get it.
  map(obj, [&](auto k, auto v) {
    const char* symbol_str = symbol_string(k);
    auto it = fmt.find(symbol_str);
    if (it == fmt.end()) {
      throw std::runtime_error(std::string("Parameter ") + symbol_str + " not found in url " +
                               url.data());
    } else {
      // Location of the parameter in the url.
      int param_slash = it->second.slash_pos; // index of slash before param.
      if (param_slash >= int(slashes.size()))
        throw http_error::bad_request("Missing url parameter ", symbol_str);

      int param_start = slashes[param_slash] + 1;
      if (it->second.is_path)
      {
        if constexpr(std::is_same<std::decay_t<decltype(obj[k])>, std::string>::value or
                     std::is_same<std::decay_t<decltype(obj[k])>, std::string_view>::value) {
          obj[k] = std::string_view(url.data() + param_start - 1, url.size() - param_start + 1); // -1 to include the first /.
        }
        else {
          throw std::runtime_error("{{path...}} parameters only accept std::string or std::string_view types.");
        }

      }
      else
      {
        int param_end = param_start;
        while (int(url.size()) > (param_end) and url[param_end] != '/')
          param_end++;

        std::string content(url.data() + param_start, param_end - param_start);
        content.resize(MHD_http_unescape(&content[0]));
        try {
          obj[k] = boost::lexical_cast<decltype(v)>(content);
        } catch (std::exception e) {
          throw http_error::bad_request("Cannot decode url parameter ", li::symbol_string(k), " : ",
                                        e.what());
        }
      }
    }
  });
  return obj;
}

inline const char* http_request::header(const char* k) const {
  return MHD_lookup_connection_value(mhd_connection, MHD_HEADER_KIND, k);
}

inline const char* http_request::cookie(const char* k) const {
  return MHD_lookup_connection_value(mhd_connection, MHD_COOKIE_KIND, k);
}

template <typename S, typename V, typename... T>
auto http_request::url_parameters(assign_exp<S, V> e, T... tail) const {
  return url_parameters(mmm(e, tail...));
}

template <typename S, typename V, typename... T>
auto http_request::get_parameters(assign_exp<S, V> e, T... tail) const {
  return get_parameters(mmm(e, tail...));
}

template <typename S, typename V, typename... T>
auto http_request::post_parameters(assign_exp<S, V> e, T... tail) const {
  auto o = mmm(e, tail...);
  return post_parameters(o);
}

template <typename O> auto http_request::url_parameters(const O& res) const {
  O r;
  return url_parameters(r);
}

template <typename O> auto http_request::get_parameters(const O& res) const {
  O r;
  return get_parameters(r);
}
template <typename O> auto http_request::post_parameters(const O& res) const {
  O r;
  return post_parameters(r);
}

template <typename O> auto http_request::url_parameters(O& res) const {
  auto info = make_url_parser_info(url_spec);
  return parse_url_parameters(info, url, res);
}

template <typename O> auto http_request::get_parameters(O& res) const {
  std::set<void*> found;
  auto add = [&](const char* k, const char* v) {
    url_decode2(found, std::string(k) + "=" + v, res, true);
  };

  MHD_get_connection_values(mhd_connection, MHD_GET_ARGUMENT_KIND,
                            &mhd_keyvalue_iterator<decltype(add)>, &add);

  // Check for missing fields.
  std::string missing = url_decode_check_missing_fields(found, res, true);
  if (missing.size())
    throw http_error::bad_request("Error while decoding the GET parameter: ", missing);
  return res;
}

template <typename O> auto http_request::post_parameters(O& res) const {
  try {
    const char* encoding = this->header("Content-Type");
    if (!encoding)
      throw http_error::bad_request(std::string(
          "Content-Type is required to decode the POST parameters"));

    if (encoding == std::string_view("application/x-www-form-urlencoded"))
      url_decode(body, res);
    else if (encoding == std::string_view("application/json"))
      json_decode(body, res);
  } catch (std::exception e) {
    throw http_error::bad_request("Error while decoding the POST parameters: ", e.what());
  }

  return res;
}

} // namespace li

#endif // LITHIUM_SINGLE_HEADER_GUARD_LI_HTTP_BACKEND_REQUEST

#ifndef LITHIUM_SINGLE_HEADER_GUARD_LI_HTTP_BACKEND_RESPONSE
#define LITHIUM_SINGLE_HEADER_GUARD_LI_HTTP_BACKEND_RESPONSE


//#include <stdlib.h>

#if defined(_MSC_VER)
#endif

//#include <sys/stat.h>

namespace li {
using namespace li;

struct http_response {
  inline http_response() : status(200), file_descriptor(-1) {}
  inline void set_header(std::string k, std::string v) { headers[k] = v; }
  inline void set_cookie(std::string k, std::string v) { cookies[k] = v; }

  inline void write() {}
  template <typename A1, typename... A>
  inline void write(A1 a1, A&&... a) { body += boost::lexical_cast<std::string>(a1); write(a...); }
  inline void write_file(const std::string path) {

#if defined(_MSC_VER)
    int fd; 
    _sopen_s(&fd, path.c_str(), O_RDONLY, _SH_DENYRW, _S_IREAD);
#else
    int fd = open(path.c_str(), O_RDONLY);
#endif

    if (fd == -1)
      throw http_error::not_found("File not found.");
    file_descriptor = fd;
  }

  int status;
  std::string body;
  int file_descriptor;
  std::unordered_map<std::string, std::string> cookies;
  std::unordered_map<std::string, std::string> headers;
};

} // namespace li

#endif // LITHIUM_SINGLE_HEADER_GUARD_LI_HTTP_BACKEND_RESPONSE

#ifndef LITHIUM_SINGLE_HEADER_GUARD_LI_HTTP_BACKEND_SQL_CRUD_API
#define LITHIUM_SINGLE_HEADER_GUARD_LI_HTTP_BACKEND_SQL_CRUD_API



namespace li {
  
template <typename A, typename B, typename C> auto sql_crud_api(sql_orm_schema<A, B, C>& orm_schema) {

  api<http_request, http_response> api;

  api(POST, "/find_by_id") = [&](http_request& request, http_response& response) {
    auto params = request.post_parameters(s::id = int());
    if (auto obj = orm_schema.connect().find_one(s::id = params.id, request, response))
      response.write(json_encode(obj));
    else
      throw http_error::not_found(orm_schema.table_name(), " with id ", params.id, " does not exist.");
  };

  api(POST, "/create") = [&](http_request& request, http_response& response) {
    auto insert_fields = orm_schema.all_fields_except_computed();
    auto obj = request.post_parameters(insert_fields);
    long long int id = orm_schema.connect().insert(obj, request, response);
    response.write(json_encode(s::id = id));
  };

  api(POST, "/update") = [&](http_request& request, http_response& response) {
    auto obj = request.post_parameters(orm_schema.all_fields());
    orm_schema.connect().update(obj, request, response);
  };

  api(POST, "/remove") = [&](http_request& request, http_response& response) {
    auto obj = request.post_parameters(orm_schema.primary_key());
    orm_schema.connect().remove(obj, request, response);
  };

  return api;
}

} // namespace li

#endif // LITHIUM_SINGLE_HEADER_GUARD_LI_HTTP_BACKEND_SQL_CRUD_API

#ifndef LITHIUM_SINGLE_HEADER_GUARD_LI_HTTP_BACKEND_MHD
#define LITHIUM_SINGLE_HEADER_GUARD_LI_HTTP_BACKEND_MHD



#if defined(__GNUC__) && defined(__MINGW32__)
#endif

#if defined(_MSC_VER)
void usleep(__int64 usec) 
{ 
    HANDLE timer; 
    LARGE_INTEGER ft; 

    ft.QuadPart = -(10*usec); // Convert to 100 nanosecond interval, negative value indicates relative time

    timer = CreateWaitableTimer(NULL, TRUE, NULL); 
    SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0); 
    WaitForSingleObject(timer, INFINITE); 
    CloseHandle(timer); 
}
#endif


//#include <li/http_backend/file.hh>
//#include <li/http_backend/url_decode.hh>

namespace li {
  using namespace li;
    
  template <typename S>
  int mhd_handler(void * cls,
                  struct MHD_Connection * connection,
                  const char * url,
                  const char * method,
                  const char * version,
                  const char * upload_data,
                  size_t * upload_data_size,
                  void ** ptr)
  {

    MHD_Response* response = nullptr;
    int ret = 0;

    std::string* pp = (std::string*)*ptr;
    if (!pp)
    {
      pp = new std::string;
      *ptr = pp;
      return MHD_YES;
    }
    if (*upload_data_size)
    {
      pp->append(std::string(upload_data, *upload_data_size));
      *upload_data_size = 0;
      return MHD_YES;
    }

    http_request rq{connection, *pp, url};
    http_response resp;

    try
    {
      auto& api = * (S*)cls;
      //api(std::string("/") + std::string(method) + url, &rq, &resp, connection);      
      api.call(method, url, rq, resp);

      if (resp.file_descriptor > -1)
      {
        struct stat st;
        if (fstat(resp.file_descriptor, &st) != 0)
          throw http_error::not_found("Cannot fstat this file");
        response = MHD_create_response_from_fd(st.st_size, resp.file_descriptor);
      }
      
    }
    catch(const http_error& e)
    {
      resp.status = e.status();
      std::string m = e.what();
      resp.body = m.data();
    }
    catch(const std::runtime_error& e)
    {
      std::cout << e.what() << std::endl;
      resp.status = 500;
      resp.body = "Internal server error.";
    }



    if (resp.file_descriptor == -1)
    {
      const std::string& str = resp.body;
      response = MHD_create_response_from_buffer(str.size(),
                                                 (void*) str.c_str(),
                                                 MHD_RESPMEM_MUST_COPY);
    }

    if (!response)
    {
      resp.status = 500;
      resp.body = "Failed to create response object.";
    }
    else
    {
      for(auto kv : resp.headers)
      {
        if (kv.first.size() != 0 and kv.second.size() != 0)
          if (MHD_NO == MHD_add_response_header (response,
                                                 kv.first.c_str(),
                                                 kv.second.c_str()))
            std::cerr << "Failed to set header" << std::endl;
      }

      // Set cookies.
      for(auto kv : resp.cookies)
        if (kv.first.size() != 0 and kv.second.size() != 0)
        {
          std::string set_cookie_string = kv.first + '=' + kv.second + "; Path=/";
          if (MHD_NO == MHD_add_response_header (response,
                                                 MHD_HTTP_HEADER_SET_COOKIE,
                                                 set_cookie_string.c_str()))
            std::cerr << "Failed to set cookie" << std::endl;
        }

      if (resp.headers.find(MHD_HTTP_HEADER_SERVER) == resp.headers.end())
        MHD_add_response_header (response,
                                 MHD_HTTP_HEADER_SERVER,
                                 "silicon");

      ret = MHD_queue_response(connection,
                               resp.status,
                               response);

      MHD_destroy_response(response);
    }

    delete pp;
    return ret;
  }

  struct silicon_mhd_ctx
  {
    silicon_mhd_ctx(MHD_Daemon* d, char* cert, char* key)
      : daemon_(d),
        cert_(cert),
        key_(key) {}

    ~silicon_mhd_ctx()
    {
      MHD_stop_daemon(daemon_);
      if (cert_)
        free(cert_);
      if (key_)
        free(key_);
    }

    MHD_Daemon* daemon_;

    char* cert_, *key_;
  };

  /*! 
  ** Start the microhttpd json backend. This function is by default blocking.
  ** 
  ** @param api The api
  ** @param port the port
  ** @param opts Available options are:
  **         s::one_thread_per_connection: Spans one thread per connection.
  **         s::linux_epoll: One thread per CPU core with epoll.
  **         s::select: select instead of epoll (active by default).
  **         s::nthreads: Set the number of thread. Default: The numbers of CPU cores.
  **         s::non_blocking: Run the server in a thread and return in a non blocking way.
  **         s::blocking: (Active by default) Blocking call.
  **         s::https_key: path to the https key file.
  **         s::https_cert: path to the https cert file.
  ** 
  ** @return If set as non_blocking, this function returns a
  ** silicon_mhd_ctx that will stop and cleanup the server at the end
  ** of its lifetime. If set as blocking (default), never returns
  ** except if an error prevents or stops the execution of the server.
  **
  */
  template <typename A, typename... O>
  auto http_serve(A& api, int port, O... opts)
  {

    int flags = MHD_USE_SELECT_INTERNALLY;
    auto options = mmm(opts...);
    if (has_key(options, s::one_thread_per_connection))
      flags = MHD_USE_THREAD_PER_CONNECTION;
    else if (has_key(options, s::select))
      flags = MHD_USE_SELECT_INTERNALLY;
    else if (has_key(options, s::linux_epoll))
    {
#if MHD_VERSION >= 0x00095100
      flags = MHD_USE_EPOLL_INTERNALLY;
#else
      flags = MHD_USE_EPOLL_INTERNALLY_LINUX_ONLY;
#endif
    }

    auto read_file = [] (std::string path) {
      std::ifstream in(path);
      if (!in.good())
      {
        std::stringstream err_ss;
#if defined (_MSC_VER)
        err_ss << "Cannot read " << path;
#else
        err_ss << "Cannot read " << path << " " << strerror(errno);
#endif
        throw std::runtime_error(err_ss.str());
      }
      std::ostringstream ss{};
      ss << in.rdbuf();
      return ss.str();
    };

    std::string https_cert, https_key;
    if (has_key(options, s::https_cert) || has_key(options, s::https_key))
    {
      std::string cert_file = get_or(options, s::https_cert, "");
      std::string key_file = get_or(options, s::https_key, "");
#ifdef MHD_USE_TLS
      flags |= MHD_USE_TLS;
#else
      flags |= MHD_USE_SSL;
#endif
      
      if (cert_file.size() == 0) throw std::runtime_error("Missing HTTPS certificate file"); 
      if (key_file.size() == 0) throw std::runtime_error("Missing HTTPS key file");

      https_key = std::move(read_file(key_file));
      https_cert = std::move(read_file(cert_file));
      
    }

#if defined (_MSC_VER)
  #define strdup _strdup
#endif
    char* https_cert_buffer = https_cert.size() ? strdup(https_cert.c_str()) : 0;
    char* https_key_buffer = https_key.size() ? strdup(https_key.c_str()) : 0;
#if defined (_MSC_VER)
  #undef strdup
#endif
  
    int thread_pool_size = get_or(options, s::nthreads, std::thread::hardware_concurrency());
    
    using api_t = std::decay_t<decltype(api)>;
    
    MHD_Daemon* d;

    void* cls = (void*)  &api;
    if (https_key.size() > 0)
    {
      if (MHD_is_feature_supported(MHD_FEATURE_SSL) == MHD_NO)
        throw std::runtime_error("microhttpd has not been compiled with SSL support.");
        
      if ((flags & MHD_USE_THREAD_PER_CONNECTION) != MHD_USE_THREAD_PER_CONNECTION)
        d = MHD_start_daemon(
                             flags,
                             port,
                             NULL,
                             NULL,
                             &mhd_handler<api_t>,
                             cls,
                             MHD_OPTION_THREAD_POOL_SIZE, thread_pool_size,
                             MHD_OPTION_HTTPS_MEM_KEY, https_key_buffer,
                             MHD_OPTION_HTTPS_MEM_CERT, https_cert_buffer,
                             MHD_OPTION_END);
      else
        d = MHD_start_daemon(
                             flags,
                             port,
                             NULL,
                             NULL,
                             &mhd_handler<api_t>,
                             cls,
                             MHD_OPTION_HTTPS_MEM_KEY, https_key_buffer,
                             MHD_OPTION_HTTPS_MEM_CERT, https_cert_buffer,
                             MHD_OPTION_END);
      
    }
    else // Without SSL
    {
      if ((flags & MHD_USE_THREAD_PER_CONNECTION) != MHD_USE_THREAD_PER_CONNECTION)
        d = MHD_start_daemon(
                             flags,
                             port,
                             NULL,
                             NULL,
                             &mhd_handler<api_t>,
                             cls,
                             MHD_OPTION_THREAD_POOL_SIZE, thread_pool_size,
                             MHD_OPTION_END);
      else
        d = MHD_start_daemon(
                             flags,
                             port,
                             NULL,
                             NULL,
                             &mhd_handler<api_t>,
                             cls,
                             MHD_OPTION_END);
    }

    if (d == NULL)
      throw std::runtime_error("Cannot start the microhttpd daemon");

    if (!has_key(options, s::non_blocking))
    {
      while (true) usleep(1000000);
    }

    return silicon_mhd_ctx(d, https_cert_buffer, https_key_buffer);
  }
  

}

#endif // LITHIUM_SINGLE_HEADER_GUARD_LI_HTTP_BACKEND_MHD

#ifndef LITHIUM_SINGLE_HEADER_GUARD_LI_HTTP_BACKEND_SQL_HTTP_SESSION
#define LITHIUM_SINGLE_HEADER_GUARD_LI_HTTP_BACKEND_SQL_HTTP_SESSION

#ifndef LITHIUM_SINGLE_HEADER_GUARD_LI_HTTP_BACKEND_RANDOM_COOKIE
#define LITHIUM_SINGLE_HEADER_GUARD_LI_HTTP_BACKEND_RANDOM_COOKIE


namespace li {

  std::string generate_secret_tracking_id()
  {
    std::ostringstream os;
    std::random_device rd;
    os << std::hex << rd() << rd() << rd() << rd();
    return os.str();
  }
  
  inline std::string random_cookie(http_request& request,
				    http_response& response,
				    const char* key = "silicon_token")
  {
    std::string token;
    const char* token_ = request.cookie(key);
    if (!token_)
      {
        token = generate_secret_tracking_id();
        response.set_cookie(key, token);
      }
    else
      {
        token = token_;
      }

    return token;
  }

}

#endif // LITHIUM_SINGLE_HEADER_GUARD_LI_HTTP_BACKEND_RANDOM_COOKIE


namespace li {

template <typename ORM> struct connected_sql_http_session {

  // Construct the session.
  // Retrive the cookie
  // Retrieve it from the database.
  // Insert it if it does not exists.
  connected_sql_http_session(typename ORM::object_type& defaults, ORM orm,
                             const std::string& session_id)
      : loaded_(false), session_id_(session_id), orm_(orm), values_(defaults) {}

  // Store fiels into the session
  template <typename... F> auto store(F... fields) {
    map(mmm(fields...), [this](auto k, auto v) { values_[k] = v; });
    if (!orm_.exists(s::session_id = session_id_))
      orm_.insert(s::session_id = session_id_, fields...);
    else
      orm_.update(s::session_id = session_id_, fields...);
  }

  // Access values of the session.
  const auto values() {
    load();
    return values_;
  }

  // Delete the session from the database.
  void logout() { orm_.remove(s::session_id = session_id_); }

private:
  auto load() {
    if (loaded_)
      return;
    if (auto new_values_ = orm_.find_one(s::session_id = session_id_))
      values_ = *new_values_;
    loaded_ = true;
  }

  bool loaded_;
  std::string session_id_;
  ORM orm_;
  typename ORM::object_type values_;
};

template <typename DB, typename... F>
decltype(auto) create_session_orm(DB& db, std::string table_name,
                                  F... fields) {
  return sql_orm_schema<DB>(db, table_name)
      .fields(s::session_id(s::read_only, s::primary_key) = sql_varchar<32>(), fields...);
}

template <typename DB, typename... F> struct sql_http_session {

  sql_http_session(DB& db, std::string table_name, std::string cookie_name, F... fields)
      : cookie_name_(cookie_name),
        default_values_(mmm(s::session_id = sql_varchar<32>(), fields...)),
        session_table_(create_session_orm(db, table_name, fields...)) {}

  auto connect(http_request& request, http_response& response) {
    return connected_sql_http_session(default_values_, session_table_.connect(),
                                      random_cookie(request, response, cookie_name_.c_str()));
  }

  auto orm() { return session_table_; }

  std::string cookie_name_;
  std::decay_t<decltype(mmm(s::session_id = sql_varchar<32>(), std::declval<F>()...))>
      default_values_;
  std::decay_t<decltype(
      create_session_orm(std::declval<DB&>(), std::string(), std::declval<F>()...))>
      session_table_;
};

} // namespace li

#endif // LITHIUM_SINGLE_HEADER_GUARD_LI_HTTP_BACKEND_SQL_HTTP_SESSION

#ifndef LITHIUM_SINGLE_HEADER_GUARD_LI_HTTP_BACKEND_HASHMAP_HTTP_SESSION
#define LITHIUM_SINGLE_HEADER_GUARD_LI_HTTP_BACKEND_HASHMAP_HTTP_SESSION


namespace li {

template <typename O> struct connected_hashmap_http_session {

  connected_hashmap_http_session(std::string session_id_, O* values_,
                                 std::unordered_map<std::string, O>& sessions_, std::mutex& mutex_)
      : session_id_(session_id_), values_(values_), sessions_(sessions_), mutex_(mutex_) {}

  // Store fiels into the session
  template <typename... F> auto store(F... fields) {
    map(mmm(fields...), [this](auto k, auto v) { values()[k] = v; });
  }

  // Access values of the session.
  O& values() {
    if (!values_)
      throw http_error::internal_server_error("Cannot access session values after logout.");
    return *values_;
  }

  // Delete the session from the database.
  void logout() {
    std::lock_guard<std::mutex> guard(mutex_);
    sessions_.erase(session_id_);
  }

private:
  std::string session_id_;
  O* values_;
  std::unordered_map<std::string, O>& sessions_;
  std::mutex& mutex_;
};

template <typename... F> struct hashmap_http_session {

  typedef decltype(mmm(std::declval<F>()...)) session_values_type;
  inline hashmap_http_session(std::string cookie_name, F... fields)
      : cookie_name_(cookie_name), default_values_(mmm(s::session_id = std::string(), fields...)) {}

  inline auto connect(http_request& request, http_response& response) {
    std::string session_id = random_cookie(request, response, cookie_name_.c_str());
    auto it = sessions_.try_emplace(session_id, default_values_).first;
    return connected_hashmap_http_session<session_values_type>{session_id, &it->second, sessions_,
                                                               sessions_mutex_};
  }

  std::string cookie_name_;
  session_values_type default_values_;
  std::unordered_map<std::string, session_values_type> sessions_;
  std::mutex sessions_mutex_;
};

} // namespace li

#endif // LITHIUM_SINGLE_HEADER_GUARD_LI_HTTP_BACKEND_HASHMAP_HTTP_SESSION

#ifndef LITHIUM_SINGLE_HEADER_GUARD_LI_HTTP_BACKEND_SERVE_DIRECTORY
#define LITHIUM_SINGLE_HEADER_GUARD_LI_HTTP_BACKEND_SERVE_DIRECTORY


namespace li {

auto serve_file(const std::string& root, std::string path, http_response& response) {
  std::string base_path = root;
  if (!base_path.empty() && base_path[base_path.size() - 1] != '/') {
    base_path.push_back('/');
  }

  static char dot = '.', slash = '/';

  // remove first slahs if needed.
  //std::string path(r->url.substr(prefix.string().size(), r->url.size() - prefix.string().size()));
  size_t len = path.size();
  if (!path.empty() && path[0] == slash) {
    path.erase(0, 1);
  }

  if (path.empty()) {
    throw http_error::bad_request("No file path given, directory listing not supported.");
  }

  if (len == 1 && path[0] == dot) {
    throw http_error::bad_request("Invalid URI ", path);
  } else if (len == 2 && path[0] == dot && path[1] == dot) {
    throw http_error::bad_request("Invalid URI ", path);
  } else {
    char prev0 = slash, prev1 = slash;
    for (size_t i = 0; i < len; ++i) {
      if (prev0 == dot && prev1 == dot && path[i] == slash) {
        throw http_error::bad_request("Unsupported URI, ../ is not allowed in the URI");
      }
      prev0 = prev1;
      prev1 = path[i];
    }
  }

  response.write_file(base_path + path);
};

inline auto serve_directory(std::string root) {
  api<http_request, http_response> api;

  api.get("/{{path...}}") = [root](http_request& request, http_response& response) {
    auto path = request.url_parameters(s::path = std::string()).path;
    return serve_file(root, path, response);
  };
  return api;
}

} // namespace li

#endif // LITHIUM_SINGLE_HEADER_GUARD_LI_HTTP_BACKEND_SERVE_DIRECTORY

#ifndef LITHIUM_SINGLE_HEADER_GUARD_LI_HTTP_BACKEND_HTTP_AUTHENTICATION
#define LITHIUM_SINGLE_HEADER_GUARD_LI_HTTP_BACKEND_HTTP_AUTHENTICATION



namespace li {

template <typename S, typename U, typename L, typename P, typename... CB>
struct http_authentication {
  http_authentication(S& session, U& users, L login_field, P password_field,
                      CB... callbacks)
      : sessions_(session),
        users_(users),
        login_field_(login_field),
        password_field_(password_field),
        callbacks_(mmm(callbacks...))
        {

    auto allowed_callbacks = mmm(s::hash_password, s::create_secret_key);

    static_assert(metamap_size<decltype(substract(callbacks_, allowed_callbacks))>() == 0, 
    "The only supported callbacks for http_authentication are: s::hash_password, s::create_secret_key");
        }


  template <typename SS, typename... A> void call_callback(SS s, A&&... args) {
    if constexpr(has_key<decltype(callbacks_)>(s))
      return callbacks_[s](std::forward<A>(args)...);
  }
  
 bool login(http_request& req, http_response& resp) {
    auto lp = req.post_parameters(login_field_ = users_.all_fields()[login_field_],
                                  password_field_ = users_.all_fields()[password_field_]);

    if constexpr(has_key<decltype(callbacks_)>(s::hash_password))
      lp[password_field_] = callbacks_[s::hash_password](lp[login_field_], lp[password_field_]);

    if (auto user = users_.connect().find_one(lp)) {
      sessions_.connect(req, resp).store(s::user_id = user->id);
      return true;
    } else
      return false;
  }

  auto current_user(http_request& req, http_response& resp) {
    auto sess = sessions_.connect(req, resp);
    if (sess.values().user_id != -1)
      return users_.connect().find_one(s::id = sess.values().user_id);
    else
      return decltype(users_.connect().find_one(s::id = sess.values().user_id)){};
  }

  void logout(http_request& req, http_response& resp) {
    sessions_.connect(req, resp).logout();
  }

  bool signup(http_request& req, http_response& resp) {
      auto new_user = req.post_parameters(users_.all_fields_except_computed());
      auto users = users_.connect();

      if (users.exists(login_field_ = new_user[login_field_]))
        return false;
      else 
      {
        if constexpr(has_key<decltype(callbacks_)>(s::update_secret_key))
          callbacks_[s::update_secret_key](new_user[login_field_], new_user[password_field_]);        
        if constexpr(has_key<decltype(callbacks_)>(s::hash_password))
          new_user[password_field_] = callbacks_[s::hash_password](new_user[login_field_], new_user[password_field_]);        
        users.insert(new_user);
        return true;
      }
  }

  S& sessions_;
  U& users_;
  L login_field_;
  P password_field_;
  decltype(mmm(std::declval<CB>()...)) callbacks_;
};

template <typename... A>
api<http_request, http_response> http_authentication_api(http_authentication<A...>& auth) {

  api<http_request, http_response> api;

  api.post("/login") = [&] (http_request& request, http_response& response) {
    if (!auth.login(request, response))
      throw http_error::unauthorized("Bad login.");
  };

  api.get("/logout") = [&] (http_request& request, http_response& response) {
    auth.logout(request, response);
  };

  api.get("/signup") = [&] (http_request& request, http_response& response) {
    if (!auth.signup(request, response))
      throw http_error::bad_request("User already exists.");
  };


  return api;
}

// Disable this for now. (No time to install nettle on windows.)
// #include <nettle/sha3.h>
// inline std::string hash_sha3_512(const std::string& str)
// {
//   struct sha3_512_ctx ctx;
//   sha3_512_init(&ctx);
//   sha3_512_update(&ctx, str.size(), (const uint8_t*) str.data());
//   uint8_t h[SHA3_512_DIGEST_SIZE];
//   sha3_512_digest(&ctx, sizeof(h), h);
//   return std::string((const char*)h, sizeof(h));
// }

} // namespace li

#endif // LITHIUM_SINGLE_HEADER_GUARD_LI_HTTP_BACKEND_HTTP_AUTHENTICATION


namespace li {
  using http_api = api<http_request, http_response>;
}

#endif // LITHIUM_SINGLE_HEADER_GUARD_LI_HTTP_BACKEND_HTTP_BACKEND
