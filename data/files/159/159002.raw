# Converts time strings e.g. "10:30:00 AM" to a mathematical time object to
# work resolve clashes in Julia.
include("lecture.jl")

function str2time(time_string::String)
  minutes_past_midnight = 0;
  day_part = match(r"[PAM]", time_string).match;
  hours = parseint(match(r"\d{2}(?=:\d{2}:\d{2})", time_string).match);
  minutes = parseint(match(r"(?<=\d{2}:)\d{2}(?=:\d{2})", time_string).match);

  if (day_part == "PM")
    minutes_past_midnight = (hours * 60) + minutes + 720;
  else
    minutes_past_midnight = (hours * 60) + minutes;
  end

  return minutes_past_midnight

end

function isEmpty(set::LectureSet)
  if length(set.lectures) == 0;
    return true;
  else
    return false;
  end
end

function isClash(subjectA::LectureSet, subjectB::LectureSet)

  i = 1;
  clash = false;
  start_time1 = "";
  end_time1 = "";
  start_time2 = "";
  end_time2 = "";
  day1 = "";
  day2 = "";
  for lecture in subjectA.lectures
    start_time1 = str2time(lecture.start_time);
    end_time1 = str2time(lecture.end_time);
    day1 = lecture.day;

    for lecture2 in  subjectB.lectures
      start_time2 = str2time(lecture2.start_time);
      end_time2 = str2time(lecture2.end_time);
      day2 = lecture2.day;

      if day1 == day2 && ((start_time1 <= start_time2 < end_time1) || (start_time1 < end_time2 < end_time1) || (start_time2 <= start_time1 < end_time2) || (start_time2 < end_time1 < end_time2))
        clash = true;
        return clash;

      else
        continue
      end

    end

  end

  return clash;

end
