#include "../../include/emotion.h"
#include <string>
#include <sstream>

namespace emotion {

std::string format_output(const std::string& generated) {

    std::stringstream result;
    
    result << "// made by c^_^\n";
    
    // required
    result << "#include <iostream>\n";
    result << "#include <string>\n\n";
    
    result << generated;
    
    result << "\n";
    
    return result.str();
}

} 
