#  this function takes in a fits_name and returns
#  a dictionary with the exact same member names.

# TO FINISH:   Implement gcount loop to create multi_dimensional
#              return dict objec.
#              multi_D_dict = fill(return_dictionary, gcount_value)
#
#              Loop through return types as well to define the return type.
#              Currently, everything is Float32.
#
#              Figure out how to dereference a PyObject chararry in order
#              to pass string arrays.
#              It might be a PyCall issue.
#
#
# TEST CASE is 1D
# fits_name = "/Users/alex/Desktop/make_pros/old/completeness_test_results.fits"
# fits_name = "/Users/alex/Desktop/final_files/s0927/s0927_analysis.fits"
import FITSIO


function open_fits(fits_name)


include("/Users/alex/CODES/Julia_Custom_jl/alex/src/get_fits_members.jl")
include("/Users/alex/CODES/Julia_Custom_jl/alex/src/remove_char.jl")



# open the PyObject
data=FITSIO.fits_open_data(fits_name)

# get the fits members
members=get_fits_members(fits_name)

# pass the ttype_names to itterate over
# in order to create the custom return object
iters = members[:ttype_names]

#######################################################################################################
#######################################################################################################
#                                                                                          ############
#                                                                                          ############
#                                   make return object                                     ############
#                                                                                          ############
#                                                                                          ############
#######################################################################################################
#######################################################################################################
                   new_dict = Dict{Symbol,Any}()                                           ############
                        println("making new dictionary with members:")                     ############
                                                                                           ############
                                                                                           ############
                        # create new dictionary with each field empty                      ############
                        for sym in iters                                                   ############
                        println(sym)                                                       ############

                        # temp=Array(Float64, 6898)
                        # fits_read_col(data, Float32, 11, 1, 1, temp)
                        fits_read_col(data, String, 11, 1, 1, temp)

# function fits_read_col{T}(f::FITSFile, ::Type{T}, colnum::Int64, firstrow::Int64, firstelem::Int64, data::Array{T})


                         new_dict[symbol(sym)] = temp                                      ############


                        end                                                                ############
#######################################################################################################
#######################################################################################################

return new_dict





end







