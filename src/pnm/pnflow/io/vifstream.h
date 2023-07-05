#ifndef _IO_VIFSTREAM_H_
#define _IO_VIFSTREAM_H_

#include <fstream>
#include <ios>
#include <memory>
#include <ostream>
#include <string>

#include "io/virtual_files_manager.h"

namespace io {

// Virtual ifstream
// If no virtual file was registered, interact with a actual file.
class vifstream {
  public:
    vifstream();
    vifstream(const std::string &filename, std::ios_base::openmode mode = std::ios_base::in);
    ~vifstream();

    void open(const std::string &filename, std::ios_base::openmode mode = std::ios_base::in);

    vifstream& read(char *s, std::streamsize count);

    void close();

    template<typename T>
    vifstream& operator>>(T &value) {
        if (actual_file_) {
            *actual_file_ >> value;
        } else {
            VirtualFilesManager::Read(filename_) >> value;
        }
        return *this;
    }

    template<class T>
    vifstream& operator>>(T *value) {
        if (actual_file_) {
            *actual_file_ >> value;
        } else {
            VirtualFilesManager::Read(filename_) >> value;
        }
        return *this;
    }

    operator bool() const;

    // vifstream& operator<<(std::ostream& (*os)(std::ostream&));

  private:
    std::string filename_;
    std::unique_ptr<std::ifstream> actual_file_;
};

}  // namespace io

#endif  // _IO_VIFSTREAM_H_