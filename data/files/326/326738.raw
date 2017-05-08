
module StatefulIterators

export StatefulIterator

import Base: start, next, done

type StatefulIterator
    iter
    state
    StatefulIterator(iter) = new(iter, start(iter))
end

start(i::StatefulIterator) = i

function next(i::StatefulIterator, s::StatefulIterator)
    item, state = next(i.iter, i.state)
    i.state = state
    item, i
end

done(i::StatefulIterator, s::StatefulIterator) = done(i.iter, i.state)

end
