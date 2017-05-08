using DoublelengthFloat

@assert Doublelength(1.0, eps()*0.125) + Doublelength(1.0, eps()*0.25) == Doublelength(2.0, 0.375eps())
@assert Doublelength(1.0, 0.125eps()) - Doublelength(1.0, 0.25eps()) == Doublelength(-0.125eps(), 0.0)
@assert (1.0+eps()) ⋅ (1.0+2eps()) == Doublelength(1.0+3eps(), 2eps()^2)
@assert Doublelength(1.0, 0.5eps()) * Doublelength(1.0, 0.75eps()) == Doublelength(1.0+eps(), 0.25eps())
@assert Doublelength(1.0, 0.125eps()) / Doublelength(1.0, 128eps()) == Doublelength(1.0-128eps(), 0.125eps())
@assert sqrt(Doublelength(1.0, 0.25eps())) == Doublelength(1.0, 0.125eps())