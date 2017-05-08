module IntervalTrees

	typealias Interval (Int, Int)
	export Interval, Node, buildnode

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

	function buildnode(intervals::Vector{Interval})
		if isempty(intervals)
			return Sentinel()
		end
		lefts=map( i ->i[1], intervals)
		rights=map( i ->i[2], intervals)
		center=mean([lefts; rights])
		to_left=filter(i-> i[2]<center, intervals)
		to_right=filter(i-> i[1]>center, intervals)
		intersecting=filter(i-> (i[1]<center) && (i[2]>center), intervals)
		inter_by_left=sort(intersecting, by=i->i[1])
		inter_by_right=sort(intersecting, by=i->i[2])
		leftnode::ANode=buildnode(to_left)
		rightnode::ANode=buildnode(to_right)
		Node(center, leftnode, rightnode, inter_by_left, inter_by_right)
  end

  function test()
  	intervals = [(1, 10), (2,4), (6,9), (2,15)]
  	println(intervals)
  	buildnode(intervals)
  end

end
