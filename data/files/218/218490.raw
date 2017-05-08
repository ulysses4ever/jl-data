function acceleration(time::Float64, pos::Vector{Float64})
    moon_pos = moon_position(time) # Get the moon's position at this time

    distance_from_earth = pos # Earth is at the origin
    distance_to_moon = pos - moon_pos # Distance between command module and moon
    mag_e = magnitude(distance_from_earth) # Get the magnitude of this vector
    mag_m = magnitude(distance_to_moon)
    return -G * (ME * distance_from_earth / mag_e^3 + MM * distance_to_moon / mag_m^3)
end

function update(me::Command_Module, time::Float64, h::Float64)
    acceleration0 = acceleration(time, me.position) # Get acceleration at current time
    velocityE = me.velocity + h * acceleration0 # Calculate Euler's velocity,
                                                # Accounting for the adaptive step size
    positionE = me.position + h * me.velocity   # Calculater Euler's position

    # Heun's method looks ahead to the next step and averages the two values
    velocityH = me.velocity + h * 0.5 * (acceleration0 + acceleration(time + h, positionE))
    positionH = me.position + h * 0.5 * (me.velocity + velocityH)

    # We will use the Heun's values
    me.velocity = velocityH
    me.position = positionH

    # Store these on the command_module so the simulation can access them
    me.positionH = positionH
    me.velocityH = velocityH
    me.positionE = positionE
    me.velocityE= velocityE

    me
end
