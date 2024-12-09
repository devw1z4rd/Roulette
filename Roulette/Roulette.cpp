#include <cstdint>
#include <cstring> 
#include <iostream>
#include <unordered_map>

uintptr_t scanModule(const char* moduleName, const uint8_t* pattern, size_t patternSize) {
    std::cout << "Scanning module: " << moduleName << std::endl;
    return 0x2017B20;
}

std::unordered_map<std::string, uintptr_t> symbolTable;

void registerSymbol(const char* symbolName, uintptr_t address) {
    std::cout << "Registering symbol: " << symbolName << " at address: " << std::hex << address << std::endl;
    symbolTable[symbolName] = address;
}

uintptr_t getSymbolAddress(const char* symbolName) {
    std::cout << "Getting address for symbol: " << symbolName << std::endl;
    return symbolTable[symbolName];
}

void unregisterSymbol(const char* symbolName) {
    std::cout << "Unregistering symbol: " << symbolName << std::endl;
    symbolTable.erase(symbolName);
}

struct GodotShuffleArrayFunc {
    static constexpr uint8_t original_code[15] = { 0xE3, 0x41, 0x5F, 0x41, 0x5E, 0x41, 0x5C, 0x5F, 0x5E, 0xC3, 0x48, 0x89, 0x5C, 0x24, 0x10 };
    static constexpr uint8_t modified_code[5] = { 0xC3, 0x89, 0x5C, 0x24, 0x10 };
    static constexpr uintptr_t injection_point = 0x2017B20;
};

void enable() {
    uintptr_t address = scanModule("Buckshot Roulette.exe", GodotShuffleArrayFunc::original_code, sizeof(GodotShuffleArrayFunc::original_code));

    if (address == 0) {
        std::cerr << "Error: Invalid address returned from scanModule!" << std::endl;
        return;
    }

    std::cout << "Found address: " << std::hex << address << std::endl;

    registerSymbol("godotShuffleArrayFunc", address);

    uintptr_t targetAddress = address + 0x0A;
    if (targetAddress != 0) {
        std::cout << "Writing modified code to address: " << std::hex << targetAddress << std::endl;
        memcpy(reinterpret_cast<void*>(targetAddress), GodotShuffleArrayFunc::modified_code, sizeof(GodotShuffleArrayFunc::modified_code));
    }
    else {
        std::cerr << "Error: Invalid memory address for injection!" << std::endl;
    }
}


int main() {
    int state;
    std::cout << "no shuffle mode - enabled";
	enable();
    return 0;
}
