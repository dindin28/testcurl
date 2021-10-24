
#include <downloader/downloader.h>
#include <curl/curl.h>

#include <iostream>   //cout
#include <filesystem> //current_path
#include <string>     //string

using namespace std::chrono;

int main(int argc, char **argv)
{
  char a[10];
  a[10] = 0;
  return 0;

  std::string file_path;
  file_path += std::filesystem::current_path().c_str();
  file_path += "/../downloaded_pic.jpg";
  Downloader download("http://arduino.ru/sites/default/files/Hardware/updated/Mega_fron.jpg", file_path.c_str());
  CURLcode code = download.StartDownload();
  if (code != CURLE_OK)
  {
    std::cout << "StartDownload() failed: " << curl_easy_strerror(code);
  }
  return 0;
}