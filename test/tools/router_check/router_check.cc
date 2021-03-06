#include <iostream>
#include <string>

#include "test/tools/router_check/router.h"

int main(int argc, char* argv[]) {
  if (argc < 3 || argc > 4) {
    return EXIT_FAILURE;
  }

  try {
    RouterCheckTool checktool = RouterCheckTool::create(argv[1]);

    // TODO(hennna): Switch to gflags
    if (argc == 4 && std::string(argv[3]) == "--details") {
      checktool.setShowDetails();
    }

    // Test fails if routes do not match what is expected
    if (!checktool.compareEntriesInJson(argv[2])) {
      return EXIT_FAILURE;
    }
  } catch (const EnvoyException& ex) {
    std::cerr << ex.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
