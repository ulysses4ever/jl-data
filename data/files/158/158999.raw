include("lecture.jl");



function read_and_concat(f::IOStream)
  filestring = "";
  for line in eachline(f)
    filestring = string(filestring, line);
  end
  return filestring;
end

function get_lectures(subjects::Array, language_preference)

  possible_sets = Array[];

  for subject in subjects

    filestring = open(read_and_concat, "HatfieldCampus.html");
    language_re = Regex(join(["\/", language_preference, "\/"]));

    subject_re = Regex(join(["<tr><td>\\d\\/",subject, "\\/([A-Z]|:|[a-z]|\\d|\\/|(<\\/?td>)|(<\\/tr>)|\\s|\\-)+"]));

    lecture_info = String[];
    groups = String[];
    lecture_sets = LectureSet[];

    if ismatch(subject_re, filestring)
      result = matchall(subject_re, filestring);
      for string in result
        current_group = match(r"(?<=\/G)\d{2}(?=\/)", string).match;
        if current_group in groups
          continue;
        else
          push!(groups, current_group);
          new_set = LectureSet(subject, current_group, Lecture[]);
          push!(lecture_sets, new_set);
        end
      end

      for string in result
        if (ismatch(r"\/L\d</td>", string) && ismatch(language_re, string))# Indicates a lecture
          current_group = match(r"(?<=\/G)\d{2}(?=\/)", string).match;
          language = match(r"(?<=\/G\d{2}\/)[A-Z](?=\/)", string).match;
          group = match(r"(?<=\/G)\d{2}(?=\/)", string).match;
          day = match(r"(?<=<td>)[A-Z][a-z]+(?=<\/td>)", string).match;
          lecture_number = match(r"(?<=\/L)\d(?=</td>)", string).match;
          start_time = match(r"(?<=<td>)\d{2}:\d{2}:\d{2}\s[PAM]{2}(?=</td>)", string).match;
          end_time = match(r"(?<=<td>)\d{2}:\d{2}:\d{2}\s[PAM]{2}(?=<\/td><td>[A-Z])", string).match;
          venue = match(r"(?<=(<td>\d{2}:\d{2}:\d{2}\s[PAM]{2}</td>){2}<td>).+(?=</td></tr>)", string).match;
          lecture = Lecture(subject, group, day, start_time, end_time, venue, language, lecture_number);

          for set in lecture_sets
            if group == set.group
              push!(set.lectures, lecture);
            else
              continue
            end
          end
        else

            if (ismatch(r"\/L\d</td>", string) && ismatch(r"\/B\/", string))# Indicates a lecture
              language = match(r"(?<=\/G\d{2}\/)[A-Z](?=\/)", string).match;
              group = match(r"(?<=\/G)\d{2}(?=\/)", string).match;
              day = match(r"(?<=<td>)[A-Z][a-z]+(?=<\/td>)", string).match;
              lecture_number = match(r"(?<=\/L)\d(?=</td>)", string).match;
              start_time = match(r"(?<=<td>)\d{2}:\d{2}:\d{2}\s[PAM]{2}(?=</td>)", string).match;
              end_time = match(r"(?<=<td>)\d{2}:\d{2}:\d{2}\s[PAM]{2}(?=<\/td><td>[A-Z])", string).match;
              venue = match(r"(?<=(<td>\d{2}:\d{2}:\d{2}\s[PAM]{2}</td>){2}<td>).+(?=</td></tr>)", string).match;
              lecture = Lecture(subject, group, day, start_time, end_time, venue, language, lecture_number);

              for set in lecture_sets
                if group == set.group
                  push!(set.lectures, lecture);
                else
                  continue
                end
              end

            else
              continue
            end
        end
      end

    if ( length(lecture_sets) == 0 )
      for string in result
        if (ismatch(r"\/L\d</td>", string) && ismatch(r"\/B\/", string))# Indicates a lecture
          language = match(r"(?<=\/G\d{2}\/)[A-Z](?=\/)", string).match;
          group = match(r"(?<=\/G)\d{2}(?=\/)", string).match;
          day = match(r"(?<=<td>)[A-Z][a-z]+(?=<\/td>)", string).match;
          lecture_number = match(r"(?<=\/L)\d(?=</td>)", string).match;
          start_time = match(r"(?<=<td>)\d{2}:\d{2}:\d{2}\s[PAM]{2}(?=</td>)", string).match;
          end_time = match(r"(?<=<td>)\d{2}:\d{2}:\d{2}\s[PAM]{2}(?=<\/td><td>[A-Z])", string).match;
          lecture = Lecture(subject, group, start_time, end_time, venue, language, lecture_number);

          for set in lecture_sets
            if group == set.group
              push!(set.lectures, lecture);
            else
              continue
            end
          end

        else
          continue
        end
      end
    end


      push!(possible_sets, lecture_sets);

    else
      push!(possible_sets, []);
    end

  end
  return possible_sets;

end
