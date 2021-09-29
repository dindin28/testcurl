#include <string>
#include <filesystem>
#include <curl/curl.h>

class Downloader
{
public:
  //No object creating
  Downloader() = delete;
  Downloader(const Downloader &) = delete;
  void operator=(const Downloader &) = delete;
  ~Downloader() = delete;

  static void SetFilePath(std::filesystem::path file_path);
  static int Download(std::string url, std::string file_name = "");
  static double GetProgress();

private:
  static int ProgressBar(void *ptr,
                         curl_off_t TotalToDownload,
                         curl_off_t NowDownloaded, curl_off_t TotalToUpload,
                         curl_off_t NowUploaded);
  static size_t WriteInHandler(char *ptr, size_t size, size_t nmemb, void *data);

private:
  static double progress_;
  static std::filesystem::path file_path_; //Current path by default
};