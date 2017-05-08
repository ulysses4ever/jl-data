# Framebuffer wrapper, ported from Python's https://github.com/cgoldberg/xvfbwrapper
module XvfbWrapper
export Xvfb, start!, stop!

type Xvfb
    width ::Int
    height ::Int
    colordepth ::Int
    exec ::Array{ByteString,1}
    proc # Nullable(Base.Process) or Union{None,Base.Process}?
    oldDisplayNum::Int
    vDisplayNum::Int
end

function Xvfb(width=800, height=680, colordepth=24; args...)
    bashargs = mapreduce( x->[string("-",x[1]),x[2]], append!, [], args)
    exec = ["-screen", "0", "$(width)x$(height)x$(colordepth)", bashargs ]
    oldDisplayNum = 0
    oldDisplayNum = try parse(Int,split(ENV["DISPLAY"],':')[2]) end
    proc = None
  return Xvfb(width, height, colordepth, exec, proc, oldDisplayNum, oldDisplayNum )
end

function start!(fb::Xvfb)
    if fb.proc == None
        fb.vDisplayNum = search_for_free_display()
        prepend!( fb.exec , ["Xvfb", ":$(fb.vDisplayNum)"] )

        fb.proc = spawn(`$(fb.exec)`)
        sleep(0.2)  # give Xvfb time to start

        if !process_exited(fb.proc) 
            _redirect_display(fb.vDisplayNum)
        else
            _redirect_display(fb.oldDisplayNum)
            fb.proc = None
            error("Xvfb did not start, exitcode = ", fb.proc.exitcode)
        end
    else
        error("framebuffer process already started")
    end
end

function stop!(fb)
    if fb.proc == None
        error("framebuffer process already stopped")
    else
        _redirect_display(fb.oldDisplayNum)
        fb.exec = fb.exec[3:end]
        if fb.proc != None
            kill( fb.proc )
            wait( fb.proc )
            fb.proc = None
        end
    end
end

_redirect_display(display_num) = ENV["DISPLAY"] = ":$(display_num)"

_lock_files() = filter(x->ismatch(r"\.X[0-9]+-lock",x),readdir("/tmp/"))

function search_for_free_display()
    ls = [parse(Int,split(file_name,['X','-'])[2]) for file_name=_lock_files()]
    min_display_num = 1000
    if length(ls) > 0
        display_num = max(min_display_num, max(0, ls...) + 1)
    else
        display_num = min_display_num
    end
    srand()
    display_num += rand(0:100)
    return display_num
end

end
