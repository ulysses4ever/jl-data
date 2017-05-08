using DoublelengthFloat

@assert DoublelengthFloat(1.0, eps()*0.125) + DoublelengthFloat(1.0, eps()*0.25) == DoublelengthFloat(2.0, 0.375eps())
@assert DoublelengthFloat(1.0, 0.125eps()) - DoublelengthFloat(1.0, 0.25eps()) == DoublelengthFloat(-0.125eps(), 0.0)
@assert (1.0+eps()) ⋅ (1.0+2eps()) == DoublelengthFloat(1.0+3eps(), 2eps()^2)
@assert DoublelengthFloat(1.0, 0.5eps()) * DoublelengthFloat(1.0, 0.75eps()) == DoublelengthFloat(1.0+eps(), 0.25eps())
@assert DoublelengthFloat(1.0, 0.125eps()) / DoublelengthFloat(1.0, 128eps()) == DoublelengthFloat(1.0-128eps(), 0.125eps())
@assert sqrt(DoublelengthFloat(1.0, 0.25eps())) == DoublelengthFloat(1.0, 0.125eps())