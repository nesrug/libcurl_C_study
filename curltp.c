#include <stdio.h>
#include <curl/curl.h>

int main(int argc, char *argv[]) {
	CURL *curl;

	// curl setup
	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, "https://qiita.com/");
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);

	// execution
	curl_easy_perform(curl);

	// cleanup
	curl_easy_cleanup(curl);

	return 0;
}
