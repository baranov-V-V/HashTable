#include "Hash.h"

uint64_t Ror(uint64_t key, int value) {
    assert(value >= 0);
    return (key >> value) | (key << sizeof(uint64_t) * 8 - value);
}

uint64_t Rol(uint64_t key, int value) {
    assert(value >= 0);
    return (key << value) | (key >> sizeof(uint64_t) * 8 - value);
}

uint64_t HashFunc1(char* key) {
    uint64_t hash_val = 0;
    return hash_val;
};

uint64_t HashFunc2(char* key) {
    uint64_t hash_val = 0;
    hash_val = key[0];
    return hash_val;
};

uint64_t HashFunc3(char* key) {
    uint64_t hash_val = 0;
    hash_val = strlen(key);
    return hash_val;
};

uint64_t HashFunc4(char* key) {
    uint64_t hash_val = 0;

    for (int i = 0; key[i] != '\0'; ++i) {
        hash_val += key[i];
    }

    return hash_val;
};

uint64_t HashFunc5(char* key) {
    uint64_t hash_val = 0;

    for (int i = 0; key[i] != '\0'; ++i) {
        hash_val = Ror(hash_val, 1) ^ key[i];
    }

    return hash_val;
};

uint64_t HashFunc6(char* key) {
    uint64_t hash_val = 0;

    for (int i = 0; key[i] != '\0'; ++i) {
        hash_val = Rol(hash_val, 1) ^ key[i];
    }

    return hash_val;
};
