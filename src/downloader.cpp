#include <downloader/downloader.h>

#include <iostream>
#include <iomanip>

//Static Variables
std::filesystem::path Downloader::file_path_ = std::filesystem::current_path();
double Downloader::progress_ = 0;

int Downloader::ProgressBar(void *ptr,
                            curl_off_t TotalToDownload,
                            curl_off_t NowDownloaded,
                            curl_off_t TotalToUpload,
                            curl_off_t NowUploaded)
{
  if (TotalToDownload <= 0)
  {
    progress_ = 0;
  }
  else
  {
    progress_ = static_cast<double>(NowDownloaded) / TotalToDownload * 100;
  }

  std::system("clear");
  std::cout << "<";
  for (int i = 0; i < progress_; i++)
  {
    std::cout << "#";
  }
  for (int i = 0; i < 100 - progress_; i++)
  {
    std::cout << " ";
  }
  std::cout << "> " << std::setprecision(4) << progress_ << "%" << std::endl;

  return CURLE_OK;
} //Function (ProgressBar)

void Downloader::SetFilePath(std::filesystem::path file_path)
{
  file_path_ = std::filesystem::weakly_canonical(file_path);
} //Function (SetFilePath)

size_t Downloader::WriteInHandler(char *ptr, size_t size, size_t nmemb, void *data)
{
  FILE *writehere = (FILE *)data;
  return fwrite(ptr, size, nmemb, writehere);
} //Function (WriteInHandler)

int Downloader::Download(std::string url, std::string file_name)
{
  int return_code = CURLE_OK;

  curl_global_init(CURL_GLOBAL_ALL); //Check another args

  //Creating handler
  CURL *curl_handler = curl_easy_init();
  if (curl_handler == NULL)
  {
    return_code = CURLE_FAILED_INIT;
  }

  //Opening(creating) file with same name and exstension
  FILE *file_handler;
  if (return_code == CURLE_OK)
  {
    if (std::filesystem::exists(file_path_) == false)
    {
      std::filesystem::create_directories(file_path_);
    }
    if (file_name == "")
    {
      file_name = std::filesystem::path(url).filename();
    }
    file_handler = fopen((std ::string(file_path_) + "/" + file_name).c_str(), "w");
    if (file_handler == NULL)
    {
      std::cout << "Could not create file handler" << std::endl;
      return_code = CURLE_FAILED_INIT;
    }
  }

  if (return_code == CURLE_OK)
  {
    curl_easy_setopt(curl_handler, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl_handler, CURLOPT_NOPROGRESS, 0L);
    curl_easy_setopt(curl_handler, CURLOPT_XFERINFOFUNCTION, ProgressBar);
    curl_easy_setopt(curl_handler, CURLOPT_WRITEFUNCTION, WriteInHandler);
    curl_easy_setopt(curl_handler, CURLOPT_WRITEDATA, file_handler);

    return_code = curl_easy_perform(curl_handler);
  }

  //If curl handler is valid, clean it
  if (curl_handler != NULL)
  {
    curl_easy_cleanup(curl_handler);
  }

  //Always need to be
  curl_global_cleanup();

  return return_code;
} //Function Download
