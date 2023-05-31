<img src="https://user-images.githubusercontent.com/19248072/225727493-def23a0b-96e3-4310-aa9b-5f27fb0c6f2a.png"  width="300" height="200">


# Measurement Based Quantum Computation (MBQC) Simulator (MBQC V0.01)

Measurement-based quantum computation (MBQC) is an alternative computational model to the circuit-based quantum computation (CBQC) model. While many quantum computing simulators like Qiskit-aer, PyQuil-qvm, and QuEST are based on the CBQC model, QuEST stands out by offering flexibility with mid-circuit measurement and the ability to perform feed-forward actions, such as adaptive basis measurements for future qubits. This repository aims to simulate a general MBQC framework using QuEST and leveraging the Boost Graph Library ([BGL](https://www.boost.org/doc/libs/1_78_0/libs/graph/doc/index.html)), which is developed under the [Boost](https://www.boost.org/) library in C++.

By combining QuEST's capabilities with the power of the Boost Graph Library, this project provides a versatile MBQC simulator. As more verification protocols rely on MBQC, this repository can prove to be a valuable resource.

### What is MBQC


**<span style="color:red">TODO: Some brief MBQC overview content</span>**


## Project status

This project is in active development, labelled as version 0.01. There is some basic functionality in this repositors, but by no means is a complete simulator. To run this repository see below for external library requirements.

### External library requirements

Along with the standard C/C++ libraries there are two additional external libraries. Since MBQC is a graph theoretic based paradigm, the numerical library, Boost is called and with it, its graph library. To performthe quantum computation the current backend simulator is QuEST. Each of these libraries can be found here:

1. Boost: https://www.boost.org/
    1. Boost graph library: https://www.boost.org/doc/libs/1_78_0/libs/graph/doc/index.html
    2. Download: https://www.boost.org/users/download/
    3. Homebrew: https://formulae.brew.sh/formula/boost
2. QuEST: https://quest.qtechtheory.org/
    1. Download page: https://quest.qtechtheory.org/download/
    2. Github: https://github.com/QuEST-Kit/QuEST
    3. Github organisation: https://github.com/QuEST-Kit
    4. Documentation: https://quest-kit.github.io/QuEST/modules.html

These (Boost and QuEST) are both REQUIRED to run this MBQC.

1. Download boost, the `CMakeLists.txt` file in the root of this repository attempts to find Boost. For any trouble with this step please open and issue and we will respond as soon as possible.
2. Download the QuEST repository from GitHub and save the folder to `$HOME/Projects/QuEST/` and `CMakeLists.txt` should be able to load it. For any trouble with this step please open and issue and we will respond as soon as possible. (Note that `$HOME` is used in Linux to represent the home directory such as `/home/username/`

### Compile and execute a starter file

To run a simple script executing a two dimensional lattice graph and measuring every qubit do the following

1. Clone this repos with `git clone git@github.com:ediparquantum/MBQC.git` (I use ssh, use what works for you) to `$HOME/Projects`
2. Navigate to `$HOME/Projects` (eg `cd $HOME/Projects/MBQC`)
3. Make a directory called `build` in `$HOME/Projects/MBQC` with `mkdir build`.
4. Navigate to `build` (eg `cd build` assuming you are already in `cd $HOME/Projects/MBQC`)

Now you are ready to run cmake: `cmake ..` and should see

<img width="606" alt="Screenshot 2023-05-31 at 18 48 32" src="https://github.com/ediparquantum/MBQC/assets/19248072/e96fe87c-22da-4577-af21-4b8ee6bfe1e0">

Now run `make` and should see

<img width="323" alt="Screenshot 2023-05-31 at 18 49 43" src="https://github.com/ediparquantum/MBQC/assets/19248072/54bf8aae-a043-4ce1-97f8-7ed8db6b3cf8">

Now run `./mbqcStarterFile` and should see

<img width="406" alt="Screenshot 2023-05-31 at 18 50 42" src="https://github.com/ediparquantum/MBQC/assets/19248072/4c3b9da3-d212-49b5-b1a7-3ff77ee524ff">

For any trouble with this step please open and issue and we will respond as soon as possible.


