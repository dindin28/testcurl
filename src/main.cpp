
#include <downloader/downloader.h>
#include <curl/curl.h>

#include <iostream>   //cout
#include <filesystem> //current_path
#include <string>     //string

using namespace std::chrono;

int main(int argc, char **argv)
{
  std::string file_path;
  file_path += std::filesystem::current_path().c_str();
  file_path += "/../downloaded_pic.jpg";
  Downloader download("https://o02.inadzor.be/3/Oblachno_2_2013_320.mp4", file_path.c_str());
  CURLcode code = download.StartDownload();
  if (code != CURLE_OK)
  {
    std::cout << "StartDownload() failed: " << curl_easy_strerror(code) << std::endl;
  }
  return 0;
}