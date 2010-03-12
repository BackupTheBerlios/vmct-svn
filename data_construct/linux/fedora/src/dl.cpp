#include <iostream>
#include <fstream>
#include <curl/curl.h>
#include <err.h>
#include <string.h>
#include "dl.h"
#include "log.h"

static data_t data = data_t ();
const data_t dl_content () {
	return data;
}

#include <stdio.h>

static size_t dl( void *ptr, size_t size, size_t nmemb, void *stream) {
	ssize_t len = nmemb * size;
	ssize_t dest = data.size ();
	data.resize (data.size () + len);
	memcpy (&data[dest], ptr, len);
	return nmemb;
}

int file_dl (const std::string& url) {
	log ("dl " + url);
	CURL* curl;
	CURLcode res;

	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);

	data.resize (0);

	if (curl) {
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*) &data /*NULL*/);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, dl);
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str ());
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		return res;
	}
	return 0;
}

std::string dl_unpack (const std::string& url) {
	log ("dl & unpack " + url);
        file_dl (url);
        std::string name = "/tmp/"; name.append (basename (url.c_str ()));
        std::ofstream ofile;
        ofile.open (name.c_str (), std::ofstream::out);
        ofile.write (dl_content ().data (), dl_content ().size ());
        ofile.close ();
        std::string cmd = "/usr/bin/gzip -df " + name + ">";
        cmd.append (name.begin (), name.end () - 3);
        FILE* fp = popen (cmd.c_str (), "r");
        fclose (fp);
        return std::string (name.begin (), name.end () - 3);
}

