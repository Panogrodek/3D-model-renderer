workspace "3D-Model-Renderer"
   startproject "Sandbox"
   architecture "x64"
   configurations {
      "debug", 
      "release" 
   }

   filter { "platforms:Win64" }
      system "Windows"
      
include "Sandbox"