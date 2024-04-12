#include "LinearProbe.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <cstdlib> 

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    size_t numIndexes, numUnits;
    cout << "Enter the number of indexes: ";
    cin >> numIndexes;
    cout << "Enter the number of units: ";
    cin >> numUnits;

    HashTable<int, int> hashTable(numIndexes);

    // Start timing
    auto startTime = chrono::high_resolution_clock::now();

    // Insert random values into the hash table
    for (int i = 0; i < numUnits; ++i) {
        hashTable.insert(i, i);
    }

    // Randomly select one of the inserted indexes to retrieve and remove
    int randomIndex = rand() % numUnits;
    auto retrievedValue = hashTable.retrieve(randomIndex);

    // Remove the retrieved index from the hash table
    if (retrievedValue) {
        hashTable.remove(*retrievedValue);
    }

    // End timing
    auto endTime = chrono::high_resolution_clock::now();
    double duration = chrono::duration<double, milli>(endTime - startTime).count();

    // Display the hash table after removal
    hashTable.display();

    if (retrievedValue) {
        cout << "Retrieved value at index " << randomIndex << ": " << *retrievedValue << endl;
    }
    else {
        cout << "Key not found at index " << randomIndex << "." << endl;
    }
    cout << "Removed index " << randomIndex << ":" << endl;    // Display the removed index

    cout << fixed << setprecision(3);
    cout << "Insertion, retrieval, and removal took " << duration << " milliseconds." << endl;

    return 0;
}

