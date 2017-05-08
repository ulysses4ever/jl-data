using Events
using Base.Test  
import Events.EVENT_ACTION_QUEUE


@test length(EVENT_ACTION_QUEUE) == 1
tic()
publishEvent(MouseMoved{1}(0,0))
println("time for adding an event: ",toq())
@test length(EVENT_ACTION_QUEUE) == 1


test{ID}(event::MouseMoved{ID}) 	= @test ID == 1
test2{ID}(event::MouseMoved{ID}) 	= @test ID == 2


eventAction1 = EventAction{MouseMoved{1}}(x-> true, (), test, ())
eventAction2 = EventAction{MouseMoved{2}}(x-> true, (), test2, ())
eventAction3 = EventAction{MouseMoved{2}}(x-> x.x == 1, (), test2, ())

tic()
registerEventAction(eventAction1)
println("time for adding an eventAction: ", toq())
tic()
registerEventAction(eventAction2)
println("time for adding a second eventAction: ", toq())
@test length(EVENT_ACTION_QUEUE) == 3
@test length(EVENT_ACTION_QUEUE[MouseMoved{2}]) == 1
registerEventAction(eventAction3)
@test length(EVENT_ACTION_QUEUE[MouseMoved{2}]) == 2



tic()
for i=1:200000
	publishEvent(MouseMoved{i%2 + 1}(0,0))
end
println("time for publishing 200,000 events: ", toq())



tic()
deleteEventAction(eventAction1)
println("time for deleting an eventAction: ", toq())
deleteEventAction(eventAction2)
@test length(EVENT_ACTION_QUEUE[MouseMoved{2}]) == 1
deleteEventAction(eventAction3)
@test length(EVENT_ACTION_QUEUE[MouseMoved{2}]) == 0


global counter = 0
function test3(event::MouseMoved{2}, _) 
	global counter += 1
	@test event.x == 1
end

tic()
eventActions = 2000
for i=1:eventActions
	registerEventAction(EventAction{MouseMoved{2}}(x-> x.x == 1, (), test3, (i,)))
end
println("time for adding 2000 eventActions: ", toq())

eventsToPublish = 2000
tic()
for i=1:eventsToPublish
	publishEvent(MouseMoved{2}(1,i))
end
println("time for delegating $(eventsToPublish) * $(eventActions) events: ", toq())

@test eventsToPublish * eventActions == counter


clearEventActionQueue()
@test length(EVENT_ACTION_QUEUE) == 1


test5(event::MouseMoved{1}) = @test false
test5(event::MouseMoved{2}) = global counter += 1


global counter 	= 0
eventAction1 	= EventAction{MouseMoved{1}}(x-> true, (), republishEvent, (2,))
eventAction3 	= EventAction{MouseMoved{2}}(x-> true, (), test5, ())


registerEventAction(eventAction1)
registerEventAction(eventAction2)
registerEventAction(eventAction3)


eventsToPublish = 200
for i=1:eventsToPublish
	publishEvent(MouseMoved{1}(i ,i))
end
@test counter == eventsToPublish