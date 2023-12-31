fd "\.cpp" | xargs clang-format -i
fd "\.h" | grep -v "tools/catch/catch.hpp" | xargs clang-format -i
