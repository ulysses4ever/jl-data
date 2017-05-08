module GTD

using DataFrames
using SQLite
using LibCURL
using Base.Markdown
using DataStreams
using Lazy

#include("this.jl")
#include("that.jl")

export add_gtd_db, collect_stuff, show_stuff, process_inbox


# first step: create our database
function add_gtd_db(path::AbstractString, fname::AbstractString)
  cd(path)
  db = SQLite.DB(path * "/" * fname * ".db")
  try
    SQLite.execute!(db,
    """create table stuff (item varchar(140), notes varchar(140), time varchar(140), id varchar(36));""")
  finally
    return db
  end
end

function collect_stuff(db::SQLite.DB, item::AbstractString, notes::AbstractString = "")
  SQLite.execute!(db, """insert into stuff (item, notes, time, id) values ('"""
                  * item * "', '" * notes * "', '" * string(now()) * "', '"
                  * string(Base.Random.uuid4()) * "');")
end

function show_stuff(db::SQLite.DB)
  @>> """select * from stuff""" SQLite.query(db) DataFrame
end

function process_inbox(db::SQLite.DB)
  stuff = @>> """select * from stuff""" SQLite.query(db) DataFrame
  for i in 1:nrow(stuff)
    process_item(stuff[i,:])
  end
end

function process_item(stuff::DataFrame)
  @show stuff
  # is it actionable
    # yes
      # can be done under 2 min && do
      # requires multiple steps && project
      # else make action
        # can it be delegated? delegate
        # can it be postponed? postpone
    # no
      # is it someday/maybe
      # is it reference
end

#=
function process(item)
  if actionable
    process_actionable(item)
  else
    process_other(item)
  end
end

function process_actionable(item)
  if project
    create_project(item)
  else
    create_action(item)
  end
end

function process_other(item)
  if smdmb
    create_someday_maybe(item)
  elseif reference
    create_reference(item) # references must be tieable to projects
  end
end=#




  # end of module
end

