#pragma once

#include <string>

#include "utils.h"

class Settings {
public:

    /** Output path where the downloader is going to put everything.
     */
    static std::string OutputPath;

    /** Maximum number of files that can reside in a given directory.

      This limit is used for performance reasons where filesystems are not happy with too many files in a single directory.

      Note that due to the IdToPath conversion mechanism, a full directory will contain the specified number of files *and* the same number of directories.
     */
    static int MaxFilesPerDirectory;









    /** Takes given id and produces a path from it that would make sure the MaxFilesPerDirectory limit is not broken assuming full utilization of the ids.
     */
    static std::string IdToPath(long id) {
        std::string result = "";
        // get the directory id first, which chops the ids into chunks of MaxEntriesPerDirectorySize
        long dirId = id / MaxFilesPerDirectory;
        // construct the path while dirId != 0
        while (dirId != 0) {
            result = STR("/" << std::to_string(dirId % MaxFilesPerDirectory) << result);
            dirId = dirId / MaxFilesPerDirectory;
        }
        return result;
    }

    /** If the given id is the last id in a given directory, returns true.

      To be a last id in a directory means that no higher id will end up directly in the same directory as this id and therefore all files in the directory can be for instance compressed to save space.
     */
    static bool ClosesPathDir(long id) {
        return ((id + 1) % MaxFilesPerDirectory) == 0;
    }
};
