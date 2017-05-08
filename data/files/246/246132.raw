function two_sum(nums, target)
    if length(nums) <= 1
        return false
    end
    hdict = Dict()
    for i in 1:length(nums)
        if haskey(hdict, nums[i])
            return [hdict[nums[i]], i]
        else
            hdict[target - nums[i]] = i
        end
    end
end