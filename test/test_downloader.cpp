#include <gtest/gtest.h>
#include <downloader/downloader.hpp>

#include <filesystem>

TEST(DownloaderUnitTest, AccessibleUrl)
{
  std::string file_path;
  file_path += std::filesystem::current_path().c_str();
  file_path += "/downloaded_pic.jpg";
  Downloader download("http://arduino.ru/sites/default/files/Hardware/updated/Mega_fron.jpg", file_path.c_str());
  EXPECT_EQ(download.StartDownload(), CURLE_OK);
}

TEST(DownloaderUnitTest, InaccessibleUrl)
{
  std::string file_path;
  file_path += std::filesystem::current_path().c_str();
  file_path += "/downloaded_pic.jpg";
  Downloader download("http://ardu123ino.ru/sites/default/files/Hardware/updated/Mega_fron.jpg", file_path.c_str());
  EXPECT_EQ(download.StartDownload(), CURLE_COULDNT_RESOLVE_HOST);
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}