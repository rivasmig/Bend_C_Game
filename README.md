# Asteroids Game with Bend and C++

## Project Overview

This project aims to create a hybrid Asteroids game using Bend for game logic and C++ for window management and input/output handling. Currently, the project includes the foundation for integrating Bend with C++ and a setup to test the execution of external scripts, both in Python and C++.

## Current Features

1. **Window Management**:
   - Implemented using SDL2 in C++.
   - Capable of rendering pixel arrays on a window.

2. **Script Execution**:
   - `ScriptRunner` class to execute external scripts and capture their output.
   - Supports both Python and C++ scripts.
   - Abstract command building using `CommandBuilder` class.

3. **Pixel Manipulation Scripts**:
   - **Python Script**: `pixel_shifter.py` generates blue noise and shifts pixels.
   - **C++ Script**: `pixel_shifter.cpp` replicates the functionality of the Python script for comparison.

4. **Performance Monitoring**:
   - Measures and outputs script execution time and frames per second (FPS).
   - Toggleable debug output for development.

## Project Structure

.
├── README.md
├── Makefile
├── application_verify.cpp
├── command_builder.cpp
├── command_builder.h
├── script_runner.cpp
├── script_runner.h
├── window_manager.cpp
├── window_manager.h
├── pixel_shifter.cpp
├── pixel_shifter.py
└── pixels.json (generated during execution)

## How to Build and Run

1. **Build the Project**:
    ```bash
    make
    ```

2. **Run the Executable**:
    ```bash
    ./application_verify
    ```

## Future Goals

1. **Integrate Bend for Game Logic**:
   - Replace current pixel manipulation scripts with Bend implementations.
   - Use Bend's parallel processing capabilities for efficient game logic execution.

2. **Enhance Game Features**:
   - Implement full game mechanics for Asteroids.
   - Handle user inputs for controlling the spaceship.

3. **Optimize Performance**:
   - Reduce script execution overhead.
   - Improve rendering performance.

4. **Expand ScriptRunner**:
   - Support more languages and frameworks for script execution.
   - Improve error handling and logging.

5. **Documentation and Testing**:
   - Provide comprehensive documentation for the project.
   - Implement unit and integration tests to ensure reliability.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
