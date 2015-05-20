To use this example, do the following:

1. Make sure you have a recent Java version installed (e.g. 1.7 or higher).

2. Run

   java -jar ../../_buildtools/DataStructureGenerator-r1.jar --withCMake Example6Data.odvd

   A new folder libexample6data will be generated containing all the header
   and source files of the data specification in the Example6Data.odvd file.

3. Edit the ../CMakeFile.txt (in the super folder) to enable building this
   example project.

4. Return to your build directory and re-run cmake to  make sure that the
   newly activated project is considered during the build cycle.

5. Run example6sender and example6receiver to see how the data structure
   is used in the example.
