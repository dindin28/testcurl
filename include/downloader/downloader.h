#include <curl/curl.h>

#include <string>
#include <filesystem>
#include <vector>
#include <utility>
#include <thread>

class Downloader
{
public:
  Downloader();
  ~Downloader();

  void AddDownload(std::string url, std::string file_path = "");

  //FilePath setter/getters
  inline void SetDefaultFilePath(std::filesystem::path default_file_path);
  inline std::filesystem::path GetDefaultFilePath() const;
  inline std::filesystem::path GetCurrentFilePath() const; //Confused? (Ask Vanya)

  double GetProgressOfCurrentFile() const;
  std::string GetCurrentDownloadUrl() const;
  inline void SetProgressOfCurrentFile(double value); //Not in private (Ask Vanya)

private:
  friend int ProgressBar(void *handler,
                         curl_off_t TotalToDownload,
                         curl_off_t NowDownloaded,
                         curl_off_t TotalToUpload,
                         curl_off_t NowUploaded);
  friend size_t WriteInHandler(char *ptr, size_t size, size_t nmemb, void *data);

  void ActiveDownload();                                                 //Run up downloading and push it in thread
  void DownloadThread(std::string url, std::filesystem::path file_path); //Function goes in thread

private:
  std::thread thread_;
  bool thread_is_busy_;
  double current_download_progress_;
  std::filesystem::path default_file_path_; //Current path by default
  std::vector<std::pair<std::string, std::string>> queue_;
};