addprocs(3)

using SharedDicts
using Base.Test

@everywhere begin
    function check(DS::SharedDicts.SharedDict, idx::Int)
        Base.Test.@test DS[idx] == idx * 2
        nothing
    end

    function checkiter(DS::SharedDicts.SharedDict)
        Base.Test.@test !isempty(DS)
        for idx in 1:length(DS)
            Base.Test.@test DS[idx] == idx * 2
        end
        nothing
    end
end

function dotests()
    N = 1000
    D = Dict{Int, Int}()

    for idx in 1:N
        D[idx] = idx * 2
    end

    DS = share(D)

    @sync @parallel for idx in 1:N
        check(DS, idx)
    end
    for w in workers()
        remotecall_fetch(checkiter, w, DS)
    end
end

dotests()
