module IntervalTrees

	typealias Interval (Int, Int)
	export Interval, Node, buildnode

  type Node
		left::Node
		right::Node
		inter_by_left::Vector{Interval}
		inter_by_right::Vector{Interval}
	end

	function buildnode(intervals::Vector{Interval})
		lefts=map((l,r)->l, intervals)
		rights=map((l,r)->r, intervals)
		center=mean([lefts; rights])
		to_left=filter(i-> i[0]<center, intervals)
		to_right=filter(i-> i[1]>center, intervals)
		intresecting=filter(i-> (i[0]<center)&&(i[1]>center), intervals)
		inter_by_left=sort(intersecting, by=(l,r)->l)
		inter_by_right=sort(intersecting, by=(l,r)->r)
		Node(buildnode(to_left), buildnode(to_right), inter_by_left, inter_by_right)
  end

end
