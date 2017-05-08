using DictWrappers
using FactCheck

facts("Failure") do
    for T in subtypes(DictWrapper)
        context(string(T)) do
            @fact_throws ArgumentError T(3)
            @fact_throws ArgumentError T(3.0)
            @fact_throws ArgumentError T((3, 3.0))
            @fact_throws ArgumentError T(())
            @fact_throws ArgumentError T(true)
        end
    end
end

facts("Simple composite") do
    test = 1 + im
    for T in subtypes(DictWrapper)
        context(string(T)) do
            wrapper = T(test)
            @fact typeof(wrapper) --> T
            @fact wrapper.wrapped --> exactly(test)

            fields = collect(keys(wrapper))
            @fact typeof(fields) --> Vector{Symbol}
            @fact length(fields) --> 2

            for field in fields
                @fact wrapper[field] --> exactly(getfield(test, field))
                value = wrapper[field]
                @fact value --> exactly(1)
            end

            for value in values(wrapper)
                @fact value --> exactly(1)
            end
        end
    end
end

facts("Complex composite") do
    test_part = 1 + im
    test = (test_part=>test_part)::Pair{Complex{Int64}, Complex{Int64}}

    context(string(RecursiveDictWrapper)) do
        wrapper = RecursiveDictWrapper(test)
        @fact typeof(wrapper) --> RecursiveDictWrapper
        @fact wrapper.wrapped --> exactly(test)

        fields = collect(keys(wrapper))
        @fact typeof(fields) --> Vector{Symbol}
        @fact length(fields) --> 2

        for field in fields
            @fact wrapper[field] --> RecursiveDictWrapper(getfield(test, field))
            @fact wrapper[field] --> RecursiveDictWrapper(test_part)
            value = wrapper[field]
            @fact value.wrapped --> exactly(test_part)

            subfields = collect(keys(value))
            @fact typeof(subfields) --> Vector{Symbol}
            @fact length(subfields) --> 2

            for subfield in subfields
                @fact value[subfield] --> getfield(test_part, subfield)
                subvalue = value[subfield]
                @fact subvalue --> exactly(1)
            end
        end

        @fact get(wrapper, :foo, 4) --> 4
        @fact (:first=>RecursiveDictWrapper(test_part)) in wrapper --> true
        @fact (:second=>RecursiveDictWrapper(test_part)) in wrapper --> true
        @fact (:first=>:wrong) in wrapper --> false
    end

    context(string(ShallowDictWrapper)) do
        wrapper = ShallowDictWrapper(test)
        @fact typeof(wrapper) --> ShallowDictWrapper
        @fact wrapper.wrapped --> exactly(test)

        fields = collect(keys(wrapper))
        @fact typeof(fields) --> Vector{Symbol}
        @fact length(fields) --> 2

        for field in fields
            @fact wrapper[field] --> getfield(test, field)
            @fact wrapper[field] --> test_part
        end

        @fact get(wrapper, :foo, 4) --> 4
        @fact (:first=>test_part) in wrapper --> true
        @fact (:second=>test_part) in wrapper --> true
        @fact (:first=>:wrong) in wrapper --> false
    end
end
