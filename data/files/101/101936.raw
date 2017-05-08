function set{K,V}( sv::StepVector{K,V}, from::K, value::V )
    iter, found = find(sv.tree, from)
    if found
        currentNode(iter).value = value
    else
        if currentNode(iter).value != value
            insert(sv.tree, from, value)
        end
    end
end

function set{K,V}( sv::StepVector{K,V}, from::K, to::K, value::V )
    iter, found = goTo(sv.tree, from)
    node = currentNode(iter)
    toDelete = Array(K, 0)
    lastValue = node.value
    while goNext(iter)
        if currentNode(iter).key >= to
            break
        end
        lastValue = currentNode(iter).value
        push!(toDelete, currentNode(iter).key)
    end
    if found
        node.value = value
    else
        if node.value != value
            insert(sv.tree, from, value)
            push!(toDelete, node.key)
        end
    end
    for key in toDelete
        delete!( sv.tree, key )
    end
    iter, found = find(sv.tree, to)
    if !found
        insert(sv.tree, to, lastValue)
    end
end

function apply!{K,V}(sv::StepVector{K,V}, from, to, fun = x -> x + 1)
    iter, found = find(sv.tree, from)
    if found
        currentNode(iter).value = fun(currentNode(iter).value)
    else
        insert(sv.tree, from, fun(currentNode(iter).value))
    end
    iter, found = goTo(sv.tree, from)
    lastValue = currentNode(iter).value
    while goNext(iter)
        if currentNode(iter).key >= to
            break
        end
        lastValue = currentNode(iter).value
        currentNode(iter).value = fun(currentNode(iter).value) #apply the function
    end
    iter, found = find(sv.tree, to)
    if !found
        insert(sv.tree, to, lastValue )
    end
end
