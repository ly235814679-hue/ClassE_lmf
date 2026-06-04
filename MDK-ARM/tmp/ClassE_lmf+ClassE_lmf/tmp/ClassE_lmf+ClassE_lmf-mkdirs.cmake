# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "D:/STDemoProject/F103_ClassE_LMF_Demo/ClassE_lmf/MDK-ARM/tmp/ClassE_lmf+ClassE_lmf")
  file(MAKE_DIRECTORY "D:/STDemoProject/F103_ClassE_LMF_Demo/ClassE_lmf/MDK-ARM/tmp/ClassE_lmf+ClassE_lmf")
endif()
file(MAKE_DIRECTORY
  "D:/STDemoProject/F103_ClassE_LMF_Demo/ClassE_lmf/MDK-ARM/tmp/1"
  "D:/STDemoProject/F103_ClassE_LMF_Demo/ClassE_lmf/MDK-ARM/tmp/ClassE_lmf+ClassE_lmf"
  "D:/STDemoProject/F103_ClassE_LMF_Demo/ClassE_lmf/MDK-ARM/tmp/ClassE_lmf+ClassE_lmf/tmp"
  "D:/STDemoProject/F103_ClassE_LMF_Demo/ClassE_lmf/MDK-ARM/tmp/ClassE_lmf+ClassE_lmf/src/ClassE_lmf+ClassE_lmf-stamp"
  "D:/STDemoProject/F103_ClassE_LMF_Demo/ClassE_lmf/MDK-ARM/tmp/ClassE_lmf+ClassE_lmf/src"
  "D:/STDemoProject/F103_ClassE_LMF_Demo/ClassE_lmf/MDK-ARM/tmp/ClassE_lmf+ClassE_lmf/src/ClassE_lmf+ClassE_lmf-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/STDemoProject/F103_ClassE_LMF_Demo/ClassE_lmf/MDK-ARM/tmp/ClassE_lmf+ClassE_lmf/src/ClassE_lmf+ClassE_lmf-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/STDemoProject/F103_ClassE_LMF_Demo/ClassE_lmf/MDK-ARM/tmp/ClassE_lmf+ClassE_lmf/src/ClassE_lmf+ClassE_lmf-stamp${cfgdir}") # cfgdir has leading slash
endif()
