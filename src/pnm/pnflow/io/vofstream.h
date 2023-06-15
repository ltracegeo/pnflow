#ifndef _IO_VOFSTREAM_H_
#define _IO_VOFSTREAM_H_

#include <fstream>
#include <ios>
#include <memory>
#include <ostream>
#include <string>

#include "io/virtual_files_manager.h"

namespace io {

// Virtual ofstream
// If no virtual file was registered, interact with a actual file.
class vofstream {
  public:
    vofstream(const std::string &filename, std::ios_base::openmode mode = std::ios_base::out);
    ~vofstream();

    void close();

    template<typename T>
    vofstream& operator<<(const T &value) {
        if (actual_file_) {
            *actual_file_ << value;
        } else {
            VirtualFilesManager::Write(filename_, value);
        }
        return *this;
    }

    template<class T>
    vofstream& operator<<(const T *value) {
        if (actual_file_) {
            *actual_file_ << value;
        } else {
            VirtualFilesManager::Write(filename_, value);
        }
        return *this;
    }

    vofstream& operator<<(std::ostream& (*os)(std::ostream&));

  private:
    std::string filename_;
    std::unique_ptr<std::ofstream> actual_file_;
};

}  // namespace io

#endif  // _IO_VOFSTREAM_H_