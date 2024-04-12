#include "DoubleHash.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>


using namespace std;

int main() {
    size_t numIndexes, numUnits;
    cout << "Enter the number of indexes: ";
    cin >> numIndexes;
    cout << "Enter the number of units: ";
    cin >> numUnits;

    HashTable<int, int> hashTable(numIndexes);

    auto startTime = chrono::high_resolution_clock::now();

    for (int i = 0; i < numUnits; ++i) {
        // For simplicity, we'll just insert numbers as both keys and values
        hashTable.insert(i, i);
    }

    auto endTime = chrono::high_resolution_clock::now();
    double duration = chrono::duration<double, milli>(endTime - startTime).count();


    hashTable.display();

    // Testing retrieve function
    cout << "Enter a key to retrieve its value: ";
    int key;
    cin >> key;
    int retrievedValue = hashTable.retrieve(key);
    if (retrievedValue != 0)
        cout << "Retrieved value: " << retrievedValue << endl;
    else
        cout << "Key not found." << endl;

    // Testing remove function
    cout << "Enter a key to remove: ";
    cin >> key;
    hashTable.remove(key);
    cout << "After removal:" << endl;
    hashTable.display();

    cout << fixed << setprecision(3);
    cout << "Insertion took " << duration << " milliseconds." << endl;


    return 0;
}
