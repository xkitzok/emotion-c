#include "../../include/emotion.h"

namespace emotion {

void setup_language_config(Config& config) {
    // format: EMOTION_KEYWORD("word", "c++ translation")
    
    // funciton
    EMOTION_KEYWORD("store", "int");        // store main() -> int main()
    EMOTION_KEYWORD("input", "std::getline()");
    EMOTION_KEYWORD("storeinput", "std::string");
    
    // otput
    EMOTION_KEYWORD("output", "std::cout << ");
    EMOTION_KEYWORD("ask", "std::cin >> ");
    EMOTION_KEYWORD("\n", "<< std::endl");
    
    // types
    EMOTION_KEYWORD("num", "int");
    EMOTION_KEYWORD("decimal", "double");
    EMOTION_KEYWORD("words", "std::string");
    EMOTION_KEYWORD("yesno", "bool");
    
    // control flow
    EMOTION_KEYWORD("if", "if");
    EMOTION_KEYWORD("repeat.stop", "break");
    EMOTION_KEYWORD("otherwise", "else");
    EMOTION_KEYWORD("repeat.for", "for");
    EMOTION_KEYWORD("repeat.forever", "while(true)");
    
    // easter egg
    EMOTION_KEYWORD("keyword", "std::abort();");
}

}
