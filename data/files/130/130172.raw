# Basic operations
const OP1 = 1 # Ook. Ook?
const OP2 = 2 # Ook? Ook.
const OP3 = 3 # Ook. Ook.
const OP4 = 4 # Ook! Ook!
const OP5 = 5 # Ook. Ook!
const OP6 = 6 # Ook! Ook.
const OP7 = 7 # Ook! Ook?
const OP8 = 8 # Ook? Ook!

function getop(token1::Integer, token2::Integer)
    if token1 == PERIOD
        if token2 == PERIOD
            return OP3
        elseif token2 == QUESTION
            return OP1
        elseif token2 == EXCLAMATION
            return OP5
        else
            msg = @sprintf("Unknown token type: %d", token2)
            throw(ArgumentError(msg))
        end
    elseif token1 == QUESTION
        if token2 == PERIOD
            return OP2
        elseif token2 == QUESTION
            msg = @sprintf("Invalid token pair: Ook? Ook?")
            throw(ArgumentError(msg))
        elseif token2 == EXCLAMATION
            return OP8
        else
            msg = @sprintf("Unknown token type: %d", token2)
            throw(ArgumentError(msg))
        end
    elseif token1 == EXCLAMATION
        if token2 == PERIOD
            return OP6
        elseif token2 == QUESTION
            return OP7
        elseif token2 == EXCLAMATION
            return OP4
        else
            msg = @sprintf("Unknown token type: %d", token2)
            throw(ArgumentError(msg))
        end
    else
        msg = @sprintf("Unknown token type: %d", token1)
        throw(ArgumentError(msg))
    end
end

function parse(tokens::Vector{Int})
    n_tokens = length(tokens)

    if mod(n_tokens, 2) != 0
        msg = "At least one Ook token is missing from input"
        throw(ArgumentError(msg))
    end

    n_ops = fld(n_tokens, 2)

    ops = Array(Int, n_ops)

    for i in 1:n_ops
        j = 2 * (i - 1)
        ops[i] = getop(tokens[j + 1], tokens[j + 2])
    end

    return ops
end
