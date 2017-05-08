#!/usr/bin/env julia

# This program is used to calculate the Lennard-Jones and Coulomb Energy for a series
# of waters per frame of a trajectory. For each frame the LJ and E_c are written to a file
# water_analysis.out and water_sum.out
# This program requires the relevant cluster.000(index).pdb files from HSA.
# Cluster files must be named so that nearest neighbor clusters are listed in order.
# From the .prmtop file : 
# LJ parameters for oxygen-oxygen interactions -> A = 5.81935564E5 ; B = 5.94825035E2
# Charges of Oxygen and Hydrogen = -1.5197E1 and 7.598699 respectively


require("argparse") ## argparse approx 4 secs to runtime
using ArgParse

z = ArgParseSettings()
@add_arg_table z begin
    "-d"
       help = "O-O cutoff distance for H-bond [m]"
       default = 3.5
    "-e"
       help = "H-bond cutoff energy in kcal/mol"
       default = -1.5
    "-a"
       help = "H-bond cutoff angle"
       default = 30
end

parsed_args = parse_args(ARGS,z)

cutoff_dist = parsed_args["d"]
cutoff_energy = parsed_args["e"]
cutoff_angle = parsed_args["a"]

#=
cutoff_dist = 3.5
cutoff_energy = -1.5
cutoff_angle = 30
=#
num_waters = 5


type Atom
    name::String
    x::Float64
    y::Float64
    z::Float64
    coords::Array{Float64,2}
    frame_id::String
    
end

type Water
    atoms::Array{Atom}
    frame_id::String
end

type Frame
    waters::Array{Water}
    frame_id::String
end

type WaterFile
    filename::String
    fd::IOStream
    read_ahead_water::Any
end

type System
    water_files::Array{WaterFile}
end

function add_water_file(ss,file)
    wf = WaterFile(file,open(file),None)
    for i = [1:4]
        if eof(wf.fd)
            println("Unexpected EOF:", file)
            exit(1)
        else
            readline(wf.fd)
        end
    end
    push!(ss.water_files,wf)
end

function read_next_water(wf)
    if eof(wf.fd)
        return None
    end


    if wf.read_ahead_water != None
        raw = wf.read_ahead_water
        wf.read_ahead_water = None
        return raw
    end

    atoms = Any []
    for i = [1:3]
        if eof(wf.fd)
            println("Unexpected EOF during atom read:", wf.filename)
            exit(1)
        end
        line = readline(wf.fd)            
        fields = split(line[33:55])
        name = line[14:15]
        x = float(fields[1])
        y = float(fields[2])
        z = float(fields[3])
        coords = zeros(1,3)
        coords[1] = x
        coords[2] = y
        coords[3] = z
        frame_id = line[56:61]
        a = Atom(name, x, y, z, coords, frame_id)
        push!(atoms,a)
    end

    if atoms[1].frame_id == atoms[2].frame_id && atoms[1].frame_id == atoms[3].frame_id
        w = Water(atoms,atoms[1].frame_id)
    else
        println("ATOM FRAME IDs DO NOT MATCH:", atoms)
        exit(1)
    end
end

function compare_pair(x,y)
    (wf_x,w_x) = x
    (wf_y,w_y) = y
    w_x.frame_id < w_y.frame_id
end

function read_next_frame(ss)
    waters = Any []
    for wf in ss.water_files
        w = read_next_water(wf)
        if w != None
            push!(waters,(wf,w))
        else
            println("read_next_water == None for ", wf.filename)            
        end
    end

    if waters == []
        return(None)
    else
        new_waters = Any []
        waters = sort(waters,1,lt=compare_pair)
        (wf_1,w_1) = waters[1]
        push!(new_waters,w_1)
        if length(waters) > 1          
            for (wf,w) in waters[2:end]
                if w.frame_id == w_1.frame_id
                    push!(new_waters,w)
                else
                    wf.read_ahead_water = w
                end
            end
        end
        frame = Frame(new_waters,w_1.frame_id)
        return(frame)
    end
end

function system_create()
    ss = System(Any [])
    file_list = readdir()
    for file in file_list
        if contains(file,"cluster.")
            add_water_file(ss,file)
        end
    end
    return(ss)
end

function is_DE(inv_cos)
    if inv_cos > 1
        return 1
    elseif inv_cos < -1
        return -1
    else
        return inv_cos
    end
end


function hb_donor(angles,h_ang)

    if (angles[1] <= h_ang || angles[2] <= h_ang) && (angles[3] <= h_ang || angles[4] <= h_ang)
        "not hbonded"
    elseif angles[1] <= h_ang || angles[2] <= h_ang 
        "water1" 
    else
        "water2"
    end

end


function is_hbond(w1,w2,h_ang)
    angles = Float64[]
    OO = vec(w2.atoms[1].coords - w1.atoms[1].coords)
    OO2 = vec(w1.atoms[1].coords - w2.atoms[1].coords)
    R = sqrt(dot(OO,OO))
    
    OH1 = vec(w1.atoms[2].coords - w1.atoms[1].coords)
    r1 = sqrt(dot(OH1,OH1))
    
    OH2 = vec(w1.atoms[3].coords - w1.atoms[1].coords)
    r2 = sqrt(dot(OH2,OH2))
    
    OH3 = vec(w2.atoms[2].coords - w2.atoms[1].coords)
    r3 = sqrt(dot(OH3,OH3))
    
    OH4 = vec(w2.atoms[3].coords - w2.atoms[1].coords)
    r4 = sqrt(dot(OH4,OH4))
    
    inv_cos1 = dot(OO,OH1)/(R*r1)
    inv_cos1 = is_DE(inv_cos1)
    angle1 = rad2deg(acos(inv_cos1))
    push!(angles,angle1)

    inv_cos2 = dot(OO,OH2)/(R*r2)
    inv_cos2 = is_DE(inv_cos2) 
    angle2 = rad2deg(acos(inv_cos2))
    push!(angles,angle2)

    inv_cos3 = dot(OO2,OH3)/(R*r3)
    inv_cos3 = is_DE(inv_cos3)
    angle3 = rad2deg(acos(inv_cos3))
    push!(angles,angle3)
    
    inv_cos4 = dot(OO2,OH4)/(R*r1)
    inv_cos4 = is_DE(inv_cos4)
    angle4 = rad2deg(acos(inv_cos4))
    push!(angles,angle4)


    is_donor = 
        if any(i->(i <= h_ang),angles)  
            hb_donor(angles,h_ang) 
        else
            "not hbonded"
        end

    h_bond = 
        if is_donor == "not hbonded" 
            false
        else
            true
        end

    return h_bond, is_donor
end



function calc_energy(water1,water2,dist,cutoff_energy,cutoff_angle)
    A = 5.81935564E5 # LJ parameter 
    B = 5.94825035E2 # LJ parameter
    q = [-15.197,7.598699,7.598699] # Charges from AMBER prmtop (O, H, H) 
    sum_energy = 0
    h_bond = Any[]
    values = Any[]
  
    for i = [1:3]
        for j = [1:3]
            dvec = water1.atoms[i].coords - water2.atoms[j].coords
            dvec = vec(dvec)
            r = sqrt(dot(dvec,dvec))
            energy = (q[i]*q[j])/r ## Coulomb calculation
            
            sum_energy += energy
            
            if i == 1 && j == 1 ## Lennard Jones Calculation 
                r6 = r^6
                r12 = (r6)^2
                LJ = (A/r12) - (B/r6)
                LJ = round(LJ,5)
                push!(values,LJ)
                if r <= dist
                    push!(h_bond,dvec)
                
                end
            end
        end
    end
    coulomb = sum_energy
    tot_energy = (coulomb + values[1])/2

    H_bond, is_donor =
        if length(h_bond) != 0 && tot_energy <= cutoff_energy
            is_hbond(water1,water2,cutoff_angle)
        else
            false, "not hbonded"
        end

    return tot_energy, H_bond, is_donor 
end


function write_it(f,frame,energy,num_h,allh,fourh)
    @printf(f,"%s ",frame)    
    for i = [1:length(energy)]
        @printf(f,"%0.5f  ", energy[i])
    end
    @printf(f, "%d   %s   %s\n",num_h, string(allh),string(fourh))
 
end


function calc_stats(tot_all_occ,total_frames,sums,all_PW,four_PW)

    frac_all_occ = tot_all_occ/total_frames
    frac_PW = all_PW/tot_all_occ
    frac_sm_PW = four_PW/tot_all_occ
    avgE = sums/tot_all_occ
    return frac_all_occ, frac_PW, frac_sm_PW, avgE 
end


function write_summary(f,frac_all_occ, frac_PW, frac_sm_PW, avgE,PW_frames)

    println(f, "Summary: ")
    println(f, "Fraction all occupied =",frac_all_occ)
    println(f, "Fraction complete proton wire = ", frac_PW)
    println(f, "Fraction 4-H20 proton wire = ",frac_sm_PW)
    for i =[1:length(avgE)-1]
        println(f,"<E",string(i),"> = ",avgE[i])
    end
    println(f, "Average number of H-bonds when all occupied = ", avgE[length(avgE)]) 
    println(f, "Frames with complete Proton Wires: ")
    L = length(PW_frames)
    for i = [1:L]
        println(f, PW_frames[i])
    end
end


####################### Main ############################

ss = system_create()

output1 = open("water_analysis.out", "w")

println(output1,"Frame# Energies between pairs #hbonds, whether it has a full PW, and partial PW")

total_frames = tot_all_occ = all_PW = four_PW = 0

PW_frames = String[]

sums = zeros(num_waters,1)


while (frame = read_next_frame(ss)) != None
    total_frames += 1

    if length(frame.waters) == num_waters
        tot_all_occ += 1
        energy = Any[]
        hbonded = Any[]
        donor = Any[]

        for i = [1:(num_waters -1)]
            tot_energy,H_bond,is_donor = calc_energy(frame.waters[i],frame.waters[i+1],cutoff_dist,cutoff_energy,cutoff_angle)
            
            push!(energy, tot_energy)
            push!(hbonded,H_bond)
            push!(donor,is_donor)
        end


        if all(i->(i=="water1"),donor) || all(i->(i=="water2"),donor)
            full_wire = true
            all_PW += 1
            push!(PW_frames,frame.frame_id)
        else
            full_wire = false
        end
        # Next if block is situational and requires tweaking for different systems
        if donor[1] != "not hbonded" && donor[2] == donor[1] && donor[3] == donor[2]  
            four = true
            four_PW += 1
        else
            four = false
        end
        #
        num_h = 0
        for item in hbonded
            if item == true
                num_h +=1
            end
        end
        
        write_it(output1,frame.frame_id,energy,num_h,full_wire,four)

        for i = [1:(num_waters-1)]
            sums[i] += energy[i]
        end
        sums[num_waters] += num_h

    end

end

close(output1)

frac_all_occ, frac_PW, frac_sm_PW, avgE = calc_stats(tot_all_occ,total_frames,sums,all_PW,four_PW)

output2 = open("water_sum.out", "w")

write_summary(output2,frac_all_occ, frac_PW, frac_sm_PW, avgE,PW_frames)

close(output2)



