# Some default events
# More events should be added here
abstract Event{ID}

immutable MouseMoved{ID} <: Event{ID}
    x::Int
    y::Int
end

immutable MouseClicked{ID} <: Event{ID}
    key::Int
    status::Int
    x::Int
    y::Int
end
immutable MouseMovingClicked{ID} <: Event{ID}
	start::MouseClicked
    x::Int
    y::Int
end
immutable KeyDown{ID} <: Event{ID}
    special::Bool
    key::Char
    x::Int
    y::Int
end
immutable KeyUp{ID} <: Event{ID}
    special::Bool
    key::Char
    x::Int
    y::Int
end

immutable KeyDownMouseClicked{ID} <: Event{ID}
	currentMouseClicked::Dict{Int, (Int, Int)}
	currentKeyDown::Dict{Int, Bool}
	x::Int
    y::Int
end

immutable EnteredWindow{ID} <: Event{ID}
    entered::Bool
    id::Int
end

immutable WindowResized{ID} <: Event{ID}
    w::Int
    h::Int
end

export KeyUp, KeyDown, MouseMoved, MouseMovingClicked, MouseClicked, KeyDownMouseClicked, EnteredWindow, WindowResized, Event