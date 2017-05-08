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
println("This list contains...");
for node in lst
  println(node.val);
end
pnode = remove!(lst, 6);
println("The sixth element was...");
println(pnode.val);
@test pnode.val == 1;
@test length(lst) == 7;

println("This list contains...");
for node in lst
  println(node.val);
end

empty!(lst);
@test length(lst) == 0
@test lst.head == nothing
@test lst.tail == nothing

some_array = rand(-50:50, 50);
@test push!(lst, some_array) == 50;
for i=1:50
  @test shift!(lst).val == some_array[i];
end

some_array = rand(-50:50, 50);
@test push!(lst, some_array) == 50;
for i=50:-1:1
  @test pop!(lst).val == some_array[i];
end

println("This list contains...");
for node in lst
  println(node.val);
end
println("and is length ", length(lst));

@test length(lst) == 0;
@test lst.head == nothing;
@test lst.tail == nothing;

@test unshift!(lst, 9) == 1;
@test unshift!(lst, 8) == 2;
@test unshift!(lst, 7) == 3;
@test unshift!(lst, 6) == 4;
@test unshift!(lst, 5) == 5;
@test unshift!(lst, 4) == 6;
@test unshift!(lst, 3) == 7;
@test unshift!(lst, 2) == 8;
@test unshift!(lst, 1) == 9;

@test remove!(lst, 7).val == 7;
@test remove!(lst, 7).val == 8;
@test length(lst) == 7;
@test remove!(lst, 7).val == 9;
@test remove!(lst, 3).val == 3;
@test remove!(lst, 2).val == 2;
@test remove!(lst, 1).val == 1;
@test remove!(lst, 2).val == 5;
@test remove!(lst, 2).val == 6;
@test remove!(lst, lst.head).val == 4;

some_array = rand(-50:50, 50);
@test unshift!(lst, some_array) == 50;
for i=50:-1:1
  @test shift!(lst).val == some_array[i];
end

some_array = rand(-50:50, 50);
@test unshift!(lst, some_array) == 50;
for i=1:50
  @test pop!(lst).val == some_array[i];
end

t = (2, 3, 5, 1, 4);
lst = DoublyLinkedList{Int64}(t...);
for i=1:length(t);
  @test remove!(lst, 1).val == t[i];
end

println("DOUBLY LINKED LIST TESTS PASSED!");

# write your own tests here
@test 1 == 1 # this better not fail

lst = SinglyLinkedList{Int64}()
push!(lst, 3);
@test length(lst) == 1;
@test lst.head.val == 3;
@test lst.tail.val == 3;
@test lst.head == lst.tail;

push!(lst, rand(1:100, 4));
@test length(lst) == 5;
@test lst.head.val == 3;

push!(lst, 1);
push!(lst, 2);
push!(lst, 3);
println("This list contains...");
for node in lst
  println(node.val);
end
pnode = remove!(lst, 6);
println("The sixth element was...");
println(pnode.val);
@test pnode.val == 1;
@test length(lst) == 7;

println("This list contains...");
for node in lst
  println(node.val);
end

empty!(lst);
@test length(lst) == 0
@test lst.head == nothing
@test lst.tail == nothing

some_array = rand(-50:50, 50);
@test push!(lst, some_array) == 50;
for i=1:50
  @test shift!(lst).val == some_array[i];
end

some_array = rand(-50:50, 50);
@test push!(lst, some_array) == 50;
for i=50:-1:1
  @test pop!(lst).val == some_array[i];
end

println("This list contains...");
for node in lst
  println(node.val);
end
println("and is length ", length(lst));

@test length(lst) == 0;
@test lst.head == nothing;
@test lst.tail == nothing;

@test unshift!(lst, 9) == 1;
@test unshift!(lst, 8) == 2;
@test unshift!(lst, 7) == 3;
@test unshift!(lst, 6) == 4;
@test unshift!(lst, 5) == 5;
@test unshift!(lst, 4) == 6;
@test unshift!(lst, 3) == 7;
@test unshift!(lst, 2) == 8;
@test unshift!(lst, 1) == 9;

@test remove!(lst, 7).val == 7;
@test remove!(lst, 7).val == 8;
@test length(lst) == 7;
@test remove!(lst, 7).val == 9;
@test remove!(lst, 3).val == 3;
@test remove!(lst, 2).val == 2;
@test remove!(lst, 1).val == 1;
@test remove!(lst, 2).val == 5;
@test remove!(lst, 2).val == 6;
@test pop!(lst).val == 4;

some_array = rand(-50:50, 50);
@test unshift!(lst, some_array) == 50;
for i=50:-1:1
  @test shift!(lst).val == some_array[i];
end

some_array = rand(-50:50, 50);
@test unshift!(lst, some_array) == 50;
for i=1:50
  @test pop!(lst).val == some_array[i];
end

t = (2, 3, 5, 1, 4);
lst = DoublyLinkedList{Int64}(t...);
for i=1:length(t);
  @test remove!(lst, 1).val == t[i];
end

println("SINGLY LINKED LIST TESTS PASSED!");
