module RuleExtractor

using CoreBasics_unipolar
using DataStructures

export Vertex, RuleSet, get_id, in_rules_lb, in_rules_ub, test!, succ_id, make_succ, successors, rules_for_target, extract_rules

type Vertex

    lbub::Bool              # true lb, false if ub
    target::Int             # index of target output neuron (head)
    isRule::Bool            # true if v is or is subsumed by a rule
    isPos::Bool             # true if target is positive given activation in val
    decID::Int 

    val::Array{Int, 1}
    mem::Array{Int, 1}

    Vertex(lbub::Bool, target::Int, val::Array{Int, 1}, mem::Array{Int, 1}) = new(lbub, target, false, false, get_id(val), val, mem)
end # type




type RuleSet
    lbRules::Array{Int, 2}
    ubRules::Array{Int, 2}
end # type



function get_id(val::Array{Int,1})      #computes decimal id for a vertex based on binary value of val
    max = length(val)
    exp = [2^(max - i) for i = 1:max]
    id = dot(val, exp) + 1 #b/c vVec goes from 1 to n, not 0 to n-1
    return id
end # function



function in_rules_lb(v::Vertex, r::RuleSet)  #return true if v.val is subsumed by known lower bound rules

    isSub = false # assume rule is new. disprove later
    subRule = zeros(Int,size(r.lbRules,2)) # store the subsuming rule

        # say r.lbRules contains all known rules ordered in binary... 
        # scrap that! just go through all known rules 
    for i = 1:size(r.lbRules,1)
        if minimum( v.val - vec(r.lbRules[i,:]) ) == 0 # all 1s in rule are 1s in val -> not new
            isSub = true
            subRule = vec(r.lbRules[i,:])
            break # insufficient. need to take all subsuming rules into account
        end #if
    end #for

    return isSub, subRule
end #function



function in_rules_ub(v::Vertex, r::RuleSet) #return true if v.val is subsumed by known upper bound rules

    isSub = false #assume rule is new. disprove later
    subRule = zeros(Int,size(r.ubRules ,2)) # store the subsuming rule

    for i = 1:size(r.ubRules,1)
        if maximum( v.val - vec(r.ubRules[i,:]) ) == 0 # all 1s in val are 1s in rule -> not new
            isSub = true
            subRule = vec(r.ubRules[i,:])
            break
        end #if
    end #for

    return isSub, subRule
end # function



function test!(core::LogicCore, v::Vertex, r::RuleSet)  # evals v given r and adapts v.mem. adds v to r if v is a new rule sets isRule to true if part of a rule
                                                           
    cOut, rest = run_core(core, float(v.val))                        # see if v is positive or negative                                

    v.isPos = cOut[v.target] == 1.0 ? true : false


    if v.lbub       # test for lower bound
        
        # if positive, see if v is part of some known rule (lb). if not, add to rules. then either way set v.mem to zeros.
        if v.isPos

            isSub, subRule = in_rules_lb(v, r)
            if !isSub
                r.lbRules = [r.lbRules; v.val']
                #println("    lb rule: $(v.val)")
            end #if
            v.mem *= 0
            v.isRule = true
        # if negative, see if v is part of some known impossibility (ub). if so, adapt mem so only interesting successors are generated.
        else
            isSub, subRule = in_rules_ub(v, r)

            if isSub
                # adapting mem: set mem to -1 wherever subRule is 1 (and mem not 0 already)
                #v.mem -= v.mem .* subRule * 2   # note: mem can now contain values of -1 <-----------

                for i = 1:length(subRule)
                    if subRule[i] == 1 && v.mem[i] != 0
                        v.mem[i] = -1
                    end #if
                end #for
            end #if                         
                                            
        end #ifelse                         
        
    else            # test for upper bound
        
        # if positive, see if v is part of some known rule (lb). if so, adapt mem, so only interesting successors are generated.
        if v.isPos

            isSub, subRule = in_rules_lb(v, r)

            if isSub
                #adapting mem: set mem to -1 wherever subRule is 0 (and mem not 0 already)
                #v.mem += v.mem .* (subRule -1) * 2 # <---------------------------------------------------------------
                for i = 1:length(subRule)
                    if subRule[i] == 0 && v.mem[i] != 0
                        v.mem[i] = -1
                    end #if
                end #for
            end #if

        # if negative, see if v is part of some known impossibility (ub). if not, add to impossibilities. then either way set v.mem to zeros.
        else
            isSub, subRule = in_rules_ub(v, r)

            if !isSub
                r.ubRules = [r.ubRules; v.val']
                #println("    ub rule: $(v.val)")
            end #if
            v.mem *= 0
            v.isRule = true
        end #ifelse

    end #ifelse

end # function


# returns id of the vertex created by changing activation of the neuron at position ind in v.
# if this is not a valid successor, -1 is returned
function succ_id(v::Vertex, ind::Int)
    if v.mem[ind] == 0
        return -1
    end # if
    max = length(v.val)
    newID = v.lbub ? v.decID + 2^(max-ind) : v.decID - 2^(max-ind)
    return newID
end # function



function make_succ(v::Vertex, ind::Int)

    newV = deepcopy(v)
    newV.val[ind] = v.lbub ? 1 : 0
    newV.mem = abs(newV.mem)    # eliminate -1s
    newV.mem[ind] = 0
    newV.decID = succ_id(v,ind)
    return newV
end # function



function successors(core::LogicCore, v::Vertex, r::RuleSet, vVec::Array{Vertex,1}, q::Queue{Deque{Int}}) # computes suc. of v, tests them to compute new v.mem and then updates v'.mem accordingly.

    # test v again, given new information
    test!(core, v, r)
    #println("$(v.mem)")
        # go through v.mem, for each 1 make and/or investigate successor, and enq it
    
    
    noMatchSucc = minimum(v.mem) >= 0 ? true : false # only matters if v.mem contains no -1s (see notes)
    

    for i = 1:length(v.mem)
        if v.mem[i] == 1
            succID = succ_id(v,i)
            if !isdefined(vVec, succID)
                vVec[succID] = make_succ(v,i)
                test!(core, vVec[succID], r)
                enqueue!(q,succID)
                #println("            enq: $(vVec[succID].val) $(vVec[succID].lbub)")
            end #if
        # update v.mem accordingly
            if vVec[succID].isRule
                v.mem[i] = 0
            end #if

            if vVec[succID].isPos == v.isPos
                noMatchSucc = false # true if no successors have the same isPos value as v a
            end #if
        end #if
    end #for

    if noMatchSucc                  # see if v is an 'anti' rule
        if v.lbub && !v.isPos
            r.ubRules = [r.ubRules; v.val']
        elseif !v.lbub && v.isPos
            r.lbRules = [r.lbRules; v.val']
        end
    end

        # then update all successors with v.mem
    for i = 1:length(v.mem)
        if v.mem[i] == 1
            succID = succ_id(v,i)
            vVec[succID].mem = vVec[succID].mem .* abs(v.mem)     # all 0s of v.mem become 0 in successors. no other change (-1 don't carry over)
        end #if
    end #for

end # function



function rules_for_target(core::LogicCore, target::Int) # traverses inputs to core and returns vector of rules

    # create bottom and top element and place them in vVec.
    nBits = 2*core.nAtoms
    botEl = Vertex(true , target, zeros(Int, nBits), ones(Int, nBits))
    topEl = Vertex(false, target, ones(Int , nBits), ones(Int, nBits))

    # enq top and bottom element using just one queue, sacrificing alternation, ensuring equal layer progression
    q = Queue(Int)
    enqueue!(q, botEl.decID)
    enqueue!(q, topEl.decID)
    

    # create vVec and insert top and bottom element
    vVec = Array(Vertex, topEl.decID)
    vVec[1]   = botEl
    vVec[end] = topEl

    # create empty ruleset (and hope access doesn't blow up anywhere)
    r = RuleSet(Array(Int, 0, nBits), Array(Int, 0, nBits))

    # while queue not empty
        # deq front element, get successors, which are enqueued automatically

    nIter = 0 # (count iterations to see, how successful pruning was)
    
    while !isempty(q)
        v = vVec[dequeue!(q)]
        #print("deq: $(v.val) $(v.lbub) ")
        successors(core, v, r, vVec, q)

        nIter += 1
    end #while

    println("target: $target   iterations: $nIter   total states: $(topEl.decID)   %pruned: $((topEl.decID - nIter)/topEl.decID)")
    # return ruleset 
    return r

end # function



function extract_rules(core::LogicCore, outDir::String) # calls rules_for_target for each atom. processes rule list.

    # for each atom run rules_for_target
    # parse lb-rule-list and construct clause.
    # write to file.
    
end # function

end #module