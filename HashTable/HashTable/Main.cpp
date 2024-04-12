#include "HashTable.h"
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
    hashTable.display();


    // Randomly select one of the inserted indexes to retrieve and remove
    int randomIndex = rand() % numUnits;
    int retrievedValue = hashTable.retrieve(randomIndex);


    // Remove the retrieved index from the hash table
    hashTable.remove(randomIndex);

    // End timing
    auto endTime = chrono::high_resolution_clock::now();
    double duration = chrono::duration<double, milli>(endTime - startTime).count();

    // Display the hash table after removal
    hashTable.display();

    cout << "Retrieved index " << randomIndex << " with value " << retrievedValue << endl;    // Display the retrieved index and its value
    cout << "Removed index " << randomIndex << ":" << endl;    // Display the removed index

    cout << fixed << setprecision(3);
    cout << "Insertion, retrieval, and removal took " << duration << " milliseconds." << endl;

    return 0;
}
