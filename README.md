# 3D model renderer
 An openGL 3d model rendering framework, made for College
![text](https://github.com/Panogrodek/3D-model-renderer/blob/main/repo/demo.png?raw=true)
![text](https://github.com/Panogrodek/3D-model-renderer/blob/main/repo/demo_multiple.png?raw=true)

# How to install
1. Download repository
2. Open build.bat to make visual studio files
3. Compile the project. Binaries should be located in bin folder
# Features
-Orthographic camera and perspective camera support<br>
-Perspective camera controller<br>
-Shader loading class<br>
-Vertex buffer, Index buffer, Buffer layout and Vertex array support<br>
-Imgui window support (no class abstraction, Imgui is only linked)<br>
-Obj file model loader (only supports simple obj files)
# Documentation
## Singletons
**Application** - Runtime type class that controlls the update and render functions. This is the heart of the simulation<br>
**Renderer** - an opengl framework type class. It takes care of the imgui layer (temporarily) and is responsible for clearing the window.
It also provides information about mouse position, and current camera being used<br>
**Geometry Renderer** - handles the rendering of 3d models from obj files<br>
**Model Loader** - handles the loading of 3d models from obj files<br>
## Non-singletons
**Camera** - is used in shader when rendering, to control the user ViewProjection matrix<br>
**Camera Controller** - modifies the camera position with user input<br>
**Shader** - abstraction of opengl shader programs. Is responsible for loading and binding opengl shaders<br>
**Buffer/Vertex buffer** - stores all vertex data (e.g. vertex position, vertex normal, vertex texture coords...)<br>
**Buffer/Index buffer** - stores the information about triangles, that are built from vertices from vertex buffer<br>
**Buffer/Buffer layout** - stores the information about single vertex data size. Tells vertex array how to handle vertex data<br>
**Vertex Array** - stores the information about vertex buffers, vertex buffer layouts and index buffers. Are used during render<br>
## Rest
**Global** - defines some usefull variables, i.e. window size, clear color, delta time and fixed delta time variable, light properties

