
#include <downloader/downloader.h>

#include <iostream>
#include <chrono>

using namespace std::chrono;

int main(int argc, char **argv)
{
  Downloader download_movie;
  download_movie.AddDownload("http://arduino.ru/sites/default/files/Hardware/updated/Mega_fron.jpg"); // Without second parameter
  download_movie.AddDownload("https://3d-diy.ru/upload/resize_cache/webp/upload/iblock/e8e/raspberry_pi_4_model_b.webp");
  download_movie.AddDownload("https://ru.mouser.com/images/arduino/lrg/A000073_t.jpg", ".."); // With path parameter
  time_point<steady_clock> start = steady_clock::now();
  while (download_movie.GetCurrentDownloadUrl() != "")
  {
    if (steady_clock::now() - start > 10ms)
    {
      std::cout << download_movie.GetCurrentDownloadUrl() << ": " << download_movie.GetProgressOfCurrentFile() << std::endl;
      start = steady_clock::now();
    }
  }
  return 0;
}