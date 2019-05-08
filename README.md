#### BiMap - a fixed-size bi-directional static flat map.

Complexity Remarks:
* complexity for searching a value by a key: O(log(i)), where i is the position of the key in the map.
  it is supposed to always be faster then map at searching a value by a key.
* complexity for searching a key by a value: O(n), where n is the number of elements in the map.
  notice that if several identical values exist - the smaller key will be returned.
  
General Remarks:
* Since BiMap was designed only fo searching, it can not modify its data, i.e. - once it was created,
  its elements can not be modified (change vale, change key, remove entry).
* if the key is known at compile time, then the 'get value' operation is performed at compile time (no run time cost).
  same goes for finding the key from a known value.
* requires c++17.
