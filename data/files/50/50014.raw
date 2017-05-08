module MethImp

using Lazy

# Objects are like objects in the OO sense –
# a piece of data with some behaviour thrown in.

# Methods are just names – messages that can
# be sent to objects. Objects have implementations
# for a given set of methods which they'll respond to.

# Implementations are decoupled from methods. A single
# method call could result in many implementations
# responding, or none at all. Implementations themselves
# declare what methods will trigger them.

# Objects have "type tags" which are, well, tags.
# An object can have more than one tag, and each
# determines a set of implementations that form
# the object's behaviour.

export object, @~, @tag, @tag_str, @+, @-, addtags, rmtags,
  imp

include("weakset.jl")
include("meta.jl")
include("tags.jl")
include("implementations.jl")
include("objects.jl")

end # module
