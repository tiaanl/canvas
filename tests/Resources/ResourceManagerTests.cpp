
#include "canvas/Resources/ResourceManager.h"
#include "nucleus/Testing.h"

namespace ca {

TEST_CASE("basic resource manager") {
  ResourceManager resourceManager;
  resourceManager.createDefaults();
}

}  // namespace ca
