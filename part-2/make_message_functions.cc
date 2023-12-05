// Marcus McKinstry
// marcmckinstry@csu.fullerton.edu
// @heyyyitsmarcus
// Partners: @pachmi

#include "make_message_functions.h"

#include <iomanip>

bool HasMatchingFileExtension(const std::string& file_name,
                              const std::string& extension) {
  int file_name_length = file_name.size();
  int extension_length = extension.size();

  bool is_long_enough = file_name_length > extension_length;

  bool has_extension = false;

  if (is_long_enough) {
    int period_location = file_name_length - extension_length;
    has_extension =
        file_name.compare(period_location, extension_length, extension) == 0;
  }

  return has_extension;
}

// Secret global variable to make the randome number generator
// predictable
std::seed_seq rng_seed{1, 2, 3, 4, 5};

// Secret global variable that is used by RandomDouble_01()
RandomNumberGenerator rng_01{0, 1, rng_seed};

// Secret global variable that is used by RandomDouble_11()
RandomNumberGenerator rng_11{-1, 1, rng_seed};

// Secret global variable that is used by CoinFlip()
RandomNumberGenerator rng_coin_flip{-1, 1, rng_seed};

// Returns a random double between o and 1
double RandomDouble01() {
  // X: Using rng_01, call Next() and return the next random number.
  return rng_01.Next();
}

// Returns a random double between -1 and 1
double RandomDouble11() {
  // X: Using rng_11, call Next() and return the next random number.
  return rng_11.Next();
}

/// Return a True or False depending on a random value.
/// Generates a random number and then decides to return True or False
bool CoinFlip() {
  // X: Using rng_coin_flip, call Next() and return true if the randome
  // number is greater than 0.0 and false otherwise.
  if (rng_coin_flip.Next() > 0.0) {
    return true;
  }

  return false;
}
