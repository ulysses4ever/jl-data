collection = readcsv("C:/Users/adm/Desktop/MaxFlowNet.csv",Int)
#
NumNode=maximum(collection[:,1:2])
Size=size(collection,1)
type Arc
  toNode::Int
  Flow::Int
end
adjList=Array(Array{Arc},NumNode)
for i in 1:NumNode
  adjList[i]=[]
end
for x in 1:Size
  a,b,c=collection[x,:]
  push!(adjList[a],Arc(b,c))
end

function MaxFlow(adjList,SourceNode,SinkNode)
  LabelNode=zeros(Int,NumNode)
  LabelNode[SinkNode]=1
  Pred=zeros(Int,NumNode)
  while LabelNode[SinkNode]==1
    for i=1:length(Pred)
      Pred[i]=0 end
    for i=1:length(Pred)
      LabelNode[i]=0 end

    LabelNode[SourceNode]=1
    List=[SourceNode]

    while isempty(List)==false && LabelNode[SinkNode]==0
      i = shift!(List)
      for j = 1:length(adjList[i])
        NextNode=adjList[i][j].toNode
      if LabelNode[NextNode]==0 && adjList[i][j].Flow > 0
        LabelNode[NextNode]=1
        Pred[NextNode]=i
        push!(List,NextNode)
        end
      end
      end
      if LabelNode[SinkNode]==1
        ahmed=getminm(Pred,SourceNode,SinkNode)
        x=agum(Pred,SourceNode,SinkNode,ahmed)
      println("############################################################")
      println("x=",x)
   end

  end
 # return adjList
end
function getminm(Pred,SourceNode,SinkNode)
  mi=Inf
  while(SourceNode !=SinkNode )
    Pnode=Pred[SinkNode]
    m=length(adjList[Pnode])
        for x=1:m
          if adjList[Pnode][x].toNode == SinkNode
            if adjList[Pnode][x].Flow < mi
              mi=adjList[Pnode][x].Flow
        end
      end
    end
    SinkNode=Pnode
  end
  return mi
end

function agum(Pre,SourceNode,SinkNode,ahmed)
  while(SourceNode !=SinkNode )
    Pnode=Pre[SinkNode]
    m=length(adjList[Pnode])
        for x=1:m
          if adjList[Pnode][x].toNode == SinkNode
             adjList[Pnode][x].Flow=adjList[Pnode][x].Flow-ahmed
             end
        end
    SinkNode=Pnode
  end
    return adjList
end

println("newnewnew")
MaxFlow(adjList,1,25)
