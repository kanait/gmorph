# gmorph2 #

gmorph2 is a research code for 3D morphing between two meshes with arbitrary connectivies.

This code is an implementation of the following paper:

Takashi Kanai, Hiromasa Suzuki, Fumihiko Kimura:
"Metamorphosis of Arbitrary Triangular Meshes,"
IEEE Computer Graphics and Applications, Vol.20, No.2, pp.62-75, March/April 2000.

This code can be used only for research purpose *with no support*.

I don't remember its contents because I created this code about 17-18 years ago.

Now I've succeeded to compile this code on Fedora 24 and ubuntu 15.10. 
To compile this code, you have to install the following libraries:
(by using dnf or apt-get, other required files are automatically installed)

*Fedora 24

- motif-devel
- mesa-libGLw-devel
- libXpm-devel

*ubuntu 15.10 

- libmotif-dev
- libglw-dev

After installing these libraries, simply

% make

to create an exacutable file (gmorph2b8).

4 July, 2016

Takashi Kanai



