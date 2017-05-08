module OBJFileIO

export Shapeobject, loadOBJFile, createCylinderVertices

############### Begin Type declaration for Shape Object ################
type Shapeobject
    #A new type declaration. This is a shape object that is composed of
    #An array of vertices and an array of faces
    vertices::Array{Float64, 2}
    faces::Array{Int64, 2}

    #Constructor that creates an object from an obj file
    function Shapeobject(filename::String)
        #Create instance of the object
        shapeOBJ = new()
        #Populate the object fields using the loadOBJFile method
        shapeOBJ.vertices, shapeOBJ.faces = loadOBJFile(filename)
        #Return object
        return shapeOBJ
    end #end constructor

    #Constructor that creates an object from an obj file
    function Shapeobject(cylDiamter::Float64, cylLength::Float64,
                         numVertices::Int64, filename::String)
        #Create instance of the object
        shapeOBJ = new()
        #Populate the object.faces field using the loadOBJFile method
        x, shapeOBJ.faces = loadOBJFile(filename)
        #Populate the object.vertices field using the createCylinderVertices method
        shapeOBJ.vertices = createCylinderVertices(cylDiamter, cylLength, numVertices)
        #Return object
        return shapeOBJ
    end #end constructor

end # end of type declaration

############### Begin Functions ###############

#FUNCTION
#SUMMARY:
#This function loads an obj file and returns an array of vertices and an array of faces
#
#INPUTS:
#    objFile::String -
#    Path to the obj file containing the object that you want
#
#OUTPUTS:
#    Tuple of arrays
#
#    objectVertices::Array{Float64,2} -
#    array containing the vertices of the object
#
#    objectFaces::Array{Float64,2} -
#    array containing the faces of the object
function loadOBJFile(objFile::String)
    #Initiate variables for the object vertices and faces
    objectVertices = zeros(Float64,1,3)
    objectFaces = zeros(Int64,1,3)

    #Initialise variables to temporarily store the data for each line.
    lineVertex = zeros(Float64,1,3)
    lineFace = zeros(Int64,1,3)

    #Initialise counter for the vertex and face line number
    vertexLineCounter = 1
    faceLineCounter = 1

    #Open OBJ file for reading
    objFileContent = open(objFile)

    #Loop through each line of the file and look for vertex lines and face lines
    #Those lines begin with a 'v' or and 'f' respectively.
    #Foor those lines store the values in the repsective objectvertices or object faces
    #array.
    for line in eachline(objFileContent)
        if line[1] == 'v'
            vertexLine = split(line)
            #Initialise counter for the vertex line number
            for i = 1:length(vertexLine)
                if i != 1
                    if vertexLineCounter == 1
                        objectVertices[vertexLineCounter,i-1] = parsefloat(vertexLine[i])
                    else
                        lineVertex[i-1] = parsefloat(vertexLine[i])
                    end
                end
            end
            if vertexLineCounter != 1
                #Concatenate the vertex from the parsed line to the object vertices array
                objectVertices = vcat(objectVertices,lineVertex)
            end
            #Increment counter
            vertexLineCounter += 1

        elseif line[1] == 'f'
            faceLine = split(line)
            for i = 1:length(faceLine)
                if i != 1
                    if faceLineCounter == 1
                        objectFaces[faceLineCounter,i-1] = parseint(faceLine[i])
                    else
                        lineFace[i-1] = parsefloat(faceLine[i])
                    end
                end
            end
            if faceLineCounter != 1
                #Concatenate the face from the parsed line to the object vertices array
                objectFaces = vcat(objectFaces,lineFace)
            end
            #Increment counter
            faceLineCounter += 1
        end
    end

    #Close the file now we are done with it
    close(objFileContent)

    #return Object vertices and faces
    return objectVertices, objectFaces
end #end loadOBJFile function

#FUNCTION
#SUMMARY:
#Takes in parameters and returns a cylinder object from those parameters
#
#INPUTS:
#    cylDiameter::Float64 -
#    Diameter of cylinder
#
#    cylLength::Float64 -
#    Axial length of the cylinder
#
#    numVertices::Int64 -
#    number of vertices around each end of cylinder i.e. this is half of the total number
#    of vertices in the cylinder object
#
#OUTPUTS:
#    vertices::Array{Float64,2}
#    An 2*numVertices x 3 array containing the coordinates of each vertex of the cylinder
function createCylinderVertices(cylDiamter::Float64, cylLength::Float64, numVertices::Int64)
    #Calculate radius
    cylRadius = cylDiamter/2

    #Create xCoordinates
    cylBase = cylLength/2
    xCoordBase = -cylBase
    xCoordTop = cylBase

    #Calculate angular step around circle
    angleToVertex = -2π/numVertices

    #Preallocate vertices array
    vertices = zeros(Float64, 2 * numVertices, 3)

    #Loop through each vertex
    for vertex = 1:numVertices
        #Calculate points around the circle
        yCoord = cylRadius * cos((vertex - 1) * angleToVertex)
        ZCoord = cylRadius * sin((vertex - 1) * angleToVertex)

        #Add points to the vertices array for the Base
        vertices[2 * vertex - 1, 1] = xCoordBase
        vertices[2 * vertex - 1, 2] = yCoord
        vertices[2 * vertex - 1, 3] = ZCoord

        #Add points to the vertices array for the Top
        vertices[2 * vertex, 1] = xCoordTop
        vertices[2 * vertex, 2] = yCoord
        vertices[2 * vertex, 3] = ZCoord
    end

    #return vertices
    return vertices
end #end createCylinderVertices method

end #end module
