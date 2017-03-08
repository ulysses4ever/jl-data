#pragma once

#include <string>
#include <sstream>
#include <ctime>

/** Shorthand for converting different types to string as long as they support the std::ostream << operator.
 */
#define STR(WHAT) static_cast<std::stringstream&>(std::stringstream() << WHAT).str()



/** Escapes the string in MySQL fashion.
 */
inline std::string escape(std::string const & from, bool quote = true) {
    std::string result = "";
    if (quote)
        result += "\"";
    for (char c : from) {
        switch (c) {
            case 0:
                result += "\\0";
                break;
            case '\'':
            case '"':
            case '%':
            case '_':
                result += "\\";
                result += c;
                break;
            case '\\':
                result += "\\\\";
                break;
            case '\b':
                result += "\\b";
                break;
            case '\n':
                result += "\\n";
                break;
            case '\r':
                result += "\\r";
                break;
            case '\t':
                result += "\\t";
                break;
            case 26:
                result += "\\Z";
                break;
            default:
                result += c;
        }
    }
    if (quote)
        result += "\"";
    return result;
}

inline int timestamp() {
    return std::time(nullptr);
}

