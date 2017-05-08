const UNASSIGNED = 0
global iterCnt = 0 # debug

function solveSudoku!(tab)
    #debug
    global iterCnt
    println(iterCnt+=1)

    # 测试是否完成
    isComp, x, y = checkCompleted(tab)
    if isComp
        return true
    else
        println((x, y)) # debug
    end

    # 顺序测试1~9个数在ind位置
    for num = 1:9
        # 检测是否满足
        if isSafe(tab, x, y, num)
            # 多满足则在此位置填入该数
            tab[x, y] = num

            # 递归调用主求解函数直到完成
            if solveSudoku!(tab)
                return true
            end

            # 试完9个数后未找到正确值说明前面的不正确
            tab[x, y] = UNASSIGNED
        end
    end

    return false
end

function calcXY(ind)
    const xy = [(x, y) for x=1:9, y=1:9]
    return xy[ind]
end

function checkCompleted(tab)
    zInd = find(x->x==UNASSIGNED, tab)
    if isempty(zInd)
        return true, 1, 1
    else
        xy = calcXY(zInd[1])
        return false, xy[1], xy[2]
    end
end

function isSafe(tab, x, y, num)
    return !isInRow(tab, x, num) &&
            !isInCol(tab, y, num) &&
            !isInSubTab(tab, x, y, num)
end

isInRow(tab, x, num) = begin
    if num in tab[x, :]
        return true
    else
        return false
    end
end

isInCol(tab, y, num) = begin
    if num in tab[:, y]
        return true
    else
        return false
    end
end

#@debug isInSubTab(tab, x, y, num) = begin
isInSubTab(tab, x, y, num) = begin
#    @bp
    const startInd = [1, 1, 1, 4, 4, 4, 7, 7, 7]
    xsi = startInd[x]
    ysi = startInd[y]
    if num in tab[xsi:xsi+2, ysi:ysi+2]
        return true
    else
        return false
    end
end

function test()
    grid = [3 0 6 5 0 8 4 0 0;
            5 2 0 0 0 0 0 0 0;
            0 8 7 0 0 0 0 3 1;
            0 0 3 0 1 0 0 8 0;
            9 0 0 8 6 3 0 0 5;
            0 5 0 0 9 0 6 0 0;
            1 3 0 0 0 0 2 5 0;
            0 0 0 0 0 0 0 7 4;
            0 0 5 2 0 6 3 0 0]
    solveSudoku!(grid)
    println(grid)
end
