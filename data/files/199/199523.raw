# ps3000_open_unit_progress.jl

export ps3000_open_unit_progress

function ps3000_open_unit_progress()
  handle = Ref{Int16}
  progress_percent = Ref{Int16}
  open_unit_progress_status = ccall((:ps3000_open_unit_progress, ps3000driver), int16,
    (Ref{Int16}, Ref{Int16}),
    handle, progress_percent)
  if open_unit_progress_status == -1
    error("ps3000 Error: unit failed to open or was not found")
  end
  return (handle, progress_percent)
end
