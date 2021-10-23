#include <downloader/downloader.h>

#include <iostream>
#include <iomanip>

Downloader::Downloader()
{
  curl_global_init(CURL_GLOBAL_ALL); // Check another args
  current_download_progress_ = 0;
  default_file_path_ = std::filesystem::current_path();
  thread_is_busy_ = false;
}

Downloader::~Downloader()
{
  while (queue_.size() != 0) // Infinite loop (Ask Vanya)
  {
  }
  thread_.detach(); // Remove core dump
  // Always need to be
  curl_global_cleanup();
}

void Downloader::AddDownload(std::string url, std::string file_path)
{
  queue_.push_back(std::make_pair(url, file_path));
  ActiveDownload();
}

// FilePath setter/getters
inline void Downloader::SetDefaultFilePath(std::filesystem::path default_file_path)
{
  default_file_path_ = std::filesystem::weakly_canonical(default_file_path);
} // Function (SetDefaultFilePath)
inline std::filesystem::path Downloader::GetDefaultFilePath() const
{
  return default_file_path_;
} // Function (GetDefaultFilePath)
inline std::filesystem::path Downloader::GetCurrentFilePath() const // Confused? (Ask Vanya)
{
  if (queue_.size() != 0)
  {
    return queue_[0].second;
  }
  return std::filesystem::path("");
} // Function (GetCurrentFilePath)

double Downloader::GetProgressOfCurrentFile() const
{
  return current_download_progress_;
} // Function (GetProgressOfCurrentFile)
std::string Downloader::GetCurrentDownloadUrl() const
{
  if (queue_.size() != 0)
  {
    return queue_[0].first;
  }
  return "";
} // Function (GetCurrentDownloadUrl)
inline void Downloader::SetProgressOfCurrentFile(double value) // Not in private (Ask Vanya)
{
  current_download_progress_ = value;
}

size_t WriteInHandler(char *ptr, size_t size, size_t nmemb, void *data)
{
  FILE *writehere = (FILE *)data;
  return fwrite(ptr, size, nmemb, writehere);
} // Function (WriteInHandler)

int ProgressBar(void *handler,
                curl_off_t TotalToDownload,
                curl_off_t NowDownloaded,
                curl_off_t TotalToUpload,
                curl_off_t NowUploaded)
{
  if (TotalToDownload <= 0)
  {
    ((Downloader *)handler)->SetProgressOfCurrentFile(0);
  }
  else
  {
    ((Downloader *)handler)->SetProgressOfCurrentFile(static_cast<double>(NowDownloaded) / TotalToDownload * 100);
  }

  return CURLE_OK;
} // Function (ProgressBar)

void Downloader::ActiveDownload()
{
  if (thread_is_busy_ == false && queue_.size() != 0)
  {
    if (thread_.native_handle() != 0)
    {
      thread_.detach();
    }
    current_download_progress_ = 0;
    std::filesystem::path path_to_file;
    if (queue_[0].second != "") // Choose if need default_file_path_
    {
      path_to_file = std::filesystem::weakly_canonical(std::filesystem::path(queue_[0].second));
    }
    else
    {
      path_to_file = default_file_path_;
    }
    if (path_to_file.has_extension() == false) // Fill filename if nessesary
    {
      path_to_file += "/";
      path_to_file += std::filesystem::path(queue_[0].first).filename(); // Take filename from url
    }

    if (std::filesystem::exists(path_to_file) == false)
    {
      std::filesystem::create_directories(path_to_file.parent_path());
    }
    thread_is_busy_ = true;
    thread_ = std::thread(&Downloader::DownloadThread, this, queue_[0].first, path_to_file);
  }
}

void Downloader::DownloadThread(std::string url, std::filesystem::path file_path)
{
  int return_code = CURLE_OK;

  // Creating handler
  CURL *curl_handler = curl_easy_init();
  if (curl_handler == NULL)
  {
    return_code = CURLE_FAILED_INIT;
  }

  // Opening(creating) file with same name and exstension
  FILE *file_handler;
  if (return_code == CURLE_OK)
  {
    file_handler = fopen(file_path.c_str(), "w");
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
    curl_easy_setopt(curl_handler, CURLOPT_XFERINFODATA, this);
    curl_easy_setopt(curl_handler, CURLOPT_WRITEFUNCTION, WriteInHandler);
    curl_easy_setopt(curl_handler, CURLOPT_WRITEDATA, file_handler);

    return_code = curl_easy_perform(curl_handler);
  }
  // If curl handler is valid, clean it
  if (curl_handler != NULL)
  {
    curl_easy_cleanup(curl_handler);
  }
  queue_.erase(queue_.begin());
  thread_is_busy_ = false;
  ActiveDownload();
}