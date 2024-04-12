#include <vector>
#include <functional>
#include <iostream>
#include <optional>

using namespace std;

template<typename Key, typename Value>
class HashTable {
private:
    struct Bucket {
        Key key;
        Value value;
        bool occupied = false; // check if the spot is occupied
    };

    vector<optional<Bucket>> table;
    size_t capacity;
    size_t size; // Number of elements currently in the hash table

    size_t hash(const Key& key) const {
        return std::hash<Key>{}(key) % capacity;
    }

    void resize() {
        size_t newCapacity = capacity * 2; // Double the capacity
        vector<optional<Bucket>> newTable(newCapacity);

        // Rehash all existing elements into the new table
        for (const auto& optBucket : table) {
            if (optBucket && optBucket->occupied) {
                size_t index = hash(optBucket->key);
                size_t originalIndex = index;
                while (newTable[index] && newTable[index]->occupied) {
                    index = (index + 1) % newCapacity;
                    if (index == originalIndex) {
                        throw runtime_error("HashTable is full");
                    }
                }
                newTable[index] = *optBucket;
            }
        }

        // Replace the old table with the new one
        table = move(newTable);
        capacity = newCapacity;
    }

public:
    HashTable(size_t initialCapacity) : capacity(initialCapacity), table(initialCapacity), size(0) {}

    void insert(const Key& key, const Value& value) {
        if (size >= capacity / 2) {
            resize();
        }

        size_t index = hash(key);
        size_t original_index = index;
        while (table[index] && table[index]->occupied) {
            if (table[index]->key == key) {
                // Overwrite the value if the key already exists
                table[index]->value = value;
                return;
            }
            index = (index + 1) % capacity;
            if (index == original_index) {
                throw runtime_error("HashTable is full");
            }
        }
        table[index] = Bucket{ key, value, true };
        size++;
    }

    optional<Value> retrieve(const Key& key) const {
        size_t index = hash(key);
        size_t original_index = index;
        while (table[index]) {
            if (table[index]->occupied && table[index]->key == key) {
                return table[index]->value;
            }
            index = (index + 1) % capacity;
            if (index == original_index) {
                break;
            }
        }
        return nullopt; // Key not found
    }

    void remove(const Key& key) {
        size_t index = hash(key);
        size_t original_index = index;
        while (table[index]) {
            if (table[index]->occupied && table[index]->key == key) {
                table[index]->occupied = false; // Lazy deletion
                size--;
                return;
            }
            index = (index + 1) % capacity;
            if (index == original_index) {
                return; // Key not found
            }
        }
    }

    void display() const {
        for (size_t i = 0; i < capacity; ++i) {
            cout << "Index " << i << ": ";
            if (table[i] && table[i]->occupied) {
                cout << "(" << table[i]->key << ", " << table[i]->value << ") ";
            }
            else {
                cout << "Empty ";
            }
            cout << endl;
        }
    }
};
