

# --- convolution


# http://developer.amd.com/resources/documentation-articles/articles-whitepapers/tiled-convolution-fast-image-filtering/
# has a detailed argument about why and how to do this better on a
# real gpu (although this case is simpler as it fits in a single tile)

"""convolve a 3x3 cross-shaped kernel."""
function convolve(input, border, kernel, output, n)
    @forall i j n begin
        a = 0
        # cannot use forneighbours because we need di, dj
        for (di, dj) in ((0, 1), (0, -1), (1, 0), (-1, 0))
            ii, jj = i+di, j+dj
            if ii > 0 && ii <= n && jj > 0 && jj <= n
                a = a + kernel[di+2, dj+2] * input[ii, jj]
            else
                a = a + kernel[di+2, dj+2] * border
            end
            output[i, j] = a
        end
    end
end

function blank!{N}(data, p::Position{N})
    @forall i j N begin
        if point(p, i, j) != empty
            data[i, j] = 0
        end
    end
end
