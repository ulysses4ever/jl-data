
# constants for use with Float64 values

const PRECISION         =    53
const BIAS              =  1023
const EXPO_MAX          =  1023
const EXPO_MIN          = -1074
const EXPO_LEAST_NORMAL = -1022
const SIGN_MASK         =  0x7ff0000000000000

const SPLITTER          =  134217729.0

# constant vector used int scaledSqureRoot
const sqrtGammaToM = [ 
    5.26013590154837350724098988288012866555033980282317e210, # gamma^-2/2 = (2^-350)^-2 
    2.29349861599007151161082089530208694079656498916828e105, # gamma^-1/2 = (2^-350)^-1
    1.0,                                                      # gamma^0/2  = (2^-350)^0
    4.3601508761683463371878950054372442606045150559341e-106, # gamma^1/2  = (2^-350)^1
    1.9010915662951598235150724058351031092648712063735e-211  # gamma^2/2  = (2^-350)^2
];

# constants used in faithfulFinal()  
const bound1    = 3.08469742733169167070816004443201143863168634177267e-179  # beta_lo^2 / eps^3 = 2^-593
const bound2    = 1.4396524142538228424993723224595141948383030778566e+163   # beta_hi^2 * eps^2 = 2^542
const gamma     = 1.9010915662951598235150724058351031092648712063735e-211   # gamma             = 2^-700
const gammaToM1 = 5.26013590154837350724098988288012866555033980282317e+210  # gamma^-1          = 2^700  

# constants used in faithfulNorm()
const SignBitFilter = 0x7fffffffffffffff  # mask that strips the sign of a Float64
const boundA  = 0x5450000000000000 # 2^+326 bound
const boundB  = 0x2890000000000000 # 2^-374 bound
const twoM700 = 0x1430000000000000 # 2^-700 scaling factor
const two700  = 0x6bb0000000000000 # 2^700 scaling factor


