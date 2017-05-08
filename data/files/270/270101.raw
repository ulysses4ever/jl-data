using DataFrames

# the base type used to represent intervals on a chromsome
# --------------------------------------------------------

type ChromosomeInterval
    chromosome::ASCIIString # we could make a fixed size custom type here...but for now we don't
    first::Int64
    last::Int64
    value::Float64
    valueNA::Bool
end

immutable IntegerInterval
    first::Int64
    last::Int64
    value::Float64
end
IntegerInterval(first, last) = IntegerInterval(first, last, 0)

immutable IntegerPointValue
    position::Int64
    value::Float64
end

function ChromosomeInterval(chromosome, first, last, value)
    if isna(value)
        return ChromosomeInterval(chromosome, first, last, 0, true)
    end
    ChromosomeInterval(chromosome, first, last, value, false)
end

ChromosomeInterval(chromosome, first, last) = ChromosomeInterval(chromosome, first, last, 0, true)

const emptyInterval = ChromosomeInterval("",0,0)

==(x::ChromosomeInterval, y::ChromosomeInterval) = x.chromosome == y.chromosome && x.first == y.first && x.last == y.last && x.value == y.value && x.valueNA == y.valueNA

function Base.string(x::ChromosomeInterval)
    "ChromosomeInterval($(x.chromosome), $(x.first), $(x.last), $(x.valueNA ? NA : x.value))"
end

Base.print(io::IO, x::ChromosomeInterval) = print(io, "$(x.chromosome) ($(x.first),$(x.last)) $(x.valueNA ? NA : x.value)")
Base.show(io::IO, x::ChromosomeInterval) = print(io, "$(x.chromosome) ($(x.first),$(x.last)) $(x.valueNA ? NA : x.value)")

# iterates through each line of a stream and emits the intervals
# --------------------------------------------------------------

function eachchromosomeinterval(stream; format="bedGraph")
    EachChromosomeInterval(eachline(stream), emptyInterval, emptyInterval, 1, format)
end
type EachChromosomeInterval
    lineItr::EachLine
    nextInterval::ChromosomeInterval
    prevInterval::ChromosomeInterval
    count::Uint
    format::ASCIIString
end

function Base.start(itr::EachChromosomeInterval)
    start(itr.lineItr)
    1
end

function Base.done(itr::EachChromosomeInterval, count)

    # see if we have an interval in the queue
    if count < itr.count
        return false
    end

    # if not get another one from the file if we can
    while !done(itr.lineItr, nothing) # EachLine has no state
        line = next(itr.lineItr, nothing)[1]

        # Break apart the line
        parts = split(line)
        if length(parts) < 3 continue end # make sure we have a valid line
        startInd = int(parts[2])+1 # convert zero based to one based
        endInd = int(parts[3]) # convert zero based to one based and also to inclusive end-point
        value = 0
        valueNA = true
        if length(parts) > 3 && parts[4] != "NA" && itr.format == "bedGraph"
            value = float(parts[4])
            valueNA = false
        elseif length(parts) > 4 && parts[5] != "." && itr.format == "bed"
            value = float(parts[5])
            valueNA = false
        end

        interval = ChromosomeInterval(parts[1], startInd, endInd, value, valueNA)
        itr.nextInterval = interval
        return false
    end
    
    true
end

function Base.next(itr::EachChromosomeInterval, count)
    if count == itr.count-1
        return (itr.prevInterval, itr.count)
    end
    
    itr.prevInterval = itr.nextInterval
    itr.count += 1
    (itr.prevInterval, itr.count)
end

Base.eltype(itr::EachChromosomeInterval) = ChromosomeInterval


# this is way faster than parseint but only deals with simple sequences of ascii numerals
function parseintsimple(str, startPos, endPos)
    value = 0
    power = 1
    i = endPos
    while i >= startPos
        value += (str[i]-'0')*power
        power *= 10
        i -= 1
    end
    value
end

# this is way faster than parsefloat but only deals with simple sequences of ascii numerals with a decimal point
function parsefloatsimple(str, startPos, endPos)
    value = 0.0
    power = 1
    i = endPos
    while i >= startPos
        value += (str[i]-'0')*power
        power *= 10
        i -= 1
        if i >= startPos && str[i] == '.'
            value /= power
            power = 1
            i -= 1
        end
    end
    value
end

# this is an optimized parser for bed graph lines
function parsebedgraphline(line::ASCIIString)

    # we avoid using split
    count = 1
    pos1 = 1
    pos2 = 1
    pos3 = 1
    i = 1
    while i <= length(line)
        if line[i] == '\t' || line[i] == '\n'
            if count == 1
                pos1 = i-1
            elseif count == 2
                pos2 = i-1
            elseif count == 3
                pos3 = i-1
            else
                break
            end
            count += 1
        end
        i += 1
    end
    
    # here we use our own simple parse functions that are way faster than the standard ones
    ChromosomeInterval(
        line[1:pos1],
        parseintsimple(line, pos1+2, pos2)+1, # convert zero based to one based
        parseintsimple(line, pos2+2, pos3),
        parsefloatsimple(line, pos3+2, i-1),
        false
    )
end

# this ignores the chromosome
function parsebedgraphlineii(line::ASCIIString)

    # we avoid using split
    count = 1
    pos1 = 1
    pos2 = 1
    pos3 = 1
    i = 1
    while i <= length(line)
        if line[i] == '\t' || line[i] == '\n'
            if count == 1
                pos1 = i-1
            elseif count == 2
                pos2 = i-1
            elseif count == 3
                pos3 = i-1
            else
                break
            end
            count += 1
        end
        i += 1
    end
    
    # here we use our own simple parse functions that are way faster than the standard ones
    IntegerInterval(
        parseintsimple(line, pos1+2, pos2)+1, # convert zero based to one based
        parseintsimple(line, pos2+2, pos3),
        parsefloatsimple(line, pos3+2, i-1)
    )
end

# Test if the given interval overlaps 
function testoverlap(interval::ChromosomeInterval, intervals::Array{ChromosomeInterval,1})
    for intr in intervals
        if intr.chromosome == interval.chromosome && interval.first <= intr.last && interval.last >= intr.first
            return true
        end
    end
    
    false
end
function testoverlap(interval::IntegerInterval, intervals::Array{IntegerInterval,1})
    for intr in intervals
        if interval.first <= intr.last && interval.last >= intr.first
            return true
        end
    end
    
    false
end


# 
function bin(binSize, numBins, intervals; threshold=0.5, method="average")
    const totalLength = binSize*numBins
    bins = @data(zeros(numBins))
    counts = zeros(Uint32, numBins)

    for interval in intervals
        
        # Step through each position of this interval setting
        if interval.first <= totalLength

            # check if this interval is within a single bin
            index = int(ceil(interval.first/binSize))
            if index == int(ceil(interval.last/binSize))
                width = interval.last - interval.first + 1
                bins[index] += interval.value * width
                counts[index] += width

            # if not then we add each member of the interval one-by-one
            else
                for i in interval.first:min(interval.last, totalLength)
                    index = int(ceil(i/binSize))
                    bins[index] += interval.value
                    counts[index] += 1
                end
            end
        end
    end
    
    # If we have less than a threshold percentage of the bin defined with values, then we treat the whole bin as NA
    bins[counts .<= binSize*threshold] = NA
    
    # Set this track to be the average of the values found in each window or leave it as a sum
    if method == "average"
        bins ./= counts
    end

    bins
end

# just like bin but uses zeros instead of NA
function zerobin(binSize, numBins, intervals; threshold=0.5, method="average")
    const totalLength = binSize*numBins
    bins = zeros(numBins)
    counts = zeros(Uint32, numBins)

    isMethodMax = method == "max"

    for interval in intervals
        
        # Step through each position of this interval setting
        if interval.first <= totalLength

            # check if this interval is within a single bin
            index = int(ceil(interval.first/binSize))
            if index == int(ceil(interval.last/binSize))
                width = interval.last - interval.first + 1
                if isMethodMax
                    bins[index] = max(bins[index], interval.value)
                else
                    bins[index] += interval.value * width
                end
                counts[index] += width

            # if not then we add each member of the interval one-by-one
            else
                for i in interval.first:min(interval.last, totalLength)
                    index = int(ceil(i/binSize))
                    if isMethodMax
                        bins[index] = max(bins[index], interval.value)
                    else
                        bins[index] += interval.value
                    end
                    counts[index] += 1
                end
            end
        end
    end
    
    # If we have less than a threshold percentage of the bin defined with values, then we treat the whole bin as NA
    bins[counts .<= binSize*threshold] = 0
    
    # Set this track to be the average of the values found in each window
    if method == "average"
        bins ./= counts

    # mark all nonzero entries in a binary fashion
    elseif method == "nonzero"
        bins = int(bins .!= 0)
    end

    bins
end

type JointInterval
    first::Int64
    last::Int64
    values::Array{Float64,1}
end
function jointintervals(intervals)
    results = JointInterval[]
    openIntervals = Collections.PriorityQueue()
    index = 1
    lastPosition = typemax(Int64)
    position = intervals[index].first
    while position != lastPosition
        
        # Pull in the new intervals for our position
        while index <= length(intervals) && intervals[index].first <= position
            Collections.enqueue!(openIntervals, (index, intervals[index].value), intervals[index].last)
            index += 1
        end
        
        # Throw out the old intervals for our position
        while length(openIntervals) > 0 && Collections.peek(openIntervals)[2] < position
            Collections.dequeue!(openIntervals)
        end
        
        # Move just past the end of the next interval that will become old
        # or until we get a new interval
        lastPosition = position
        nextIntervalStart = index <= length(intervals) ? intervals[index].first : typemax(Int64)
        nextIntervalEnd = length(openIntervals) > 0 ? Collections.peek(openIntervals)[2] + 1 : typemax(Int64)
        if nextIntervalStart != typemax(Int64) || nextIntervalEnd != typemax(Int64)
            position = min(nextIntervalEnd, nextIntervalStart)
        end
        
        if position-lastPosition > 0
            push!(results, JointInterval(lastPosition, position-1, [k[2] for k in sort(collect(keys(openIntervals)))]))
        end
    end
    
    results
end

# this downsamples the set of intervals to points while keeping the min and max, this is good for visual wide-out views of the data
# each level is a factor of 4 more downsampled (where 0 is no downsampling)
# note that the input intervals are assumed to be non-overlapping
function minmaxdownsample(intervals, level)
    divisor = 4^level

    # take all the end points of the intervals and round them
    rints = IntegerInterval[]
    for i in intervals
        pos1 = int(round(i.first/divisor))*divisor
        pos2 = int(round(i.last/divisor))*divisor
        push!(rints, IntegerInterval(pos1, pos2, i.value))
    end
    
    # prune overlapping points to just the min and max
    results = IntegerPointValue[]
    i = 1
    longIndex = 0
    while i <= length(rints)

        # loop over all the intervals starting at this position and find the max,min and their relative ordering
        j = 0
        maxValue = rints[i].value
        minValue = rints[i].value
        minLast = false
        while i+j <= length(rints) && rints[i+j].first == rints[i].first
            if maxValue < rints[i+j].value
                maxValue = rints[i+j].value
                minLast = false
            elseif minValue > rints[i+j].value
                minValue = rints[i+j].value
                minLast = true
            end
            
            # note that the intervals are assumed to be non-overlapping so only one interval could be
            # extending forward at a given point in time, here we look for that one
            if rints[i+j].last > rints[i].first
                longIndex = i+j
            end
            
            j += 1
        end

        # append min and max points minimally and in the right order
        if maxValue == minValue
            push!(results, IntegerPointValue(rints[i].first, maxValue))
        elseif minLast
            push!(results, IntegerPointValue(rints[i].first-1, maxValue))
            push!(results, IntegerPointValue(rints[i].first+1, minValue))
        else
            push!(results, IntegerPointValue(rints[i].first-1, minValue))
            push!(results, IntegerPointValue(rints[i].first+1, maxValue))
        end
            
        if longIndex >= i

            # If the long index spans multiple rounding points then we need to add boundary points so
            # the middle is always correctly represented
            len = rints[longIndex].last - rints[longIndex].first
            if len > divisor && results[end].value != rints[longIndex].value
                push!(results, IntegerPointValue(rints[i].first+divisor, rints[longIndex].value))
            end
            if len > 2*divisor
                push!(results, IntegerPointValue(rints[longIndex].last-divisor, rints[longIndex].value))
            end
            
            # if we have a long interval then we need to look at it again at the next iteration
            i -= 1
            rints[i+j] = IntegerInterval(rints[longIndex].last, rints[longIndex].last, rints[longIndex].value)

            longIndex = 0
        end
            
        i += j
    end

    # if we are only given one interval then we might not have enough points to match
    # the beginning and end of the intervals given, so add one
    if length(results) == 1
        push!(results, results[1])
    end
    
    # make sure the first point matches the intervals starting point
    results[1] = IntegerPointValue(intervals[1].first, results[1].value)
    if length(results) > 1 && results[2].position <= results[1].position
        results[2] = IntegerPointValue(results[1].position+1, results[2].value)
    end
    
    # make sure the last point matches the intervals ending point
    results[end] = IntegerPointValue(intervals[end].last, results[end].value)
    if length(results) > 1 && results[end-1].position >= results[end].position
        results[end-1] = IntegerPointValue(results[end].position-1, results[end-1].value)
    end
    
    results
end

# this divides the intervals into chunks of the given size, cutting them at chunk boundaries as needed
function chunkintervals(intervals, chunkSize)
    numChunks = int(ceil((intervals[end].last - intervals[1].first + 1)/chunkSize))
    chunks = [Array(IntegerInterval, 0) for i in 1:numChunks]

    for i in intervals
        firstIndex = int(ceil(i.first/chunkSize))
        lastIndex = int(ceil(i.last/chunkSize))

        if firstIndex == lastIndex
            push!(chunks[firstIndex], IntegerInterval(i.first, i.last, i.value))
        else
            push!(chunks[firstIndex], IntegerInterval(i.first, firstIndex*chunkSize, i.value))

            while firstIndex != lastIndex
                push!(chunks[firstIndex+1], IntegerInterval(firstIndex*chunkSize+1, min((firstIndex+1)*chunkSize, i.last), i.value))
                firstIndex += 1
            end
        end
    end

    chunks
end

# function eachjointinterval(intervals)
#     EachJointInterval(eachline(stream), emptyInterval, emptyInterval, 1, format)
# end
# type EachJointInterval
#     intervals
#     intervalsState
#     openIntervals
#     index::Int64
#     lastPosition::Int64
#     position::Int64
#     count::Int64
# end

# function Base.start(itr::EachJointInterval)
#     itr.openIntervals = Collections.PriorityQueue()
#     itr.intervalsState = start(itr.intervals)
#     1
# end

# function Base.done(itr::EachJointInterval, count)

#     # see if we have an interval in the queue
#     if count < itr.count
#         return false
#     end

#     # if not get another one from the intervals iterator
#     while !done(itr.intervals, intervalsState)
#         interval,itr.intervalsState = next(itr.intervals, intervalsState)

#         # Break apart the line
#         parts = split(line)
#         if length(parts) < 3 continue end # make sure we have a valid line
#         startInd = int(parts[2])+1 # convert zero based to one based
#         endInd = int(parts[3]) # convert zero based to one based and also to inclusive end-point
#         value = 0
#         valueNA = true
#         if length(parts) > 3 && parts[4] != "NA" && itr.format == "bedGraph"
#             value = float(parts[4])
#             valueNA = false
#         elseif length(parts) > 4 && parts[5] != "." && itr.format == "bed"
#             value = float(parts[5])
#             valueNA = false
#         end

#         interval = ChromosomeInterval(parts[1], startInd, endInd, value, valueNA)
#         itr.nextInterval = interval
#         return false
#     end
    
#     true
# end

# function Base.next(itr::EachJointInterval, count)





#     if count == itr.count-1
#         return (itr.prevInterval, itr.count)
#     end
    
#     itr.prevInterval = itr.nextInterval
#     itr.count += 1
#     (itr.prevInterval, itr.count)
# end

# Base.eltype(itr::EachJointInterval) = Array{ChromosomeInterval,1}

# This iterates through all of the interval intersections (note that invervals must be sorted by their starting points)
# function jointintervals(intervals)
#     results = Array{Int64,1}[]
#     openIntervals = Collections.PriorityQueue()
#     index = 1
#     lastPosition = typemax(Int64)
#     position = intervals[index][1]
#     while position != lastPosition
        
#         # Pull in the new intervals for our position
#         while index <= length(intervals) && intervals[index].first <= position
#             #print("ASDF $index $position\n")
#             Collections.enqueue!(openIntervals, (index, intervals[index].last), intervals[index].last)
#             index += 1
#         end
        
#         # Throw out the old intervals for our position
#         while length(openIntervals) > 0 && Collections.peek(openIntervals)[2] < position
#             Collections.dequeue!(openIntervals)
#         end
        
#         # Move just past the end of the next interval that will become old
#         # or until we get a new interval
#         lastPosition = position
#         nextIntervalStart = index <= length(intervals) ? intervals[index].first : typemax(Int64)
#         nextIntervalEnd = length(openIntervals) > 0 ? Collections.peek(openIntervals)[2] + 1 : typemax(Int64)
#         if nextIntervalStart != typemax(Int64) || nextIntervalEnd != typemax(Int64)
#             position = min(nextIntervalEnd, nextIntervalStart)
#         end
        
#         if position-lastPosition > 0
#             push!(results, (position-lastPosition, [k[1] for k in keys(openIntervals)], (lastPosition, position-1)))
#         end
#     end
    
#     results
# end

