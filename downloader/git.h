#pragma once
#include <string>
#include <vector>
#include <unordered_set>

class Git {
public:

    struct FileInfo {
        std::string filename;
        int created;

        FileInfo(std::string const & filename, int created):
            filename(filename),
            created(created) {
        }
    };

    struct FileHistory {
        std::string filename; // the filename may change when renamed, etc. 
        int date;
        std::string hash;
        FileHistory(std::string const & filename,  int date, std::string const & hash):
            filename(filename),
            date(date),
            hash(hash) {
        }
    };


    /** Clones the given repository to specified path.

      Returns true if successful. The destination path must not exist when calling the function.
     */
    static bool Clone(std::string const & url, std::string const & into);

    /** Returns list of all branches in the given repository.
     */
    static std::unordered_set<std::string> GetBranches(std::string const & repoUrl);

    /** Returns the current branch of the github repository.
     */
    static std::string GetCurrentBranch(std::string const & repoUrl);

    /** Checkouts the given branch.

      Returns true if successful, false otherwise.
     */
    static bool SetBranch(std::string const & repoUrl, std::string const branch);

    /** Returns list of all files from given repository (including the deleted ones).
     */
    static std::vector<FileInfo> GetFileInfo(std::string const & repoUrl);

    /** For a given file, returns the list of its revisions.
     */
    static std::vector<FileHistory> GetFileHistory(std::string const & repoUrl, FileInfo const & file);

    /** For a given file history, stores the contents of the given file at that level into the specified string (into). If the file does not exist at that revision, does not change the string and returns false. 
     */
    static bool GetFileRevision(std::string const & repoUrl,  const FileHistory & file, std::string & into);








};
