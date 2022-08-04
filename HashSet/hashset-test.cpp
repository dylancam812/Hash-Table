#include <cs70/testinglogger.hpp>

size_t myhash(std::string const& s) {
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

#include "hashset.hpp"
#include <iostream>
#include <sstream>

bool testingDefaultConstructor() {
    TestingLogger log("Begin Test Default");

    HashSet<std::string> hashSet;

    affirm(hashSet.size() == 0);
    return log.summarize();
}
bool testingDefaultConstructorMaximal() {
    TestingLogger log("Begin Test Default Maximal");

    HashSet<std::string> hashSet;

    affirm(hashSet.maximal() == 0);
    return log.summarize();
}

bool testingDefaultConstructorCollisions() {
    TestingLogger log("Begin Test Default Collisions");

    HashSet<std::string> hashSet;

    affirm(hashSet.collisions() == 0);
    return log.summarize();
}

bool testingDefaultConstructorReallocations() {
    TestingLogger log("Begin Test Default Collisions");

    HashSet<std::string> hashSet;

    affirm(hashSet.reallocations() == 0);
    return log.summarize();
}

bool testingParametrizedConstructor() {
    TestingLogger log("Begin Test Parametrized");

    HashSet<std::string> hashSet = HashSet<std::string>{5};

    affirm(hashSet.buckets() == 5);
    affirm(hashSet.size() == 0);
    return log.summarize();
}

bool testingInsert() {
    TestingLogger log("Begin Test Insert");

    HashSet<std::string> hashSet;

    hashSet.insert("Hi");
    hashSet.insert("How");
    hashSet.insert("Are");
    hashSet.insert("You?");

    affirm(hashSet.size() == 4);
    return log.summarize();
}

bool testingExists() {
    TestingLogger log("Begin Test Exists");

    HashSet<std::string> hashSet;

    hashSet.insert("Hi");
    hashSet.insert("How");
    hashSet.insert("Are");
    hashSet.insert("You?");

    affirm(hashSet.exists("Hi"));
    affirm(!hashSet.exists("Hey"));
    return log.summarize();
}

bool testingLoadFactor() {
    TestingLogger log("Begin Test Load Factor");

    HashSet<std::string> hashSet;

    hashSet.insert("Hi");
    hashSet.insert("How");
    hashSet.insert("Are");
    hashSet.insert("You?");

    affirm(hashSet.loadFactor() == .25);
    return log.summarize();
}

int main() {
    // Initalize testing environment
    TestingLogger alltests{"All tests"};
    testingDefaultConstructor();
    testingParametrizedConstructor();
    testingDefaultConstructorCollisions();
    testingDefaultConstructorMaximal();
    testingDefaultConstructorReallocations();
    testingInsert();
    testingExists();
    testingLoadFactor();
    if (alltests.summarize(true)) {
        return 0;  // Error code of 0 == Success
    } else {
        return 2;  // Arbitrarily chosen exit code of 2 means tests failed
    }
}
