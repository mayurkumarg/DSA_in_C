#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10
#define MAX_FACES 4

typedef struct PITEntry {
    unsigned int fingerprint;
    unsigned int expiration;
    unsigned int faces;
    int occupied;
} PITEntry;

PITEntry hashTable[TABLE_SIZE];

unsigned int hashFunction(unsigned int fingerprint) {
    return fingerprint % TABLE_SIZE;
}

void insertPIT(unsigned int fingerprint, unsigned int expiration, unsigned int face) {
    if (face >= MAX_FACES) {
        printf("Error: Face index %u exceeds the maximum allowed faces (%d).\n", face, MAX_FACES - 1);
        return;
    }

    unsigned int index = hashFunction(fingerprint);
    unsigned int originalIndex = index;

    while (hashTable[index].occupied == 1) {
        index = (index + 1) % TABLE_SIZE;
        if (index == originalIndex) {
            printf("Error: Hash table is full. Cannot insert fingerprint %u.\n", fingerprint);
            return;
        }
    }

    hashTable[index].fingerprint = fingerprint;
    hashTable[index].expiration = expiration;
    hashTable[index].faces |= (1 << face);
    hashTable[index].occupied = 1;

    printf("Inserted fingerprint %u at index %u with face %u\n", fingerprint, index, face);
}

int searchPIT(unsigned int fingerprint) {
    unsigned int index = hashFunction(fingerprint);
    unsigned int originalIndex = index;

    while (hashTable[index].occupied == 1) {
        if (hashTable[index].fingerprint == fingerprint) {
            return index;
        }
        index = (index + 1) % TABLE_SIZE;
        if (index == originalIndex) {
            break;
        }
    }
    return -1;
}

void printPIT() {
    printf("\nPIT Content:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashTable[i].occupied) {
            printf("Index %d: Fingerprint = %u, Expiration = %u, Faces = %u (bit vector)\n",
                   i, hashTable[i].fingerprint, hashTable[i].expiration, hashTable[i].faces);
        }
    }
}

int checkFaceRequest(unsigned int fingerprint, unsigned int face) {
    if (face >= MAX_FACES) {
        printf("Error: Face index %u exceeds the maximum allowed faces (%d).\n", face, MAX_FACES - 1);
        return 0;
    }

    int index = searchPIT(fingerprint);
    if (index != -1) {
        return (hashTable[index].faces & (1 << face)) != 0;
    }
    return 0;
}

int main() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i].occupied = 0;
        hashTable[i].faces = 0;
    }

    unsigned int fingerprint, expiration, face;
    int numEntries;

    printf("Enter number of PIT entries to insert: ");
    scanf("%d", &numEntries);

    for (int i = 0; i < numEntries; i++) {
        printf("Enter fingerprint (number) for entry %d: ", i + 1);
        scanf("%u", &fingerprint);
        printf("Enter expiration time (in seconds) for entry %d: ", i + 1);
        scanf("%u", &expiration);
        printf("Enter face index (0 to 3) for entry %d: ", i + 1);
        scanf("%u", &face);
        insertPIT(fingerprint, expiration, face);
    }

    unsigned int checkFingerprint, checkFace;
    printf("Enter fingerprint to check: ");
    scanf("%u", &checkFingerprint);
    printf("Enter face index to check (0 to 3): ");
    scanf("%u", &checkFace);

    printf("\nFace %u requested fingerprint %u: %s\n", checkFace, checkFingerprint,
           checkFaceRequest(checkFingerprint, checkFace) ? "Yes" : "No");

    printPIT();

    return 0;
}
