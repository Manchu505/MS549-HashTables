#include <vector>
#include <list>
#include <functional>
#include <chrono>
#include <iostream>

using namespace std;

template<typename Key, typename Value>
class HashTable {
private:
    vector<list<pair<Key, Value>>> table;
    size_t size;

    size_t hash(const Key& key) const {
       return std::hash<Key>{}(key) % table.size();
    }

public:
    HashTable(size_t initialSize) : size(initialSize), table(initialSize) {}

    void insert(const Key& key, const Value& value) {
        size_t index = hash(key);
        table[index].push_back(make_pair(key, value));
    }

    Value retrieve(const Key& key) const {
        size_t index = hash(key);
        for (const auto& pair : table[index]) {
            if (pair.first == key)
                return pair.second;
        }
        return Value(); // return default Value if key not found
    }

    void remove(const Key& key) {
        size_t index = hash(key);
        auto& list = table[index];
        for (auto it = list.begin(); it != list.end(); ++it) {
            if (it->first == key) {
                list.erase(it);
                return;
            }
        }
    }

    void display() const {
        for (size_t i = 0; i < size; ++i) {
            cout << "Index " << i << ": ";
            for (const auto& pair : table[i]) {
                cout << "(" << pair.first << ", " << pair.second << ") ";
            }
            cout << endl;
        }
    }
};