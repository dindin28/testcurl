#include <string>
#include <filesystem>
#include <curl/curl.h>

class Downloader
{
public:
  Downloader();

  void SetFilePath(std::filesystem::path file_path);
  int Download(std::string url, std::string file_name = "");

  inline double GetProgress() { return progress_; }
  inline void SetProgress(double value) { progress_ = value; }

private:
  friend int ProgressBar(void *handler,
                         curl_off_t TotalToDownload,
                         curl_off_t NowDownloaded, curl_off_t TotalToUpload,
                         curl_off_t NowUploaded);
  friend size_t WriteInHandler(char *ptr, size_t size, size_t nmemb, void *data);

private:
  double progress_;
  std::filesystem::path file_path_; //Current path by default
};