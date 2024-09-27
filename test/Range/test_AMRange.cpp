#include "../../AMRange.h"
#include "gtest/gtest.h"

using namespace AMCore;


TEST(AMRange, basicTest)
{

    //operator ==
    AMRange<int> r1(1,5);
    AMRange<int> r2(1,5);
    EXPECT_EQ(r1, r2);
    r2.to = 6;
    EXPECT_NE(r1, r2);

    //asignment
    r1 = r2;
    EXPECT_EQ(r1, r2);

    //intersect
    AMRange<int> ri1(1,8);
    AMRange<int> ri2(5, 12);
    AMRange<int> ri3 = ri1;
    ri3.intersect(ri2);
    EXPECT_EQ(ri3, AMRange<int>(5,8));
    ri3 = ri2;
    ri3.intersect(ri1);
    EXPECT_EQ(ri3, AMRange<int>(5,8));
    ri2 = AMRange(1,10);
    ri3 = ri1;
    ri3.intersect(ri2);
    EXPECT_EQ(ri3, AMRange<int>(1,8));
    ri2 = AMRange(8, 12);
    ri3 = ri1;
    ri3.intersect(ri2);
    EXPECT_TRUE(ri3.empty());
    ri3 = intersect(ri1, AMRange(9,12));
    EXPECT_TRUE(ri3.empty());
    ri3 = intersect(ri1, AMRange(-9,-1));
    EXPECT_TRUE(ri3.empty());
    ri3 = intersect(ri1, AMRange(-9,1));
    EXPECT_TRUE(ri3.empty());
    ri3 = intersect(ri1, AMRange(-9,2));
    EXPECT_TRUE(!ri3.empty());

    //empty
    EXPECT_TRUE(AMRange(-9,-9).empty());
    EXPECT_TRUE(AMRange(2,2).empty());
    EXPECT_FALSE(AMRange(4,9).empty());
    EXPECT_FALSE(AMRange(4,-9).empty());

    //valid
    EXPECT_TRUE(AMRange(-9,10).valid());
    EXPECT_TRUE(AMRange(0,0).valid());
    EXPECT_FALSE(AMRange(0,-1).valid());

    //in
    EXPECT_TRUE(AMRange(-5,5).in(0));
    EXPECT_TRUE(AMRange(-5,5).in(-5));
    EXPECT_FALSE(AMRange(-5,5).in(-6));
    EXPECT_FALSE(AMRange(-5,5).in(5));
    EXPECT_FALSE(AMRange(-5,5).in(10));
    EXPECT_TRUE(AMRange(-5,5).in(AMRange(0,1)));
    EXPECT_TRUE(AMRange(-5,5).in(AMRange(0,5)));
    EXPECT_TRUE(AMRange(-5,5).in(AMRange(-5,2)));
    EXPECT_TRUE(AMRange(-5,5).in(AMRange(-5,5)));
    EXPECT_FALSE(AMRange(-5,5).in(AMRange(-10,0)));
    EXPECT_FALSE(AMRange(-5,5).in(AMRange(-5,6)));
    EXPECT_FALSE(AMRange(-5,5).in(AMRange(-10,-5)));
    EXPECT_FALSE(AMRange(-5,5).in(AMRange(-5,-9)));
    EXPECT_FALSE(AMRange(-5,5).in(AMRange(-6,5)));
    EXPECT_FALSE(AMRange(-5,5).in(AMRange(-10,15)));
    EXPECT_FALSE(AMRange(5,-5).in(AMRange( 2, 5)));
    EXPECT_FALSE(AMRange(5,-5).in(AMRange( 2, -5)));

    //operator <
    EXPECT_TRUE(AMRange(-5,5) < AMRange(0,10));
    EXPECT_TRUE(AMRange(-5,5) < AMRange(-4,10));
    EXPECT_TRUE(AMRange(-5,5) < AMRange(-5,10));
    EXPECT_TRUE(AMRange(-5,5) < AMRange(-5,10));
    EXPECT_FALSE(AMRange(-5,5) < AMRange(-5,5));
    EXPECT_FALSE(AMRange(-5,5) < AMRange(-10,10));
    EXPECT_FALSE(AMRange(-5,5) < AMRange(-5,2));

    //operator +
    AMRange rp1(1,5);
    AMRange rp2(4,10);
    AMRange rp3 = rp1;
    rp3 += rp2;
    EXPECT_EQ(rp3,AMRange(1,10));
    EXPECT_EQ(AMRange(1,5) + AMRange(1,7), AMRange(1,7));
    EXPECT_EQ(AMRange(1,5) + AMRange(-1,2), AMRange(-1,5));
    EXPECT_EQ(AMRange(1,5) + AMRange(-1,10), AMRange(-1,10));
    EXPECT_EQ(AMRange(1,5) + AMRange(2,3), AMRange(1,5));
    EXPECT_FALSE((AMRange(1,5) + AMRange(6,7)).valid());
    EXPECT_FALSE((AMRange(1,5) + AMRange(9,7)).valid());
    EXPECT_FALSE((AMRange(11,5) + AMRange(5,7)).valid());
    EXPECT_FALSE((AMRange(5,7) + AMRange(11,5)).valid());
    EXPECT_FALSE((AMRange(5,7) + AMRange(6,5)).valid());
    EXPECT_TRUE((AMRange(5,7) + AMRange(-11,5)).valid());
    EXPECT_FALSE((AMRange(-5,-1) + AMRange(6,7)).valid());

    //operator -
    AMRange rm1(1,5);
    AMRange rm2(4,10);
    AMRange rm3 = rp1;
    rp3 -= rp2;
    EXPECT_EQ(rp3,AMRange(1,4));
    EXPECT_EQ(AMRange(1,5) - AMRange(3,7), AMRange(1,3));
    EXPECT_EQ(AMRange(1,5) - AMRange(-1,2), AMRange(2,5));
    EXPECT_EQ(AMRange(1,5) - AMRange(7,10), AMRange(1,5));
    EXPECT_EQ(AMRange(1,5) - AMRange(5,13), AMRange(1,5));
    EXPECT_FALSE((AMRange(1,15) - AMRange(4,7)).valid());
    EXPECT_FALSE((AMRange(1,5) - AMRange(9,7)).valid());
    EXPECT_FALSE((AMRange(11,5) - AMRange(5,7)).valid());
    EXPECT_TRUE((AMRange(5,7) - AMRange(-11,5)).valid());
    EXPECT_TRUE((AMRange(-5,-1) - AMRange(-1,7)).valid());
    EXPECT_TRUE((AMRange(-5,-1) - AMRange(-10,7)).valid());
    EXPECT_TRUE((AMRange(-5,-1) - AMRange(-10,7)).empty());

}

TEST(AMRange, setTest)
{
    std::set<AMRange<int> > s01;
    std::set<AMRange<int> > s02 = {AMRange(1,5)};
    std::set<AMRange<int> > s03 = {AMRange(1,5), AMRange(7, 9)};
    std::set<AMRange<int> > s04 = {AMRange(1,5), AMRange(5, 9)};
    std::set<AMRange<int> > s05 = {AMRange(1,5), AMRange(3, 9)};
    std::set<AMRange<int> > s06 = {AMRange(1,5), AMRange(12, 9)};
    std::set<AMRange<int> > s07 = {AMRange(1,5), AMRange(7, 9), AMRange(7, 12), AMRange(12, 15), AMRange(17, 19)};
    std::set<AMRange<int> > s08 = {AMRange(1, 5), AMRange(7,15), AMRange(17, 19)};
    std::set<AMRange<int> > s09 = {AMRange(16, 17), AMRange(19,20), AMRange(27, 29)};
    std::set<AMRange<int> > s10 = {AMRange(1, 5), AMRange(7,15),AMRange(16, 20), AMRange(27, 29)};
    std::set<AMRange<int> > s11 = {AMRange(1, 15), AMRange(17, 19)};
    std::set<AMRange<int> > s12 = {AMRange(1, 9)};
    std::set<AMRange<int> > s13 = {AMRange(9, 15), AMRange(17, 19)};
    std::set<AMRange<int> > s14 = {AMRange(-1, 8), AMRange(15,18)};
    std::set<AMRange<int> > s15 = {AMRange(8, 15), AMRange(18,19)};
    std::set<AMRange<int> > s16 = {AMRange(0,1), AMRange(5, 7), AMRange(15, 17), AMRange(19, 35)};
    std::set<AMRange<int> > s17 = {AMRange(1, 5), AMRange(7,15), AMRange(17, 18)};
    std::set<AMRange<int> > s18 = {AMRange(5, 7), AMRange(15,16),AMRange(20, 27)};


    //isPacked
    EXPECT_TRUE(isPacked(s01));
    EXPECT_TRUE(isPacked(s02));
    EXPECT_TRUE(isPacked(s03));
    EXPECT_FALSE(isPacked(s04));
    EXPECT_FALSE(isPacked(s05));
    EXPECT_FALSE(isPacked(s06));

    //valid
    EXPECT_TRUE(valid(s01));
    EXPECT_TRUE(valid(s02));
    EXPECT_TRUE(valid(s03));
    EXPECT_TRUE(valid(s04));
    EXPECT_TRUE(valid(s05));
    EXPECT_FALSE(valid(s06));

    //pack
    EXPECT_EQ(pack(s01), s01);
    EXPECT_EQ(pack(s02), s02);
    EXPECT_EQ(pack(s03), s03);
    EXPECT_EQ(pack(s04), std::set<AMRange<int> >{AMRange(1, 9)});
    EXPECT_EQ(pack(s05), std::set<AMRange<int> >{AMRange(1, 9)});
    EXPECT_EQ(pack(s07), s08);
    EXPECT_EQ(pack(s08), s08);

    //operator+
    EXPECT_EQ(s07 + s05, s11);
    EXPECT_EQ(s03 + s01, s03);
    EXPECT_EQ(s03 + s02, s03);
    EXPECT_EQ(s03 + s04, s12);
    EXPECT_EQ(s07 + s09, s10);

    //operator-
    EXPECT_EQ(s07 - s05, s13);
    EXPECT_EQ(s03 - s01, s03);
    EXPECT_EQ(s03 - s02, std::set<AMRange<int> >{AMRange(7, 9)});
    EXPECT_EQ(s04 - s03, std::set<AMRange<int> >{AMRange(5, 7)});
    EXPECT_EQ(s07 - s09, s08);
    EXPECT_EQ(s07 - s08, s01);
    EXPECT_EQ(s07 - s14, s15);
    EXPECT_EQ(AMRange(0, 35) - s07, s16);
    EXPECT_EQ(s07 - AMRange(18, 20), s17);
    EXPECT_EQ(AMRange(1, 28) - s10, s18);
}


int main(int argc, char **argv) {

     ::testing::InitGoogleTest(&argc, argv);
     return RUN_ALL_TESTS();
}
