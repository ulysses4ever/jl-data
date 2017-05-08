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
        prompt
        num_rows::Int
        curs_row::Int
        indent
    end

    completeLine(c::EmptyCompletionProvider,s) = []

    function completeLine(s::ReadlineState)
        completions = completeLine(s.complete,s)
        if length(completions) == 0
            beep(s.terminal)
        elseif length(completions) == 1
            # Replace word by completion
            prev_pos = position(s.input_buffer)
            char_move_word_left(s)
            edit_replace(s,position(s.input_buffer),prev_pos,completions[1])
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
        cur_row = 0
        buf_pos = position(s.input_buffer)
        line_pos = buf_pos
        # Write out the prompt string
        write(s.terminal,s.prompt)

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
            else
                # We expect to be line after the last valid output line (due to
                # the '\n' at the end of the previous line)
                if curs_row == -1
                    if line_pos < slength
                        num_chars = length(l[1:linepos])
                        curs_row = cur_row+div(s.indent+num_chars-1,cols)
                        curs_pos = (s.indent+num_chars-1)%cols+1
                    end
                    line_pos -= slength+1 #'\n' gets an extra pos
                end
                cur_row += div(llength+s.indent-1,cols)
                cmove_col(s.terminal,s.indent+1)
            end
            write(s.terminal,l)
        end

        seek(s.input_buffer,buf_pos)

        # If we are at the end of the buffer, we need to put the cursor one past the 
        # last character we have written
        
        if curs_row == -1
            curs_pos = (s.indent+llength-1)%cols+1
            curs_row = cur_row
        end


        # Let's move the cursor to the right position
        # The line first
        n = cur_row-curs_row
        if n>0
            cmove_up(s.terminal,n)
        end

        #columns are 1 based
        cmove_col(s.terminal,curs_pos+1)
        # There's another issue if the last character we wrote was at the very right end of the screen. In that case we need to
        # emit a new line and move the cursor there. 
        if curs_pos == cols
            write(s.terminal,"\n")
            cmove_col(s.terminal,0)
            curs_row+=1
            curs_pos=0
            cur_row+=1
        end

        s.num_rows = cur_row
        s.curs_row = curs_row

        flush(s.terminal)
    end


    # Edit functionality

    function char_move_left(s)
        while position(s.input_buffer)>0
            seek(s.input_buffer,position(s.input_buffer)-1)
            c = peek(s.input_buffer)
            if ((c&0x80) == 0) || ((c&0xc0) == 0xc0)
                break
            end
        end
    end

    function edit_move_left(s)
        if position(s.input_buffer)>0
            #move to the next UTF8 character to the left
            char_move_left(s)
            refresh_line(s)
        end
    end

    function char_move_right(s)
        while position(s.input_buffer)!=s.input_buffer.size
            seek(s.input_buffer,position(s.input_buffer)+1)
            if position(s.input_buffer)==s.input_buffer.size
                break
            end
            c = peek(s.input_buffer)
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

    function edit_insert(s,c)
        if eof(s.input_buffer)
            write(s.input_buffer,c)
            #if (position(s.input_buffer) + length(s.prompt)) < width(s.terminal) #Avoid full update
            #    write(s.terminal,c)
            #else
                refresh_line(s)
            #end
        else
            ensureroom(s.input_buffer,s.input_buffer.size-position(s.input_buffer)+charlen(c))
            oldpos = position(s.input_buffer)
            ccall(:memmove, Void, (Ptr{Void},Ptr{Void},Int), pointer(s.input_buffer.data,position(s.input_buffer)+1+charlen(c)), pointer(s.input_buffer.data,position(s.input_buffer)+1), 
                s.input_buffer.size-position(s.input_buffer))
            s.input_buffer.size += charlen(c)
            write(s.input_buffer,c)
            refresh_line(s)
        end
    end

    function edit_backspace(s)
        if position(s.input_buffer) > 0 && s.input_buffer.size>0
            oldpos = position(s.input_buffer)
            char_move_left(s)
            ccall(:memmove, Void, (Ptr{Void},Ptr{Void},Int), pointer(s.input_buffer.data,position(s.input_buffer)+1), pointer(s.input_buffer.data,oldpos+1), 
                s.input_buffer.size-oldpos) 
            s.input_buffer.size -= oldpos-position(s.input_buffer)
            refresh_line(s)
        else
            beep(s.terminal)
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

    function prompt!(terminal,prompt;complete=EmptyCompletionProvider(),on_enter=default_enter_cb,hist=EmptyHistoryProvider())
        s = ReadlineState(terminal,hist,complete,on_enter,IOBuffer(),prompt,1,1,length(prompt))
        raw!(terminal,true)
        try
            write(s.terminal,prompt)
            while true
                c=read(terminal,Char)

                # Need switch-case (though LLVM might be smart enough to optimize this anyway)
                if c == '\t'
                    completeLine(s)
                    refresh_line(s)
                elseif c == '\r'
                    if s.enter_cb(s)
                        println(s.terminal)
                        add_history(s.hist,s)
                        return (s.input_buffer,true)
                    else
                        edit_insert(s,'\n')
                        refresh_line(s)
                    end
                elseif c == 127 || c==8 #Backspace/^H
                    edit_backspace(s)
                elseif c == 4 #^D
                    if s.input_buffer.size > 0
                        edit_delete(s)
                    else
                        println(s.terminal)
                        return (s.input_buffer,false)
                    end
                elseif c == 2 #^B
                    edit_move_left(s)
                elseif c == 6 #^F
                    edit_move_right(s)
                elseif c == 16 #^P
                    history_prev(s)
                elseif c == 14 #^N
                    history_next(s)
                elseif c == 27 #Escape Sequence
                    seq = Array(Uint8,2)
                    read(terminal,seq)
                    if seq[1] == 91 
                        if seq[2] == 68 #Left Arrow
                            edit_move_left(s)
                        elseif seq[2] == 67 #Right Arrow
                            edit_move_right(s)
                        elseif seq[2] == 66 #Down Arrow
                            history_next(s)
                        elseif seq[2] == 65 #Up Arrow
                            history_prev(s)
                        elseif seq[2] > 48 && seq[2] < 55 #Extended Escape Sequence
                            seq2 = Array(Uint8,2)
                            read(terminal,seq2)
                            if seq[2] == 51 && seq2[1] == 126
                                edit_delete(s)
                            end
                        end
                    end
                elseif c == 21 #^U
                    truncate(s.input_buffer,0)
                    refresh_line(s)
                elseif c == 11 #^K
                    truncate(s.input_buffer,position(s.input_buffer))
                    refresh_line(s)
                elseif c == 1 #^A
                    seek(s.input_buffer,0)
                    refresh_line(s)
                elseif c == 5 #^E
                    seek(s.input_buffer,s.input_buffer.size-1)
                    refresh_line(s)
                elseif c == 12
                    clear(s.terminal)
                    refresh_line(s)
                elseif c == 23
                    error("Unimplemented")
                    #edit_delte_prev_word(s)
                else
                    edit_insert(s,c)
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