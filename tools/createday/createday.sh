rootdir=../..
targetday=$1

mkdir ${rootdir}/days/day${targetday}
mkdir ${rootdir}/days/day${targetday}/include
mkdir ${rootdir}/days/day${targetday}/src
mkdir ${rootdir}/days/day${targetday}/tests

cp example_CMakeLists ${rootdir}/days/day${targetday}/CMakeLists.txt
sed -i "s/EXAMPLEDAY/${targetday}/" ${rootdir}/days/day${targetday}/CMakeLists.txt
cp example_test ${rootdir}/days/day${targetday}/tests/test.cpp
sed -i "s/EXAMPLEDAY/${targetday}/" ${rootdir}/days/day${targetday}/tests/test.cpp
cp example_cpp ${rootdir}/days/day${targetday}/src/Day${targetday}.cpp
sed -i "s/EXAMPLEDAY/${targetday}/" ${rootdir}/days/day${targetday}/src/Day${targetday}.cpp
cp example_h ${rootdir}/days/day${targetday}/include/Day${targetday}.h
sed -i "s/EXAMPLEDAY/${targetday}/" ${rootdir}/days/day${targetday}/include/Day${targetday}.h

sed -i "/^    # Further days go here/i\ \ \ \ day${targetday}" ${rootdir}/CMakeLists.txt

sed -i "/^    \/\/Further days go here/i\ \ \ \ {\"Day${targetday}\", std::make_shared<Day${targetday}>(\"..\/res\/day${targetday}.txt\")}," ${rootdir}/aoc2022.cpp
sed -i "/^\/\/Further day includes go here/i #include \"Day${targetday}.h\"" ${rootdir}/aoc2022.cpp

