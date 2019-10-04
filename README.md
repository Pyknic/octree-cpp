# C++ Octree
Generic implementation of an Octree in C++.

## Usage
```cpp
#include "Octree.h"

struct Color {
   uint8_t red, green, blue;
   Color() : red{0}, green{0}, blue{0} {};
   Color(uint8_t red, uint8_t green, uint8_t blue) :
      red{red}, green{green}, blue{blue} {}
};

int main() {
    auto* colorTree { Octree<Color>::create(Color{}) };
    colorTree.set(20, 100, 5, Color{255, 0, 0});
}
```

## License

   Copyright 2019 Emil Forslund

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
