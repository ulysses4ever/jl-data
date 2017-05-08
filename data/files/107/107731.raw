
regen = false

a = ones(UInt32, 19, 19)
b = zeros(UInt32, 19, 19)
@Go.forall i j 19 begin
    b[i, j] = 2 * a[i, j]
end
@test b == 2a
c = @Go.forall_fold i j 19 (+) 0 b begin
    b[i, j] = 3 * a[i, j]
end
@test c == 3 * 19 * 19


b = Go.Board{19}()
@test length(b.row) == 19
@test point(b, 1, 1) == empty
@test point(b, 19, 19) == empty
move!(b, black, 10, 10)
@test point(b, 10, 10) == black
move!(b, white, 12, 11)
compare("position/print-board.txt", b)

p = Position()
move!(p, black, 5, 5)
for (x,y) in ((5,6),(6,6),(6,5),(5,4),(4,5))
    move!(p, white, x, y)
end
compare("position/print-position.txt", p)
@test p.groups.size[1] == 0
@test p.groups.size[2] == 3
@test p.groups.size[3] == 1
@test p.groups.size[4] == 1

p = Position()
move!(p, black, 5, 5)
compare("position/print-group-0.txt", p)
# note (4,6) is shifted so get group join at print-group-4.txt
for (i, (x,y)) in enumerate(((4,4),(4,5),(5,6),(4,6),(6,6),(6,5),(6,4),(5,4)))
    move!(p, white, x, y)
    compare("position/print-group-$i.txt", p)
end

for i in 1:10
    move!(p, black, 11-i, 20-i)
end
compare("position/print-space.txt", p)

p = random_position(1, 9, 50)
compare("position/random-position.txt", p)

p1 = Position()
move!(p1, white, 2, 3)
move!(p1, white, 3, 2)
move!(p1, white, 3, 4)
move!(p1, black, 4, 2)
move!(p1, black, 4, 4)
move!(p1, black, 5, 3)
p2 = Position(p1)
move!(p2, white, 4, 3)
p3 = Position(p2)
move!(p3, black, 3, 3)
p4 = Position(p3)
move!(p4, white, 4, 3)
#println(p1)
#println(p2)
#println(p3)
#println(p4)
@test Go.ko([p1,p2,p3], white, 4, 3)
