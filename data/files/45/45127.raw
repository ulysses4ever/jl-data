module GCloud

using JSON

import Base: show, addprocs

export external_ip, instances, create_instance, delete_instance, instance

function input(prompt::String="")
    print(prompt)
    chomp(readline())
end

## ------------- ##
#- Machine Types -#
## ------------- ##

## NOTE: This data was taken from https://cloud.google.com/compute/pricing
#        on 2014-10-14 00:50:09

immutable MachineType
    configuration::String
    virtual_cores::Int
    memory::Real
    GCEU::Union(Real, String)
    local_disk::Real
    price_per_hour::Real
end

function show(io::IO, mt::MachineType)
    kind = split(mt.configuration, '-')[2]
    msg = "$kind machine ($(mt.virtual_cores) cores, $(mt.memory) GB memory, "
    msg *= "\$$(mt.price_per_hour)/hr.)"
    print(io, msg)
end

const machine_types = Dict{String, MachineType}()

# standard
machine_types["n1-standard-1"] = MachineType("n1-standard-1", 1, 3.75, 2.75, 0,
                                             0.063)
machine_types["n1-standard-2"] = MachineType("n1-standard-2", 2, 7.50, 5.50, 0,
                                             0.126)
machine_types["n1-standard-8"] = MachineType("n1-standard-8", 8, 30, 22, 0,
                                             0.504)
machine_types["n1-standard-4"] = MachineType("n1-standard-4", 4, 15, 11, 0,
                                             0.252)
machine_types["n1-standard-16"] = MachineType("n1-standard-16", 16, 60, 44, 0,
                                              1.008)

# bursting
machine_types["f1-micro"] = MachineType("f1-micro", 1, 0.60,
                                        "Shared CPU, not guaranteed", 0, 0.012)
machine_types["g1-small"] = MachineType("g1-small", 1, 1.70, 1.38, 0, 0.032)

# high-memory
machine_types["n1-highmem-2"] = MachineType("n1-highmem-2", 2, 13, 5.50, 0,
                                            0.148)
machine_types["n1-highmem-4"] = MachineType("n1-highmem-4", 4, 26, 11, 0,
                                            0.296)
machine_types["n1-highmem-8"] = MachineType("n1-highmem-8", 8, 52, 22, 0,
                                            0.592)
machine_types["n1-highmem-16"] = MachineType("n1-highmem-16", 16, 104, 44, 0,
                                             1.184)

# high-cpu
machine_types["n1-highcpu-2"] = MachineType("n1-highcpu-2", 2, 1.80,  5.50, 0,
                                            0.080)
machine_types["n1-highcpu-4"] = MachineType("n1-highcpu-4", 4, 3.60, 11, 0,
                                            0.160)
machine_types["n1-highcpu-8"] = MachineType("n1-highcpu-8", 8, 7.20, 22, 0,
                                            0.320)
machine_types["n1-highcpu-16"] = MachineType("n1-highcpu-16", 16, 14.40, 44, 0,
                                             0.640)


## --------- ##
#- Instances -#
## --------- ##

immutable Instance
    name::String
    zone::String
    kind::MachineType
    external_ip::String
    status::String
end

function show(io::IO, i::Instance)
    kind = split(i.kind.configuration, '-')[2]
    msg = "GCloud compute Instance\n"
    msg *= "  * name: $(i.name)\n"
    msg *= "  * zone: $(i.zone)\n"
    msg *= "  * machine type: $(i.kind)\n"
    msg *= "  * external ip address: $(i.external_ip)\n"
    msg *= "  * status: $(i.status)"
    print(io, msg)
end


function instances()
    data = JSON.parse(readchomp(`gcloud compute instances list --format json`))

    out = Array(Instance, length(data))
    for (i, machine) in enumerate(data)
        out[i] = Instance(machine["name"],
                          machine["zone"],
                          machine_types[machine["machineType"]],
                          external_ip(machine),
                          machine["status"])
    end
    return out
end


function instance(name::String)
    all_instances = instances()

    for i in all_instances
        if i.name == name
            return i
        end
    end

    error("Instance with name $name not found")
end

function create_instance()

    name = input("Instance name: ")
    # for now let google handle the rest with their own menus (will just have
    # to pick zone)
    run(`gcloud compute instances create $name`)
end

function create_instance(name::String,
                         m_type::MachineType,
                         zone::String;
                         options...)
    # Parse options

    opts1 = isempty(options) ? "" :
                    join(map(x->"--$(x[1]) $(x[2])", options), " ")
    opts2 = isempty(unary_options) ? "" : join(unary_options, " ")
    opts = join(Any[opts1, opts2], " ")

    # construct command
    cmd = `gcloud compute instances create $name --zone $zone
           --machine-type $(m_type.configuration)
           --network "default"
           --maintenance-policy "MIGRATE"
           --scopes 'https://www.googleapis.com/auth/devstorage.read_only'
           $opts
           `

    return cmd
    # run command
    # run(cmd)

    # return instance(name)
end

function create_instance(name::String,
                         m_type::String,
                         zone::String,
                         project::String,
                         image::String)
    # construct command
    cmd = `gcloud compute instances create $name --zone $zone
           --machine-type $m_type
           --network 'default'
           --maintenance-policy 'MIGRATE'
           --scopes 'https://www.googleapis.com/auth/devstorage.read_only'
           --image $image
           --project $project
           `
    # run command
    run(cmd)

    return instance(name)
end


function create_instance{T <: String}(name::String,
                                      m_type::String,
                                      zone::String,
                                      options::Dict{T, T}=Dict{T, T}(),
                                      unary_options::Array{T}=T[])
    m = machine_types[m_type]
    return create_instance(name, m, zone, options, unary_options)
end


delete_instance(name::String) = delete(filter(x->x.name==name, instances())[1])

function delete(instance::Instance)
    run(`gcloud compute instances delete $(instance.name)
         --zone $(instance.zone)`)
end


# accepts machine dict from parsed JSON
external_ip(d::Dict) = d["networkInterfaces"][1]["accessConfigs"][1]["natIP"]

external_ip(i::Instance) = i.external_ip

function external_ip(name::String)
    data = JSON.parse(readchomp(`gcloud compute instances list --format json`))

    # filter data to find data for instance with given name
    data = filter(x->x["name"] == name, data)

    if isempty(data)
        throw(ArgumentError("no instance with name: $name"))
    end

    data[1]["networkInterfaces"][1]["accessConfigs"][1]["natIP"]
end


function addprocs(i::Instance, dir::String,
                  username::String=readchomp(`whoami`); n::Int=1)
    ip = external_ip(i)
    # for some reason I have to do it in a loop or ssh borks with high n
    for i=1:n
        addprocs(["$(username)@$(ip)"], tunnel=true, dir=dir)
    end
    nothing
end

## ------- ##
#- Storage -#
## ------- ##

# TODO: work with storage


end # module
