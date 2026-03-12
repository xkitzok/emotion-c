#include "../../include/emotion/core.h"
#include <iostream>

namespace emotion {

void reportError(const std::string& msg, int line, int column) {
    std::cerr << "[!]: " << line << ":" << column << " - " << msg << std::endl;
}

void reportWarning(const std::string& msg, int line, int column) {
    std::cerr << "[*]: " << line << ":" << column << " - " << msg << std::endl;
}

}
