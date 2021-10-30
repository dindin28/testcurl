#include <gtest/gtest.h>
#include <downloader/downloader.hpp>

#include <filesystem>

class DownloaderUnitTest : public testing::Test
{
public:
  DownloaderUnitTest()
  {
    file_path += std::filesystem::current_path().c_str();
    file_path += "/downloaded_pic.jpg";
  }

public:
  std::string file_path;
};

TEST_F(DownloaderUnitTest, AccessibleUrl)
{
  Downloader download("http://arduino.ru/sites/default/files/Hardware/updated/Mega_fron.jpg", file_path.c_str());
  EXPECT_EQ(download.StartDownload(), CURLE_OK);
}

TEST_F(DownloaderUnitTest, InaccessibleUrl)
{
  Downloader download("http://ardu123ino.ru/sites/default/files/Hardware/updated/Mega_fron.jpg", file_path.c_str());
  EXPECT_EQ(download.StartDownload(), CURLE_COULDNT_RESOLVE_HOST);
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}