module CodeToString

export code_llvm_to_bytestring, @code_llvm_to_bytestring, code_native_to_bytestring, @code_native_to_bytestring, code_warntype_to_bytestring, @code_warntype_to_bytestring

macro stdout_to_bytestring(ex)
    quote
        old_stdout = STDOUT
        (rd, wr) = redirect_stdout()
        $(esc(ex))
        close(wr)
        data = readavailable(rd)
        close(rd)
        redirect_stdout(old_stdout)
        data
    end
end

function code_llvm_to_bytestring(f, types)
    @stdout_to_bytestring code_llvm(f, types)
end

macro code_llvm_to_bytestring(ex)
    quote
        @stdout_to_bytestring @code_llvm $(esc(ex))
    end
end

function code_native_to_bytestring(f, types)
    @stdout_to_bytestring code_native(f, types)
end

macro code_native_to_bytestring(ex)
    quote
        @stdout_to_bytestring @code_native $(esc(ex))
    end
end

function code_warntype_to_bytestring(f, types)
    @stdout_to_bytestring code_warntype(f, types)
end

macro code_warntype_to_bytestring(ex)
    quote
        @stdout_to_bytestring @code_warntype $(esc(ex))
    end
end

end #module
