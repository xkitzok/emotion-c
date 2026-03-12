#include "../../include/emotion/types.h"
#include "../../include/emotion/core.h"
#include <string>
#include <sstream>

namespace emotion {

class CodeGen {
private:
    std::stringstream output;
    
public:
    void generate(const std::unique_ptr<ASTNode>& ast) {
        output << "// made by c^_^\n";
    }
    
    std::string getCode() const {
        return output.str();
    }
};

}
