export create_new_net_with_prior_counts

function create_new_net_with_prior_counts(net::Network, r::AbstractVector{Int}, d::AbstractMatrix{Int};
    priorcount :: Int = 1
    )

    nvars = length(r)
    stats = statistics(net, r, d)
    net2 = Network()

    for i = 1 : nvars
        nodeid = add_node(net2, DSL_CPT, get_name(get_node(net, i-1)))
        set_number_of_outcomes(definition(get_node(net2, nodeid)), r[i])
        @assert(nodeid == i - 1)
    end
    for i = 1 : nvars
        nodeid = i - 1
        for p_id in get_parents(net, nodeid)
            add_arc(net2, p_id, nodeid)
        end
    end
    for i = 1 : nvars

        nodeid = i - 1

        ri = r[i]
        syscoord = SysCoordinates(definition(get_node(net2, nodeid)))
        counts = stats[i]

        # note that the ordering of parents is different than the ordering for parents in Bayes nets
        # Smile:     parent 1 is the most  significant bit so changes the least quickly
        # BayesNets: parent 1 is the least significant bit so changes the most  quickly

        parent_ids = get_parents(net, nodeid)

        nPa = length(parent_ids)
        if nPa > 0
            q = prod(r[parent_ids+1])
            dims = tuple(r[parent_ids+1]...)
            revdims = tuple(ri, reverse(dims)...)

            for ind_dmat in 1 : q
                sub = ind2sub(dims, ind_dmat)
                ind_dset = sub2ind(revdims, 1, sub...)-1

                # get the new normalized probability
                p = (counts[:,ind_dmat] .+ 1)
                p ./= sum(p)

                for j = 1 : ri
                    go_to(syscoord, ind_dset + j - 1)
                    set_unchecked_value(syscoord, p[j])
                end

            end
        else

            ind_dmat = 1
            ind_dset = 0

            # get the new normalized probability
            p = counts[:,ind_dmat] .+ priorcount
            p ./= sum(p)

            for j = 1 : ri
                go_to(syscoord, ind_dset + j - 1)
                set_unchecked_value(syscoord, p[j])
            end
        end
    end

    net2
end
function create_new_net_with_prior_counts(net::Network, r::AbstractVector{Int}, stats::Vector{Matrix{Float64}};
    priorcount :: Int = 1
    )

    nvars = length(r)
    net2 = Network()

    for i = 1 : nvars
        nodeid = add_node(net2, DSL_CPT, get_name(get_node(net, i-1)))
        set_number_of_outcomes(definition(get_node(net2, nodeid)), r[i])
        @assert(nodeid == i - 1)
    end
    for i = 1 : nvars
        nodeid = i - 1
        for p_id in get_parents(net, nodeid)
            add_arc(net2, p_id, nodeid)
        end
    end
    for i = 1 : nvars

        nodeid = i - 1

        ri = r[i]
        syscoord = SysCoordinates(definition(get_node(net2, nodeid)))
        counts = stats[i]

        # note that the ordering of parents is different than the ordering for parents in Bayes nets
        # Smile:     parent 1 is the most  significant bit so changes the least quickly
        # BayesNets: parent 1 is the least significant bit so changes the most  quickly

        parent_ids = get_parents(net, nodeid)

        nPa = length(parent_ids)
        if nPa > 0
            q = prod(r[parent_ids+1])
            dims = tuple(r[parent_ids+1]...)
            revdims = tuple(ri, reverse(dims)...)

            for ind_dmat in 1 : q
                sub = ind2sub(dims, ind_dmat)
                ind_dset = sub2ind(revdims, 1, sub...)-1

                # get the new normalized probability
                p = (counts[:,ind_dmat] .+ 1)
                p ./= sum(p)

                for j = 1 : ri
                    go_to(syscoord, ind_dset + j - 1)
                    set_unchecked_value(syscoord, p[j])
                end

            end
        else

            ind_dmat = 1
            ind_dset = 0

            # get the new normalized probability
            p = counts[:,ind_dmat] .+ priorcount
            p ./= sum(p)

            for j = 1 : ri
                go_to(syscoord, ind_dset + j - 1)
                set_unchecked_value(syscoord, p[j])
            end
        end
    end

    net2
end