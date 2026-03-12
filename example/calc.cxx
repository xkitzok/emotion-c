store main() {
    output "=== Emotion C Calculator ===";
    output "Select operation:";
    output "1. Add";
    output "2. Subtract";
    output "3. Multiply";
    output "4. Divide";
    
    num choice;
    output "Enter choice (1-4): ";
    ask choice;
    
    num a;
    num b;
    output "Enter first number: ";
    ask a;
    output "Enter second number: ";
    ask b;
    
    if (choice == 1) {
        output "Result: " << (a + b);
    }
    if (choice == 2) {
        output "Result: " << (a - b);
    }
    if (choice == 3) {
        output "Result: " << (a * b);
    }
    if (choice == 4) {
        if (b != 0) {
            output "Result: " << (a / b);
        } otherwise {
            output "Error: Division by zero!";
        }
    }
    
    return 0;
}
