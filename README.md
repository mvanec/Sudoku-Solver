# Sudoku Solver

## Project Overview

Sudoku Solver is a desktop application for solving and analyzing Sudoku puzzles. It provides a user-friendly interface built with Qt, allowing users to input puzzles, solve them automatically, and visualize the solution process. The project includes both the main application and a suite of unit tests using Google Test.

---

## 1. Project Setup in Visual Studio

### Prerequisites
- Visual Studio 2022 or newer
- [Qt Visual Studio Tools Extension](https://marketplace.visualstudio.com/items?itemName=TheQtCompany.QtVisualStudioTools2022)
- Qt 6.7.2 (or later) installed and configured
- C++20 toolset (v143)

### Steps
1. **Install Qt Visual Studio Tools**
   - Go to Extensions > Manage Extensions > Online, search for "Qt Visual Studio Tools", and install.
2. **Configure Qt in Visual Studio**
   - Open Qt VS Tools > Qt Options and add your Qt installation (e.g., `C:/Qt/6.9.1/msvc2019_64`).
3. **Open the Solution**
   - Open `Sudoku Solver.sln`.
4. **Restore NuGet Packages** (if prompted)
   - Visual Studio will restore any required packages automatically.
5. **Build the Solution**
   - Select the desired configuration (Debug/Release, x64).
   - Build both `SudokuSolver` and `SudokuSolverTest` projects.
6. **Run the Application**
   - Set `SudokuSolver` as the startup project and run.

---

## 2. Project Setup in Qt Creator

### Prerequisites
- Qt Creator (latest recommended)
- Qt 6.7.2 (or later)

### Steps
1. **Open Project**
   - Open `SudokuSolver/SudokuSolver.pro` in Qt Creator.
2. **Configure Build Kit**
   - Select a kit matching your Qt installation and compiler (e.g., MSVC 64-bit or MinGW 64-bit).
3. **Build the Project**
   - Build the `SudokuSolver` target.
4. **Run the Application**
   - Use the green play button to launch.
5. **Open and Build Tests**
   - Open `SudokuSolverTest/SudokuSolverTest.pro` for unit tests.

---

## 3. Configuring the Test Libraries (Google Test)

### Visual Studio
- Google Test is included via NuGet or manually in the `packages/` directory.
- Ensure the test project references the correct library paths.
- No additional configuration is needed if using the provided solution.

### Qt Creator
- The test project uses `gtest_dependency.pri` to locate Google Test.
- Set the `GOOGLETEST_DIR` environment variable or qmake variable to point to your Google Test installation if not using the provided binaries.
- Example:
  ```sh
  export GOOGLETEST_DIR=/path/to/googletest
  ```
- By default, the project will link against the libraries in `packages/` if available.

---

## 4. Building and Running the Program

### Visual Studio
1. Build the solution (`Ctrl+Shift+B`).
2. Run the main application (`SudokuSolver`).
3. To run tests, build and run `SudokuSolverTest` (output in the terminal or Test Explorer).

### Qt Creator
1. Build the project using the selected kit.
2. Run the main application from the IDE.
3. To run tests, build and run the `SudokuSolverTest` target.

---

## Additional Notes
- The `.pro.user` file is not included in the repository; Qt Creator will generate a new one on first open.
- For translation support, ensure Qt Linguist tools are installed.
- For troubleshooting, consult the Qt and Visual Studio documentation or check the `build/` and `x64/Debug/` folders for logs.

---

## License
See `License.txt` for details.