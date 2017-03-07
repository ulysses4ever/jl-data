#pragma once

#include <string>
#include <sstream>

/** Shorthand for converting different types to string as long as they support the std::ostream << operator.
 */
#define STR(WHAT) static_cast<std::stringstream&>(std::stringstream() << WHAT).str()
