#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <iostream>

using namespace std;

template<typename Key, typename Value>
class HashTable {
private:
    vector<pair<Key, Value>> table;
    size_t size;

    size_t hash1(const Key& key) const {
        // First hash function
        return hash<Key>{}(key) % size;
    }

    size_t hash2(const Key& key) const {
        // Second hash function
        // Adjust as needed to avoid infinite loops and achieve good performance
        // For simplicity, using a linear probing approach for demonstration
        return 1 + (hash<Key>{}(key) % (size - 1));
    }

public:
    HashTable(size_t initialSize) : size(initialSize), table(initialSize, make_pair(Key(), Value())) {}


    void insert(const Key& key, const Value& value) {
        size_t index = hash1(key);
        size_t step = hash2(key);
        size_t originalIndex = index;

        // Probe until an empty slot is found
        while (!table[index].first.empty()) {
            index = (index + step) % size;
            if (index == originalIndex) {
                cerr << "HashTable is full, unable to insert." << endl;
                return;
            }
        }

        table[index] = make_pair(key, value);
    }

    Value retrieve(const Key& key) const {
        size_t index = hash1(key);
        size_t step = hash2(key);
        size_t originalIndex = index;

        // Probe until either the key is found or an empty slot is encountered
        while (!table[index].first.empty() && table[index].first != key) {
            index = (index + step) % size;
            if (index == originalIndex)
                break;
        }

        if (index < size && !table[index].first.empty() && table[index].first == key)
            return table[index].second;
        else
            return Value(); // return default-constructed Value if key not found
    }

    void remove(const Key& key) {
        size_t index = hash1(key);
        size_t step = hash2(key);
        size_t originalIndex = index;

        // Probe until either the key is found or an empty slot is encountered
        while (!table[index].first.empty() && table[index].first != key) {
            index = (index + step) % size;
            if (index == originalIndex)
                return; // Key not found, exit
        }

        if (index < size && !table[index].first.empty() && table[index].first == key)
            table.erase(table.begin() + index); // Erase the element from the table
    }


    void display() const {
        for (size_t i = 0; i < size; ++i) {
            if (!table[i].first.empty()) {
                cout << "Index " << i << ": ";
                cout << "(" << table[i].first << ", " << table[i].second << ") ";
            }
            else {
                cout << "Index " << i << ": Empty ";
            }
            cout << endl;
        }
    }
};

#endif
