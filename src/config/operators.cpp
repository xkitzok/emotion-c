#include "../../include/emotion.h"

namespace emotion {

void setup_operator_precedence(Config& config) {
    
    EMOTION_OPERATOR(":", 100);    
    EMOTION_OPERATOR("*", 50);
    EMOTION_OPERATOR("/", 50); 
    EMOTION_OPERATOR("%", 50);
    
    EMOTION_OPERATOR("+", 45);
    EMOTION_OPERATOR("-", 45);
    
    EMOTION_OPERATOR("<", 35);
    EMOTION_OPERATOR(">", 35);
    EMOTION_OPERATOR("<=", 35);   
    EMOTION_OPERATOR(">=", 35);   
    
    EMOTION_OPERATOR("?=", 30);  // uhh equal
    EMOTION_OPERATOR("!=", 30);
    
    EMOTION_OPERATOR("&", 20);   // basically AND
    EMOTION_OPERATOR("|", 15);   // basically OR
    
    EMOTION_OPERATOR("=", 10);
}

} 
