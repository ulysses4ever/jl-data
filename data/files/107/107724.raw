
regen = false

a = ones(UInt32, 19, 19)
b = zeros(UInt32, 19, 19)
@GoCL.forall i j 19 begin
    b[i, j] = 2 * a[i, j]
end
@test b == 2a
c = @GoCL.forall_fold i j 19 (+) 0 b begin
    b[i, j] = 3 * a[i, j]
end
@test c == 3 * 19 * 19


b = GoCL.Board{19}()
@test length(b.row) == 19
@test point(b, 1, 1) == empty
@test point(b, 19, 19) == empty
move!(b, black, 10, 10)
@test point(b, 10, 10) == black
move!(b, white, 12, 11)
if regen
    open("print-board.txt", "w") do io
        print(io, b)
    end
end
@test sprint(print, b) == open(readall, "print-board.txt", "r")

p = Position()
move!(p, black, 5, 5)
for (x,y) in ((5,6),(6,6),(6,5),(5,4),(4,5))
    move!(p, white, x, y)
end
if regen
    open("print-position.txt", "w") do io
        print(io, p)
    end
end
@test sprint(print, p) == open(readall, "print-position.txt", "r")
@test p.groups.size[1] == 0
@test p.groups.size[2] == 3
@test p.groups.size[3] == 1
@test p.groups.size[4] == 1

p = Position()
move!(p, black, 5, 5)
if regen
    open("print-group-0.txt", "w") do io
        print(io, p)
    end
end
@test sprint(print, p) == open(readall, "print-group-0.txt", "r")
# note (4,6) is shifted so get group join at print-group-4.txt
for (i, (x,y)) in enumerate(((4,4),(4,5),(5,6),(4,6),(6,6),(6,5),(6,4),(5,4)))
    move!(p, white, x, y)
    if regen
        open("print-group-$i.txt", "w") do io
            print(io, p)
        end
        @test sprint(print, p) == open(readall, "print-group-$i.txt", "r")
    end
end

for i in 1:10
    move!(p, black, 11-i, 20-i)
end
if regen
    open("print-space.txt", "w") do io
        print(io, p)
    end
end
@test sprint(print, p) == open(readall, "print-space.txt", "r")

p = random_position(1, 9, 50)
if regen
    open("random-position.txt", "w") do io
        print(io, p)
    end
end
@test sprint(print, p) == open(readall, "random-position.txt", "r")
