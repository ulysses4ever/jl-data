### file: Identity/test/runtests.jl

## Copyright (c) 2015 Samuel B. Johnson

## Author: Samuel B. Johnson <sabjohnso@yahoo.com>

## This file is lincesed under a two license system. For commercial use
## that is not compatible with the GPLv3, please contact the author.
## Otherwise, continue reading below.

## This file is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 3, or (at your option)
## any later version.

## You should have received a copy of the GNU General Public License
## along with this program. If not, see <http://www.gnu.org/licenses/>.

### Code:

using Identity
using FactCheck

facts( "Additive Identity" ) do
    @fact 3+additive_identity --> 3
    @fact additive_identity+3 --> 3
    @fact additive_identity+additive_identity --> additive_identity
    @fact "cow"-additive_identity --> "cow"
    @fact additive_identity-additive_identity --> additive_identity
end

facts( "Multiplicative Identity" ) do
    @fact 3*multiplicative_identity --> 3
    @fact multiplicative_identity*3 --> 3
    @fact multiplicative_identity*multiplicative_identity --> multiplicative_identity
    @fact "bull"/multiplicative_identity --> "bull"
    @fact multiplicative_identity/multiplicative_identity --> multiplicative_identity
end

