#include <curl/curl.h>
#include <err.h>
#include <string.h>
#include "dl.h"
#include <iostream>

static data_t data = data_t ();
const data_t dl_content () {
	return data;
}

size_t dl( void *ptr, size_t size, size_t nmemb, void *stream) {
	ssize_t len = nmemb * size;
	ssize_t dest = data.size ();
	data.resize (data.size () + len);
	memcpy (&data[dest], ptr, len);
	return nmemb;
}

int file_dl (const std::string& url) {
	CURL* curl;
	CURLcode res;

	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);

	if (curl) {
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, NULL);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, dl);
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str ());
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		return res;
	}
	return 0;
}

