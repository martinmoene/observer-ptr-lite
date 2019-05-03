from conans import ConanFile, CMake

class ObserverPtrLiteConan(ConanFile):
    version = "0.3.0"
    name = "observer-ptr-lite"
    description = "An observer_ptr for C++98 and later in a single-file header-only library (Extensions for Library Fundamentals, v2, v3) "
    license = "Boost Software License - Version 1.0. http://www.boost.org/LICENSE_1_0.txt"
    url = "https://github.com/martinmoene/observer-ptr-lite.git"
    exports_sources = "include/nonstd/*", "CMakeLists.txt", "cmake/*", "LICENSE.txt"
    build_policy = "missing"
    author = "Martin Moene"

    def build(self):
        """Avoid warning on build step"""
        pass

    def package(self):
        """Run CMake install"""
        cmake = CMake(self)
        cmake.definitions["NSOP_OPT_BUILD_TESTS"] = "OFF"
        cmake.definitions["NSOP_OPT_BUILD_EXAMPLES"] = "OFF"
        cmake.configure()
        cmake.install()

    def package_info(self):
        self.info.header_only()
