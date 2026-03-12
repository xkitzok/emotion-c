CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -O2 -Iinclude
LDFLAGS = 

SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include

CORE_SRCS = $(SRC_DIR)/core/engine.cpp
CONFIG_SRCS = $(SRC_DIR)/config/keywords.cpp \
              $(SRC_DIR)/config/operators.cpp \
              $(SRC_DIR)/config/output.cpp \
              $(SRC_DIR)/config/types.cpp
MAIN_SRC = $(SRC_DIR)/main.cpp

ALL_SRCS = $(CORE_SRCS) $(CONFIG_SRCS) $(MAIN_SRC)
ALL_OBJS = $(ALL_SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

TARGET = emotion

DEBUG ?= 0
ifeq ($(DEBUG), 1)
    SILENT = 
    ECHO_PREFIX = 
else
    SILENT = @
    ECHO_PREFIX = @echo
endif

all: directories $(TARGET)
	$(SILENT)for file in *.cxx; do \
		if [ -f "$$file" ]; then \
			$(ECHO_PREFIX) "[*] Compiling $$file"; \
			./$(TARGET) "$$file"; \
		fi \
	done

compiler: directories $(TARGET)

file: $(TARGET)
	$(SILENT)if [ -n "$(FILE)" ]; then \
		if [ -f "$(FILE)" ]; then \
			$(ECHO_PREFIX) "[*] Compiling $(FILE)"; \
			./$(TARGET) "$(FILE)"; \
		else \
			$(ECHO_PREFIX) "[!] File not found: $(FILE)"; \
		fi \
	else \
		$(ECHO_PREFIX) "[!] Usage: make file FILE=path/to/file.cxx"; \
	fi

watch:
	@echo "[!] Watch mode is experimental and won't work"
	@echo "    Use 'make' manually for now"

directories:
	$(SILENT)mkdir -p $(BUILD_DIR)/core
	$(SILENT)mkdir -p $(BUILD_DIR)/config
	$(SILENT)mkdir -p $(BUILD_DIR)
	$(ECHO_PREFIX) "[*] Created build directories"

$(TARGET): $(ALL_OBJS)
	$(SILENT)$(CXX) $^ -o $@ $(LDFLAGS)
	$(ECHO_PREFIX) "[+] Compiler built: ./$(TARGET)"

$(BUILD_DIR)/core/%.o: $(SRC_DIR)/core/%.cpp
	$(SILENT)mkdir -p $(dir $@)
	$(SILENT)$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/config/%.o: $(SRC_DIR)/config/%.cpp
	$(SILENT)mkdir -p $(dir $@)
	$(SILENT)$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(SILENT)mkdir -p $(BUILD_DIR)
	$(SILENT)$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(SILENT)rm -rf $(BUILD_DIR) $(TARGET) *.cpp *.out
	$(ECHO_PREFIX) "[+] Clean complete"

install: $(TARGET)
	$(SILENT)sudo cp $(TARGET) /usr/local/bin/
	$(ECHO_PREFIX) "[+] Installed to /usr/local/bin/$(TARGET)"

.PHONY: all compiler file watch clean install directories

ifneq ($(findstring --debug,$(MAKEFLAGS)),)
    DEBUG = 1
endif
