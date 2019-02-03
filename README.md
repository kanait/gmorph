# gmorph

gmorph is a research code for 3D morphing between two meshes with arbitrary connectivies, which includes an implementation of the following papers:

Takashi Kanai, Hiromasa Suzuki, Fumihiko Kimura:
"Metamorphosis of Arbitrary Triangular Meshes,"
IEEE Computer Graphics and Applications, Vol.20, No.2, pp.62-75, March/April 2000.

This software was originally developed in 1997-1998 and was renovated in 2016 so as to build successfully by Visual Studio 2015 (VS2015).

## Getting Started

This software is provided only for Windows.

Double-click src\OpenGL.sln (A solution file for VS2015) or src\gmorph-vs2017.sln (for VS2017) and then "build the solution", and if successfully finished, you can find an executable in src\Release\gmorph.exe or src\Release\gmorph-vs2017.exe .

In the data.v2.0 folder, all examples used in the paper are included. You can check 3D morphing animation as follows:

1. Copy an execution file gmorph.exe (or gmorph-vs2017.exe) to a folder including .gmh file.
2. Execute gmorph.exe (or gmorph-vs2017.exe).
3. "File" -> "Open" -> "GMH file" to load a .gmh file.
4. "Morph" -> "Create PPD" to create an interpolation mesh.
5. "Display" -> "Interp. Mesh"
6. "Morph" -> "Start Morph" then you can see 3D morphing animation.

## Prerequisites

This software uses MFC (Microsoft Foundation Class). Then, to build this software, VS2015/VS2017 Professional or upper versions are required for Windows application.

This software also requires [Eigen](http://eigen.tuxfamily.org/) library. When you execute "git clone" with "--recursive" option, You will also get Eigen library as a submodule "external/eigen":

```
git clone git@github.com:kanait/gmorph.git --recursive
```
## Authors

* **[Takashi Kanai](https://graphics.c.u-tokyo.ac.jp/hp/en/)** - The University of Tokyo

## License

This software except Eigen is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details. You also have to follow Eigen's license.

