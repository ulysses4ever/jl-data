function insert!(quad::Quadtree, shape::Shape, level::Int64 = 0)
    index = get_index(quad.rect, shape)

    if(index == 1)
        if(!isdefined(quad, :ne))
            quad.ne = Quadtree(split!(quad.rect, index))
        end
        level += 1
        insert!(quad.ne, shape, level)

    elseif(index == 2)
        if(!isdefined(quad, :nw))
            quad.nw = Quadtree(split!(quad.rect, index))
        end
        level += 1
        insert!(quad.nw, shape, level)

    elseif(index == 3)
        if(!isdefined(quad, :sw))
            quad.sw = Quadtree(split!(quad.rect, index))
        end
        level += 1
        insert!(quad.sw, shape, level)

    elseif(index == 4)
        if(!isdefined(quad, :se))
            quad.se = Quadtree(split!(quad.rect, index))
        end
        level += 1
        insert!(quad.se, shape, level)

    else
        push!(quad.objects, shape)
        max_level_quadtree[1] = max_level_quadtree[1] < level ? level : max_level_quadtree[1]
        level = 0
        return quad.objects
    end

    return nothing
end
