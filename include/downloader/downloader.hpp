#include <curl/curl.h>

#include <string>

class Downloader
{
public:
  /*!
  @brief A constructor

  Create object and preparate class to download

  @param[in] url - Url, from which file is downloading
  @param[in] file_path - Path, where file locate
  */
  Downloader(const std::string &url, const std::string &file_path);

  /*!
  @brief A destructor

  Delete object and clean up memory after download
  */
  ~Downloader();

  /*!
  @brief File download start function

  @return CURLcode enum, which declarated in <curl.h>. If download finishes OK it returns CURLE_OK
  */
  CURLcode StartDownload();

private:
  /*!
  @brief Callback for writing received data.

  This callback function gets called by libcurl as soon as there is data received that needs to be saved.
  For most transfers, this callback gets called many times and each invoke delivers another chunk of data

  @param ptr - points to the delivered data. (set by curl library)
  @param size - size is always 1, sizeof(char). (set by curl library)
  @param nmemb - size of received data, bytes. (set by curl library)
  @param[in,out] data - set the userdata argument with the CURLOPT_WRITEDATA option(File handler)
  */
  friend size_t WriteInHandler(char *ptr,
                               size_t size,
                               size_t nmemb,
                               void *data);

private:
  std::string url_;       ///< Url, from which file is downloading
  std::string file_path_; ///< Path, where file locates
};