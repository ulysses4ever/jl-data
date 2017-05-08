import FITSIO

function get_fits_members(fits_name)
include("/Users/alex/CODES/Julia_Custom_jl/alex/src/remove_char.jl")


# fits_name = "/Users/alex/Desktop/make_pros/old/completeness_test_results.fits"

  # open the fits_file
fits_data=FITSIO.fits_open_data(fits_name)

  # get the header information
fits_total_header=FITSIO.fits_hdr2str(fits_data)
  # split the header into individual strings
fits_header_items = split(fits_total_header)

  # search for NAXIS2, TFIELDS and GCOUNT in the header
  # in order to get the rowsxcolumns of the data
tfields = 0.0
naxis2 = 0.0
gcount = 0.0
  for i in 1:size(fits_header_items,1)
      # get TFIELDS
       if fits_header_items[i] == "TFIELDS"
            tfields = float(fits_header_items[i + 2])
      end

      # get NAXIS2
      if fits_header_items[i] == "NAXIS2"
        naxis2 = float(fits_header_items[i + 2])
      end

      # get gcount
      if fits_header_items[i] == "GCOUNT"
        gcount = float(fits_header_items[i + 2])
      end

  end

##########################################################################
#### get and create each TFIELD string names                  ############
#### which are the structure member names                     ############
#### to be used in the definition of the return type          ############
##########################################################################
                                                              ############
  # ttype_names will hold the name of each ttype              ############
ttype_names=Array(String, int64(tfields))                     ############
  # ttype_array_call will hold the  TTYPE id'                 ############
ttype_array_call=Array(String, int64(tfields))                ############
                                                              ############
    # populate ttype_array_call with the ttype identifiers    ############
  for i in 1:tfields                                          ############
    ttype_array_call[i] = string("TTYPE", string(int64(i)))   ############
  end                                                         ############
                                                              ############
    # search for all TTYPE's as populated in ttype_array_call       ######
    # and pass them to ttype_names                            ############
  for i in 1:size(fits_header_items,1)                        ############
    # i cycles through all individual header items            ############
      for x in 1:tfields                                      ############
        # x cycles trhough ttype_array_call to search for each TTYPE   ###
          if fits_header_items[i] == ttype_array_call[x]      ############
            ttype_names[x]=fits_header_items[i+2]             ############
          end                                                 ############
      end                                                     ############
  end                                                         ############
                                                              ############
##########################################################################

##########################################################################
#### get and create each TFORM string names                   ############
#### which are the structure member names                     ############
#### to be used in the definition of the return type          ############
##########################################################################
                                                              ############
  # tform_names will hold the name of each tform              ############
tform_names=Array(String, int64(tfields))                     ############
  # tform_array_call will hold the  tform id'                 ############
tform_array_call=Array(String, int64(tfields))                ############
                                                              ############
    # populate tform_array_call with the tform identifiers    ############
  for i in 1:tfields                                          ############
    tform_array_call[i] = string("TFORM", string(int64(i)))   ############
  end                                                         ############
                                                              ############
    # search for all tform's as populated in tform_array_call       ######
    # and pass them to tform_names                            ############
  for i in 1:size(fits_header_items,1)                        ############
    # i cycles through all individual header items            ############
      for x in 1:tfields                                      ############
        # x cycles trhough tform_array_call to search for each tform   ###
          if fits_header_items[i] == tform_array_call[x]      ############
            tform_names[x]=fits_header_items[i+2]             ############
          end                                                 ############
      end                                                     ############
  end                                                         ############
                                                              ############
##########################################################################

##########################################################################
####                                                          ############
####    the problem now is that tform_names and ttype_names   ############
####    could be "polluted" by "'"                            ############
####                                                          ############
##########################################################################
                                                              ############
tform_names_final=Array(String, int64(tfields))               ############
ttype_names_final=Array(String, int64(tfields))               ############
                                                              ############
                                                              ############
  for i in 1:tfields                                          ############
    tform_names_final[i] = remove_char(tform_names[i], "'")   ############
    ttype_names_final[i] = remove_char(ttype_names[i], "'")   ############
  end                                                         ############
                                                              ############
##########################################################################



##########################################################################
####                                                          ############
####     create a custom Dict to return                       ############
####     as an object                                         ############
####                                                          ############
##########################################################################
                                                              ############
return_dictionary = Dict{Symbol,Any}()                        ############
return_dictionary[:tform_names] = tform_names_final           ############
return_dictionary[:ttype_names] = ttype_names_final           ############
return_dictionary[:tfields] = tfields                         ############
return_dictionary[:naxis2] = naxis2                           ############
return_dictionary[:gcount] = gcount                           ############
                                                              ############
return return_dictionary                                      ############
##########################################################################



end
