module Template

export TemplLexem, template

@enum LexemType Arg=1 Tag=2 Other=4

@enum ParserState Wait=1 TagOpen=2 TagName=3 ValueOpen=4

type TemplLexem
    content
    lexem_type::LexemType
end

@enum NodeType Block=1 For=2

type Node
    node_type::NodeType
    content
    children
end

function parse_template(str, enable_tags)
    lexs = []
    cur_state = Wait::ParserState
    cur_cnt = ""
    cur_type = Other::LexemType

    cur_node = Node(Block::NodeType, "", [])
    parse_stack = [cur_node,]

    for c = str
        #println(c)
        if cur_state == Wait::ParserState
            if (c != '<' || !enable_tags) && c != '{'
                cur_cnt = cur_cnt * string(c)
            else
                if length(cur_cnt) > 0
                    lex = TemplLexem(cur_cnt, cur_type)
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
                lex = TemplLexem(cur_cnt, cur_type)
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
                    println("<FOR>")
                    add = Node(For::NodeType, "", [])
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
                    lex = TemplLexem(cur_cnt, cur_type)
                    push!(parse_stack[size(parse_stack)[1]].children, lex)
                    cur_cnt = ""
                    cur_state = Wait::ParserState
                    cur_type = Other::LexemType
                end
            end
        end
    end
    if length(cur_cnt) > 0
        lex = TemplLexem(cur_cnt, cur_type)
        push!(parse_stack[size(parse_stack)[1]].children, lex)
    end
    parse_stack[1]
end

function render(node, context)
    rendered = ""

    if length(node.children) > 0
        if node.node_type == For::NodeType
            vals = get(context, "names", [])
            for i=vals
                current_context = context
                current_context["i"] = i
                for child=node.children
                    add = child.content
                    if is(typeof(child), Node)
                        add = render(child, current_context)
                    elseif child.lexem_type == Arg::LexemType
                        add = get(current_context, child.content, child.content)
                    end
                    rendered = rendered * add
                end
            end
        else
            for child=node.children
                add = child.content
                if is(typeof(child), Node)
                    add = render(child, context)
                elseif child.lexem_type == Arg::LexemType
                    add = get(context, child.content, child.content)
                end
                rendered = rendered * add
            end
        end

    else
        rendered = node.content
    end

    rendered
end


function template(template_str, context)
    template_root = parse_template(template_str, false)

    println("R ", template_root)

    rendered = render(template_root, context)
    println("Ctx", context)
    rendered
end

end # module Template
