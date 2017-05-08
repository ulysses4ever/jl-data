
using GoCL
using Base.Test

a = ones(UInt32, 19, 19)
b = zeros(UInt32, 19, 19)
@forall i j begin
    b[i, j] = 2 * a[i, j]
end
@test b == 2a
c = @forall_fold i j (+) 0 b begin
    b[i, j] = 3 * a[i, j]
end
@test c == 3 * 19 * 19

b = Board()
@test length(b.rows) == 19
@test point(b, 1, 1) == empty
@test point(b, 19, 19) == empty
move!(b, black, 10, 10)
@test point(b, 10, 10) == black
move!(b, white, 12, 11)
s = sprint(print, b)
#io = open("print-board.txt", "w")
#print(io, b)
#close(io)
@test s == open(readall, "print-board.txt", "r")

p = Position()
move!(p, black, 5, 5)
for (x,y) in ((5,6),(6,6),(6,5),(5,4),(4,5))
    move!(p, white, x, y)
end
s = sprint(print, p)
#io = open("print-position.txt", "w")
#print(io, p)
#close(io)
@test s == open(readall, "print-position.txt", "r")

srand(1)
p = Position()
for i in 1:60
    for t in (black, white)
        x, y = 0, 0
        while true
            x, y = rand(1:19), rand(1:19)
            if point(p, x, y) == empty
                break
            end
        end
        move!(p, t, x, y)
    end
end
io = open("random-position.txt", "w")
print(io, p)
close(io)
