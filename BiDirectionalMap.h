/**
* BiMap is a fixed-size bi-directional flat map.
*
* Complexity Remarks:
* > complexity for searching a value by a key: O(log(i)), where i is the position of the key in the map.
*   it is supposed to always be faster then map at searching a value by a key.
* > complexity for searching a key by a value: O(n), where n is the number of elements in the map.
*   notice that if several identical values exist - the smaller key will be returned.
*
* General Remarks:
* > Since BiMap was designed only fo searching, it can not modify its data, i.e. - once it was created,
*   its elements can not be modified (change vale, change key, remove entry).
* > if the key is known at compile time, then the 'get value' operation is performed at compile time (no run time cost).
*   same goes for finding the key from a known value.
* > requires c++17.
*
* Dan Israel Malta
**/
#pragma once
#include<type_traits>
#include<cstdint>
#include<utility>
#include<algorithm>
#include<array>
#include<assert.h>

// type traits
namespace {
    // type trait to test if a given object has the '==' operator
    template<typename T, typename R, typename = R> struct has_equality_operator : std::false_type {};
    template<typename T, typename R>               struct has_equality_operator<T, R, decltype(std::declval<T>() == std::declval<R>())> : std::true_type {};
    template<typename T, typename R = bool>        struct equality_operator_exist : has_equality_operator<T, R> {};

    // type trait to test if a given object has the '>' operator
    template<typename T, typename R, typename = R> struct has_greater_than_operator : std::false_type {};
    template<typename T, typename R>               struct has_greater_than_operator<T, R, decltype(std::declval<T>() > std::declval<R>())> : std::true_type{};
    template<typename T, typename R = bool>        struct greater_than_operator_exist : has_greater_than_operator<T, R> {};
};

/**
* \brief fixed-size bi-directional flat map
* 
* @param {std::size_t, in} number of items/entrys in dictionary
* @param {KEY,     in} key type (must support '==' & '>' operators and have a default constructor)
* @param {VALUE,   in} value type (must support '==' & '>' operators and have a default constructor)
**/
template<std::size_t N, class KEY, class VALUE> class BiMap {
    static_assert(equality_operator_exist<KEY>::value,       "BiMap<M, KEY, VALU>: KEY must support the '==' operator.");
    static_assert(greater_than_operator_exist<KEY>::value,   "BiMap<M, KEY, VALU>: KEY must support the '>' operator.");
    static_assert(equality_operator_exist<VALUE>::value,     "BiMap<M, KEY, VALU>: VALUE must support the '==' operator.");
    static_assert(greater_than_operator_exist<VALUE>::value, "BiMap<M, KEY, VALU>: VALUE must support the '>' operator.");

    // aliases and properties
    private:
        using Item = std::pair<KEY, VALUE>;
        alignas(typename std::aligned_storage<sizeof(Item), alignof(Item)>::type) std::array<Item, N> dictionary;

    // internal helpers
    private:

        // sort (according to keys) and assert if there are duplicate keys
        void Sort();

        /**
        * \brief recursive binary search
        * 
        * @param {KEY,     in}  key
        * @param {std::size_t, in}  index of serching region left boundary
        * @param {std::size_t, in}  index of serching region right boundary
        * @param {VALUE,   out} value (if not found, return a defaulT VALUE)
        **/
        constexpr inline VALUE BinarySearch(const KEY key, std::size_t left, std::size_t right);

    // constructor
    public:

        explicit constexpr BiMap(std::array<Item, N> xi_dictionary)                      : dictionary(xi_dictionary) { Sort(); }
        explicit constexpr BiMap(std::initializer_list<Item>&& xi_list)                  : dictionary(reinterpret_cast<const std::array<Item, N>&>(*xi_list.begin())) { Sort(); }
        template<class ... Items> explicit constexpr BiMap(Item first, Items&&... items) : BiMap{ first, std::forward<Item>(static_cast<Item>(items))... } { Sort(); }

    // queries
    public:
        /**
        * \brief return the value of a given key (O(log2(index of n))) using exponential search
        *
        * @param {KEY,   in}  key
        * @param {VALUE, out} value (if not found, return a defaulT VALUE)
        **/
        constexpr inline VALUE GetValueOfKey(const KEY key);

        /**
        * \brief return the key of a given value (O(n))
        *        if there are several identical value's, return the key of
        *        the first value according to dictionary construction order
        *
        * @param {VALUE, int} value
        * @param {KEY,   out} key (if not found, return a defaulT KEY)
        **/
        constexpr inline KEY GetKeyOfValue(const VALUE value);
};

template<std::size_t N, class KEY, class VALUE> 
void BiMap<N, KEY, VALUE>::Sort() {
    // sort
    std::sort(dictionary.begin(), dictionary.end(), [](const Item& left, const Item& right) {
        return (left.first < right.first);
    });

    // alert for duplicate keys
    auto it = std::adjacent_find(dictionary.begin(), dictionary.end(), [](const Item& left, const Item& right) {
        return (left.first == right.first);
    });
    assert(it == dictionary.end() && " BiMap was constructed with a duplicate key!");
}

template<std::size_t N, class KEY, class VALUE> 
constexpr VALUE BiMap<N, KEY, VALUE>::BinarySearch(const KEY key, std::size_t left, std::size_t right) {
    // region center point
    std::size_t middle{};

    while (left != right) {
        // update range center
        middle = left + (right - left) / 2;

        // update regions
        if (dictionary[middle].first < key) {
            left = middle;
        } else {
            right = middle - 1;
        }
    }

    if (left == right) return dictionary[middle].second;

    // key not found
     return VALUE{};
}

template<std::size_t N, class KEY, class VALUE>
constexpr VALUE BiMap<N, KEY, VALUE>::GetValueOfKey(const KEY key) {
    if (dictionary[0].first == key) return dictionary[0].second;

    // "exponential search"
    std::size_t i{ 1 };
    while ((i < N) && (dictionary[i].first < key)) i *= 2;

    // apply binary search
    return BinarySearch(key, i / 2, (i + 1 < N) ? (i + 1) : N); 
}

template<std::size_t N, class KEY, class VALUE>
constexpr KEY BiMap<N, KEY, VALUE>::GetKeyOfValue(const VALUE value)
{
    bool found{ false };
    std::size_t i{};

    for (; !found && (i < N); ++i)
        found = dictionary[i].second == value;

    if (found) return dictionary[i - 1].first;
    return KEY{};
}
