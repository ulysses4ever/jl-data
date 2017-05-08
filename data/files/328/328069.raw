using PeaksAndValleys
using Base.Test

using Compat

function test_initial_pivot()
    # Strictly increasing.
    data = linspace(1.0, 2.0, 10)
    @test identify_initial_pivot(data, 0.1, -0.1) == VALLEY
    
    # Strictly decreasing.
    data = linspace(1, 0.5, 10)
    @test identify_initial_pivot(data, 0.1, -0.1) == PEAK
    
    # Increasing but kinked.
    data = [1.0, 0.99, 1.1]
    @test identify_initial_pivot(data, 0.1, -0.1) == PEAK
    
    # Decreasing but kinked.
    data = [1.0, 1.01, 0.9]
    @test identify_initial_pivot(data, 0.1, -0.1) == VALLEY
    
    # Strictly increasing but under threshold.
    data = linspace(1, 1.01, 10)
    @test identify_initial_pivot(data, 0.1, -0.1) == VALLEY

    # Strictly decreasing but under threshold.
    data = linspace(1, 0.99, 10)
    @test identify_initial_pivot(data, 0.1, -0.1) == PEAK

    # Increasing but under threshold and kinked.
    data = [1.0, 0.99, 1.02]
    @test identify_initial_pivot(data, 0.1, -0.1) == VALLEY

    # Decreasing but under threshold and kinked.
    data = [1.0, 1.01, 0.99]
    @test identify_initial_pivot(data, 0.1, -0.1) == PEAK
end

function test_pivots()
    # The relative change should be a negative number. When coding,
    # I kept mistakenly using positive numbers for both. Having 
    # a positive and a negative makes things more clear, without 
    # having to use named parameters. 
    data = [1.0, 2.0, 3.0]
    @test_throws AssertionError peak_valley_pivots(data, 0.1, 0.1)

    # Strictly increasing.
    data = linspace(1, 10, 10)
    result = peak_valley_pivots(data, 0.1, -0.1)
    expected_result = zeros(data)
    expected_result[1], expected_result[end] = VALLEY, PEAK
    @test result == expected_result
    
    # Strictly decreasing.
    data = linspace(10, 0, 10)
    result = peak_valley_pivots(data, 0.1, -0.1)
    expected_result = zeros(data)
    expected_result[1], expected_result[end] = PEAK, VALLEY
    @test result == expected_result

    # Strictly increasing but under threshold.
    data = linspace(1.0, 1.05, 10)
    result = peak_valley_pivots(data, 0.1, -0.1)
    expected_result = zeros(data)
    expected_result[1], expected_result[end] = VALLEY, PEAK
    @test data[1] < data[end]
    @test result == expected_result

    # Strictly decreasing but under threshold.
    data = linspace(1.05, 1.0, 10)
    result = peak_valley_pivots(data, 0.1, -0.1)
    expected_result = zeros(data)
    expected_result[1], expected_result[end] = PEAK, VALLEY
    @test result == expected_result
    
    # Increasing but kinked.
    data = [1.0, 0.99, 1.1]
    result = peak_valley_pivots(data, 0.1, -0.1)
    expected_result = [PEAK, VALLEY, PEAK]
    @test result == expected_result

    # Decreasing but kinked.
    data = [1.0, 1.01, 0.9]
    result = peak_valley_pivots(data, 0.1, -0.1)
    expected_result = [VALLEY, PEAK, VALLEY]
    @test result == expected_result

    # Single peaked.
    data = [1.0, 1.2, 1.05]
    result = peak_valley_pivots(data, 0.1, -0.1)
    expected_result = [VALLEY, PEAK, VALLEY]
    @test result == expected_result

    # Single valleyed.
    data = [1.0, 0.9, 1.2]
    result = peak_valley_pivots(data, 0.1, -0.1)
    expected_result = [PEAK, VALLEY, PEAK]
    @test result == expected_result
end

function test_segment_return()
    # Strictly increasing.
    data = linspace(1.0, 100.0, 10)
    pivots = peak_valley_pivots(data, 0.1, -0.1)
    @test compute_segment_returns(data, pivots) == [99.0]

    # Strictly decreasing.
    data = linspace(100.0, 1.0, 10)
    pivots = peak_valley_pivots(data, 0.1, -0.1)
    @test compute_segment_returns(data, pivots) == [-0.99]

    # Rise-Fall-Rise.
    data = [1.0, 1.05, 1.1, 1.0, 0.9, 1.5]
    pivots = peak_valley_pivots(data, 0.1, -0.1)
    result = compute_segment_returns(data, pivots)
    expected = [0.1, -0.181818, 0.6666666]
    for (a,b) in zip(result, expected)
        @test_approx_eq_eps a b 1e-2
    end
end

function test_max_drawdown()
    # Strictly increasing.
    data = linspace(1.0, 100.0, 10)
    @test max_drawdown(data) == 0.0

    # Strictly decreasing.
    data = linspace(100.0, 1.0, 10)
    @test_approx_eq max_drawdown(data) 0.99

    # Rise-Fall-Rise.
    data = [1.0, 1.05, 1.1, 1.0, 0.9, 1.5]
    @test_approx_eq max_drawdown(data) 0.18181818181818188
end

function test_modes_to_pivots()
    data = [1, 0, 0, 0, -1, 0, 0, 1, -1, 0, 1]
    result = pivots_to_modes(data)
    expected = [1, -1, -1, -1, -1, 1, 1, 1, -1, 1, 1]

    @test result == expected
end

test_initial_pivot()
test_pivots()
test_segment_return()
test_max_drawdown()
test_modes_to_pivots()

