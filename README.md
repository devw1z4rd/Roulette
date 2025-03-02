# No Shuffle Mode Patch for Buckshot Roulette

## Abstract
This project provides a patch that disables the shuffle functionality in *Buckshot Roulette.exe* by modifying the `GodotShuffleArrayFunc`. The patch is implemented by scanning for a predefined byte pattern within the executable and injecting a modified instruction set at a specific memory address. The patching process is designed to be efficient, ensuring minimal disruption to the game's execution.

## Problem Statement
Many applications implement randomized algorithms for gameplay mechanics, often relying on specific functions that shuffle data. In this case, the `GodotShuffleArrayFunc` is responsible for shuffling elements, which this patch aims to disable. The problem is twofold:
1. **Identifying the memory address** where the function resides in a dynamically loaded module.
2. **Injecting an alternative instruction sequence** to override the shuffling behavior without corrupting execution flow.

## Methodology
1. **Pattern Scanning:**  
   - The executable is scanned for a predefined sequence of bytes corresponding to the original `GodotShuffleArrayFunc`.
   - This scanning ensures compatibility across different builds where memory addresses might change.

2. **Symbol Registration & Address Retrieval:**  
   - Once located, the function's address is stored in a symbol table to facilitate further modifications.

3. **Instruction Patching:**  
   - The function’s instruction set is modified by writing a shorter alternative sequence at the detected address.
   - `memcpy()` is used to inject the modified code, ensuring immediate effect.

4. **Error Handling & Logging:**  
   - The system logs errors in case of unsuccessful address resolution or invalid memory access.
   - Console messages confirm successful execution steps.

## Technology Stack
- **Programming Language:** C++

## Installation & Execution
### Prerequisites
- A compiled version of this program
- *Buckshot Roulette.exe* available in the same directory

### Running the Patch
1. Compile the program using a C++ compiler supporting C++17.
2. Execute the compiled binary.
3. The console will display:
   ```
   No shuffle mode - enabled
   ```
   followed by confirmation logs for successful patch application.
