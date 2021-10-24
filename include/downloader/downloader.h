#include <string>

#include <curl/curl.h>

class Downloader
{
public:
  Downloader(const std::string &url, const std::string &file_path);
  ~Downloader();

  CURLcode StartDownload();

private:
  friend size_t WriteInHandler(char *ptr,
                               size_t size,
                               size_t nmemb,
                               void *data);

private:
  std::string url_;
  std::string file_path_;
};