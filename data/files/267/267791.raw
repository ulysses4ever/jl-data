# Author: Youngjun Kim, youngjun@stanford.edu
# Date: 04/02/2015

module UAVList_

export UAVList


using UAV_


UAVList = UAV[]


function UAV_common(uav::UAV)

    uav.nwaypoints = length(uav.waypoints)

    uav.velocity = 40.

    # GPS_INS, deadreckoning or radiolocation
    uav.localization = :GPS_INS

    # deadreckoning
    uav.IMU_acc_instability = 6.e-6
    uav.IMU_acc_VRW = 0.06
    uav.IMU_gyr_instability = 4.e-5
    uav.IMU_gyr_ARW = 0.75

    # radiolocation
    uav.rl_error_bound = 50.

end

function UAV1()

    uav = UAV()

    uav.start_loc = [100., 2500.]
    uav.end_loc = [4900., 3000.]

    uav.waypoints = Vector{Float64}[[2000., 2000.], [3600., 3000.]]

    UAV_common(uav)

    return uav
end


function UAV2()

    uav = UAV()

    uav.start_loc = [4000., 4900.]
    uav.end_loc = [1500., 100.]

    uav.waypoints = Vector{Float64}[[2000., 3000.]]

    UAV_common(uav)

    return uav
end


function UAV3()

    uav = UAV()

    uav.start_loc = [400., 4900.]
    uav.end_loc = [4900., 4000.]

    uav.waypoints = Vector{Float64}[[2700., 4200.]]

    UAV_common(uav)

    return uav
end


function UAV4()

    uav = UAV()

    uav.start_loc = [3200., 100.]
    uav.end_loc = [4400., 4900.]

    uav.waypoints = Vector{Float64}[[4400., 1800.], [3800., 3900.]]

    UAV_common(uav)

    return uav
end


function UAV5()

    uav = UAV()

    uav.start_loc = [4900., 2200.]
    uav.end_loc = [100., 900.]

    uav.waypoints = Vector{Float64}[[1600., 1200.]]

    UAV_common(uav)

    return uav
end


push!(UAVList, UAV1())
push!(UAVList, UAV2())
push!(UAVList, UAV3())
push!(UAVList, UAV4())
push!(UAVList, UAV5())


end


