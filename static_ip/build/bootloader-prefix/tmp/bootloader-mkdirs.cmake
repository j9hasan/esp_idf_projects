# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/LENOVO/esp/esp-idf/components/bootloader/subproject"
  "C:/Users/LENOVO/Documents/JENCE-JUBAID/ESP_IDF_PROJECTS/static_ip/build/bootloader"
  "C:/Users/LENOVO/Documents/JENCE-JUBAID/ESP_IDF_PROJECTS/static_ip/build/bootloader-prefix"
  "C:/Users/LENOVO/Documents/JENCE-JUBAID/ESP_IDF_PROJECTS/static_ip/build/bootloader-prefix/tmp"
  "C:/Users/LENOVO/Documents/JENCE-JUBAID/ESP_IDF_PROJECTS/static_ip/build/bootloader-prefix/src/bootloader-stamp"
  "C:/Users/LENOVO/Documents/JENCE-JUBAID/ESP_IDF_PROJECTS/static_ip/build/bootloader-prefix/src"
  "C:/Users/LENOVO/Documents/JENCE-JUBAID/ESP_IDF_PROJECTS/static_ip/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/LENOVO/Documents/JENCE-JUBAID/ESP_IDF_PROJECTS/static_ip/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
