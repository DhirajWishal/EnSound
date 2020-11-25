<div style="text-align:center"><img src="https://github.com/DhirajWishal/EnSound/blob/master/Assets/Logo/EnSound_L4.png" alt="EnSound Logo" /></div>
A cross-platform audio engine designed for games! Ensound is designed with a data-driven backend which consists of multiple APIs which are selectable (which are available for a given platform) at runtime and also contains two APIs, low level and high level (engine).

## Build
To build the repository, you need these tools/ applications,
- [GitHub Desktop](https://desktop.github.com/)/ [GitBash](https://git-scm.com/downloads).
- [Visual Studio](https://visualstudio.microsoft.com/) (we recommend using 2019) with the C++ workloads installed.
- [Premake5](https://premake.github.io/).

After installing all of them (which are required), clone the repository to a local directory either using GitHub Desktop or GitBash. The run the `GenerateProjects.bat` file to create the required solution files. Then open the `Ensound.sln` file in Visual Studio.

Select the required configuration (`Release` or `Debug`) and build the `Ensound` project. The output files will be stored at `Builds/Binaries/Ensound/" directory.

## License
The Ensound codebase is licensed under [Apache v2.0](https://www.apache.org/licenses/LICENSE-2.0).