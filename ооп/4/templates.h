#ifndef D_TEMPLATES_H_
#define D_TEMPLATES_H_ 1

#include <tuple>
#include <type_traits>

#include "vertex.h"

//basic
template<class T>
struct is_vertex : std::false_type {};

template<class T>
struct is_vertex<vertex<T>> : std::true_type {};

template<class T>
struct is_figurelike_tuple : std::false_type {};

template<class Head, class... Tail>
  struct is_figurelike_tuple<std::tuple<Head, Tail...>> :
  std::conjunction<is_vertex<Head>,
  std::is_same<Head, Tail>...> {};

template<class Type, size_t SIZE>
  struct is_figurelike_tuple<std::array<Type, SIZE>> :
  is_vertex<Type> {};

template<class T>
inline constexpr bool is_figurelike_tuple_v =
  is_figurelike_tuple<T>::value;

//center
template<class T, class = void>
  struct has_center_method : std::false_type {};

template<class T>
struct has_center_method<T,
  std::void_t<decltype(std::declval<const T>().center())>> :
  std::true_type {};

template<class T>
inline constexpr bool has_center_method_v =
  has_center_method<T>::value;

template<class T>
std::enable_if_t<has_center_method_v<T>, vertex<double>>
  center(const T& figure) {
  return figure.center();
}

template<class T>
inline constexpr const int tuple_size_v = std::tuple_size<T>::value;

template<size_t ID, class T>
  vertex<double> sngl_center(const T& t) {
  vertex<double> v;
  v.x = std::get<ID>(t).x;
  v.y = std::get<ID>(t).y;
  v.x = v.x / std::tuple_size_v<T>;
  v.y = v.y / std::tuple_size_v<T>;
  return v;
}

template<size_t ID, class T>
  vertex<double> rcrsv_center(const T& t) {
  if constexpr (ID < std::tuple_size_v<T>){
      return  {sngl_center<ID>(t).x + rcrsv_center<ID+1>(t).x, sngl_center<ID>(t).y + rcrsv_center<ID+1>(t).y};
    } else {
    vertex<double> v;
    v.x = 0;
    v.y = 0;
    return v;
  }
}

template<class T>
std::enable_if_t<is_figurelike_tuple_v<T>, vertex<double>>
  center(const T& tuple) {
  return rcrsv_center<0>(tuple);
}

//area
template<class T, class = void>
  struct has_area_method : std::false_type {};

template<class T>
struct has_area_method<T,
  std::void_t<decltype(std::declval<const T>().area())>> :
  std::true_type {};

template<class T>
inline constexpr bool has_area_method_v =
  has_area_method<T>::value;

template<class T>
std::enable_if_t<has_area_method_v<T>, double>
  area(const T& figure) {
  return figure.area();
}

template<size_t ID, class T>
  double sngl_area(const T& t) {
  const auto& a = std::get<0>(t);
  const auto& b = std::get<ID - 1>(t);
  const auto& c = std::get<ID>(t);
  const double dx1 = b.x - a.x;
  const double dy1 = b.y - a.y;
  const double dx2 = c.x - a.x;
  const double dy2 = c.y - a.y;
  return std::abs(dx1 * dy2 - dy1 * dx2) * 0.5;
}

template<size_t ID, class T>
  double rcrsv_area(const T& t) {
  if constexpr (ID < std::tuple_size_v<T>){
      return sngl_area<ID>(t) + rcrsv_area<ID + 1>(t);
    }
  return 0;
}

template<class T>
std::enable_if_t<is_figurelike_tuple_v<T>, double>
  area(const T& tuple) {
  return rcrsv_area<2>(tuple);
}

//print
template<class T, class = void>
  struct has_print_method : std::false_type {};

template<class T>
struct has_print_method<T,
  std::void_t<decltype(std::declval<const T>().print(std::cout))>> :
  std::true_type {};
    
template<class T>
inline constexpr bool has_print_method_v =
  has_print_method<T>::value;

template<class T>
std::enable_if_t<has_print_method_v<T>, void>
  print (const T& figure,std::ostream& os) {
  return figure.print(os);
}

template<size_t ID, class T>
  void sngl_print(const T& t) {
  std::cout << "[" << std::get<ID>(t) << "]";
  if (ID < 3){
    std::cout << " ";
  }
  return ;
}

template<size_t ID, class T>
  void rcrsv_print(const T& t) {
  if constexpr (ID < std::tuple_size_v<T>){
      sngl_print<ID>(t);
      rcrsv_print<ID+1>(t);
      return ;
    }
  return;
}

template<class T>
std::enable_if_t<is_figurelike_tuple_v<T>, void>
  print(const T& tuple) {
  return rcrsv_print<0>(tuple);
}

#endif // D_TEMPLATES_H_
