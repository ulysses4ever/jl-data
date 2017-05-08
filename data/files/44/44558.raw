using List
using Base.Test

# write your own tests here
@test 1 == 1 # this better not fail

lst = DoublyLinkedList{Int64}()
push!(lst, 3);
@test length(lst) == 1;
@test lst.head.val == 3;
@test lst.tail.val == 3;
@test lst.head == lst.tail;

push!(lst, rand(1:100, 4));
@test length(lst) == 5;
@test lst.head.val == 3;
@test lst.head.prev == nothing;
@test lst.head.next.prev.val == 3;

push!(lst, 1);
push!(lst, 2);
push!(lst, 3);
pnode = remove!(lst, 7);
@test pnode.val == 2;
@test length(lst) == 7;

println("This list contains...");
for node in lst
  println(node.val);
end
