#include <iostream>
#include <cstring>
#include <cstdint>
#include <cstdlib>

using namespace std;

// Linked List node
struct node {
    const char* key;
    const char* value;
    node* next;
};

void setNode(node* n, const char* key, const char* value) {
    n->key = key;
    n->value = value;
    n->next = nullptr;
}

struct hashMap {
    int numOfElements, capacity;
    node** arr;
};

void initializeHashMap(hashMap* mp) {
    mp->capacity = 100;
    mp->numOfElements = 0;
    mp->arr = new node * [mp->capacity]();
}

int hashFunction(hashMap* mp, const char* key) {
    int sum = 0, factor = 31;
    for (size_t i = 0; i < strlen(key); i++) {
        sum = (sum + static_cast<int>(key[i]) * factor) % mp->capacity;
        factor = (factor * 31) % INT16_MAX;
    }
    return sum % mp->capacity;
}

void insert(hashMap* mp, const char* key, const char* value) {
    int bucketIndex = hashFunction(mp, key);
    node* newNode = new node;
    setNode(newNode, key, value);
    newNode->next = mp->arr[bucketIndex];
    mp->arr[bucketIndex] = newNode;
    mp->numOfElements++;
}

void deleteKey(hashMap* mp, const char* key) {
    int bucketIndex = hashFunction(mp, key);
    node* prevNode = nullptr, * currNode = mp->arr[bucketIndex];
    while (currNode) {
        if (strcmp(currNode->key, key) == 0) {
            if (prevNode == nullptr) {
                mp->arr[bucketIndex] = currNode->next;
            }
            else {
                prevNode->next = currNode->next;
            }
            delete currNode;
            break;
        }
        prevNode = currNode;
        currNode = currNode->next;
    }
}

const char* search(hashMap* mp, const char* key) {
    int bucketIndex = hashFunction(mp, key);
    node* bucketHead = mp->arr[bucketIndex];
    while (bucketHead) {
        if (strcmp(bucketHead->key, key) == 0) {
            return bucketHead->value;
        }
        bucketHead = bucketHead->next;
    }
    return "Oops! No data found.";
}

int main() {
    hashMap* mp = new hashMap;
    initializeHashMap(mp);
    insert(mp, "Yogaholic", "Anjali");
    insert(mp, "pluto14", "Vartika");
    insert(mp, "elite_Programmer", "Manish");
    insert(mp, "GFG", "GeeksforGeeks");
    insert(mp, "decentBoy", "Mayank");

    cout << search(mp, "elite_Programmer") << endl;
    cout << search(mp, "Yogaholic") << endl;
    cout << search(mp, "pluto14") << endl;
    cout << search(mp, "decentBoy") << endl;
    cout << search(mp, "GFG") << endl;

    cout << "\nAfter deletion: \n";
    deleteKey(mp, "decentBoy");
    cout << search(mp, "decentBoy") << endl;

    return 0;
}
