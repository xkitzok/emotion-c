#include "../include/emotion.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

namespace emotion {
    void setup_language_config(Config& config);
    void setup_operator_precedence(Config& config);
    void setup_types(Config& config);
    std::string format_output(const std::string& generated);
}

// Recursive function to find all .cxx files
void find_cxx_files(const std::string& path, std::vector<std::string>& files) {
    try {
        for (const auto& entry : std::filesystem::recursive_directory_iterator(path)) {
            if (entry.is_regular_file()) {
                std::string file = entry.path().string();
                if (file.size() >= 4 && file.substr(file.size() - 4) == ".cxx") {
                    files.push_back(file);
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "[!] Error scanning directory: " << e.what() << "\n";
    }
}

int main(int argc, char** argv) {
    std::cout << "\n";
    std::cout << "╔════════════════════════════════╗\n";
    std::cout << "║       C^_^ Emotion C           ║\n";
    std::cout << "║ made by xkitz7                 ║\n";
    std::cout << "╚════════════════════════════════╝\n\n";
    
    std::vector<std::string> targetFiles;
    
    // If no arguments, find ALL .cxx files recursively from current directory
    if (argc < 2) {
        std::cout << "[*] No files specified, scanning for .cxx files recursively...\n";
        find_cxx_files(".", targetFiles);
        
        if (targetFiles.empty()) {
            std::cout << "[!] No .cxx files found in current directory or subdirectories\n";
            return 1;
        }
        
        std::cout << "[*] Found " << targetFiles.size() << " .cxx files\n";
    } else {
        // Use command line arguments
        for (int i = 1; i < argc; i++) {
            std::string inputFile = argv[i];
            
            // Check if it's a directory
            if (std::filesystem::is_directory(inputFile)) {
                std::cout << "[*] Scanning directory: " << inputFile << "\n";
                find_cxx_files(inputFile, targetFiles);
            }
            // Check if it's a .cxx file
            else if (inputFile.size() >= 4 && inputFile.substr(inputFile.size() - 4) == ".cxx") {
                if (std::filesystem::exists(inputFile)) {
                    targetFiles.push_back(inputFile);
                } else {
                    std::cout << "[!]: File not found: " << inputFile << "\n";
                }
            }
            else {
                std::cout << "[!]: Skipping " << inputFile << " - not a .cxx file or directory\n";
            }
        }
    }
    
    if (targetFiles.empty()) {
        std::cout << "[!] No valid .cxx files to compile\n";
        return 1;
    }
    
    // Track compiled files
    std::vector<std::string> compiledFiles;
    std::vector<std::string> failedFiles;
    
    // Process each file
    for (const auto& inputFile : targetFiles) {
        std::cout << "\n[*]: Compiling: " << inputFile << "\n";
        
        // Create compiler instance for each file
        emotion::Compiler compiler;
        
        emotion::Config config;
        emotion::setup_language_config(config);
        emotion::setup_operator_precedence(config);
        emotion::setup_types(config);
        
        compiler.loadConfig(config);
        
        bool success = compiler.compileFile(inputFile);
        
        // Show errors/warnings
        for (const auto& err : compiler.getErrors()) {
            std::cerr << "[!]: " << inputFile << " - " << err << "\n";
        }
        
        for (const auto& warn : compiler.getWarnings()) {
            std::cout << "[*]: " << inputFile << " - " << warn << "\n";
        }
        
        if (!success) {
            std::cerr << "[!]: " << inputFile << " - Compilation failed!\n";
            failedFiles.push_back(inputFile);
            continue;
        }
        
        // Format and save output
        std::string output = emotion::format_output(compiler.getGeneratedCode());
        
        // Generate filenames
        std::string baseName = inputFile;
        size_t lastSlash = baseName.find_last_of("/\\");
        if (lastSlash != std::string::npos) {
            baseName = baseName.substr(lastSlash + 1);
        }
        // Remove .cxx extension
        baseName = baseName.substr(0, baseName.size() - 4);
        
        // Get directory of input file
        std::string fileDir = ".";
        size_t dirPos = inputFile.find_last_of("/\\");
        if (dirPos != std::string::npos) {
            fileDir = inputFile.substr(0, dirPos);
        }
        
        std::string cppFile = fileDir + "/" + baseName + ".cpp";
        std::string exeFile = fileDir + "/" + baseName + ".out";
        
        std::ofstream out(cppFile);
        out << output;
        out.close();
        
        std::cout << "[+]: Generated: " << cppFile << "\n";
        
        std::cout << "[...]: Compiling with g++...\n";
        std::string cmd = "g++ -Wall -std=c++17 -o " + exeFile + " " + cppFile + " 2>&1 > /dev/null";
        
        int result = system(cmd.c_str());
        
        if (result == 0) {
            std::cout << "[+]: Success! Run with: " << exeFile << "\n";
            compiledFiles.push_back(exeFile);
        } else {
            std::cout << "[!]: g++ compilation failed for " << cppFile << "\n";
            failedFiles.push_back(inputFile);
        }
    }
    
    // Summary
    std::cout << "\n══════════════════════════════════════\n";
    std::cout << "[*]: Compilation summary:\n";
    std::cout << "[+]: Successfully compiled: " << compiledFiles.size() << " files\n";
    if (!failedFiles.empty()) {
        std::cout << "[!]: Failed: " << failedFiles.size() << " files\n";
        for (const auto& f : failedFiles) {
            std::cout << "     - " << f << "\n";
        }
    }
    std::cout << "══════════════════════════════════════\n";
    
    return 0;
}
