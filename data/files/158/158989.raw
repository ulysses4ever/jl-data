include("parser.jl");
include("string_to_time.jl");
include("lecture.jl");

subjects = ["WTW 218", "WTW 211", "WTW 286", "PHY 255", "CMY 282"];

modules = get_lectures(subjects,"E");


timetables = Timetable[]

set_array = Array[]
checked_sets = Array[]

Monday = Lecture[]
Tuesday = Lecture[]
Wednesday = Lecture[]
Thursday = Lecture[]
Friday = Lecture[]
clash = false;
loopbreak = false;



for i=1:length(modules)
  for set in modules[i]
    if !isEmpty(set)
      sets = LectureSet[];
      push!(sets, set);
      for sets2 in modules
        if (sets2 != modules[i] && !(sets2 in checked_sets))

            for set2 in sets2
              if !isEmpty(set2)
                for test_set in sets
                  if isClash(set2, test_set)
                    clash = true;
                  else
                    continue;
                  end
                end
                if clash
                  continue;
                else
                  push!(sets, set2);

                  clash = false;
                  break;
                end

              else
                continue;
              end

            end

        else

        end
      end
      push!(set_array, sets);

    else
      continue;
    end
  end
end



for set in set_array
  if length(set) == length(subjects)
    for modules in set
      print(modules.lectures)
      print("\n\n")
    end
  else
    continue;
  end
  print("\n\n-------\n\n")
end
