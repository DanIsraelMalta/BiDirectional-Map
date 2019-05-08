#include "BiMap.h"
#include "ExecutionTimer.h"
#include <iostream>
#include <map>
#include <unordered_map>
#include <chrono>

int main() {

    int indices[] = { 1, 2, 3, 8, 9, 10, 16, 17, 18 };

    // compiled with -O3 optimization)
    for (std::size_t k{}; k < 9; ++k) {
        std::cout << "iteration #" << std::to_string(k) << std::endl;

        // --- BiMap performance test ---
        BiMap<18, int, char> Map(std::make_pair(1, '1'), std::make_pair(2, '2'), std::make_pair(3, '3'),
            std::make_pair(4, '4'), std::make_pair(5, '5'), std::make_pair(6, '6'),
            std::make_pair(7, '7'), std::make_pair(8, '8'), std::make_pair(9, '9'),
            std::make_pair(10, 'A'), std::make_pair(11, 'B'), std::make_pair(12, 'C'),
            std::make_pair(13, 'D'), std::make_pair(14, 'E'), std::make_pair(15, 'F'),
            std::make_pair(16, 'G'), std::make_pair(17, 'H'), std::make_pair(18, 'I'));

        {
            ExecutionTimer<std::chrono::microseconds> timer("bimap");
            for (std::size_t i{}; i < 10'000'000; ++i) {
                for (int n : indices) {
                    const char a0{ Map.GetValueOfKey(n) };
                }
                //int key9{ Map.GetKeyOfValue("90") };
            }
        }

        // --- std::map performance test ---
        std::map<int, char> a{ { 1, '1' }, { 2, '2' }, { 3, '3' },
                               { 4, '4' }, { 5, '5' }, { 6, '6' },
                               { 7, '7' }, { 8, '8' }, { 9, '9' },
                               { 10, 'A' }, { 11, 'B' }, { 12, 'C' },
                               { 13, 'D' }, { 14, 'E' }, { 15, 'F' },
                               { 16, 'G' }, { 17, 'H' }, { 18, 'I' } };

        {
            ExecutionTimer<std::chrono::microseconds> timer2("std::map");
            for (std::size_t i{}; i < 10'000'000; ++i) {
                for (int n : indices) {
                    const char a0{ a[n] };
                }
            }
        }

        // --- std::unordered_map performance test ---
        std::unordered_map<int, char> b;
        b.insert(std::make_pair(1, '1'));
        b.insert(std::make_pair(2, '2'));
        b.insert(std::make_pair(3, '3'));
        b.insert(std::make_pair(4, '4'));
        b.insert(std::make_pair(5, '5'));
        b.insert(std::make_pair(6, '6'));
        b.insert(std::make_pair(7, '7'));
        b.insert(std::make_pair(8, '8'));
        b.insert(std::make_pair(9, '9'));
        b.insert(std::make_pair(10, 'A'));
        b.insert(std::make_pair(11, 'B'));
        b.insert(std::make_pair(12, 'C'));
        b.insert(std::make_pair(13, 'D'));
        b.insert(std::make_pair(14, 'E'));
        b.insert(std::make_pair(15, 'F'));
        b.insert(std::make_pair(16, 'G'));
        b.insert(std::make_pair(17, 'H'));
        b.insert(std::make_pair(18, 'I'));

        {
            ExecutionTimer<std::chrono::microseconds> timer3("std::unordered_map");
            for (std::size_t i{}; i < 10'000'000; ++i) {
                for (int n : indices) {
                    const char a0{ b[n] };
                }
            }
        }
    }

    return 1;
}
