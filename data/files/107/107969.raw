
using GoCL
using Base.Test

#a = ones(UInt32, 19, 19)
#b = zeros(UInt32, 19, 19)
#@forall i j begin
#    b[i, j] = 2 * a[i, j]
#end
#@test b == 2a
#c = @forall_fold i j 19 (+) 0 b begin
#    b[i, j] = 3 * a[i, j]
#end
#@test c == 3 * 19 * 19

b = Board{19}()
@test length(b.row) == 19
@test point(b, 1, 1) == empty
@test point(b, 19, 19) == empty
move!(b, black, 10, 10)
@test point(b, 10, 10) == black
move!(b, white, 12, 11)
#io = open("print-board.txt", "w")
#print(io, b)
#close(io)
@test sprint(print, b) == open(readall, "print-board.txt", "r")

p = Position{19}()
move!(p, black, 5, 5)
for (x,y) in ((5,6),(6,6),(6,5),(5,4),(4,5))
    move!(p, white, x, y)
end
#io = open("print-position.txt", "w")
#print(io, p)
#close(io)
@test sprint(print, p) == open(readall, "print-position.txt", "r")
@test p.groups.size[1] == 0
@test p.groups.size[2] == 3
@test p.groups.size[3] == 1
@test p.groups.size[4] == 1

p = Position{19}()
move!(p, black, 5, 5)
#io = open("print-group-0.txt", "w")
#print(io, p)
#close(io)
@test sprint(print, p) == open(readall, "print-group-0.txt", "r")
# note (4,6) is shifted so get group join at print-group-4.txt
for (i, (x,y)) in enumerate(((4,4),(4,5),(5,6),(4,6),(6,6),(6,5),(6,4),(5,4)))
    move!(p, white, x, y)
#    io = open("print-group-$i.txt", "w")
#    print(io, p)
#    close(io)
    @test sprint(print, p) == open(readall, "print-group-$i.txt", "r")
end

for i in 1:10
    move!(p, black, 11-i, 20-i)
end
println(p)
#io = open("print-space.txt", "w")
#print(io, p)
#close(io)
@test sprint(print, p) == open(readall, "print-space.txt", "r")

#srand(1)
#p = Position()
#for i in 1:60
#    for t in (black, white)
#        x, y = 0, 0
#        while true
#            x, y = rand(1:19), rand(1:19)
#            if point(p, x, y) == empty
#                break
#            end
#        end
#        move!(p, t, x, y)
#    end
#end
#io = open("random-position.txt", "w")
#print(io, p)
#close(io)
#out = zeros(Int8, 19, 19)
#div = Int8[0 -1 0; -1 4 -1; 0 -1 0]
#println(div)
#convolve(p.flood.distance, 1, div, out)
#blank!(out, p)
#println(fix(out))
