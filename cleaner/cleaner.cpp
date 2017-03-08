#include <iostream>
#include <string>
#include <unordered_set>

#include "include/csv.h"





class Cleaner {
public:
    static void Help() {

    }

    static void Clean(std::string const & input, std::string const & output) {
        Cleaner c;
        std::cout << "Reading ghtorrent projects in " << input << std::endl;
        long total = c.load(input);
        std::cout << "  total projects: " << total << std::endl;
        std::cout << "  filtered:       " << c.projects_.size() << std::endl;
        std::cout << "Storing filtered projects to " << output << std::endl;
        c.store(output);
        std::cout << "DONE." << std::endl;
    }

    static bool OutputForks;
    static bool OutputDuplicates;
    static long Limit;

    static void FilterLanguage(std::string const & lang) {
        FilterLanguage_.insert(lang);
    }

private:

    static std::unordered_set<std::string> FilterLanguage_;


    static bool IsForked(std::vector<std::string> const & row) {
        return row[7] != "\\N";
    }

    static bool IsDeleted(std::vector<std::string> const & row) {
        return row[8] != "0";
    }

    static std::string const & Language(std::vector<std::string> const & row) {
        return row[5];
    }

    static std::string const & Url(std::vector<std::string> const & row) {
        return row[1];
    }

    long load(std::string const & input) {
        CSVParser p(input);
        long count = 0;
        for (auto row : p) {
            if (not IsDeleted(row) and (OutputForks or not IsForked(row))) {
                // check the language now
                bool ok = FilterLanguage_.empty();
                for (std::string const & l : FilterLanguage_)
                    if (l == Language(row)) {
                        ok = true;
                        break;
                    }
                if (ok) {
                    projects_.insert(Url(row));
                    if (projects_.size() == Limit)
                        break;
                }
            }
            if (count++ % 100000 == 0)
                std::cout << "." << std::flush;
        }
        std::cout << std::endl;
        return count;
    }

    void store(std::string const & output) {
        std::ofstream f(output);
        for (std::string url : projects_)
            f << url << std::endl;
        f.close();
    }
    std::unordered_set<std::string> projects_;
};


std::unordered_set<std::string> Cleaner::FilterLanguage_;
bool Cleaner::OutputForks = false;
long Cleaner::Limit = -1;


/** Cleaner takes the ghtorrent input and selects only non-deleted non-forked repositories of the given language.

 */
int main(int argc, char* argv[]) {
    Cleaner::FilterLanguage("JavaScript");
    Cleaner::Clean("/data/ghtorrent/projects.csv", "/data/ele/projects.csv");
    return EXIT_SUCCESS;
}
