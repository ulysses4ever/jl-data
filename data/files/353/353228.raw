using Base.Test
using Inv

a = [2,3,1,5]
#@test Inv.merge_sort(a) == [1,2,3,5]

let left = [1,4,6,8],right = [0,2,5]
    @test Inv.merge(left, right) == [0,1,2,4,5,6,8]
end

let data = [5,8,2,4,1]
    @test Inv.merge_sort(data) == [1,2,4,5,8]
end

let data = [2,1,0,6]
    @test Inv.inv_count(data) == 2+1
end
