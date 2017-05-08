module Disp
export draw_square, color255, add_draw_function, initDisp, mainLoop

using OpenGL
@OpenGL.version "1.0"
@OpenGL.load
using GLUT

# intialize variables

global window

global width  = 640
global height = 480
global draw_funcs = Function[]

typealias glFloat Float64
typealias Pos (glFloat, glFloat)
typealias Color Union((glFloat, glFloat, glFloat), Array{glFloat, 1})

function draw_square(pos::Pos, w::glFloat, color::Color)
    glColor(color...)

    x, y = pos

    glBegin(GL_QUADS)
        glVertex(x   , y   , 0.0)
        glVertex(x   , y+w , 0.0)
        glVertex(x+w , y+w , 0.0)
        glVertex(x+w , y   , 0.0)
    glEnd()
end

function add_draw_function(f::Function)
    push!(draw_funcs, f)
end

function initGL(w::Integer,h::Integer)
    global width, height
    glViewport(0,0,w,h)
    glClearColor(0.0, 0.0, 0.0, 0.0)
    glClearDepth(1.0)			 
    glDepthFunc(GL_LESS)	 
    glEnable(GL_DEPTH_TEST)
    glShadeModel(GL_SMOOTH)

    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    glOrtho(0, 100, 0, 100, -1, 1)

    gluPerspective(45.0,w/h,0.1,100.0)

    glMatrixMode(GL_MODELVIEW)
end

# prepare Julia equivalents of C callbacks that are typically used in GLUT code

function ReSizeGLScene(w::Int32,h::Int32)
    if h == 0
        h = 1
    end

    glViewport(0,0,w,h)

    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    glOrtho(0, 100, 0, 100, -1, 1)

    gluPerspective(45.0,w/h,0.1,100.0)

    glMatrixMode(GL_MODELVIEW)
   
    return nothing
end

_ReSizeGLScene = cfunction(ReSizeGLScene, Void, (Int32, Int32))

function DrawGLScene()
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glLoadIdentity()

    glTranslate(0.0,0.0,-6.0)

    for f in draw_funcs
        f()
    end

    glutSwapBuffers()
   
    return nothing
end
   
_DrawGLScene = cfunction(DrawGLScene, Void, ())

function keyPressed(the_key::Char,x::Int32,y::Int32)
    global window
    if the_key == int('q')
        glutDestroyWindow(window)
    end

    return nothing # keyPressed returns "void" in C. this is a workaround for Julia's "automatically return the value of the last expression in a function" behavior.
end

_keyPressed = cfunction(keyPressed, Void, (Char, Int32, Int32))

# run GLUT routines

function initDisp()
    global window, width, height
    glutInit()
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH)
    glutInitWindowSize(width, height)
    glutInitWindowPosition(0, 0)

    window = glutCreateWindow("NeHe Tut 2")

    glutDisplayFunc(_DrawGLScene)
    #glutFullScreen()

    glutIdleFunc(_DrawGLScene)
    glutReshapeFunc(_ReSizeGLScene)
    glutKeyboardFunc(_keyPressed)

    initGL(width, height)
end

function mainLoop()
    glutMainLoop()
end

end
