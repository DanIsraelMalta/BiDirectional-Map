BiMap is a fixed-size bi-directional flat map.
It is designed purely for the purpose of key/value searching, so once it is created - it can not be modified.
However, since it is used only for searching - it is quite fast...

Complexity Remarks:
* complexity for searching a value by a key: O(log(i)), where i is the position of the key in the map.
  it is supposed to always be faster then map at searching a value by a key, and faster or with equal performance
  to unordered_map.
* complexity for searching a key by a value: O(n), where n is the number of elements in the map.
  notice that if several identical values exist - the smaller key will be returned.
 
Example usage and perofrmance comparison againt std::map and std::unordered_map:

```c
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
         ExecutionTimer<std::chrono::microseconds> timer;
         for (std::size_t i{}; i < 10'000'000; ++i) {
             const char a0{ Map.GetValueOfKey(1) },
                        a1{ Map.GetValueOfKey(2) },
                        a2{ Map.GetValueOfKey(3) },
                        a8{ Map.GetValueOfKey(8) },
                        a9{ Map.GetValueOfKey(9) },
                        a10{ Map.GetValueOfKey(10) },
                        a16{ Map.GetValueOfKey(16) },
                        a17{ Map.GetValueOfKey(17) },
                        a18{ Map.GetValueOfKey(18) };
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
         ExecutionTimer<std::chrono::microseconds> timer2;
         for (std::size_t i{}; i < 10'000'000; ++i) {
             const char a0{ a[1] },
                        a1{ a[2] },
                        a2{ a[3] },
                        a8{ a[8] },
                        a9{ a[9] },
                        a10{ a[10] },
                        a16{ a[16] },
                        a17{ a[17] },
                        a18{ a[18] };
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
         ExecutionTimer<std::chrono::microseconds> timer3;
         for (std::size_t i{}; i < 10'000'000; ++i) {
             const char a0{ b[1] },
                        a1{ b[2] },
                        a2{ b[3] },
                        a8{ b[8] },
                        a9{ b[9] },
                        a10{ b[10] },
                        a16{ b[16] },
                        a17{ b[17] },
                        a18{ b[18] };
         }
     }
}
```

output:


```c
iteration #0
 BiMap elapsed: 443695
 std::map elapsed: 702471
 std::unordered_map elapsed: 425264
iteration #1
 BiMap elapsed: 316105
 std::map: 603340
 std::unordered_map: 334658
iteration #2
 BiMap elapsed: 292862
 std::map: 569295
 std::unordered_map: 328108
iteration #3
 BiMap elapsed: 295401
 std::map: 572511
 std::unordered_map: 333907
iteration #4
 BiMap elapsed: 291025
 std::map: 610111
 std::unordered_map: 326676
iteration #5
 BiMap elapsed: 290004
 std::map: 567296
 std::unordered_map: 331655
iteration #6
 BiMap elapsed: 296455
 std::map: 574306
 std::unordered_map: 339036
iteration #7
 BiMap elapsed: 294581
 std::map: 572326
 std::unordered_map: 332962
iteration #8
 BiMap elapsed: 303746
 std::map: 567782
 std::unordered_map: 328090
```
