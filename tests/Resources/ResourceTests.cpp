
#include "canvas/Resources/Resource.h"
#include "gtest/gtest.h"
#include "nucleus/Logging.h"
#include "nucleus/Ref.h"
#include "nucleus/Text/String.h"

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

TEST(ResourceTests, ResourceIsMovedIntoContainer) {
  TrackingResource::reset();

  { ca::Resource<TrackingResource> res = TrackingResource{10}; }

  EXPECT_EQ(1, TrackingResource::constructs);
  EXPECT_EQ(1, TrackingResource::moves);
  EXPECT_EQ(0, TrackingResource::copies);
  EXPECT_EQ(2, TrackingResource::destructs);
}

TEST(ResourceTests, ResourceIsMoved) {
  TrackingResource::reset();

  {
    ca::Resource<TrackingResource> res = TrackingResource{10};
    ca::Resource<TrackingResource> res2 = std::move(res);
  }

  EXPECT_EQ(1, TrackingResource::constructs);
  EXPECT_EQ(2, TrackingResource::moves);
  EXPECT_EQ(0, TrackingResource::copies);
  EXPECT_EQ(3, TrackingResource::destructs);
}

TEST(ResourceTests, ConstructResourceInPlace) {
  TrackingResource::reset();

  { ca::Resource<TrackingResource> res{10}; }

  EXPECT_EQ(1, TrackingResource::constructs);
  EXPECT_EQ(0, TrackingResource::moves);
  EXPECT_EQ(0, TrackingResource::copies);
  EXPECT_EQ(1, TrackingResource::destructs);
}

TEST(ResourceTests, CanHoldAReference) {
  TrackingResource::reset();

  {
    ca::Resource<TrackingResource> res{10};

    nu::Ref<ca::Resource<TrackingResource>> ref1 = &res;
    nu::Ref<ca::Resource<TrackingResource>> ref2 = ref1;
  }

  EXPECT_EQ(1, TrackingResource::constructs);
  EXPECT_EQ(0, TrackingResource::moves);
  EXPECT_EQ(0, TrackingResource::copies);
  EXPECT_EQ(1, TrackingResource::destructs);
}
