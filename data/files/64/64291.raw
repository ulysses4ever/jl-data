using Wand
using Base.Test

using PyCall
@pyimport wand.color as color
Color = color.Color

@test Color("white") == Color("#ffffff")
