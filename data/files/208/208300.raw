module Template

export TemplLexem, template

@enum LexemType Arg=1 Tag=2 Other=4

@enum ParserState Wait=1 TagOpen=2 TagName=3 ValueOpen=4

type TemplLexem
    content
    lexem_type::LexemType
end

type Block
    children
end

type For
    children
    iter_var
    iter_collection
end

type Html
    content
end

type Value
    name
end

function parse_template(str, enable_tags)
    lexs = []
    cur_state = Wait::ParserState
    cur_cnt = ""
    cur_type = Other::LexemType

    cur_node = Block([])
    parse_stack = []
    push!(parse_stack, cur_node)

    for c = str
        #println(c)
        if cur_state == Wait::ParserState
            if (c != '<' || !enable_tags) && c != '{'
                cur_cnt = cur_cnt * string(c)
            else
                if length(cur_cnt) > 0
                    lex = Html(cur_cnt)
                    push!(parse_stack[size(parse_stack)[1]].children, lex)
                end
                cur_cnt = ""
                if c == '<' && enable_tags
                    cur_state = TagOpen::ParserState
                    cur_type = Tag::LexemType
                elseif c == '{'
                    cur_state = ValueOpen::ParserState
                    cur_type = Arg::LexemType
                else
                    error("Missed handling character!")
                end
            end
        elseif cur_state == TagOpen::ParserState
            if c != '>'
                cur_cnt = cur_cnt * string(c)
            else
                lex = Html(cur_cnt)
                push!(parse_stack[size(parse_stack)[1]].children, lex)
                cur_cnt = ""
                cur_state = Wait::ParserState
                cur_type = Other::LexemType
            end
        elseif cur_state == ValueOpen::ParserState
            if c != '}'
                cur_cnt = cur_cnt * string(c)
            else
                check_cmd = strip(cur_cnt)
                println("<", check_cmd, ">")
                if startswith(check_cmd, "for ")
                    range = match(r"(?P<iter_var>\w+)=(?P<iter_collection>\w+)", check_cmd)
                    println("<FOR>", range)
                    add = For([], range[:iter_var], range[:iter_collection])
                    push!(parse_stack, add)

                    cur_cnt = ""
                    cur_state = Wait::ParserState
                    cur_type = Other::LexemType
                elseif check_cmd == "endfor"
                    println("<ENDFOR>")
                    pop_state = pop!(parse_stack)
                    push!(parse_stack[size(parse_stack)[1]].children, pop_state)

                    cur_cnt = ""
                    cur_state = Wait::ParserState
                    cur_type = Other::LexemType
                else
                    if cur_type == Arg::LexemType
                        lex = Value(cur_cnt)
                    else
                        lex = Html(cur_cnt)
                    end
                    push!(parse_stack[size(parse_stack)[1]].children, lex)
                    cur_cnt = ""
                    cur_state = Wait::ParserState
                    cur_type = Other::LexemType
                end
            end
        end
    end
    if length(cur_cnt) > 0
        lex = Html(cur_cnt)
        push!(parse_stack[size(parse_stack)[1]].children, lex)
    end
    parse_stack[1]
end

function render(node::Block, context)
    rendered = ""

    for child=node.children
        rendered = rendered * render(child, context)
    end

    rendered
end

function render(node::For, context)
    rendered = ""

    vals = get(context, node.iter_collection, [])
    for i=vals
        current_context = Dict(context)
        current_context[node.iter_var] = i
        for child=node.children
            rendered = rendered * render(child, current_context)
        end
    end

    rendered
end

function render(node::Html, context)
    node.content
end

function render(node::Value, context)
    get(context, node.name, node.name)
end

function template(template_str, context)
    template_root = parse_template(template_str, false)

    println("R ", template_root)

    render(template_root, context)
end

end # module Template
