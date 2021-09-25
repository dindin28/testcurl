#include <iostream>
#include <fstream>
#include <string>
#include <curl/curl.h>

std::string data;

size_t WriteFunc(char *buf, size_t size, size_t nmemb, void *up)
{
  int realsize = size * nmemb;
  for (int i = 0; i < realsize; i++)
  {
    data.push_back(buf[i]);
  }

  return realsize;
}

int main(int argc, char **argv)
{
  curl_global_init(CURL_GLOBAL_ALL);
  CURL *curl = curl_easy_init();

  curl_easy_setopt(curl, CURLOPT_URL, "http://20.67.36.112:8083/arduino.jpg");
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteFunc);
  curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);

  curl_easy_perform(curl);

  std::ofstream file("pic.jpg");
  file << data;

  curl_easy_cleanup(curl);
  curl_global_cleanup();
  return 0;
}