# AMRange - basic operation with ranges and sets of ranges

Range is set of numeric type values described by formula <from, to).

## Usage

### Range operations

#### Range comparison

    //operator ==
    AMRange<int> r1(1,5);
    AMRange<int> r2(1,5);
    EXPECT_EQ(r1, r2);

#### Range assignment     

    //assignment
    r1 = r2;
    EXPECT_EQ(r1, r2);

#### Range intersection

    //intersect
    AMRange<int> ri1(1,8);
    AMRange<int> ri2(5, 12);
    AMRange<int> ri3 = ri1;
    ri3.intersect(ri2);
    EXPECT_EQ(ri3, AMRange<int>(5,8));

#### Test range for empty    

    //empty
    EXPECT_TRUE(AMRange(2,2).empty());
    EXPECT_FALSE(AMRange(4,9).empty());

#### Test range validity

    //valid
    EXPECT_TRUE(AMRange(-9,10).valid());
    EXPECT_FALSE(AMRange(0,-1).valid());

#### Test subrange

    //in
    EXPECT_TRUE(AMRange(-5,5).in(0));
    EXPECT_FALSE(AMRange(-5,5).in(-6));

#### Range operator less

    //operator <
    EXPECT_TRUE(AMRange(-5,5) < AMRange(0,10));
    EXPECT_FALSE(AMRange(-5,5) < AMRange(-10,10));

#### Range operator plus

    //operator +
    AMRange rp1(1,5);
    AMRange rp2(4,10);
    AMRange rp3 = rp1;
    rp3 += rp2;
    EXPECT_EQ(rp3,AMRange(1,10));

#### Range operator minus

    //operator -
    AMRange rm1(1,5);
    AMRange rm2(4,10);
    AMRange rm3 = rp1;
    rp3 -= rp2;
    EXPECT_EQ(rp3,AMRange(1,4));
    
### Set of ranges operations

#### Set of ranges definitions

    std::set<AMRange<int> > s01;
    std::set<AMRange<int> > s05 = {AMRange(1,5), AMRange(3, 9)};
    std::set<AMRange<int> > s07 = {AMRange(1,5), AMRange(7, 9), AMRange(7, 12), AMRange(12, 15), AMRange(17, 19)};
    std::set<AMRange<int> > s11 = {AMRange(1, 15), AMRange(17, 19)};
    std::set<AMRange<int> > s13 = {AMRange(9, 15), AMRange(17, 19)};

#### Test set of ranges for canonical state

    //isPacked
    EXPECT_TRUE(isPacked(s01));
    EXPECT_FALSE(isPacked(s05));

#### Test set of ranges for validity

    //valid
    EXPECT_TRUE(valid(s01));
    EXPECT_TRUE(valid(s05));

#### Pack set of ranges to canonical state

    //pack
    EXPECT_EQ(pack(s01), s01);
    EXPECT_EQ(pack(s05), std::set<AMRange<int> >{AMRange(1, 9)});

#### Set of ranges add

    //operator+
    EXPECT_EQ(s07 + s05, s11);

#### Set of ranges subtract

    //operator-
    EXPECT_EQ(s07 - s05, s13);;

## Documetation

There are doxygen generated documentation [here on andromeda.robotea.com](http://andromeda.robotea.com/amrange/latest/).

## Building AMRange

### Getting sources

```bash
git submodule update
```

### Compiling

```bash

mkdir cmake-build-debug

cd cmake-build-debug

cmake ..

make
```

### Single test (not necessary)

```bash
./TEST_AMRange
```

## License

This library is under MIT license.

## Contribute

Please contact [me](mailto:zdenek.skulinek\@robotea.com\?subject\=License%20for%20AMRange).

## Ask for help

Please contact [me](mailto:zdenek.skulinek\@robotea.com\?subject\=Consultation).

## Dependencies

- [Google test](https://github.com/google/googletest.git)
