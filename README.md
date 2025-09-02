# gmorph

**gmorph** is a research code for 3D morphing between two meshes with arbitrary connectivities, including an implementation of the following papers:

- Takashi Kanai, Hiromasa Suzuki, Fumihiko Kimura: *"Metamorphosis of Arbitrary Triangular Meshes,"* IEEE Computer Graphics and Applications, Vol.20, No.2, pp.62-75, March/April 2000.

This software was originally developed in 1997-1998 and was renovated in 2016 to build successfully with Visual Studio.

## Getting Started

This software is provided exclusively for Windows and can be compiled using CMake.

1. Install [CMake](https://cmake.org/download/) (version 3.20 or later recommended).
2. Open a terminal (e.g., `x64 Native Tools Command Prompt for VS 2019/2022`).
3. Create a build directory inside the project:
   ```bash
   cd src
   mkdir build
   cd build
   ```
4. Generate Visual Studio project files using CMake:
   ```bash
   cmake .. -G "Visual Studio 17 2022" -A x64
   ```
   - Use `"Visual Studio 16 2019"` if you are using Visual Studio 2019.
   - The `-A x64` option ensures a 64-bit build.
5. Open the generated solution:
   ```bash
   gmorph.sln
   ```
   (You can also open it directly in Visual Studio via **File → Open → Project/Solution…**).
6. Build the solution in Visual Studio (`Ctrl+Shift+B` or **Build → Build Solution**).
7. After a successful build, the executable will be located in:
   ```
   src/build/Release/gmorph.exe
   ```
   (or `src/build/x64/Release/gmorph.exe` depending on configuration).

8. In the `data.v2.0` folder, all examples used in the paper are included. You can check the 3D morphing animation as follows:

   - Copy the execution file `gmorph.exe` to a folder including a `.gmh` file.
   - Execute `gmorph.exe`.
   - "File" -> "Open" -> "GMH file" to load a `.gmh` file.
   - (If the file name does not contain "??_SP???.gmh" (i.e., it does not include '_SP"), select “Morph” → “SPATH auto” to compute the shortest path.)
   - "Morph" -> "Create PPD" to create an interpolation mesh.
   - "Display" -> "Interp. Mesh"
   - "Morph" -> "Start Morph," then you can see the 3D morphing animation.

## Prerequisites

This software uses MFC (Microsoft Foundation Classes). To build this software, Visual Studio (the Community edition is sufficient) is required for Windows applications. MFC is included as an optional component of Visual Studio, so please make sure to enable it during installation.

This software also requires the Eigen library. When you execute `git clone` with the `--recursive` option, you will also get the Eigen library as a submodule in `external/eigen`:

```bash
git clone https://github.com/kanait/gmorph.git --recursive
```

## Authors

* **[Takashi Kanai](https://graphics.c.u-tokyo.ac.jp/hp/en/)** - The University of Tokyo

## License

This software, excluding Eigen, is licensed under the MIT License - see the [LICENSE](LICENSE) file for details. You also have to adhere to Eigen's license.
