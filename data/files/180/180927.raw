module Readline
    using Terminals

    import Terminals: raw!, width, height, cmove, Rect, Size, getX, 
                      getY, clear_line, beep

    import Base: ensureroom, peek

    abstract HistoryProvider
    abstract CompletionProvider

    type EmptyCompletionProvider <: CompletionProvider
    end

    type EmptyHistoryProvider <: HistoryProvider
    end

    type ReadlineState
        terminal::TextTerminal
        hist::HistoryProvider
        complete::CompletionProvider
        enter_cb::Function
        input_buffer::IOBuffer
        prompt::ASCIIString
        prompt_color::ASCIIString
        input_color::ASCIIString
        num_rows::Int
        curs_row::Int
        indent::Int
    end

    completeLine(c::EmptyCompletionProvider,s) = []

    function common_prefix(completions)
        ret = ""
        i = nexti = 1
        cc,nexti = next(completions[1],1)
        while true
            for c in completions
                if i > length(c) || c[i] != cc
                    return ret
                end
            end
            ret = ret*string(cc)
            if i >= length(completions[1])
                return ret
            end
            i = nexti
            cc,nexti = next(completions[1],i)
        end
    end

    function completeLine(s::ReadlineState)
        (completions,partial) = completeLine(s.complete,s)
        if length(completions) == 0
            beep(s.terminal)
        elseif length(completions) == 1
            # Replace word by completion
            prev_pos = position(s.input_buffer)
            char_move_word_left(s)
            edit_replace(s,position(s.input_buffer),prev_pos,completions[1])
        else
            p = common_prefix(completions)
            if length(p) > 0 && p != partial
                # All possible completions share the same prefix, so we might as
                # well complete that
                prev_pos = position(s.input_buffer)
                char_move_word_left(s)
                edit_replace(s,position(s.input_buffer),prev_pos,p)
            else
                # Show available completions
                colmax = max(map(length,completions))
                num_cols = div(width(s.terminal),colmax+2)
                entries_per_col = div(length(completions),num_cols)+1
                println(s.terminal)
                for row = 1:entries_per_col
                    for col = 0:num_cols
                        idx = row + col*entries_per_col
                        if idx <= length(completions)
                            cmove_col(s.terminal,(colmax+2)*col)
                            print(s.terminal,completions[idx])
                        end
                    end
                    println(s.terminal)
                end
            end
        end
    end

    function refreshMultiLine(s::ReadlineState)
        cols = width(s.terminal)

        #println(s.curs_row)
        #println(s.num_rows)

        # Go to the last line
        if s.curs_row < s.num_rows
            cmove_down(s.terminal,s.num_rows-s.curs_row)
        end

        # Clear lines one by one going up
        for j=0:(s.num_rows - 2)
            clear_line(s.terminal)
            cmove_up(s.terminal)
        end

        # Clear top line
        clear_line(s.terminal)

        curs_row = -1 #relative to prompt
        curs_col = -1 #absolute
        curs_pos = -1 # 1 - based column position of the cursor
        cur_row = 0
        buf_pos = position(s.input_buffer)
        line_pos = buf_pos
        # Write out the prompt string
        write_prompt(s)

        seek(s.input_buffer,0)

        llength = 0

        l=""

        # Now go through the buffer line by line
        while cur_row == 0 || (!isempty(l) && l[end] == '\n')
            l = readline(s.input_buffer)
            cur_row += 1
            # We need to deal with UTF8 characters. Since the IOBuffer is a bytearray, we just count bytes
            llength = length(l)
            plength = length(s.prompt)
            slength = length(l.data)
            pslength = length(s.prompt.data)
            if cur_row == 1 #First line 
                if line_pos < slength
                    num_chars = length(l[1:line_pos])
                    curs_row = div(plength+num_chars-1,cols)+1
                    curs_pos = (plength+num_chars-1)%cols+1
                end
                cur_row += div(plength+llength-1,cols)
                line_pos -= slength
                write(s.terminal,l)
            else
                # We expect to be line after the last valid output line (due to
                # the '\n' at the end of the previous line)
                if curs_row == -1
                    if line_pos < slength
                        num_chars = length(l[1:line_pos])
                        curs_row = cur_row+div(s.indent+num_chars-1,cols)
                        curs_pos = (s.indent+num_chars-1)%cols+1
                    end
                    line_pos -= slength #'\n' gets an extra pos
                    cur_row += div(llength+s.indent-1,cols)
                    cmove_col(s.terminal,s.indent+1)
                    write(s.terminal,l)
                    # There's an issue if the last character we wrote was at the very right end of the screen. In that case we need to
                    # emit a new line and move the cursor there. 
                    if curs_pos == cols
                        write(s.terminal,"\n")
                        cmove_col(s.terminal,1)
                        curs_row+=1
                        curs_pos=0
                        cur_row+=1
                    end
                else
                    cur_row += div(llength+s.indent-1,cols)
                    cmove_col(s.terminal,s.indent+1)
                    write(s.terminal,l)
                end

            end
            

        end

        seek(s.input_buffer,buf_pos)

        # If we are at the end of the buffer, we need to put the cursor one past the 
        # last character we have written
        
        if curs_row == -1
            curs_pos = (s.indent+llength-1)%cols+1
            curs_row = cur_row
        end

        # Same issue as above. TODO: We should figure out 
        # how to refactor this to avoid duplcating functionality.
        if curs_pos == cols
            write(s.terminal,"\n")
            cmove_col(s.terminal,1)
            curs_row+=1
            curs_pos=0
            cur_row+=1
        end


        # Let's move the cursor to the right position
        # The line first
        n = cur_row-curs_row
        if n>0
            cmove_up(s.terminal,n)
        end

        #columns are 1 based
        cmove_col(s.terminal,curs_pos+1)

        s.num_rows = cur_row
        s.curs_row = curs_row

        flush(s.terminal)
    end


    # Edit functionality

    char_move_left(s::ReadlineState) = char_move_left(s.input_buffer)
    function char_move_left(buf::IOBuffer)
        while position(buf)>0
            seek(buf,position(buf)-1)
            c = peek(buf)
            if ((c&0x80) == 0) || ((c&0xc0) == 0xc0)
                break
            end
        end
    end

    function edit_move_left(s)
        if position(s.input_buffer)>0
            #move t=o the next UTF8 character to the left
            char_move_left(s.input_buffer)
            refresh_line(s)
        end
    end

    char_move_right(s::ReadlineState) = char_move_right(s.input_buffer)
    function char_move_right(buf::IOBuffer)
        while position(buf) != buf.size
            seek(buf,position(buf)+1)
            if position(buf)==buf.size
                break
            end
            c = peek(buf)
            if ((c&0x80) == 0) || ((c&0xc0) == 0xc0)
                break
            end
        end
    end

    const non_word_chars = " \t\n\"\\'`@\$><=:;|&{}()[].,+-*/?%^~"

    function char_move_word_right(s)
        while !eof(s.input_buffer) && !contains(non_word_chars,read(s.input_buffer,Char))
        end
    end

    function char_move_word_left(s)
        while position(s.input_buffer) > 0
            char_move_left(s)
            c = peek(s.input_buffer)
            if c < 0x80 && contains(non_word_chars,char(c))
                read(s.input_buffer,Uint8)
                break
            end
        end
    end

    function edit_move_right(s)
        if position(s.input_buffer)!=s.input_buffer.size
            #move to the next UTF8 character to the right
            char_move_right(s)
            refresh_line(s)
        end
    end

    function charlen(ch::Char)
        if ch < 0x80
            return 1
        elseif ch < 0x800
            return 2
        elseif ch < 0x10000
            return 3
        elseif ch < 0x110000
            return 4
        end
        error("Corrupt UTF8")
    end


    function edit_replace(s,from,to,str)
        room = length(str.data)-(to-from)
        ensureroom(s.input_buffer,s.input_buffer.size-to+room)
        ccall(:memmove, Void, (Ptr{Void},Ptr{Void},Int), pointer(s.input_buffer.data,to+room+1),pointer(s.input_buffer.data,to+1),s.input_buffer.size-to)
        s.input_buffer.size += room
        seek(s.input_buffer,from)
        write(s.input_buffer,str)
    end

    function edit_insert(s::ReadlineState,c)
        edit_insert(s.input_buffer,c)
        if c != '\n' && eof(s.input_buffer) && (position(s.input_buffer) + length(s.prompt)) < width(s.terminal) 
            #Avoid full update
            write(s.terminal,c)
        else
            refresh_line(s)
        end
    end

    # TODO: Don't use memmove
    function edit_insert(buf::IOBuffer,c)
        if eof(buf)
            write(buf,c)
        else
            ensureroom(buf,buf.size-position(buf)+charlen(c))
            oldpos = position(buf)
            ccall(:memmove, Void, (Ptr{Void},Ptr{Void},Int), pointer(buf.data,position(buf)+1+charlen(c)), pointer(buf.data,position(buf)+1), 
                buf.size-position(buf))
            buf.size += charlen(c)
            write(buf,c)
        end
    end

    function edit_backspace(s::ReadlineState)
        if edit_backspace(s.input_buffer)
            refresh_line(s) 
        else
            beep(s.terminal)
        end

    end
    function edit_backspace(buf::IOBuffer)
        if position(buf) > 0 && buf.size>0
            oldpos = position(buf)
            char_move_left(buf)
            ccall(:memmove, Void, (Ptr{Void},Ptr{Void},Int), pointer(buf.data,position(buf)+1), pointer(buf.data,oldpos+1), 
                buf.size-oldpos) 
            buf.size -= oldpos-position(buf)
            return true
        else
            return false
        end
    end

    function edit_delete(s)
        if s.input_buffer.size>0 && position(s.input_buffer) < s.input_buffer.size
            oldpos = position(s.input_buffer)
            char_move_right(s)
            ccall(:memmove, Void, (Ptr{Void},Ptr{Void},Int), pointer(s.input_buffer.data,oldpos+1), pointer(s.input_buffer.data,position(s.input_buffer)+1), 
                s.input_buffer.size-position(s.input_buffer))
            s.input_buffer.size -= position(s.input_buffer)-oldpos
            seek(s.input_buffer,oldpos)
            refresh_line(s)
        else
            beep(s.terminal)
        end
    end

    function replace_line(s,l::IOBuffer)
        s.input_buffer = l
    end

    function replace_line(s,l)
        s.input_buffer.ptr = 1
        s.input_buffer.size = 0
        write(s.input_buffer,l)
    end

    history_prev(::EmptyHistoryProvider) = ("",false)
    history_next(::EmptyHistoryProvider) = ("",false)
    history_search(::EmptyHistoryProvider,args...) = false
    add_history(::EmptyHistoryProvider,s) = nothing

    function history_prev(s) 
        (l,ok) = history_prev(s.hist,s)
        if ok
            replace_line(s,l)
            refresh_line(s)
        else
            beep(s.terminal)
        end
    end
    function history_next(s) 
        (l,ok) = history_next(s.hist,s)
        if ok
            replace_line(s,l)
            refresh_line(s)
        else
            beep(s.terminal)
        end
    end

    refresh_line(s) = refreshMultiLine(s)

    default_completion_cb(::IOBuffer) = []
    default_enter_cb(::IOBuffer) = true

    write_prompt(s) = write_prompt(s,s.prompt)
    function write_prompt(s,prompt)
        write(s.terminal,s.prompt_color)
        write(s.terminal,prompt)
        write(s.terminal,s.input_color)
    end

    function normalize_key(key)
        if isa(key,Char)
            return string(key)
        elseif isa(key,Integer)
            return string(char(key))
        elseif isa(key,String)
            if contains(key,'\0')
                error("Matching \\0 not currently supported.")
            end
            buf = IOBuffer()
            i = start(key)
            while !done(key,i)
                (c,i) = next(key,i)
                if c == '*'
                    write(buf,'\0')
                elseif c == '^'
                    (c,i) = next(key,i)
                    write(buf,uppercase(c)-64)
                elseif c == '\\'
                    (c,i) == next(key,i)
                    if c == 'C'
                        (c,i) == next(key,i)
                        @assert c == '-'
                        (c,i) == next(key,i)
                        write(buf,uppercase(c)-64)
                    elseif c == 'M'
                        (c,i) == next(key,i)
                        @assert c == '-'
                        (c,i) == next(key,i)
                        write(buf,'\e')
                        write(buf,c)
                    end
                else
                    write(buf,c)
                end
            end
            return takebuf_string(buf)
        end
    end

    # Turn an Dict{Any,Any} into a Dict{'Char',Any}
    # For now we use \0 to represent unknown chars so that they are sorted before everything else
    # If we ever actually want to mach \0 in input, this will have to be
    # reworked
    function normalize_keymap(keymap)
        ret = Dict{Char,Any}()
        for key in keys(keymap)
            newkey = normalize_key(key)
            current = ret
            i = start(newkey)
            while !done(newkey,i)
                (c,i) = next(newkey,i)
                if haskey(current,c)
                    if !isa(current[c],Dict)
                        println(ret)
                        error("Conflicting Definitions for keyseq "*escape_string(newkey)*" within one keymap")
                    end
                elseif done(newkey,i)
                    current[c] = keymap[key]
                    break
                else
                    current[c] = Dict{Char,Any}()
                end
                current = current[c]
            end
        end
        ret
    end

    keymap_gen_body(keymaps,body::Expr,level) = body
    keymap_gen_body(keymaps,body::Function,level) = keymap_gen_body(keymaps,:($(body)(s)))
    keymap_gen_body(keymaps,body::Char,level) = keymap_gen_body(keymaps,keymaps[body])
    keymap_gen_body(keymaps,body::Nothing,level) = nothing

    keymap_gen_body(a,b) = keymap_gen_body(a,b,1)
    function keymap_gen_body(dict,subdict::Dict,level)
        block = Expr(:block)
        bc = symbol("c"*string(level))
        push!(block.args,:($bc=read(s.terminal,Char)))

        if haskey(subdict,'\0')
            last_if = keymap_gen_body(dict,subdict['\0'],level+1)
        else 
            last_if = nothing
        end

        for c in keys(subdict)
            if c == '\0'
                continue
            end
            cblock = Expr(:if,:($bc==$c))
            push!(cblock.args,keymap_gen_body(dict,subdict[c],level+1))
            if isa(cblock,Expr)
                push!(cblock.args,last_if)
            end
            last_if = cblock
        end

        push!(block.args,last_if)
        return block
    end

    export @keymap

    # deep merge where target has higher precedence
    function keymap_merge!(target::Dict,source::Dict)
        for k in keys(source)
            if !haskey(target,k)
                target[k] = source[k]
            elseif isa(target[k],Dict)
                keymap_merge!(target[k],source[k])
            else
                # Ignore, target has higher precedence
            end
        end
    end

    fixup_keymaps!(d,l,s,sk) = nothing
    function fixup_keymaps!(dict::Dict, level, s, subkeymap)
        if level > 1
            for d in dict 
                fixup_keymaps!(d[2],level-1,s,subkeymap)
            end
        else
            if haskey(dict,s)
                if isa(dict[s],Dict) && isa(subkeymap,Dict)
                    keymap_merge!(dict[s],subkeymap)
                end
            else
                dict[s] = deepcopy(subkeymap)
            end
        end
    end

    function add_specialisations(dict,subdict,level)
        default_branch = subdict['\0']
        if isa(default_branch,Dict)
            for s in keys(default_branch)
                if s == '\0'
                    add_specialisations(dict,default_branch,level+1)
                end
                fixup_keymaps!(dict,level,s,default_branch[s])
            end
        end
    end

    fix_conflicts!(x) = fix_conflicts!(x,1)
    fix_conflicts!(others,level) = nothing
    function fix_conflicts!(dict::Dict,level)
        # needs to be done first for every branch
        if haskey(dict,'\0')
            add_specialisations(dict,dict,level)
        end
        for d in dict
            if d[1] == '\0'
                continue
            end
            fix_conflicts!(d[2],level+1)
        end
    end

    function keymap_prepare(keymaps)
        if isa(keymaps,Dict)
            keymaps = [keymaps]
        end
        push!(keymaps,{"*"=>:(error("Unrecognized input"))})
        @assert isa(keymaps,Array) && eltype(keymaps) <: Dict
        keymaps = map(normalize_keymap,keymaps)
        map(fix_conflicts!,keymaps)
        keymaps
    end

    function keymap_unify(keymaps)
        if length(keymaps) == 1
            return keymaps[1]
        else 
            ret = Dict{Char,Any}()
            for keymap in keymaps
                keymap_merge!(ret,keymap)
            end
            fix_conflicts!(ret)
            return ret
        end
    end

    macro keymap(func, keymaps)
        dict = keymap_unify(keymap_prepare(isa(keymaps,Expr)?eval(keymaps):keymaps))
        body = keymap_gen_body(dict,dict)
        esc(quote
            function $(func)(s::Readline.ReadlineState,data)
                $body
                return :ok
            end
        end)
    end

    const escape_defaults = {
        # Ignore other escape sequences by default
        "\e*" => nothing,
        "\e[*" => nothing,
        # Also ignore extended escape sequences
        # TODO: Support tanges of characters
        "\e[1**" => nothing,
        "\e[2**" => nothing,
        "\e[3**" => nothing,
        "\e[4**" => nothing,
        "\e[5**" => nothing,
        "\e[6**" => nothing
    }

    function write_response_buffer(s,data)
        offset = s.input_buffer.ptr
        ptr = data.respose_buffer.ptr
        seek(data.respose_buffer,0)
        write(s.input_buffer,readall(data.respose_buffer))
        s.input_buffer.ptr = offset+ptr-2
        data.respose_buffer.ptr = ptr
        refresh_line(s)
    end

    function update_display_buffer(s,data)
        truncate(s.input_buffer,0)
        write(s.input_buffer,pointer(data.query_buffer.data),data.query_buffer.ptr-1)
        write(s.input_buffer,"': ")
        history_search(data.s.hist,data.s,data.query_buffer,data.respose_buffer,data.backward,false) || beep(s.terminal)
        write_response_buffer(s,data)

    end

    function history_next_result(s,data)
        truncate(s.input_buffer,s.input_buffer.size - data.respose_buffer.size)
        history_search(data.s.hist,data.s,data.query_buffer,data.respose_buffer,data.backward,true) || beep(s.terminal)
        write_response_buffer(s,data)
    end

    function history_set_backward(s,data,backward)
        data.backward = backward
        s.prompt = backward ? "(reverse-i-search)`" : "(i-search)`"
    end

    const search_keymap = {
        "^R" => :( Readline.history_set_backward(s,data,true); Readline.history_next_result(s,data) ),
        "^S" => :( Readline.history_set_backward(s,data,false); Readline.history_next_result(s,data) ),
        "\r" => :( s.input_buffer = data.respose_buffer; return :done ),
        "\t" => nothing, #TODO: Maybe allow tab completion in R-Search?

        # Backspace/^H
        '\b' => :(Readline.edit_backspace(data.query_buffer)?Readline.update_display_buffer(s,data):beep(s.terminal)),
        127 => '\b',
        "^C" => :( return :abort ),
        "^D" => :( return :abort ),

        "*" => :(Readline.edit_insert(data.query_buffer,c1);Readline.update_display_buffer(s,data))
    }
    @Readline.keymap search_keymap_func [Readline.search_keymap,Readline.escape_defaults]


    type SearchState
        s::ReadlineState
        backward::Bool #rsearch or ssearch
        query_buffer::IOBuffer
        respose_buffer::IOBuffer
    end

    function enter_rsearch(s)
        (buf,ok) = prompt!(s.terminal,"(reverse-i-search)`";first_prompt = "(reverse-i-search)`': ",
            keymap_func=search_keymap_func,keymap_func_data=SearchState(s,true,IOBuffer(),IOBuffer()))
        if ok
            s.input_buffer = buf
        end
        raw!(s.terminal,true)
        refresh_line(s)
    end

    function enter_ssearch(s)
        (ok,buf) = prompt!(s.terminal,"(i-search)`";first_prompt = "(i-search)`': ",
            keymap_func=search_keymap_func,keymap_func_data=SearchState(s,false,IOBuffer(),IOBuffer()))
        if ok
            s.input_buffer = buf
        end
        raw!(s.terminal,true)
        refresh_line(s)
    end

    const default_keymap =
    {   
        # Tab
        '\t' => :(completeLine(s); refresh_line(s)),
        # Enter
        '\r' => quote
            if s.enter_cb(s)
                println(s.terminal)
                Readline.add_history(s.hist,s)
                return :done
            else
                Readline.edit_insert(s,'\n')
            end
        end,
        # Backspace/^H
        '\b' => edit_backspace,
        127 => '\b',
        # ^D
        4 => quote 
            if s.input_buffer.size > 0
                Readline.edit_delete(s)
            else
                println(s.terminal)
                return :abort
            end
        end,
        # ^B
        2 => edit_move_left,
        # ^F
        6 => edit_move_right,
        # ^P
        16 => history_prev,
        # ^N
        14 => history_next,
        # Up Arrow
        "\e[A" => history_prev,
        # Down Arrow
        "\e[B" => history_next,
        # Right Arrow
        "\e[C" => edit_move_right,
        # Left Arrow
        "\e[D" => edit_move_left,
        # Meta Enter
        "\e\r" => :(Readline.edit_insert(s,'\n')),
        # Simply insert it into the buffer by default
        "*" => :( Readline.edit_insert(s,c1) ),
        # ^U
        21 => :( truncate(s.input_buffer,0); Readline.refresh_line(s) ),
        # ^K
        11 => :( truncate(s.input_buffer,position(s.input_buffer)) ),
        # ^A    
        1 => :( seek(s.input_buffer,0); Readline.refresh_line(s) ),
        # ^E
        5 => :( seek(s.input_buffer,s.input_buffer.size-1);Readline.refresh_line(s) ),
        # ^L
        12 => :( clear(s.terminal); Readline.refresh_line(s) ),
        # ^W (#edit_delte_prev_word(s))
        23 => :( error("Unimplemented") ),
        # ^R
        "^R" => enter_rsearch,
        "^S" => enter_ssearch
    }

    @Readline.keymap default_keymap_func [Readline.default_keymap,Readline.escape_defaults]

    function prompt!(terminal,prompt;
                    first_prompt = prompt,
                    prompt_color="",
                    keymap_func = default_keymap_func,
                    keymap_func_data = nothing,
                    input_color="",
                    complete=EmptyCompletionProvider(),
                    on_enter=default_enter_cb,hist=EmptyHistoryProvider())
        s = ReadlineState(terminal,hist,complete,on_enter,IOBuffer(),prompt,prompt_color,input_color,1,1,length(prompt))
        raw!(terminal,true)
        try
            clear_line(s.terminal) 
            write_prompt(s,first_prompt)
            while true
                state = keymap_func(s,keymap_func_data)
                if state == :abort
                    return (s.input_buffer,false)
                elseif state == :done
                    return (s.input_buffer,true)
                else
                    @assert state == :ok
                end
            end
            raw!(terminal,false)
            println(terminal)
            return s.input_buffer
        finally
            raw!(terminal,false)
        end
    end
end