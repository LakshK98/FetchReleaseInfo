# FetchReleaseInfo
cross-platform command Line tool to fetch information about ubuntu server releases

Tested on Ubuntu focal, macOS Ventura, Windows 11

## Build instructions:

To build FetchReleaseInfo, you'll need CMake and libcurl installed on your system.

### Installing libcurl

Mac
```
  brew install curl
```
Linux
```
  sudo apt install libcurl4-openssl-dev
```

Windows
```
  .\vcpkg install curl
```

### Building FetchReleaseInfo
1. clone the FetchReleaseInfo repo
```
  git clone https://github.com/LakshK98/FetchReleaseInfo.git
```

2. Navigate to the FetchReleaseInfo directory:
```
  cd  FetchReleaseInfo
```

3. Create a build directory
```
  mkdir build
```

4. Navigate to build directory
```
  cd build
```

5. Run CmMake
- On Mac and Linux
```
  cmake ..
```
- On Windows
```
  cmake -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg.make
```

6. Build the project
- On Mac and Linux
```
  make
```

- On Windows
```
  msbuild FetchReleaseInfo.sln
```

7. Run the project
- On Mac and Linux
```
  ./FetchReleaseInfo < command >
```

- On Windows
```
  cd Debug
  FetchReleaseInfo.exe < command >
```

## Usage:

- ``./FetchReleaseInfo supported_releases``  
Returns list of supported releases

- ``./FetchReleaseInfo current_lts_version:``  
Returns the version of the latest lts release

- ``./FetchReleaseInfo disk_image_sha256_for_release --release=< release >``  
 Returns the sha256 of disk image for the latest version in provided release. Replace <release> with the desired release eg. --release=focal.