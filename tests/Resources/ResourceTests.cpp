
#include "canvas/Resources/Resource.h"
#include "nucleus/Logging.h"
#include "nucleus/Ref.h"
#include "nucleus/Testing.h"
#include "nucleus/Text/String.h"

namespace ca {

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

TEST_CASE("ResourceIsMovedIntoContainer") {
  TrackingResource::reset();

  {
    Resource<TrackingResource> res{10};
    res.setName("Some name");
  }

  CHECK(TrackingResource::constructs == 1);
  CHECK(TrackingResource::moves == 0);
  CHECK(TrackingResource::copies == 0);
  CHECK(TrackingResource::destructs == 1);
}

TEST_CASE("ResourceIsMoved") {
  TrackingResource::reset();

  {
    Resource<TrackingResource> res{10};
    Resource<TrackingResource> res2 = std::move(res);
  }

  CHECK(TrackingResource::constructs == 1);
  CHECK(TrackingResource::moves == 1);
  CHECK(TrackingResource::copies == 0);
  CHECK(TrackingResource::destructs == 2);
}

TEST_CASE("ConstructResourceInPlace") {
  TrackingResource::reset();

  { Resource<TrackingResource> res{10}; }

  CHECK(TrackingResource::constructs == 1);
  CHECK(TrackingResource::moves == 0);
  CHECK(TrackingResource::copies == 0);
  CHECK(TrackingResource::destructs == 1);
}

TEST_CASE("CanHoldAReference") {
  TrackingResource::reset();

  {
    Resource<TrackingResource> res{10};
    res.setName("testing");

    ResourceRef<TrackingResource> ref1 = &res;
    ResourceRef<TrackingResource> ref2 = ref1;
  }

  CHECK(TrackingResource::constructs == 1);
  CHECK(TrackingResource::moves == 0);
  CHECK(TrackingResource::copies == 0);
  CHECK(TrackingResource::destructs == 1);
}

}  // namespace ca
