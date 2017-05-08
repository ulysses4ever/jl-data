module models
export xtasy, RainZha, lifegame, brians_brain, swirl, cubism, cyclic_spirals, amoeba

using Model
using nbhd

const xtasy = generations([1,4,5,6], [2,3,5,6], 16)
const RainZha = generations([2], [2,3], 8)
const lifegame = life([2,3], [3])
const brians_brain = generations([], [2], 3)
const swirl        = generations([2,3], [3,4], 8)
const cubism = Cyclic(3, 2, 5, nbhd.neumann(2))
const cyclic_spirals = Cyclic(8, 3, 5, nbhd.moore(3))

const amoeba = Cyclic(2, 3, 10, nbhd.neumann(3))
const cca = Cyclic(14, 1, 1, nbhd.neumann(1))
const lavalamp = Cyclic(3, 2, 10, nbhd.moore(2))
const turbulent_phase = Cyclic(8, 2, 5, nbhd.moore(2))
const maze = life([1,2,3,4,5], [3])
const Flakes = life([0,1,2,3,4,5,6,7,8], [3])
const bloomerang = generations([2,3,4], [3,4,6,7,8], 24)
const chenille = generations([0,5,6,7,8], [2,4,5,6,7], 6)
const frozen_spirals = generations([3,5,6], [2, 3], 6)
const nova = generations([4,5,6,7,8], [2,4,7,8], 25)

end
