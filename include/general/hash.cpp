#include <assert.h>
#include <stdint.h>
#include <string.h>

#include <nmmintrin.h>

#include "general/debug.h"

#include "hash.h"

const int ROL_HASH_SHIFT = 5;

hash_t hash(const void* ptr, size_t size){
    assert(ptr);

    hash_t hash = 5381;
    for(size_t curByteInd = 0; curByteInd < size; curByteInd++){
        hash =((hash << 5) + hash) + (unsigned char) (*((const char*)ptr + curByteInd));
    }

    return hash;
}

hash_t constHash(hashData_t str){
    assert(str);
    
    return 0;
}

hash_t lenHash(hashData_t str){
    assert(str);

    return strlen(str);
}

hash_t firstSymHash(hashData_t str){
    assert(str);

    return *str;
}

hash_t sumHash(hashData_t str){
    assert(str);

    hash_t sum = 0;
    for(size_t i = 0; str[i] != '\0'; i++){
        sum += (hash_t) str[i];
    }

    return sum;
}

hash_t gnuHash(hashData_t str){
    assert(str);

    hash_t hash = 5381;

    for (unsigned char c = *str; c != '\0'; c = *++str) {
        hash = (hash << 5) + hash + c; // h * 33 + c
    }

    return hash;
}

hash_t crcHash(hashData_t str){
    assert(str);

    uint32_t crc = 0xFFFFFFFF;

    for(size_t i = 0; str[i] != '\0'; i++){
        crc ^= str[i];

        for(int j = 0; j < 8; j++){
            if(crc & 1){
                crc = (crc >> 1) ^ 0xEDB88320;
            }
            else{
                crc >>= 1;
            }
        }
    }

    return (hash_t) (~crc);
}

hash_t rolHash(hashData_t str){
    assert(str);

    uint32_t hash = 0;

    for(size_t i = 0; str[i] != '\0'; i++){
        hash = (hash << ROL_HASH_SHIFT) | (hash >> 32 - ROL_HASH_SHIFT);    
        hash ^= str[i];
    }
    
    return (hash_t) (hash);
}

hash_t murMurHash(hashData_t str){
    assert(str);

    uint32_t hash = 0;
    uint32_t c1   = 0xcc9e2d51;
    uint32_t c2   = 0x1b873593;

    int len       = strlen(str);

    for(size_t i = 0; i < len; i++){
        uint32_t k = str[i];

        k *= c1;
        k = (k << 15) | (k >> 17);
        k *= c2;

        hash ^= k;
        hash = (hash << 13) | (hash >> 19);
        hash = hash * 5 + 0xe6546b64;
    }

    hash ^= len;
    hash ^= hash >> 16;
    hash *= 0x85ebca6b;
    hash ^= hash >> 13;
    hash *= 0xc2b2ae35;
    hash ^= hash >> 16;

    return (hash_t) hash; 
}

hash_t crcOptimizedHash(hashData_t str){
    assert(str);

    uint32_t crc = 0xFFFFFFFF;
    
    for(size_t i = 0; str[i] != '\0'; i++){
        crc = _mm_crc32_u8(crc, (uint8_t)str[i]);
    }

    return (hash_t) (~crc);
}

hash_t crcUnwrapOptimizedHash(hashData_t str){
    assert(str);

    uint64_t crc = 0xFFFFFFFFFFFFFFFF;

    size_t len = strlen(str);
    const uint8_t* p = (const uint8_t*)str;

    while (len >= 8) {
        uint64_t chunk;
        memcpy(&chunk, p, sizeof(chunk));
        crc = _mm_crc32_u64(crc, chunk);

        p += 8;
        len -= 8;
    }

    while (len > 0) {
        crc = _mm_crc32_u8(crc, *p);
        p++;
        len--;
    }

    return ~crc;
}