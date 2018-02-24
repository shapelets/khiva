#TSA

## License
This project is licensed under [MPL-v2](https://www.mozilla.org/en-US/MPL/2.0/).

##Installation
1. Install conan, c++ package manager, preferably through `pip install conan`.  For more informacion and alternative instalation optins, please refer to [conan manual page](http://docs.conan.io/en/latest/installation.html)
2. Run `conan remote add conan-mpusz https://api.bintray.com/conan/mpusz/conan-mpusz`
3. Run `conan install . --build`, which will bring down dependencies and generate the necessary include files for the `cmake` build.
4. Create `build` folder and, after moving into the new folder, run `cmake ..` 
5. Run the actual make for your environment.
 
 