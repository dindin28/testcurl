#include <curl/curl.h>

#include <fstream>
#include <string>
#include <filesystem>
#include <iostream>

class Downloader
{
public:
  //No object creating
  Downloader() = delete;
  Downloader(const Downloader &) = delete;
  void operator=(const Downloader &) = delete;
  ~Downloader() = delete;

  void static SetFilePath(std::filesystem::path file_path);
  int static Download(std::string url, std::string file_name = "");

private:
  size_t static WriteInHandler(char *ptr, size_t size, size_t nmemb, void *data);
  std::filesystem::path static file_path_; //Current path by default
};

std::filesystem::path Downloader::file_path_ = std::filesystem::current_path();

void Downloader::SetFilePath(std::filesystem::path file_path)
{
  file_path_ = std::filesystem::weakly_canonical(file_path);
}

size_t Downloader::WriteInHandler(char *ptr, size_t size, size_t nmemb, void *data)
{
  FILE *writehere = (FILE *)data;
  return fwrite(ptr, size, nmemb, writehere);
}

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
}

int main(int argc, char **argv)
{
  Downloader::SetFilePath("./a");
  int return_code = Downloader::Download("http://20.67.36.112:8083/arduino.jpg");
  if (return_code != CURLE_OK)
  {
    std::cout << "return code is: " << return_code << std::endl;
  }
  return 0;
}