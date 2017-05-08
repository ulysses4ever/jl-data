
const UNASSIGNED = 0
const N = 9
global iterCnt = 1

# main solve function
function solveSudoku!(grid)
    global iterCnt
    println(iterCnt+=1)

    row = 1
    col = 1

    # check completed
    # end iterator
    isFind, row, col = findUnassignedLocation(grid, row, col)
    println((row, col))
    if !isFind
        return true
    end

    # test from 1 to 9
    for num = 1:9
        # test num is appropriate
        if isSafe(grid, row, col, num)
            grid[row, col] = num # temporary
            # keep on iterator
            if solveSudoku!(grid)
                return true
            end

            grid[row, col] = UNASSIGNED
        end
    end
    return false
end

function findUnassignedLocation(grid, row, col)
    for r = 1:N
        for c = 1:N
            if grid[r, c] == UNASSIGNED
                return true, r, c
            end
        end
    end
    return false, 1, 1
end

function usedInRow(grid, row, num)
    for c = 1:N
        if grid[row, c] == num
            return true
        end
    end
    return false
end

function usedInCol(grid, col, num)
    for r = 1:N
        if grid[r, col] == num
            return true
        end
    end
    return false
end

function getStartInd(ind)
    if ind <= 3
        return 1
    elseif ind >= 4 && ind <= 6
        return 4
    else
        return 7
    end
end

function usedInBox(grid, row, col, num)
    boxStartRow = getStartInd(row)
    boxStartCol = getStartInd(col)
    for r = 0:2
        for c = 0:2
            if grid[boxStartRow+r, boxStartCol+c] == num
                return true
            end
        end
    end
    return false
end

function isSafe(grid, row, col, num)
    return !usedInRow(grid, row, num) &&
            !usedInCol(grid, col, num) &&
            !usedInBox(grid, row, col, num)
end

function testSudoku()
    grid = [3 0 6 5 0 8 4 0 0;
            5 2 0 0 0 0 0 0 0;
            0 8 7 0 0 0 0 3 1;
            0 0 3 0 1 0 0 8 0;
            9 0 0 8 6 3 0 0 5;
            0 5 0 0 9 0 6 0 0;
            1 3 0 0 0 0 2 5 0;
            0 0 0 0 0 0 0 7 4;
            0 0 5 2 0 6 3 0 0]
    println(grid)

    if solveSudoku!(grid)
        println(grid)
    else
        println("can't solve!")
    end
end
