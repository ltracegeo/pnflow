#include "io/vifstream.h"

namespace io {

vifstream::vifstream() {}

vifstream::vifstream(const std::string &filename, std::ios_base::openmode mode) {
    open(filename, mode);
}

vifstream::~vifstream() {}

void vifstream::open(const std::string &filename, std::ios_base::openmode mode) {
    filename_ = filename;
    if (!VirtualFilesManager::Exists(filename_)) {
        actual_file_ = std::make_unique<std::ifstream>(filename_, mode);
    }
}

vifstream& vifstream::read(char *str_out, std::streamsize count) {
    if (actual_file_) {
        actual_file_->read(str_out, count);
    } else {
        VirtualFilesManager::Read(filename_, str_out, count);
    }
    return *this;
}

void vifstream::close() {
    if (actual_file_) {
        actual_file_->close();
        actual_file_.reset();
    }
}

vifstream::operator bool() const {
    return actual_file_ || VirtualFilesManager::Exists(filename_);
}

// vifstream& vifstream::operator<<(std::ostream& (*os)(std::ostream&)) {
//     if (actual_file_) {
//         *actual_file_ << os;
//     } else {
//         VirtualFilesManager::Write(filename_, os);
//     }
//     return *this;
// }

}  // namespace io