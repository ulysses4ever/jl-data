module IntervalTrees

	export Interval, Node, build, search
	using Base.Test

	typealias Interval (Int, Int)

	abstract ANode
    type Node <: ANode
		center::Float32
		left::ANode
		right::ANode
		inter_by_left::Vector{Interval}
		inter_by_right::Vector{Interval}
	end
	type Sentinel <: ANode
	end
    function left(i)
        i[1]
    end
    function right(i)
        i[2]
    end
  	function build(intervals::Vector{Interval})
		if isempty(intervals)
			return Sentinel()
		end
		lefts = map( left, intervals)
		rights = map( right, intervals)
		center = mean([lefts; rights])
		to_left = filter(i-> right(i)<center, intervals)
		to_right = filter(i-> left(i)>center, intervals)
		intersecting = filter(i-> (left(i)<center) && (right(i)>center), intervals)
		inter_by_left = sort(intersecting, by=left)
		inter_by_right = sort(intersecting, by=right, rev=true)
		leftnode = build(to_left)
		rightnode = build(to_right)
        n = Node(center, leftnode, rightnode, inter_by_left, inter_by_right)
        n
  	end

  	function search(tree::Sentinel, point::Int)
    	Array(Interval, 0)
  	end
	function search(tree::Sentinel, int::Interval)
		Array(Interval, 0)
	end

    # find all intervals containing this point
  	function search(tree::Node, point::Int)
        if point < tree.center
		    res = search(tree.left, point)
            append!(res, startless(tree.inter_by_left, point, left))
	        return res
		elseif point == tree.center
		    return tree.inter_by_left
		else
			res = search(tree.right, point)
            append!(res, startless(tree.inter_by_right, point, right, rev=true))
	    	return res
		end
  	end

    # find all intervals intersecting this one
	function search(tree::Node, int::Interval)
		res = Array(Interval, 0)
        if left(int) < tree.center
            append!(res, search(tree.left, int))
            append!(res, startless(tree.inter_by_left, left(int), left))
        end
        if right(int) > tree.center
            append!(res, search(tree.right, int))
            append!(res, startless(tree.inter_by_right, right(int), right, rev=true))
        end
        res
	end

    function startless(arr, point, f; rev=false)
        idx = searchsorted(map(f, arr), point, rev=rev)
        arr[1:idx.start-1]
    end

	function test()
  		intervals = [(1, 10), (2, 4), (6, 9), (2, 15)]
  		println(intervals)
  		tree=build(intervals)
    	intersecting = search(tree, 3)
		@test contains(intersecting, [(1, 10), (2, 4), (2, 15)])
		@test !contains(intersecting, (6, 9))

        intersecting = search(tree, 8)
        @test contains(intersecting, [(1, 10), (6, 9), (2, 15)])
        @test !contains(intersecting, (2,4))

        intr = search(tree, (11, 12))
        println(intr)
        @test contains(intr, (2, 15))
  	end

	function contains(res, int::Interval)
		findfirst(i -> i==int, res) > 0
	end
    function contains(res, ints::Vector{Interval})
        all(i->contains(res, i), ints)
    end
end
