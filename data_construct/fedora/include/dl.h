#ifndef DL_H
#define DL_H 

#include <string>
#include <vector>

typedef std::vector<char> data_t;

const data_t content ();

int http_dl (const std::string& url/*, data_t& data*/);

#endif

