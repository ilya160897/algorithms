category=$1
problem=$2

echo "Creating ${problem} with ${category} category..."

path=${category}/${problem}

problem_file=${path}/${problem}.h
test_file=${path}/test.cpp
cmake_file=${path}/CMakeLists.txt

sample_path=util/problem_creation_template/problem

mkdir -p ${path}
cp ${sample_path}/problem.h ${problem_file}
cp ${sample_path}/test.cpp ${test_file}
echo "add_subdirectory($problem)" > ${category}/CMakeLists.txt

if grep -q "^add_category($category)" CMakeLists.txt; then
    echo "add_category($category) already exists in CMakeLists.txt"
else
    echo "add_category($category)" >> CMakeLists.txt
    echo "Added add_category($category) to CMakeLists.txt"
fi

echo "add_algorithm_executable(${category} ${problem})" >> ${category}/${problem}/CMakeLists.txt
echo "Added add_algorithm_executable(${category} ${problem}) to ${category}/${problem}/CMakeLists.txt"

# Creating pretty class name using CamelCase
problem_camel_case=$(echo ${problem} | sed -r 's/(^|_)(\w)/\U\2/g')

echo "Problem camel case name : ${problem_camel_case}"

# # Substituting this classname
sed -i "s/SolutionClass/${problem_camel_case}/" ${problem_file} ${test_file}
sed -i "s/problem/${problem}/" ${problem_file} ${test_file}
