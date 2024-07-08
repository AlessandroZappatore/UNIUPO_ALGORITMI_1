#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definition of a slot in the hash table
typedef struct {
    char* key;
    int value;
    int tombstone; // 0 for active, 1 for tombstone
} HashTableSlot;

// Definition of the hash table with linear probing
typedef struct {
    HashTableSlot* table;
    int size;
    int (*hash)(const char*);
} HashTable;

// Hash function for strings
int hashFunction(const char* key) {
    int hash = 0;
    while (*key) {
        hash = (hash * 31 + *key) % 10;
        key++;
    }
    return hash;
}

// Function to count collisions for a single key
int countCollisions(HashTable* ht, const char* key) {
    int hash = ht->hash(key) % ht->size;
    int collisions = 0;

    for (int i = 0; i < ht->size; i++) {
        int index = (hash + i) % ht->size;
        if (ht->table[index].key == NULL || ht->table[index].tombstone || strcmp(ht->table[index].key, key) == 0) {
            break;
        }
        collisions++;
    }

    return collisions;
}

// Function to find the maximum number of collisions
int maxCollisions(HashTable* ht, const char** keys, int keyCount) {
    int maxCollisions = 0;

    for (int i = 0; i < keyCount; i++) {
        int collisions = countCollisions(ht, keys[i]);
        if (collisions > maxCollisions) {
            maxCollisions = collisions;
        }
    }

    return maxCollisions;
}

// Function to calculate the average number of collisions for a list of keys
double upo_ht_linprobk_avg_collisions(HashTable* ht, const char** keys, int keyCount) {
    if (keyCount == 0) return -1;

    int total_collisions = 0;
    int valid_keys = 0;

    for (int i = 0; i < keyCount; i++) {
        const char* key = keys[i];
        int hash = ht->hash(key) % ht->size;
        int collisions = 0;
        int found = 0;

        for (int j = 0; j < ht->size; j++) {
            int index = (hash + j) % ht->size;

            if (ht->table[index].tombstone || (ht->table[index].key && strcmp(ht->table[index].key, key) != 0)) {
                collisions++;
            } else if (ht->table[index].key && strcmp(ht->table[index].key, key) == 0) {
                total_collisions += collisions;
                valid_keys++;
                found = 1;
                break;
            } else if (ht->table[index].key == NULL && !ht->table[index].tombstone) {
                break;
            }
        }

        if (!found) {
            continue;
        }
    }

    if (valid_keys == 0) return -1;

    return (double)total_collisions / valid_keys;
}

// Example usage
int main() {
    // Constructing a sample hash table
    HashTableSlot table[10] = {{0}};
    HashTable ht = {table, 10, hashFunction};

    // Example keys
    const char* keys[] = {"A", "B", "C", "Q", "R"};

    // Insert keys and mark slots (example, assuming hash function and linear probing logic)
    table[ht.hash("A") % 10] = (HashTableSlot){"A", 1, 0};
    table[ht.hash("B") % 10] = (HashTableSlot){"B", 2, 0};
    table[ht.hash("C") % 10] = (HashTableSlot){"C", 3, 0}; // Example collision for "C"
    table[ht.hash("Q") % 10] = (HashTableSlot){"Q", 4, 0};
    table[ht.hash("R") % 10] = (HashTableSlot){"R", 5, 0}; // Example collision for "E"

    // Find the maximum number of collisions
    int maxCollisionsResult = maxCollisions(&ht, keys, 5);
    printf("Max number of collisions: %d\n", maxCollisionsResult);

    // Calculate the average number of collisions
    double avgCollisionsResult = upo_ht_linprobk_avg_collisions(&ht, keys, 5);
    printf("Average number of collisions: %.2f\n", avgCollisionsResult);

    return 0;
}
