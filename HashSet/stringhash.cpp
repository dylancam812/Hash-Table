#include <cs70/stringhash.hpp>

using std::string;

namespace {

// repeatedly multiplies and shifts the hash values
size_t djb2(const std::string& key) {
    size_t hash = 5381;

    for (auto i = key.begin(); i != key.end(); ++i) {
        hash = hash * 33 + *i;
    }

    return hash;
}

// multplies the hash value by powers of p and divides by m
size_t computeHash(string const& s) {
    const int p = 31;
    const int m = 1e9 + 9;
    size_t hash_value = 0;
    size_t p_pow = 1;
    for (char c : s) {
        hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return hash_value;
}

// repeatedly shifts the hash value
size_t sdbm(const std::string& key) {
    size_t hash = 0;

    for (auto i = key.begin(); i != key.end(); ++i) {
        hash = *i + (hash << 6) + (hash << 16) - hash;
    }
    return hash;
}

size_t myhash(const string& str) {
    return computeHash(str);
}

std::initializer_list<HashFunctionInfo> hashInfo = {
    {"DJB2", djb2},
    {"Compute Hash", computeHash},
    {"sdbm", sdbm}  // No comma for last one
};
