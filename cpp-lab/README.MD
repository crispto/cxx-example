a laboratory space for c++, where your c++ code can be test conviniently.

each file in **samples** is a independent test case;
files in src will build to a libaray called `labor`

# usage

```bash
// clone project and build library
git clone ${project_url}
cd ${project_folder}
mkdir build && cd build
cmake ..
make install


// build the sample
cd samples
mkdir build &&cd build
cmake ..
make

```
