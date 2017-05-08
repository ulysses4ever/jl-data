#! /usr/bin/env julia

import GLFW


# Initialize the library
GLFW.Init()

# Create a window and its OpenGL context
window = GLFW.CreateWindow(640, 480, "ZenFab")

# Make the window's context current
GLFW.MakeContextCurrent(window)

# Loop until the user closes the window
while !GLFW.WindowShouldClose(window)

    # Render here

    # Swap front and back buffers
    GLFW.SwapBuffers(window)

    # Poll for and process events
    GLFW.PollEvents()
end

GLFW.Terminate()
