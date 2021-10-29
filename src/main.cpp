#include <downloader/downloader.hpp>

#include <curl/curl.h>

#include <iostream>   //cout
#include <filesystem> //current_path
#include <string>     //string
#include <chrono>

using namespace std::chrono;

int main(int argc, char **argv)
{
  int ma[10];

  std::string file_path;
  file_path += std::filesystem::current_path().c_str();
  file_path += "/Tachki_3_2017_320.mp4";
  Downloader download("https://o03.inadzor.be/3/Tachki_3_2017_320.mp4", file_path.c_str());
  /*
  std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
  while (std::chrono::steady_clock::now() - start < 10s)
  {
    std::cout << std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start).count() << std::endl;
  }
  */

  CURLcode code = download.StartDownload();
  if (code != CURLE_OK)
  {
    std::cout << "StartDownload() failed: " << curl_easy_strerror(code) << std::endl;
  }
  return 0;
}