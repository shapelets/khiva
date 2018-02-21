#TSA

## License
This project is licensed under [MPL-v2](https://www.mozilla.org/en-US/MPL/2.0/).

##Installation
1. Install conan, c++ package manager, preferably through `pip install conan`.  For more informacion and alternative instalation optins, please refer to [conan manual page](http://docs.conan.io/en/latest/installation.html)
2. Run `conan intall --build`, which will bring down dependencies and generate the necessary include files for the `cmake` build.
3. Create `build` folder and, after moving into the new folder, run `cmake ..` 
4. Run the actual make for your environment.

###Caveats 
One of the recipies used by conan has an issue and it may require a manual change.  The file is called `conanfile.py` under `<home>./conan/data/google-benchmark/1.1.0/cpace6/stable/export` and you may need to replace line 24 with `cmake = CMake(self)`
 
 