using IntervalTrees
using DataFrames

# FeatureTable:
#   Description can be any metadata e.g. it could note what each column means, or
#   describe what organism this is about, or any other key - value.
#

type FeatureTable
  description::Dict{ASCIIString,Any}
  dataframe::DataFrame
end

#  Feature:  An interval, point, possibly an area??
#    represented by a single row in a dataframe - it might have a start and a stop a seqid a name and so on.
type Feature
   feature::DataFrame
   function Feature(start,stop,region_id="REGION1"; args...)
       return DataFrame(region_id=region_id,start=start,stop=stop)
       # add in other columns
   end
end


# Features are features of something, this something define as "Region".
#
#  A region is any range of something, probably tied to a sequence often, such as
#  a gene (although that isn't tied necessarily to one set of coordinates)
#  or an entire chromosome
#
#  The Features type indexes Features by Region (i.e. a region_id such as chr).
#

#
# Features is for features that are indexed by a sequence_id
# SF.features["seq1"] or SF.features["chr1"]

type Features
  description::Dict{ASCIIString,Any}
  features::Dict{Any,Any}

  function Features(FT::FeatureTable; start_field = :start, stop_field = :stop, region_id_field = :chr)
     region_features_dict = Dict()
     DF = FT.dataframe
     add_dataframe_to_interval_tree(DF,start_field=start_field,stop_field=stop_field,region_id_field=region_id_field)
     desc = FT.description
     if ! haskey(desc, "organism")
        desc["organism"] = ""  #add in organism default if it doesnt exist
     end
     new( desc, region_features_dict )
  end

  function Features(DF::DataFrame; start_field = :start, stop_field = :stop, region_id_field = :chr, regions=false )
    desc = Dict{ASCIIString,Any}()
    if regions
        region_features_dict = add_dataframe_to_interval_tree(DF,start_field=:notanything,stop_field=:notanything,region_id_field=region_id_field)
        add_dataframe_to_description(DF,description=desc, region_id_field=region_id_field)
        desc["organism"]=""
     else
       region_features_dict = add_dataframe_to_interval_tree(DF,start_field=start_field,stop_field=stop_field,region_id_field=region_id_field)
       desc["organism"]=""
     end
     new( desc, region_features_dict )
  end
end

function add_dataframe_to_description(DF::DataFrame; description=Dict{ASCIIString,Any}(),region_id_field = :chr)
    nrows = size(DF,1)
        for row = 1:nrows
          feature = DF[row, :]
          if( haskey(feature, region_id_field ))
             region_id  =  feature[region_id_field][1]
          else
             region_id = "REGION1"
          end
          if ! haskey( description, region_id )
              description[region_id] = feature
          else
              error("Regions must unique - region_id $region_id occurs at least twice")
          end
     end
    return description
end

function add_dataframe_to_interval_tree(DF::DataFrame; region_features_dict=Dict(), start_field = :start, stop_field = :stop, region_id_field = :chr )
        #region_features_dict = Dict()
        nrows = size(DF,1)
        (start_nothing_count,stop_nothing_count) = (0,0)
        for row = 1:nrows
          feature = DF[row, :]

          if(haskey( feature,start_field ) )
             start = feature[start_field][1]
          else
             start_nothing_count +=1
             start = nothing
          end

          if(haskey(feature, stop_field ))
              stop  = feature[stop_field][1]
          else
             stop_nothing_count +=1
             stop = nothing
          end

          if( haskey(feature, :name) )
            feature_id = feature[:name][1]
          else
            feature_id = "FEATURE$row"
          end

          if( haskey(feature, region_id_field ))
             region_id  =  feature[region_id_field][1]
          else
             region_id = "REGION1"
          end
          insertintervals!(region_features_dict, region_id, start, stop,feature )
     end
     if stop_nothing_count > 0 || start_nothing_count > 0
         warn( "Start pos set to nothing: $start_nothing_count. Stop pos set to nothing $stop_nothing_count")
     end
     return region_features_dict
end

# takes one set of features and adds them to an already existing
# container of features
function insertfeatures!( target::Features, features::Features; start_field = :start, stop_field = :stop, region_id_field = :chr )
end

function add_dataframe_to_features!(target::Features, DF::DataFrame; start_field = :start, stop_field = :stop, region_id_field = :chr)
    add_dataframe_to_interval_tree( DF, region_features_dict = target.features, start_field=start_field, stop_field=stop_field,region_id_field=region_id_field )
end

function insertintervals!( region_features_dict, region_id, start, stop, value::DataFrame)
    if haskey(region_features_dict, region_id)
        interval_tree = region_features_dict[region_id]
        if start != nothing && stop != nothing
             interval_tree[(start,stop)] = value
        end
        #interval_tree[(start,stop)] = value
        #println("inserted $start $stop")
    else
        try
           interval_tree = IntervalTree{Int32,DataFrame}()
           if start != nothing && stop != nothing
             interval_tree[(start,stop)] = value
           end
           region_features_dict[region_id]  = interval_tree
        catch e
           println("Exception chr: $region_id, start: $start, stop: $stop, value $value ")
           println( join( [  "Exception, ", typeof(region_id), " ", typeof(start), " ", typeof(stop) ], "\t" ) )
           error(e)
        end
    end
end

# Further thoughts
# ----------------
# A feature is a region of some size
# and it could have multiple regions
# there might also be feature_type - i.e. gene? gene_non_coding? - it gets all ontological then.
#
# Are Regions just Features or vice versa
# Is it necessary to make the distinction
