#include <downloader/downloader.hpp>

#include <curl/curl.h>

#include <filesystem>
#include <iostream>

size_t WriteInHandler(char *ptr,
                      size_t size,
                      size_t nmemb,
                      void *data)
{
  FILE *writehere = (FILE *)data;
  return fwrite(ptr, size, nmemb, writehere);
}

Downloader::Downloader(const std::string &url,
                       const std::string &file_path)
    : url_(url), file_path_(file_path)
{
  curl_global_init(CURL_GLOBAL_ALL);
}

Downloader::~Downloader()
{
  curl_global_cleanup();
}

CURLcode Downloader::StartDownload()
{
  CURLcode return_code = CURLE_OK;

  std::filesystem::path path(file_path_);

  if ((path.is_absolute() && path.has_filename()) == false)
  {
    return_code = CURLE_READ_ERROR;
  }

  CURL *curl_handler = curl_easy_init();
  if (curl_handler == NULL)
  {
    return_code = CURLE_FAILED_INIT;
  }

  FILE *file_handler;
  if (return_code == CURLE_OK)
  {
    file_handler = fopen(file_path_.c_str(), "w");
    if (file_handler == NULL)
    {
      std::cout << "Could not create file handler" << std::endl;
      return_code = CURLE_READ_ERROR;
    }
  }

  if (return_code == CURLE_OK)
  {
    curl_easy_setopt(curl_handler, CURLOPT_URL, url_.c_str());

    //callbacks for writing downloaded data
    curl_easy_setopt(curl_handler, CURLOPT_WRITEFUNCTION, WriteInHandler);
    curl_easy_setopt(curl_handler, CURLOPT_WRITEDATA, file_handler);

    //callbacks for timeout abort
    curl_easy_setopt(curl_handler, CURLOPT_TIMEOUT, 10L);

    return_code = curl_easy_perform(curl_handler);
  }

  // If curl handler is valid, clean it
  if (curl_handler != NULL)
  {
    curl_easy_cleanup(curl_handler);
  }

  return return_code;
}