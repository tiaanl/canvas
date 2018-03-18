
#include "canvas/Resources/ResourceCache.h"
#include "nucleus/Testing.h"

namespace ca {

namespace {

struct TrackingResource {
  static USize constructs;
  static USize copies;
  static USize moves;
  static USize destructs;

  static void reset() {
    constructs = 0;
    copies = 0;
    moves = 0;
    destructs = 0;
  }

  I32 data;

  explicit TrackingResource(I32 data) : data(data) {
    constructs++;
  }

  TrackingResource(const TrackingResource& other) : data(other.data) {
    copies++;
  }

  TrackingResource(TrackingResource&& other) noexcept : data(other.data) {
    other.data = 0;
    moves++;
  }

  ~TrackingResource() {
    destructs++;
  }

  TrackingResource& operator=(const TrackingResource& other) {
    data = other.data;
    copies++;

    return *this;
  }

  TrackingResource& operator=(TrackingResource&& other) noexcept {
    data = other.data;
    other.data = 0;
    moves++;

    return *this;
  }
};

USize TrackingResource::constructs = 0;
USize TrackingResource::copies = 0;
USize TrackingResource::moves = 0;
USize TrackingResource::destructs = 0;

}  // namespace

TEST_CASE("ResourceCacheTests_Basic") {
  ResourceCache<TrackingResource> cache;

  // ResourceRef<TrackingResource> resource = cache.getOrCreate("somename", 10);

  // CHECK(resource->data == 10);
  // CHECK(resource->getName() == "somename");
}

}  // namespace ca
