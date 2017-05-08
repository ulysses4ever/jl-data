### file: Identity/src/Identity.jl

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

"
module Identity
---------------
A module introducing types for universally
applicable identities.
"
module Identity

import Base.+, Base.-, Base.*, Base./


export AbstractIdentity, AdditiveIdentity, MultiplicativeIdentity, +, *,
       additive_identity, multiplicative_identity

abstract AbstractIdentity


immutable AdditiveIdentity
end

+( ::AdditiveIdentity, ::AdditiveIdentity ) = AdditiveIdentity()
+( x, ::AdditiveIdentity ) = x
+( ::AdditiveIdentity, y ) = y

-( ::AdditiveIdentity, ::AdditiveIdentity ) = AdditiveIdentity()
-( x, ::AdditiveIdentity ) =  x


const additive_identity = AdditiveIdentity()


immutable MultiplicativeIdentity
end
*( ::MultiplicativeIdentity, ::MultiplicativeIdentity ) = MultiplicativeIdentity()
*( x, ::MultiplicativeIdentity ) = x
*( ::MultiplicativeIdentity, y ) = y

/( ::MultiplicativeIdentity, ::MultiplicativeIdentity ) = MultiplicativeIdentity()
/( x, ::MultiplicativeIdentity ) = x


const multiplicative_identity = MultiplicativeIdentity()

end # module
