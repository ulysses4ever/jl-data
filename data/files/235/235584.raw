module NineML

export ODE, Assignment, Relation, Alias, OnEvent, OnCondition, Regime, Group, Population, Projection
export parse_ComponentClass, parse_Component, parse_Components
export eval_Relation, eval_Alias, eval_Regime, eval_Dynamics


using Base.Collections
using Graphs
using Sims
using LightXML
using Winston

typealias Time Float64

type ODE
    quantity:: Symbol
    freevars:: Array{Symbol}
    rhs:: Union(Float64,Symbol,Expr)
end

type Assignment
    quantity:: Symbol
    freevars:: Array{Symbol}
    rhs:: Union(Symbol,Expr)
end

type Alias
    quantity:: Symbol
    freevars:: Array{Symbol}
    rhs:: Expr
end

type Relation
    quantity:: Symbol
    argument:: Symbol
    freevars:: Array{Symbol}
    rhs:: Expr
end

type OnEvent
    quantity:: Symbol
    asgnsys:: Array{Any}
end

type OnCondition
    target_regime:: Union(Symbol,Nothing)
    trigger:: Expr
    event_quantity:: Symbol
    asgns:: Array{Any}
end

type Regime
    name:: Symbol
    odes:: Vector{ODE}
    asgns:: Vector{Assignment}
    events:: Vector{OnEvent}
    structuralEvents:: Vector{OnCondition}

end

type Population
    label:: Symbol
    n::Int64   # size
    proto::Sim   # prototype
end


type Component
    name:: Symbol
    parameterValues:: Dict{Symbol,Union(Float64,Expr)}
    initialValues:: Dict{Symbol,Union(Float64,Expr)}
end

type ComponentClass
    name:: Symbol
    parameters:: Vector{Symbol}
    states:: Vector{Symbol}
    ports:: Vector{Symbol}
    dynamics:: (Vector{Alias},Vector{Relation},Vector{Regime})
end


typealias Group Set{Population}


type Projection
    label   :: Symbol
    source  :: Group
    target  :: Group
    rule    :: Function
    weight  :: Function
    delay   :: Union (Function, Time)
    psr     :: Function
end


abstract ProjectionGraph


type SimpleProjectionGraph <: ProjectionGraph
    label :: Symbol
    G :: SimpleGraph
end


type WeightDelayProjectionGraph <: ProjectionGraph
    label :: Symbol
    G :: SimpleGraph
    M :: SparseMatrixCSC{Float64,Int64}
    D :: SparseMatrixCSC{Float64,Int64}
end


type WeightProjectionGraph <: ProjectionGraph
    label :: Symbol
    G :: SimpleGraph
    M :: SparseMatrixCSC{Float64,Int64}
end


function make_graph(n)
    G = Graphs.simple_graph(n)
    return G
end

function build_weight_delay_projection_graph (projection)
    c = projection.rule
    w = projection.weight
    d = projection.delay
    G = make_graph (n)
    W::Array{Float64,2} = zeros(n,n)
    D::Array{Float64,2} = zeros(n,n)
    eind = 1
    for i = 1 : n
        for j = 1 : n
            if c(i,j)
                add_edge! (G, i, j)
                W[i,j] = w(i,j)
                D[i,j] = d(i,j)
                eind = eind + 1
            end
        end
    end
    return WeightDelayProjectionGraph(projection.label,G,sparse(M),sparse(D))
end
    

function build_weight_projection_graph (projection)
    c = projection.rule
    w = projection.weight
    G = make_graph (n)
    W::Array{Float64,2} = zeros(n,n)
    eind = 1
    for i = 1 : n
        for j = 1 : n
            if c(i,j)
                add_edge! (G, i, j)
                W[i,j] = w(i,j)
                eind = eind + 1
            end
        end
    end
    WeightProjectionGraph(projection.label,G,sparse(M))
end




type Network

    n :: Int64
    d :: Float64
    
    State :: Array{(Function,Sim,Array {Float64,1},Array {Float64,1}),1}

    Connections :: Vector {ProjectionGraph}

    # TODO: use type Unknown for synaptic weight
    PQ :: Array {PriorityQueue {Time,Float64},1} 
end

unary_operations = [:heaviside]

find_vars(e) = find_vars(e, Any[], Any[])
function find_vars(e,lst,vars)
    if isa(e,Symbol)
        if current_module()===Main && !isdefined(e) && !(e in unary_operations) && !(e in vars) && !(e in lst)
            push!(lst, e)
        end
    elseif isa(e,Expr) && e.head !== :quote && e.head !== :top
        for x in e.args
            find_vars(x,lst,vars)
        end
    end
    lst
end


function replace_lift_vars(e, aliases, relations, parameters, states)

    if isa(e,Symbol)
        if e == :t
            return :t
        elseif current_module()===Main && !isdefined(e) && (haskey(parameters,e))
            return Expr(:ref,:p,Expr(:ref,Expr(:.,Expr(:.,:ss,:(:sm)),:(:parameter_idx_map)),
                                     Expr(:quote,parameters[e].sym)))
        elseif current_module()===Main && !isdefined(e) && (haskey(states,e))
            return Expr(:ref,:y,Expr(:ref,Expr(:.,Expr(:.,:ss,:(:sm)),:(:unknown_idx_map)),
                                     Expr(:quote,states[e].sym)))
        else
            return replace_vars(e,aliases,relations,parameters,states)
        end
    elseif isa(e,Expr) && e.head !== :quote && e.head !== :top
        begin
            e1 = Expr(e.head)
            e1.args = map((x) -> replace_lift_vars(x,aliases,relations,parameters,states), e.args)
            e1.typ = e.typ
            return e1
        end
    else
        return replace_vars(x,aliases,relations,parameters,states)
    end
end            

function replace_vars(e, aliases, relations, parameters, states)
    if isa(e,Symbol)
        if e == :t
            return MTime
        #elseif current_module()===Main && !isdefined(e) && (haskey(ports,e))
        #    return ports[e]
        elseif current_module()===Main && !isdefined(e) && (haskey(parameters,e))
            return parameters[e]
        elseif current_module()===Main && !isdefined(e) && (haskey(states,e))
            return states[e]
        elseif current_module()===Main && !isdefined(e) && (haskey(aliases,e))
            begin
                a = aliases[e]
                e1 = Expr(:call)
                e1.args = [a[1], map((x) -> replace_vars(x,aliases,relations,parameters,states), a[2])...]
                return e1
            end
        elseif current_module()===Main && !isdefined(e) && (haskey(relations,e))
            begin
                r = relations[e]
                e1 = Expr(:call)
                e1.args = [r[1], map((x) -> replace_vars(x,aliases,relations,parameters,states), r[2])...]
                return e1
            end
        else
            return e
        end
    elseif isa(e,Expr) && e.head == :call && (e.args[1] == :heaviside)
        begin
            cond = MExpr(Expr(:comparison,replace_vars(e.args[2],aliases,relations,parameters,states), :<, 0.0))
            e1 = ifelse(cond, 0.0, 1.0)
            return e1
        end
    elseif isa(e,Expr) && e.head == :call && (haskey(relations,e.args[1]))
        begin
            r = relations[e.args[1]]
            e1 = Expr(e.head)
            e1.args = [r[1], map((x) -> replace_vars(x,aliases,relations,parameters,states), [e.args[2],r[2]]...)]
            e1.typ = e.typ
            return e1
        end
    elseif isa(e,Expr) && e.head !== :quote && e.head !== :top
        begin
            e1 = Expr(e.head)
            e1.args = map((x) -> replace_vars(x,aliases,relations,parameters,states), e.args)
            e1.typ = e.typ
            return e1
        end
    else
        return e
    end
end
replace_vars(e) = replace_vars (e, Dict{Symbol,Alias}(), Dict{Symbol,Relation}(),
                                Dict{Symbol,Parameter}(), Dict{Symbol,Unknown}())




function parse_MathInline (parent)
    math = find_element(parent,"MathInline")
    if math == nothing
        return nothing
    else 
        e = parse(content(math))
        return e
    end
end


function parse_Regime (sysname,parameters,states,r)

    rname = symbol(attribute(r, "name"))
    timeDerivatives = get_elements_by_tagname (r, "TimeDerivative")
    stateAssignments =  get_elements_by_tagname (r, "StateAssignment")
    onEvents = get_elements_by_tagname (r, "OnEvent")
    onConditions = get_elements_by_tagname (r, "OnCondition")

    @assert (length (onConditions) <= 1)
    
    @assert ((!(isempty (timeDerivatives))) || (!(isempty (stateAssignments))))
    
    odes = map ((x) ->
                let
                    quantity = symbol(attribute(x, "variable"))
                    rhs = parse_MathInline(x)
                    fv = find_vars(rhs,Any[],Any[quantity])
                    return ODE (quantity, fv, rhs)
                end, timeDerivatives)
    
    asgns = map ((x) ->
                 let
                     quantity = symbol(attribute(x, "variable"))
                     rhs = parse_MathInline(x)
                     fv = find_vars(rhs,Any[],Any[quantity])
                     return Assignment (quantity, fv, rhs)
                 end, stateAssignments)

    events = map ((x) ->
                  let
                      quantity = symbol(attribute(x, "src_port"))
                      eventAssignments = get_elements_by_tagname (x, "StateAssignment")
                      easgns = map ((x) ->
                                    let
                                        quantity = symbol(attribute(x, "variable"))
                                        rhs = parse_MathInline(x)
                                        fv = find_vars(rhs,Any[],Any[quantity])
                                        return Assignment (quantity, fv, rhs)
                                    end, eventAssignments)
                      asgnsys = (map((x) ->
                                     let u = Unknown(x.quantity)
                                         reinit(u, MExpr(x.rhs))
                                     end, easgns))
                      return OnEvent (quantity, asgnsys)
                  end, onEvents)
    
    structuralEvents = map ((x) ->
                            let
                                target_regime = let a = attribute(x, "target_regime")
                                    if a == nothing
                                        nothing
                                    else
                                        symbol(a)
                                    end
                                end
                                trigger = parse_MathInline(find_element(x, "Trigger"))
                                eventAssignments = get_elements_by_tagname (x, "StateAssignment")
                                event_out = find_element (x, "EventOut")
                                event_quantity = symbol(attribute(event_out, "port"))
                                seasgns = map ((x) ->
                                               let
                                                   quantity = symbol(attribute(x, "variable"))
                                                   rhs = parse_MathInline(x)
                                                   fv = find_vars(rhs,Any[],Any[quantity])
                                                   return Assignment (quantity, fv, rhs)
                                               end, eventAssignments)

                                return OnCondition (target_regime, trigger, event_quantity, seasgns)
                            end, onConditions)
    
    Regime(rname,vec(odes),vec(asgns),vec(events),vec(structuralEvents))
end



function parse_Dynamics (sysname,parameters,dynamics)

    states = map((x)->symbol(attribute(x,"name")),
                 get_elements_by_tagname (dynamics, "StateVariable"))
    regimes   = get_elements_by_tagname (dynamics, "Regime")
    relations = get_elements_by_tagname (dynamics, "Relation")
    aliases   = get_elements_by_tagname (dynamics, "Alias")
    relations = map ((x) ->
                     let
                         quantity = symbol(attribute(x, "name"))
                         argument = symbol(attribute(x, "argument"))
                         fv = find_vars(rhs,Any[],Any[quantity,argument])
                         rhs = parse_MathInline(x)
                         return Relation (quantity, argument, fv, rhs)
                     end, relations)
    
    aliases = map ((x) ->
                   let
                       quantity = symbol(attribute(x, "name"))
                       rhs = parse_MathInline(x)
                       fv = find_vars(rhs,Any[],Any[quantity])
                       return Alias (quantity, fv, rhs)
                   end, aliases)
    
    return (states, vec(aliases), vec(relations), map((r) -> parse_Regime(sysname,parameters,states,r), regimes))
end

    
function parse_ComponentClass (filename)
    xdoc = parse_file(filename)

    xroot = root(xdoc)  # an instance of XMLElement
    #@assert(name(xroot) == "NineML")
    
    component = find_element(xroot, "ComponentClass")

    name = symbol(attribute(component, "name"))

    dynamics = find_element(component, "Dynamics")
    analog_send_ports = get_elements_by_tagname(component, "AnalogSendPort")
    analog_receive_ports = get_elements_by_tagname(component, "AnalogReceivePort")
    analog_reduce_ports = get_elements_by_tagname(component, "AnalogReducePort")
    event_send_ports = get_elements_by_tagname(component, "EventSendPort")
    event_receive_ports = get_elements_by_tagname(component, "EventReceivePort")


    parameters = map((x) -> symbol(attribute(x, "name")),
                     get_elements_by_tagname(component, "Parameter"))
    
    (states, aliases, relations, dynamics) = parse_Dynamics (name,parameters,dynamics)

    ports = setdiff (map((x) -> symbol(attribute(x,"name")),
                         [analog_receive_ports, analog_reduce_ports, event_receive_ports, analog_send_ports]),
                     states)

    ComponentClass(name, parameters, states, ports, (aliases, relations, dynamics))
end


function parse_Component (component)

    name = symbol(attribute(component, "name"))

    parameterValues = Dict{Symbol,Union(Float64,Expr)}()
    initialValues = Dict{Symbol,Union(Float64,Expr)}()

    for x in get_elements_by_tagname(component, "Property")
        let q = find_element(x,"Quantity")
            sv = find_element(q,"SingleValue")
            val = find_element(x,"MathInline") == nothing ? parse(content(sv)) : parse_MathInline(sv)
            
            parameterValues[symbol(attribute(x, "name"))] = val
        end
    end

    for x in get_elements_by_tagname(component, "Initial")
        let q = find_element(x,"Quantity")
            sv = find_element(q,"SingleValue")
            val = find_element(x,"MathInline") == nothing ? parse(content(sv)) : parse_MathInline(sv)
            
            initialValues[symbol(attribute(x, "name"))] = val
        end
    end

    Component(name, parameterValues, initialValues)

end

function parse_Components (filename)

    xdoc = parse_file(filename)

    xroot = root(xdoc)  # an instance of XMLElement
    #@assert(name(xroot) == "NineML")
    
    components = get_elements_by_tagname(xroot, "Component")
    return map(parse_Component, components)
    
end

function eval_Relation (r::Relation)

    Expr(:function,
         Expr(:call,r.quantity,[r.argument,r.freevars]),
         replace_vars(r.rhs))
    
end


function eval_Alias (a::Alias)

    Expr(:function,
         Expr(:call,a.quantity,a.freevars...),
         replace_vars(a.rhs))
end


function eval_Relation (r::Relation)

    Expr(:function,
         Expr(:call,r.quantity,r.freevars...),
         replace_vars(r.rhs))
end


function eval_Regime (regime::Regime,
                      name::Symbol,
                      parameters::Dict{Symbol,Parameter},
                      states::Dict{Symbol,Unknown},
                      aliases::Dict{Symbol,(Expr,Array{Symbol})},
                      relations::Dict{Symbol,(Expr,Array{Symbol})},
                      initialValues::Dict{Symbol,Union(Float64,Expr)})


    rname  = regime.name
    odes   = regime.odes
    asgns  = regime.asgns
    events = regime.events
    structuralEvents = regime.structuralEvents

    paramsys = (map((x) ->
                    let u = x[2]
                        InitialEquation(u - 0.0)
                    end, parameters))

    odesys = (map((x) ->
                  let u = states[x.quantity]
                      DerUnknown(x.quantity,0.0,false,u) -
                      (isa(x.rhs,Float64) ? x.rhs :
                       MExpr(replace_vars(x.rhs,aliases,relations,parameters,states)))
                  end, odes))
    
    asgnsys = (map((x) ->
                   let u = Unknown(x.quantity, 0.0)
                       u - MExpr(replace_vars(x.rhs,aliases,relations,parameters,states))
                   end, asgns))

    
    eventsys = (map((x) -> Event(x.quantity, x.asgnsys), events))

    conds = filter ((x) -> (x.target_regime == nothing) ? true : false, structuralEvents)
    condsys = map((x) ->
                  Event(MExpr(replace_vars(x.trigger,aliases,relations,parameters,states)),
                        map ((a) ->
                             reinit(states[a.quantity],
                                    replace_vars(a.rhs,aliases,relations,parameters,states)),
                             x.asgns)),
                      conds)

    strevs = filter ((x) -> (x.target_regime == nothing) ? false : true, structuralEvents)
    strevfns = map ((x) ->
                    let 
                        target_regime_name = symbol(join([x.target_regime,name]))
                        asgns_exprs = map ((a) ->
                                           Expr(:(=),
                                                replace_lift_vars(a.quantity,aliases,relations,parameters,states),
                                                replace_lift_vars(a.rhs,aliases,relations,parameters,states)),
                                           x.asgns)
                        trigger_expr = replace_vars(x.trigger,aliases,relations,parameters,states)
                        response = quote
                            (t,y,yp,p,ss) -> begin
                                println("response: t = ", t)
                                $(asgns_exprs...)
                                println("response: p = ", p)
                                return (y,p)
                                end
                        end
                        return eval(Main, quote ((eqsys) -> StructuralEvent($trigger_expr, eqsys(),
                                                                            ()->$target_regime_name(),
                                                                            pos_response=$response))
                                                 end)
                    end,
                    strevs)
    
    if isempty(strevs)
        this_regime_name = symbol(join([rname,name]))
        expr = Expr(:function,
                    Expr(:call,this_regime_name),
                         ##(map ((x) -> Expr(:kw,x[1],x[2]), initialValues))...),
                    quote
                        Equation[$paramsys...,$asgnsys...,$odesys...,$eventsys...,$condsys...]
                    end)
        eval(Main,expr)
        return this_regime_name
    else
        this_regime_eqname = symbol(join([rname,name,"eq"]))
        expr1 = Expr(:function,
                     Expr(:call,this_regime_eqname),
                          ##(map ((x) -> Expr(:kw,x[1],x[2]), initialValues))...),
                     quote
                         Equation[$paramsys...,$asgnsys...,$odesys...,$eventsys...,$condsys...]
                     end)
        eqsys = eval(Main,expr1)

        this_regime_name = symbol(join([rname,name]))
        expr2 = Expr(:function,
                     Expr(:call,this_regime_name),
                          ##(map ((x) -> Expr(:kw,x[1],x[2]), initialValues))...),
                     quote
                         Equation[$(map ((x) -> x(eqsys), strevfns))...]
                     end)
        eval(Main,expr2)
        return this_regime_name
    end
end


function eval_Dynamics (dynamics,
                        name::Symbol,
                        parameterValues::Dict{Symbol,Union(Float64,Expr)},
                        initialValues::Dict{Symbol,Union(Float64,Expr)},
                        parameterNames::Vector{Symbol},
                        stateNames::Vector{Symbol},
                        portNames::Vector{Symbol})
    
    aliasDefs    = dynamics[1]
    relationDefs = dynamics[2]
    regimes      = dynamics[3]

    states = Dict{Symbol,Unknown}()
    ports  = Dict{Symbol,Parameter}()
    parameters = Dict{Symbol,Parameter}()
    for x in parameterValues
        if x[1] in parameterNames
            parameters[x[1]] = Parameter(x[2],string(x[1]))
        end
    end
    for x in portNames
        pp = Parameter(string(x))
        ports[x] = pp
        parameters[x] = pp
    end
    for x in initialValues
        states[x[1]] = Unknown(x[1],string(x[1]))
        states[x[1]].value = x[2]
    end
    aliases = Dict{Symbol,(Expr,Array{Symbol})}()
    relations = Dict{Symbol,(Expr,Array{Symbol})}()
    for a in aliasDefs
        aliases[a.quantity] = (NineML.eval_Alias(a), a.freevars)
    end
    for r in relations
        relations[r.quantity] = (NineML.eval_Relation(r), r.freevars)
    end

    
    regimeNames = map(r -> eval_Regime(r, name, parameters, states, aliases, relations, initialValues),
                      regimes)

    first_regime_name = regimeNames[1]

    expr = quote
            function $name ()
                $first_regime_name ()
            end
    end
    eval(Main,expr)

end

end
