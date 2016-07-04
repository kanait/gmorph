# gmorph2 (windows version) #

gmorph2 is a research code for 3D morphing between two meshes with arbitrary connectivies.

This code is an implementation of the following paper:

Takashi Kanai, Hiromasa Suzuki, Fumihiko Kimura:
"Metamorphosis of Arbitrary Triangular Meshes,"
IEEE Computer Graphics and Applications, Vol.20, No.2, pp.62-75, March/April 2000.

This code can be used only for research purpose *with no support*.

I don't remember its contents because I created this code about 17-18 years ago.

Now I've succeeded to compile this code on Visual Studio 2015.

Double-click src\OpenGL.sln and then "build the solution",
and if successfully finished, you can find \src\Release\gmorph2win.exe .

In the folder data.v2.0, all examples used in the paper are included.

You can see 3D morphing animation by the following procedure:

1. Copy an execution file gmorph2win.exe to a folder including .gmh file.
2. Execute gmorph2win.exe.
3. "File" -> "Open" -> "GMH file" then load a .gmh file.
4. "Morph" -> "Create PPD" to create an interpolation mesh.
5. "Display" -> "Interp. Mesh"
6. "Morph" -> "Start Morph" then you can see 3D morphing animation.

Enjoy!

4 July, 2016

Takashi Kanai



