include("parser.jl");
include("string_to_time.jl");
include("lecture.jl");

subjects = ["CMY 282", "WTW 211", "WTW 286", "WTW 218", "PHY 255"];

modules = get_lectures(subjects,"E");


timetables = Set{Timetable}({})

set_array = Array[]
checked_sets = Array[]

Monday = Set{Lecture}({})
Tuesday = Set{Lecture}({})
Wednesday = Set{Lecture}({})
Thursday = Set{Lecture}({})
Friday = Set{Lecture}({})
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
      push!(set_array, sets)
    else
      continue;
    end
  end
end

# Can fix duplicates by creating timetable objects
# timetable = Timetable(Monday, Tuesday...)
for set in set_array
  if length(set) == length(subjects)
    for modules in set
      for lecture in modules.lectures
        if lecture.day == "Monday"
          push!(Monday, lecture);
        elseif lecture.day == "Tuesday"
          push!(Tuesday, lecture);
        elseif lecture.day == "Wednesday"
          push!(Wednesday, lecture);
        elseif lecture.day == "Thursday"
          push!(Thursday, lecture);
        elseif lecture.day == "Friday"
          push!(Friday, lecture);
        end
      end
    end
  end

  timetable = Timetable(Monday, Tuesday, Wednesday, Thursday, Friday);
  push!(timetables, timetable)
  Monday = Set{Lecture}({})
  Tuesday = Set{Lecture}({})
  Wednesday = Set{Lecture}({})
  Thursday = Set{Lecture}({})
  Friday = Set{Lecture}({})
end

for table in timetables
  print("Monday\n")
  for lecture in table.Monday
    print(lecture.subject)
    print(" - ")
    print(lecture.start_time)
    print("\n")
  end
  print("\n\n")
  print("Tuesday\n")
  for lecture in table.Tuesday
    print(lecture.subject)
    print(" - ")
    print(lecture.start_time)
    print("\n")
  end
  print("\n\n")
  print("Wenesday\n")
  for lecture in table.Wednesday
    print(lecture.subject)
    print(" - ")
    print(lecture.start_time)
    print("\n")
  end
  print("\n\n")
  print("Thursday\n")
  for lecture in table.Thursday
    print(lecture.subject)
    print(" - ")
    print(lecture.start_time)
    print("\n")
  end
  print("\n\n")
  print("Friday\n")
  for lecture in table.Friday
    print(lecture.subject)
    print(" - ")
    print(lecture.start_time)
    print("\n")
  end
  print("\n\n")
  print("\n\n\n-------\n\n\n")
end
