
#include "canvas/Resources/Resource.h"
#include "nucleus/Logging.h"
#include "nucleus/Ref.h"
#include "nucleus/Text/String.h"
#include "nucleus/Testing.h"

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

  explicit TrackingResource(I32 data = 0) : data(data) {
    constructs++;
  }

  TrackingResource(const TrackingResource& other) : data(other.data) {
    copies++;
  }

  TrackingResource(TrackingResource&& other) : data(other.data) {
    other.data = 0;
    moves++;
  }

  ~TrackingResource() {
    destructs++;
  }

  TrackingResource& operator=(const TrackingResource& other) {
    data = other.data;
    copies++;
  }

  TrackingResource& operator=(TrackingResource&& other) {
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

  { ca::Resource<TrackingResource> res = TrackingResource{10}; }

  REQUIRE(TrackingResource::constructs == 1);
  REQUIRE(TrackingResource::moves == 1);
  REQUIRE(TrackingResource::copies == 0);
  REQUIRE(TrackingResource::destructs == 2);
}

TEST_CASE("ResourceIsMoved") {
  TrackingResource::reset();

  {
    ca::Resource<TrackingResource> res = TrackingResource{10};
    ca::Resource<TrackingResource> res2 = std::move(res);
  }

  REQUIRE(TrackingResource::constructs == 1);
  REQUIRE(TrackingResource::moves == 2);
  REQUIRE(TrackingResource::copies == 0);
  REQUIRE(TrackingResource::destructs == 3);
}

TEST_CASE("ConstructResourceInPlace") {
  TrackingResource::reset();

  { ca::Resource<TrackingResource> res{10}; }

  REQUIRE(TrackingResource::constructs == 1);
  REQUIRE(TrackingResource::moves == 0);
  REQUIRE(TrackingResource::copies == 0);
  REQUIRE(TrackingResource::destructs == 1);
}

TEST_CASE("CanHoldAReference") {
  TrackingResource::reset();

  {
    ca::Resource<TrackingResource> res{10};

    nu::Ref<ca::Resource<TrackingResource>> ref1 = &res;
    nu::Ref<ca::Resource<TrackingResource>> ref2 = ref1;
  }

  REQUIRE(TrackingResource::constructs == 1);
  REQUIRE(TrackingResource::moves == 0);
  REQUIRE(TrackingResource::copies == 0);
  REQUIRE(TrackingResource::destructs == 1);
}
