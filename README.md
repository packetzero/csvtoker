# csvtoker
Simple C++ CSV line parser

This is designed for critical path CSV parsing, such as handling high throughput rsyslog data.  It does not use iostreams or boost tokenizer.  Compared to a boost::tokenizer implementation, it performs half of the allocations, and is 3 times faster.

## Usage

```
#include <csvtoker.hpp>

std::vector<std::string> result;
CsvToker::parse("some,\"data fields\",here", result);  
```

## Building Tests
Assumes you have built the googletest release somewhere, and the path has lib and include subdirectories.
```
mkdir build && cd build

# for xcode
cmake -G Xcode -DGTESTDIR=/path/to/gtest/dist  ..
xcodebuild

# regular make
cmake -DGTESTDIR=/path/to/gtest/dist  ..
make
```
