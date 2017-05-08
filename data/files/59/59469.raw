module Gherkin
export tokenize

using JSON

"""Takes a .feature file and outputs a .feature.tokens file.

For example, given the `.feature` file:

```
Feature: Background

  Background: a simple background
    Given the minimalism inside a background


  Scenario: minimalistic
    Given the minimalism
```
output the `.feature.tokens` file:
```
(1:1)FeatureLine:Feature/Background/
(2:1)Empty://
(3:3)BackgroundLine:Background/a simple background/
(4:5)StepLine:Given /the minimalism inside a background/
(5:1)Empty://
(6:1)Empty://
(7:3)ScenarioLine:Scenario/minimalistic/
(8:5)StepLine:Given /the minimalism/
EOF
```

and with a language:
```
#language:no
Egenskap: i18n support

  Scenario: Parsing many languages
    Gitt Gherkin supports many languages
    Når Norwegian keywords are parsed
    Så they should be recognized
```
tokenizes to
```
(1:1)Language:/no/
(2:1)FeatureLine:Egenskap/i18n support/
(3:1)Empty://
(4:3)ScenarioLine:Scenario/Parsing many languages/
(5:5)StepLine:Gitt /Gherkin supports many languages/
(6:5)StepLine:Når /Norwegian keywords are parsed/
(7:5)StepLine:Så /they should be recognized/
EOF
```

"""

const DEFAULT_LANG = "en"
const I18N = JSON.parsefile(joinpath(dirname(@__FILE__), "glangs.json"))
const LANGUAGE_RE = r"^\s*#\s*language\s*:(.*)$"
const TITLE_KEYWORDS = ["feature", "scenario", "scenarioOutline",
                        "background", "examples"]
const STEPS = ["but", "and", "when", "given", "then"]

type Parser
    lines::Vector{UTF8String}
    lang::UTF8String
    keywords::Dict{AbstractString, Any} # TODO remove this
    tokens::Vector{UTF8String}
end
Parser(lines) = Parser(lines, DEFAULT_LANG, I18N[DEFAULT_LANG], UTF8String[])

function tokenize(filename::AbstractString)
    # TODO stream this rather than read in at once
    tokenize(readlines(open(filename)))
end

function tokenize(lines::Vector)
    p = Parser(lines)
    nextline = get_lang!(p)
    s = no_docstring()
    for i in nextline:length(p.lines)
        s = parseline!(i, p, s)
    end
    push!(p.tokens, "EOF")
    p.tokens
end

"""The language may be specified in the first line of the `.features` file.
If the language is not present use `DEFAULT_LANG` (`"en"`).

Return line to continue parsing, i.e. 2 if there is a language line otherwise 1.
"""
function get_lang!(p::Parser)
    length(p.lines) === 0 && return 1
    m = match(LANGUAGE_RE, p.lines[1])
    m === nothing && return 1

    p.lang = strip(m.captures[1])
    # TODO pushing to tokens here feels like a complete hack
    # This should really be done as part of the next section (more generically)
    # BUT maybe it needs to be here, as can only be at the start...
    @assert p.lang in keys(I18N) "The language \"$lang\" is not supported."
    push!(p.tokens, "(1:1)Language:/$(p.lang)/")
    p.keywords = I18N[p.lang]
    return 2
end

type DocstringState
    in_docstring::Bool
    indent::Int
    sep::Char
end
no_docstring() = DocstringState(false, 0, ' ')
start_docstring(i::Int, c::Char) = DocstringState(true, i, c)
in_docstring(s::DocstringState) = s.in_docstring

function parseline!(i::Int, p::Parser, s::DocstringState)
    in_docstring(s) ? parsedocstring!(i, p, s) : parseline!(i, p)
end

function parseline!(i::Int, p::Parser)
    line = p.lines[i]
    j = _get_indent(line)
    line = strip(line)
    # match against things from p.lang....
    # is there a hierarchy for this? feature -> scenario -> given ...?
    # TODO specifically how to distinguish between empty Other and Empty.
    if line == ""
        push!(p.tokens, "($i:1)Empty://")
        return no_docstring()
    end
    for t in TITLE_KEYWORDS
        b, k = startswith_titlekeyword(line, t, p)
        if b
            rest = split(line, k * ":"; limit=2)[2] # TODO remove this hack
            if startswith(rest, ' ')
                rest = rest[2:end]
            end
            push!(p.tokens, "($i:$j)$(_titlecase(t))Line:$k/$rest/")
            return no_docstring()
        end
    end
    for s in STEPS
        b, k= startswith_step(line, s, p)
        if b
            rest = split(line, k; limit=2)[2] # TODO remove this hack
            push!(p.tokens, "($i:$j)StepLine:$k/$rest/")
            return no_docstring()
        end
    end
    if startswith(line, "#")
        push!(p.tokens, "($i:1)Comment:/" * " " ^ (j - 1) * line * "/")
        return no_docstring()
    end
    if startswith(line, "|")
        # TODO test escaping better
        entries = split(line, r"(?!<\\)\|")
        columns = (j-1) .+ cumsum(map(length, entries) .+ 1)[1:end-2]
        entries = entries[2:end-1]
        row = join(["$(c + _get_indent(v)):$(strip(v))"
                    for (c, v) in zip(columns, entries)], ",")

        push!(p.tokens, "($i:$j)TableRow://$row")
        return no_docstring()
    end
    if startswith(line, "@")
        inds = findin(line, "@")
        tags = join(["$(j-1+x[1]):$(line[x[1]:x[2]-1])" for x in zip(inds, inds[2:end])], ",")
        tags = tags * (tags == "" ? "" : ",") * "$(j-1+inds[end]):$(line[inds[end]:end])"
        push!(p.tokens, "($i:$j)TagLine://$tags")
        return no_docstring()
    end
    if startswith(line, "\"\"\"") || startswith(line, "```")
        content_type = strip(line[4:end])
        push!(p.tokens, "($i:$j)DocStringSeparator:/$content_type/")
        return start_docstring(j, line[1])
    end

    push!(p.tokens, "($i:1)Other:/" * " "^ (j - 1) * line * "/")
    no_docstring()
end

function parsedocstring!(i::Int, p::Parser, s::DocstringState)
    @assert in_docstring(s)
    line = rstrip(p.lines[i], '\n')
    if startswith(strip(line), "$(s.sep)" ^ 3)
        push!(p.tokens, "($i:$(s.indent))DocStringSeparator://")
        return no_docstring()
    end
    if !startswith(line, " " ^ (s.indent - 1))
        # This is a bad docstring indent
        push!(p.tokens, "($i:1)Other:/$(strip(line))/")
    else
        push!(p.tokens, "($i:1)Other:/$(line[s.indent:end])/")
    end
    s
end

function startswith_titlekeyword(line, title_keyword, p)
    for k in p.keywords[title_keyword]
        startswith(line, k * ":") && return true, k
    end
    return false, ""
end

function startswith_step(line, keyword, p)
    for k in p.keywords[keyword]
        startswith(line, k) && return true, k
    end
    return false, ""
end

function _titlecase(word)
    # Note this isn't portable
    string(uppercase(word[1])) * word[2:end]
end

function _get_indent(line)
    i = 1
    for c in line
        if c != ' '
            return i
        end
        i += 1
    end
    # potentially we could return 0
    return i
end

end # module
