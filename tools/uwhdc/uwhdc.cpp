//===-- uwhdc.cpp -------------------------------------------------- c++ --===//
//
//                               UWH Timer
//
//           This file is distributed under the BSD 3-Clause License.
//                      See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "uwhd/console/Console.h"
#include "uwhd/sync/ModelSync.h"

using namespace uwhtimer;

int main(int argc, char *argv[]) {
  if (argc != 3)
    return 1;

  auto SyncClient = ModelSync::CreateSocketClient(argv[1], argv[2]);
  SyncClient->Init();

  Console C(SyncClient->getMgr());

  C.Loop();

  return 0;
}
