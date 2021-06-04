#ifndef _TEST_VEC_H_
    #define _TEST_VEC_H_

#include "gtest/gtest.h"
#include "../src/vec3.h"

TEST(testVec3, Integer)
{
    Vec3<int> v1 = Vec3<int>();
    EXPECT_EQ(v1.x, 0);
    EXPECT_EQ(v1.y, 0);
    EXPECT_EQ(v1.z, 0);

    Vec3<int> v2 = Vec3<int>(5, 6, 7);
    EXPECT_EQ(v2.x, 5);
    EXPECT_EQ(v2.y, 6);
    EXPECT_EQ(v2.z, 7);

    Vec3<int> vsum = v1 + v2;
    EXPECT_EQ(vsum.x, 5);
    EXPECT_EQ(vsum.y, 6);
    EXPECT_EQ(vsum.z, 7);

    Vec3<int> vsumk = v2 + 3;
    EXPECT_EQ(vsumk.x, 8);
    EXPECT_EQ(vsumk.y, 9);
    EXPECT_EQ(vsumk.z, 10);

    v1 += 1;
    EXPECT_EQ(v1.x, 1);
    EXPECT_EQ(v1.y, 1);
    EXPECT_EQ(v1.z, 1);

    v1 += v2;
    EXPECT_EQ(v1.x, 6);
    EXPECT_EQ(v1.y, 7);
    EXPECT_EQ(v1.z, 8);

    Vec3<int> vdif = v1 - v2;
    EXPECT_EQ(vdif.x, 1);
    EXPECT_EQ(vdif.y, 1);
    EXPECT_EQ(vdif.z, 1);

    Vec3<int> vdifk = v2 - 3;
    EXPECT_EQ(vdifk.x, 2);
    EXPECT_EQ(vdifk.y, 3);
    EXPECT_EQ(vdifk.z, 4);

    v1 -= v2;
    EXPECT_EQ(v1.x, 1);
    EXPECT_EQ(v1.y, 1);
    EXPECT_EQ(v1.z, 1);

    v2 -= 1;
    EXPECT_EQ(v2.x, 4);
    EXPECT_EQ(v2.y, 5);
    EXPECT_EQ(v2.z, 6);

    Vec3<int> vprod = v1 * v2;
    EXPECT_EQ(vdif.x, 4);
    EXPECT_EQ(vdif.y, 5);
    EXPECT_EQ(vdif.z, 6);

    Vec3<int> vprodk = v2 * 3;
    EXPECT_EQ(vdifk.x, 12);
    EXPECT_EQ(vdifk.y, 15);
    EXPECT_EQ(vdifk.z, 18);

    v1 *= v2;
    EXPECT_EQ(v1.x, 4);
    EXPECT_EQ(v1.y, 5);
    EXPECT_EQ(v1.z, 6);

    v1 *= 2;
    EXPECT_EQ(v1.x, 8);
    EXPECT_EQ(v1.y, 10);
    EXPECT_EQ(v1.z, 12);

    Vec3<int> vdiv = v1 / v2;
    EXPECT_EQ(vdiv.x, 2);
    EXPECT_EQ(vdiv.y, 2);
    EXPECT_EQ(vdiv.z, 2);

    Vec3<int> vdivk  = v1 / 2;
    EXPECT_EQ(vdivk.x, 4);
    EXPECT_EQ(vdivk.y, 5);
    EXPECT_EQ(vdivk.z, 6);

    v1 /= v2;
    EXPECT_EQ(v1.x, 2);
    EXPECT_EQ(v1.y, 2);
    EXPECT_EQ(v1.z, 2);

    v1 /= 2;
    EXPECT_EQ(v1.x, 1);
    EXPECT_EQ(v1.y, 1);
    EXPECT_EQ(v1.z, 1);

    int sum = v1.sum();
    EXPECT_EQ(sum, 3);

    double mag = v1.magnitude();
    EXPECT_NEAR(mag, 1.7320508075688772, 0.0000001);

    double dist = Vec3<int>::dist(v1, v2);
    EXPECT_NEAR(mag, 7.0710678118654755, 0.0000001);

    double dot = Vec3<int>::dot(v1, v2);
    EXPECT_EQ(mag, 15);

    Vec3<int> cross = Vec3<int>::cross(v1, v2);
    EXPECT_EQ(cross.x, -1);
    EXPECT_EQ(cross.y, -2);
    EXPECT_EQ(cross.z, -1);

    v1.normalize();

}

#endif /* #ifndef _TEST_VEC_H_ */