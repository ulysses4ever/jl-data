using ConcatOperator
using Base.Test

@test "abc" ++ "def" == "abcdef"
@test "ab" ++ "cd" ++ "ef" == "abcdef"
@test "a" ++ 'b' ++ "cd" ++ 'e' ++ "f" == "abcdef"
@test 'π' ++ " ≠" ++ utf16(" α ±") ++ utf32(" β") == "π ≠ α ± β"

@test [1,2] ++ [3,4] == [1,2,3,4]
@test [1,2] ++ [3.0,4.0] == [1.0,2.0,3.0,4.0]
