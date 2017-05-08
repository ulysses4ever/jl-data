module IntervalTrees

	typealias Interval (Int, Int)
	export Interval, Node, buildnode

	abstract ANode
  type Node <: ANode
		center::Int
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
		println(center)
		to_left=filter(i-> i[2]<center, intervals)
		to_right=filter(i-> i[1]>center, intervals)
		println(to_left)
		println(to_right)
		intersecting=filter(i-> (i[1]<center) && (i[2]>center), intervals)
		inter_by_left=sort(intersecting, by=(l,r)->l)
		inter_by_right=sort(intersecting, by=(l,r)->r)
		Node(center,buildnode(to_left), buildnode(to_right), inter_by_left, inter_by_right)
  end

end
