using DataStructures

abstract gameState

abstract function draw(g::gameState,dt::Real)
abstract function update(g::gameState,dt::Real)
abstract function handleInput(g::gameState)

type game
    stack::Stack
    window
end

abstract function pushState(g::game,state::gameState)
abstract function popState(g::game)
abstract function changeState(g:game,state::gameState)
abstract function peekState(g:game)

abstract function gameLoop(g:game)

