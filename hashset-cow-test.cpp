#include "hashset.hpp"

#include <cstddef>  // For size_t
#include <ostream>  // For std::ostream

#include "signal.h"  // For signal
#include "unistd.h"  // For alarm

/**
 * Cow: Test class which implements the bare minimum to be usable
 *      with a HashSet
 */
class Cow {
 public:
    /// Non-default constructor.
    explicit Cow(size_t numHats);

 private:
    size_t numHats_;  // How many hats does Cow have

    // Give external functions friend access
    friend std::ostream& operator<<(std::ostream& out, const Cow& printMe);
    friend bool operator==(const Cow& lhs, const Cow& rhs);
};

/// Equality for Cows
bool operator==(const Cow& lhs, const Cow& rhs) {
    return lhs.numHats_ == rhs.numHats_;
}

/// Output a Cow in visual form
std::ostream& operator<<(std::ostream& out, const Cow& printMe) {
    for (size_t i = 0; i < printMe.numHats_; ++i)
        out << "        _====_\n";

    out << "         (__)\n"   // Shamelessly taken from Debian's (& Ubuntu's)
        << "         (oo)\n"   //    apt-get moo
        << "   /------\\/ \n"  // (apt has "super cow" powers)
        << "  / |    ||  \n"
        << " *  /\\---/\\  \n"
        << "    ~~   ~~  \n";
    return out;
}

Cow::Cow(size_t numHats) : numHats_(numHats) {
    // Nothing (else) to do.
}

/// Hash function for Cows
size_t myhash(const Cow&) {
    return 42;  // Really bad hash function. ;-)
}

template class HashSet<Cow>;

/*****************************************************
 * Functionality Tests
 *
 *      Functionality tests for HashSet
 * ***************************************************/

#include <cs70/testinglogger.hpp>

/// Test insert and exists for cows
bool cowTestSuite() {
    // Set up the TestingLogger object
    TestingLogger log{"example test"};

    Cow mabel(3);
    HashSet<Cow> cowSet;

    affirm(!cowSet.exists(mabel));

    cowSet.insert(mabel);
    affirm(cowSet.exists(mabel));

    // Print a summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

/****************************
 * Boilerplate main function
 * **************************/

// Called if the test runs too long.
static void timeout_handler(int) {
    write(STDERR_FILENO, "Timeout occurred!\n", 18);
    abort();
}

/// Run tests
int main() {
    // Initalize testing environment
    TestingLogger alltests{"All tests"};

    signal(SIGALRM, timeout_handler);  // Call this when the timer expires
    alarm(10);                         // set the timer at 10 seconds

    // Add calls to your tests here...
    cowTestSuite();

    if (alltests.summarize(true)) {
        return 0;  // Error code of 0 == Success!
    } else {
        return 2;  // Arbitrarily chosen exit code of 2 means tests failed.
    }
}
