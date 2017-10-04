
#include "canvas/math/transform.h"
#include "gtest/gtest.h"

//#include "glm/ext.hpp"
//#include "glm/glm.hpp"

TEST(TransformTests, Ortho) {
    F32 left = 0.f;
    F32 right = 1600.f;
    F32 top = 0.f;
    F32 bottom = 900.f;
    F32 near = -1.f;
    F32 far = 1.f;

    ca::Mat4 ortho = ca::ortho(left, right, bottom, top);

    // clang-format off
    ca::Mat4 expected = ca::Mat4{
            2.f / (right - left), 0.f, 0.f, 0.f,
            0.f, 2.f / (top - bottom), 0.f, 0.f,
            0.f, 0.f, 2.f / (far - near), 0.f,
            -(right + left) / (right - left), -(top + bottom) / (top - bottom), -(far + near) / (far - near), 1.f
    };
    // clang-format on

    EXPECT_EQ(expected, ortho);
}

#if 0
TEST(TransformTests, Sanity) {
    glm::mat4x4 o = glm::ortho(0.f, 1600.f, 900.f, 0.f);
    auto point = o * glm::vec4(10.f, 20.f, 0.f, 0.f);

    ca::Mat4 identity;

    // ca::Mat4 ortho = ca::ortho(-1.f, 1.f, 1.f, -1.f, -1.f, 1.f);
    ca::Mat4 ortho = ca::ortho(0.f, 1600.f, 900.f, 0.f);

    ca::Vec4 p = ortho * ca::Vec4(10.f, 20.f, 0.f, 0.f);

    LOG(Info) << p;
}
#endif  // 0
