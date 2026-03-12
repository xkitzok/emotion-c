#include "../../include/emotion/types.h"
#include "../../include/emotion/core.h"
#include <memory>
#include <vector>

namespace emotion {

class Parser {
private:
    std::vector<Token> tokens;
    size_t current;
    
public:
    Parser(const std::vector<Token>& tokenList) : tokens(tokenList), current(0) {}
    
    std::unique_ptr<ASTNode> parse() {
        return nullptr;
    }
};

}
