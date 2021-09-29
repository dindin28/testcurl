#include <curl/curl.h>
#include <downloader/downloader.h>

#include <iostream>

int main(int argc, char **argv)
{
  Downloader::SetFilePath("..");
  int return_code = Downloader::Download("https://o04.inadzor.be/3/Domino_2005_320.mp4");
  if (return_code != CURLE_OK)
  {
    std::cout << "return code is: " << return_code << std::endl;
  }
  return 0;
}