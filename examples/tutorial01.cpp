/**
 * @page tutorial01 Tutorial 1: Getting Started 
 * @ingroup GettingStarted
 * 
 * @section intro Introduction
 * 
 * This tutorial demonstrates the how-to of getting started. This includes the the usage of `cmake` to compile and run executable programs and algorithms in the MBQC + QuEST + Boost framework. Before proceeding, ensure that you have the following dependencies installed:
 * 
 * @subsection dependencies Dependencies
 * 
 * Note: MBQC was developed using the Unix and Linux operating systems, there is no specific reason this software should not work on Windows OS, but it has not been tested.
 * 
 * - Make
 *   - See official Make website for download instructions by clicking [here](https://www.gnu.org/software/make/)
 *   - MBQC uses `GNU Make 3.81`
 * - CMake
 *   - See official CMake website for download instructions by clicking [here](https://cmake.org/)
 *   - MBQC uses `cmake version 3.25.1` and requires minimum `cmake version 3.12`.
 * - Graphviz
 *   - See official Graphviz website for download instructions by clicking [here](https://graphviz.org/)
 *   - MBQC uses `dot - graphviz version 8.0.5 (20230430.1635)`
 * - QuEST
 *   - See QuEST GitHub repository for download instructions by clicking [here](https://github.com/QuEST-Kit/QuEST)
 *   - See QuEST website for download instructions by clicking [here](https://quest.qtechtheory.org/)
 *   - Follow the QuEST documentation for downloading and running.
 *   - QuEST is capable of being used with many different hardware backends, but development of MBQC has been done in vanilla QuEST used as-is from GitHub. 
 *   - MBQC uses the `master` branch supplied at GitHub.
 * - Boost
 *   - See Boost official website for download instruction by clicking [here](https://www.boost.org/)
 *   - Depending on OS there are different pathways to download Boost, in mac Homebrew ([here](https://brew.sh/)) is a popular package manager, as well as MacPorts ([here](https://www.macports.org/))
 *   - MBQC uses `boost version 1.81`
 * 
 * Once you have the necessary dependencies, you can continue with the build process.
 * 
 * @subsection gettingStarted Getting MBQC
 * 
 * Once the dependencies have been met, the MBQC software `code` needs to be stored on your device. To obtain the MBQC repository, you can follow these steps:
 *
 * 1. Go to the MBQC repository on GitHub: [MBQC Repository](https://github.com/ediparquantum/MBQC)
 * 2. Locate the green "Code" button and select your preferred method to download the repository:
 *    - HTTPS: `https://github.com/ediparquantum/MBQC.git`
 *    - SSH: `git@github.com:ediparquantum/MBQC.git`
 *    - GitHub CLI: `gh repo clone ediparquantum/MBQC`
 *
 * In your terminal, navigate to the folder where you want to access the project, for example:
 * @code{.bash}
 * cd /home/username/projects/
 * @endcode
 *
 * Clone the repository using one of the provided methods, such as the SSH method:
 * @code{.bash}
 * git clone git@github.com:ediparquantum/MBQC.git
 * @endcode
 *
 * @subsection runningMBQC Running MBQC
 * 
 * Navigate to the MBQC directory:
 * @code{.bash}
 * cd MBQC
 * @endcode
 *
 * Create a "build" directory:
 * @code{.bash}
 * mkdir build
 * @endcode
 *
 * Change to the build directory:
 * @code{.bash}
 * cd build
 * @endcode
 *
 * At this point, your current directory should be something like:
 * @code{.bash}
 * /home/username/projects/MBQC/build
 * @endcode
 * 
 * Build the project
 * 
 * @code{.bash}
 * cmake ..
 * @endcode
 * 
 * If there are no problems, then after some text is printed to the scree, the following should appear and the `cmake ..` has been successfully executed.
 * @code{.bash}
 *  -- Configuring done
 *  -- Generating done
 *  -- Build files have been written to: /home/username/projects/MBQC/build
 * @endcode
 * 
 * According the the file `CMakeLists.txt` located in `/home/username/projects/MBQC/` when no `USER_SOURCE` file is issued at cmake (`cmake .. -DUSER_SOURCE="some_path/to/a/file.cpp") the an example script `examples/mbqcStarter.cpp` that is chosen to be compiled. Next in the terminal run
 * 
 * @code{.cpp}
 * make
 * @endcode
 * 
 * Then run the executable
 * @code{.cpp}
 * ./mbqcStarter
 * @endcode
 * 
 * The output should look something like this.
 * 
 * @code{.bash}
 * Measured outcome vector has 16 qubits.
 * The measurements are: 0 1 1 1 0 0 1 0 0 0 1 0 1 0 1 1 
 * 
 *
 * Measured outcome lattice: 
 * 0 0 0 1 
 * 1 0 0 0 
 * 1 1 1 1 
 * 1 0 0 1 
 * @endcode
 * 
 * @subsection runningOtherFile Running Other Files
 * 
 * In the process of development many files will no doubt be created. To run these make use of the two options during `cmake`
 * 
 * 1. `USER_SOURCE`
 * 2. `OUTPUT_EXE`
 * 
 * Run the `cmake` with these options. Note I chose to make the executable the same name as the file, but this is not needed, choose what suits. See CMake website for background.
 * @code{.bash}
 * cmake .. -DUSER_SOURCE="fileToBeExecuted.cpp" -DOUTPUT_EXE=fileToBeExecuted
 * @endcode
 * 
 * Run the `make` command
 * @code{.bash}
 * make
 * @endcode
 * 
 * Execute the executable script.
 * @code{.bash}
 * ./fileToBeExecuted
 * @endcode
 * 
 * This is how you run a file. For any help, questions or problems see the [MBQC](https://github.com/ediparquantum/MBQC) repository site to create an 
 * - [issue](https://github.com/ediparquantum/MBQC/issues), 
 * - [pull-request](https://github.com/ediparquantum/MBQC/pulls) or 
 * - open a [discussion](https://github.com/ediparquantum/MBQC/discussions).
 */
