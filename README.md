# gmorph

**gmorph** is a research code for 3D morphing between two meshes with arbitrary connectivities, including an implementation of the following papers:

- Takashi Kanai, Hiromasa Suzuki, Fumihiko Kimura: *"Metamorphosis of Arbitrary Triangular Meshes,"* IEEE Computer Graphics and Applications, Vol.20, No.2, pp.62-75, March/April 2000.

This software was originally developed in 1997-1998 and was renovated in 2016 to build successfully with Visual Studio 2015 (VS2015).

## Getting Started

This software is provided exclusively for Windows.

1. Double-click on `src\OpenGL.sln` (A solution file for VS2015) or `src\gmorph-vs2019.sln` (for VS2019), then "build the solution". Upon successful completion, you can find the executable in `src\Release\gmorph.exe` or `src\x64\Release\gmorph-vs2019.exe` (64-bit binary).

2. In the `data.v2.0` folder, all examples used in the paper are included. You can check the 3D morphing animation as follows:

   - Copy the execution file `gmorph.exe` (or `gmorph-vs2019.exe`) to a folder including a `.gmh` file.
   - Execute `gmorph.exe` (or `gmorph-vs2019.exe`).
   - "File" -> "Open" -> "GMH file" to load a `.gmh` file.
   - "Morph" -> "Create PPD" to create an interpolation mesh.
   - "Display" -> "Interp. Mesh"
   - "Morph" -> "Start Morph," then you can see the 3D morphing animation.

## Prerequisites

This software uses MFC (Microsoft Foundation Class). To build this software, VS2015/VS2017 Professional or higher versions are required for Windows applications.

This software also requires the Eigen library. When you execute `git clone` with the `--recursive` option, you will also get the Eigen library as a submodule in `external/eigen`:

```bash
git clone git@github.com:kanait/gmorph.git --recursive
```

## Authors

* **[Takashi Kanai](https://graphics.c.u-tokyo.ac.jp/hp/en/)** - The University of Tokyo

## License

This software except Eigen is licensed under the MIT License - see the [LICENSE](LICENSE) file for details. You also have to follow Eigen's license.
This software, excluding Eigen, is licensed under the MIT License - see the [LICENSE](LICENSE) file for details. You also have to adhere to Eigen's license.