# cpp-cmake-template

# Features
- [**CMake**](!https://cmake.org/) as main build system for C++ project
- Format cpp files by [**clang-format**](!https://clang.llvm.org/docs/ClangFormat.html)
- Format cmake files by [**cmake-format**](!https://cmake-format.readthedocs.io/en/latest/)
- Documentation by [**MkDocs**](https://www.mkdocs.org/) with [Github Pages](https://pages.github.com/).
- [**Dracula**](https://github.com/dracula/mkdocs) as main theme of MkDocs
- [**Catch2**](https://github.com/catchorg/Catch2) as main testing framework
- [**Parse git tag**](cmake/parse_git_tag.cmake) and automatic version header generation.
- [**Static Analyzers**](cmake/static_analyzers.cmake) by [cppcheck](!https://github.com/danmar/cppcheck) and [clang-tidy](!https://clang.llvm.org/extra/clang-tidy/).
- Project configuration by [**Kconfiglib**](https://github.com/ulfalizer/Kconfiglib), [Tips](https://docs.zephyrproject.org/latest/build/kconfig/tips.html)

# Prerequisites

All requirements are **optional**.

Formatting Requirements
```bash
pip install cmake-format
sudo apt install clang-format 
```

Documentation Requirements
```bash
pip install mkdocs mkdocs-material pymdown-extensions mkdocs-dracula-theme 
```

Kconfig Requirements
```bash
pip install kconfiglib
```

Testing Requirements 
- Install appropriate version of [**Catch2**](https://github.com/catchorg/Catch2). 

Static Analyzers Requirements
```bash
sudo apt install cppcheck clang-tidy
```

# Getting Started
## Automatic Setup
```bash
make initialize PROJECT_NAME=$(PROJECT_NAME) # set PROJECT_NAME name without "".
```

## Manual Setup
- Change cmake/cpp-cmake-templateConfig.cmake.in to cmake/$(PROJECT_NAME)Config.cmake.in
- Change include/cpp-cmake-template to include/$(PROJECT_NAME)
- Replace 'cpp-cmake-template' to '$(PROJECT_NAME)' of CMakeLists.txt

# Documentations
[**MkDocs tutorial**](https://www.mkdocs.org/getting-started/)

Go to the settings of your repository and ensure that the [publishing source branch](https://docs.github.com/en/pages/getting-started-with-github-pages/configuring-a-publishing-source-for-your-github-pages-site) for your GitHub Page is set to gh-pages

# Running examples
```bash
mkdir -p build && cd build
cmake .. -DBUILD_EXAMPLE=ON
cmake --build .
make run_examples # if you want to run all examples
```

# Running the tests
```bash
mkdir -p build && cd build
cmake .. -DBUILD_TESTING=ON
cmake --build .
ctest # or make test
```

# License
This project is licensed under the [BSD-3-Clause](https://opensource.org/license/bsd-3-clause) - see the
[LICENSE](LICENSE) file for details

# Contact
timetravelCat - timetraveler930@gmail.com