module Events

include("defaultEvents.jl")

immutable EventAction{T}
	#condition(T, conditionArgs...) -> Bool
	condition::Function
	conditionArgs::Tuple
	#action(T, actionArgs...) -> nothing
	action::Function
	actionArgs::Tuple
end

#Action Event Queues 						#############################################################################
const EVENT_ACTION_QUEUE 	= Dict{DataType, Dict{Uint64, EventAction}}()
# Make it possible to register to all events
EVENT_ACTION_QUEUE[Any] 	= Dict{Uint64, EventAction}()

function clearEventActionQueue()
	empty!(EVENT_ACTION_QUEUE)
	EVENT_ACTION_QUEUE[Any] 	= Dict{Uint64, EventAction}()

end

function deleteEventAction{T}(eventAction::EventAction{T})
	id = object_id(eventAction)
	queue = get(EVENT_ACTION_QUEUE, T, Dict{Uint64, EventAction}())
	delete!(queue, id)
	eventAction
end

function registerEventAction{T}(eventAction::EventAction{T})
	id = object_id(eventAction)
	queue = get(EVENT_ACTION_QUEUE, T, Dict{Uint64, EventAction}())
	queue[id] = eventAction
	EVENT_ACTION_QUEUE[T] = queue
	eventAction
end

function publishEvent{T <: Event}(event::T)
	eventQueue = values(get(EVENT_ACTION_QUEUE, T, Dict{Uint64, EventAction}()))
	for action in eventQueue
    	if action.condition(event, action.conditionArgs...)
    		action.action(event, action.actionArgs...)
    	end
    end
    #Always go through any
	eventQueue = values(get(EVENT_ACTION_QUEUE, Any, error))
	for action in eventQueue
    	if action.condition(event, action.conditionArgs...)
    		action.action(event, action.actionArgs...)
    	end
    end
end

function republishEvent{T}(event::T, newID)
	eventValues = {}
	for field in names(T)
		push!(eventValues, getfield(event, field))
	end
	# I don't now how to get rid of {ID}, this is a workaround:
	nameWithoutID = eval(parse(string(T.name)))
	publishEvent(nameWithoutID{newID}(eventValues...))
end

export registerEventAction, publishEvent, republishEvent, EventAction, deleteEventAction, clearEventActionQueue

end