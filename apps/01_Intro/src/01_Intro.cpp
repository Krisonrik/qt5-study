// Copyright 2018 Qi Yao
HVR_WINDOWS_DISABLE_ALL_WARNING
#include <iostream>

#include "QtCore/qversionnumber.h"

HVR_WINDOWS_ENABLE_ALL_WARNING

int main()
{
  std::cout << qVersion() << std::endl;
  return 0;
}
