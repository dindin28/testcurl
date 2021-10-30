#include <downloader/downloader.hpp>

#include <iostream>   //cout
#include <filesystem> //current_path
#include <string>     //string

int main(int argc, char **argv)
{
  std::string file_path;
  file_path += std::filesystem::current_path().c_str();
  file_path += "/Park_Yurskogo_Perioda_1993_320.mp4";
  Downloader download("https://o03.inadzor.be/3/Park_Yurskogo_Perioda_1993_320.mp4", file_path.c_str());

  CURLcode code = download.StartDownload();
  if (code != CURLE_OK)
  {
    std::cout << "StartDownload() failed: " << curl_easy_strerror(code) << std::endl;
  }
  return 0;
}