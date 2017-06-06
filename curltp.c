#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

struct counter {
	int count;
};

size_t countup(char *ptr, size_t size, size_t nmemb, void *stream) {
	struct counter *counter = (struct counter *)stream;
	int block = size * nmemb;

	if (!counter) {
		return block;
	}

	counter->count++;

	return block;
}

int main(int argc, char *argv[]) {
	CURL *curl;
	struct counter *counter = (struct counter *)malloc(sizeof(struct counter));

	counter->count = 0;

	// curl setup
	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, "https://qiita.com/");
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, counter);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, countup);

	// execution
	curl_easy_perform(curl);

	// cleanup
	curl_easy_cleanup(curl);

	printf("Total count: %d\n", counter->count);

	free(counter);

	return 0;
}
