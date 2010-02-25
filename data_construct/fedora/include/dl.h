#ifndef DL_H
#define DL_H 

#include <string>
#include <vector>

typedef std::vector<char> data_t;

const data_t dl_content ();

int file_dl (const std::string& url);

#endif

