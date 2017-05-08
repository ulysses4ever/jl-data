include(“path/filename.jl”);
function integrate_euler!(state::Array,dt::Float64, duration::Float64)
    n_time_intervals = duration/dt;
    state_time = Array(Any,2);
    state_time[1] = state;
    state_time[2] = 0.;
    for i = 1:n_time_intervals
        oneStep(state,dt);
        state_time[2] += dt;
    end
    return state_time;
end

function oneStep(state::Array,dt::Float64)
        GM = 1;
        r = sqrt(state[1].^2 + state[2].^2);
        x_temp = state[1] + dt*state[3]/2;
        y_temp = state[2] + dt*state[4]/2;
        r_temp = sqrt(x_temp.^2 + y_temp.^2);
        vx_temp = state[3] + dt*(-GM*state[1]/r_temp.^3);
        vy_temp = state[4] + dt*(-GM*state[2]/r_temp.^3);
        state[3] += dt*(-GM*x_temp/r_temp.^3);
        state[4] += dt*(-GM*y_temp/r_temp.^3);
        state[1] = x_temp + dt*vx_temp/2;
        state[2] = y_temp + dt*vy_temp/2;
end

#integrate_euler!({1,0,0,1},pi/100,6*pi)
@time(integrate_euler!({1,0,0,1},pi/100,4.5*10.^9*2*pi))

