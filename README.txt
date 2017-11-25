CPSC 453 - Homework 3
Model Loader

Author:  Mingxi (Logan) Ruan
Adapted from boilerplate code provided in CPSC453 lectures,
and code from opengl-tutorials.org for backbone setup.

 ==== Compilation Instructions: ==== 

Open the file directory in a terminal and run the command:

"make"

The executable can be ran with the command:

"bin/alice [objFile] [texFile] [aoFile]"

Alternatively, directly launch the program with the command:

"make run [objFile] [texFile] [aoFile]"

YOU MUST SUPPLY 3 COMMAND LINE ARGUMENTS IN ORDER TO RUN THIS PROGRAM. The Program will reject any attempted launch with an incorrect number of arguments.

[objFile] corresponds to the *.obj file of the model.
[texFile] corresponds to the *.colour.png file of the model.
[aoFile] corresponds to the *.ao.png file of the model.

 ==== Controls ====

ESC:  Exits program
Up Arrow:  Zoom in
Down Arrow:  Zoom Out

E:  Roll Left
R:  Roll Right

T:  Yaw Left
Y:  Yaw Right

O:  Pitch Left
P:  Pitch Right

A:  Toggle Ambient Occlusion (AO)
X:  Toggle Texture


 ==== Resources ====

The following resources were consulted during development:

Boilerplate file from d2l.ucalgary.ca
http://www.glfw.org/docs/latest/group__window.html
https://glm.g-truc.net/0.9.3/api/a00199.html
http://www.opengl-tutorials.org
https://learnopengl.com/

* Thanks to Jayson for helping me through the logic on two parts of the code, credit is given where appropriate.
