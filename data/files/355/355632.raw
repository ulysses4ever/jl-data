module JuliaHungarian
  export hungarian

  function hungarian(input_matrix)
    square_mat = make_square(input_matrix)
    cost_matrix =  square_mat .- minimum(square_mat,2);
    star_mask, col_cover, row_cover = step_two(cost_matrix);
    len = length(col_cover);
    prime_mask = falses(len,len);
    done = false;
    step = 3;
    while (!done)
      if step === 3
        step, col_cover = step_three(star_mask);
      elseif step === 4
        step, prime_mask, row_cover, col_cover, idx = step_four(cost_matrix, star_mask, prime_mask, row_cover, col_cover)
      elseif step === 5
        step, star_mask, prime_mask, row_cover, col_cover = step_five(star_mask, prime_mask, row_cover, col_cover, idx)
      elseif step === 6
        step, cost_matrix = step_six(cost_matrix, row_cover, col_cover);
      else
        # cost = sum(star_mask .* cost_matrix);
        cost = sum(cost_matrix[star_mask]);
        return star_mask, cost;
      end
    end
  end

  function make_square(M)
    nrow, ncol = size(M);
    if nrow === ncol return M end;
    max_val = maximum(M,2);
   return (ncol < nrow) ? [M ones(Int64, nrow, nrow-ncol) .* max_val] : [M; ones(Int64,ncol-nrow,ncol) .* max_val];
  end

  function step_two(cost_matrix)
    len = size(cost_matrix,1);
    star_mask = falses(len, len);
    col_cover = falses(1,len);
    row_cover = falses(1,len);
    #try replacing trues with Inf and using find to check for speed
    for r = 1:len
        if row_cover[r] === true continue end
      for c = 1:len
        if col_cover[c] === true continue end
  #       println(r, " ",c, col_cover, " ", row_cover);
        if cost_matrix[r,c] === 0
          star_mask[r,c] = true;
          col_cover[c] = true;
          row_cover[r] = true;
        end
      end
    end
    fill!(col_cover, false);
    fill!(row_cover, false);
    return star_mask, col_cover, row_cover
  end

  function step_three(star_mask)
    # println("step 3");
    col_cover = any(star_mask,1);
    if sum(col_cover) === size(star_mask,1)
      step = 7;
    else
      step = 4;
    end
    return step, col_cover
  end

  function step_four(cost_matrix, star_mask, prime_mask, row_cover, col_cover)
    # println("step 4");
    done = false;
    len = length(col_cover);
    local idx;
    local step;
    # println("col_cover: ", col_cover);
    # println("row_cover: ", row_cover);
    while (!done)
      idx = find_uncovered_zero(cost_matrix,row_cover, col_cover, len);
      # println(idx);
      if idx === nothing
        idx = (999,999);
        step = 6;
        # println(row_cover);
        break;
      end
      row, col = idx;
      prime_mask[row, col] = true;

      # first_starred_zero = findfirst(star_mask[row,:])
      # findfirst is really slow here
      first_starred_zero = 0;
      for x = 1:len
        if star_mask[row,x] === true
          first_starred_zero = x
          break;
        end
      end
      if first_starred_zero > 0
        row_cover[row] = true;
        col_cover[first_starred_zero] = false; #combine any and findfirst for efficiency
      else
        step = 5;
        break;
      end
      # println("prime mask: ", prime_mask);
      # println("star mask: ", star_mask);
    end
    # println("returning", step, prime_mask, row_cover, col_cover, idx);
    return step, prime_mask, row_cover, col_cover, idx
  end

  function find_uncovered_zero(cost_matrix, row_cover, col_cover, len)
    # println("Row cover: ", row_cover);
    # println("Col cover: ", col_cover);
    # println("matrix: ", cost_matrix);
    for c = 1:len #check rows first for efficiency
      if col_cover[c] === true continue end
      for r = 1:len
        if row_cover[r] === true continue end
        # println(r,",",c);
        if cost_matrix[r,c] === 0
          # println(r,",",c);
          return (r,c);
        end
      end
    end
  end

  function step_five(star_mask, prime_mask, row_cover, col_cover, idx)
    # println("step 5");
    done = false;
    path_count = 1;
    path = [idx];
    while !done
      star_row_idx = findfirst(star_mask[:,path[path_count][2]]);
      # println(star_row_idx);
      if star_row_idx > 0
        path_count += 1;
        push!(path,(star_row_idx, path[path_count-1][2]));

      else
        done = true;
      end
      if !done
        primed_col_idx = findfirst(prime_mask[star_row_idx,:]);
        push!(path, (star_row_idx, primed_col_idx));
        path_count += 1;
      end
    end
    # println(path);
    for i = 1: length(path)
      if star_mask[path[i]...] === true
        star_mask[path[i]...] = false;
      else
        star_mask[path[i]...] = true;
      end
    end
    fill!(row_cover,false);
    fill!(col_cover,false);
    fill!(prime_mask, false);
    return 3, star_mask, prime_mask, row_cover, col_cover
  end

  function step_six(cost_matrix, row_cover, col_cover)
    # println("step 6");
    # println(cost_matrix);
    # println(cost_matrix[find(!row_cover),find(!col_cover)]);
    not_col_cover_idx = find(!col_cover);
    min_val = minimum(cost_matrix[find(!row_cover),not_col_cover_idx]);
    # println(min_val);
    cost_matrix[find(row_cover),:] += min_val;
    cost_matrix[:,not_col_cover_idx] -= min_val;
    # print(cost_matrix);
    return 4, cost_matrix;
  end
end

# hungarian([49 87 96 79 39 47 18 35 97 82; 22 48 33 47 98 6 1 98 49 23; 57 24 98 96 29 58 47 59 69 76; 20 70 7 10 87 87 33 37 22 11; 26 53 95 99 16 83 41 86 44 25; 84 13 81 46 22 25 90 19 60 63; 55 98 87 69 55 58 9 5 10 44; 71 41 29 90 51 29 49 23 82 10; 2 85 37 25 14 57 73 42 26 14; 94 36 35 87 14 5 73 99 26 73])
# Profile.clear()  # in case we have any previous profiling data
# for zz = 1:100
  # @profile hungarian([23 87 96 79 39 47 18 35 97 82; 22 48 33 47 98 6 1 98 49 23; 57 24 98 96 29 58 47 59 69 76; 20 70 7 10 87 87 33 37 22 11; 26 53 95 99 16 83 41 86 44 25; 84 13 81 46 22 25 90 19 60 63; 55 98 87 69 55 58 9 5 10 44; 71 41 29 90 51 29 49 23 82 10; 2 85 37 25 14 57 73 42 26 14; 94 36 35 87 14 5 73 99 26 73])
# end
# using ProfileView
# ProfileView.view()
