

# --- macros emulating opencl (roughly!)


"""execute the same code at each point on the board (tries to
guarantee that the julia code is structured similarly to an opencl
kernel)."""
macro forall(i, j, n, block)
    :(for $(esc(i)) in 1:$(esc(n))
          for $(esc(j)) in 1:$(esc(n))
              $(esc(block))
          end
      end)
end

"""as forall, but also include a final reduction (again, easy to
implement in a kernel)."""
macro forall_fold(i, j, n, f, z, r, block)
    :(for $(esc(i)) in 1:$(esc(n))
          for $(esc(j)) in 1:$(esc(n))
              $(esc(block))
          end
      end;
      foldl($(esc(f)), $(esc(z)), $(esc(r))))
end

"""iterate over neigbours - explicit loop (not parallelized) (to
reduce board lookup dx=0 should be grouped)."""
macro forneighbours(x, y, n, xx, yy, block)
    :(for (dx, dy) in ((0, 1), (0, -1), (1, 0), (-1, 0))
          $(esc(xx)), $(esc(yy)) = $(esc(x)) + dx, $(esc(y)) + dy      
          if $(esc(xx)) > 0 && $(esc(xx)) <= $(esc(n)) && $(esc(yy)) > 0 && $(esc(yy)) <= $(esc(n))
              $(esc(block))
          end
      end)
end


