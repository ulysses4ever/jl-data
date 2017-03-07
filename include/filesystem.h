#pragma once

#include <string>

bool isDirectory(std::string const & path);

bool isFile(std::string const & path);

void createPath(std::string const & path);


void createPathIfMissing(std::string const & path);


/** Basically a rm -rf on the given path.
 */
void deletePath(std::string const & path);

