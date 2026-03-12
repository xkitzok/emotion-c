#include "../../include/emotion.h"
#include "../../include/emotion/core.h"
#include "../../include/emotion/types.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
#include <map>

namespace emotion {

class Lexer {
    // TODO: in lexer.cpp
};

class Parser {
    // TODO: in parser.cpp
};

class CodeGen {
    // TODO: in codegen.cpp
};

class CompilerImpl {
public:
    Config config;
    std::vector<std::string> errors;
    std::vector<std::string> warnings;
    std::string generatedCode;
    std::unique_ptr<Lexer> lexer;
    std::unique_ptr<Parser> parser;
    std::unique_ptr<CodeGen> codegen;
    
    CompilerImpl() = default;
    ~CompilerImpl() = default;
    
    bool compile(const std::string& source) {
        generatedCode = translateWithKeywords(source);
        return true;
    }
    
private:
    std::string translateWithKeywords(const std::string& input) {
        std::string output;
        std::istringstream iss(input);
        std::string line;
        
        while (std::getline(iss, line)) {
            output += processLine(line) + "\n";
        }
        
        return output;
    }
    
    std::string processLine(const std::string& line) {
        std::string result;
        std::string currentWord;
        
        for (char c : line) {
            if (isalnum(c) || c == '_') {
                currentWord += c;
            } else {
                if (!currentWord.empty()) {
                    auto it = config.keywords.find(currentWord);
                    if (it != config.keywords.end()) {
                        result += it->second;
                    } else {
                        result += currentWord;
                    }
                    currentWord.clear();
                }
                result += c;
            }
        }
        
        if (!currentWord.empty()) {
            auto it = config.keywords.find(currentWord);
            if (it != config.keywords.end()) {
                result += it->second;
            } else {
                result += currentWord;
            }
        }
        
        return result;
    }
};

Compiler::Compiler() : impl(std::make_unique<CompilerImpl>()) {}
Compiler::~Compiler() = default;

void Compiler::loadConfig(const Config& cfg) {
    impl->config = cfg;
}

bool Compiler::compileFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        impl->errors.push_back("Cannot open file: " + filename);
        return false;
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    return compileString(buffer.str(), filename);
}

bool Compiler::compileString(const std::string& source, const std::string& outputName) {
    impl->errors.clear();
    impl->warnings.clear();
    
    bool success = impl->compile(source);
    
    if (success && !outputName.empty()) {
        std::ofstream out(outputName + ".cpp");
        out << impl->generatedCode;
    }
    
    return success;
}

bool Compiler::hasErrors() const {
    return !impl->errors.empty();
}

std::vector<std::string> Compiler::getErrors() const {
    return impl->errors;
}

std::vector<std::string> Compiler::getWarnings() const {
    return impl->warnings;
}

std::string Compiler::getGeneratedCode() const {
    return impl->generatedCode;
}

}
