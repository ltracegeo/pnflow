#include "io/vofstream.h"

namespace io {

vofstream::vofstream(const std::string &filename, std::ios_base::openmode mode)
        : filename_(filename) {
    if (!VirtualFilesManager::Exists(filename)) {
        actual_file_ = std::make_unique<std::ofstream>(filename, mode);
    }
}

vofstream::~vofstream() {}

void vofstream::close() {
    if (actual_file_) {
        actual_file_->close();
        actual_file_.reset();
    }
}

vofstream& vofstream::operator<<(std::ostream& (*os)(std::ostream&)) {
    if (actual_file_) {
        *actual_file_ << os;
    } else {
        VirtualFilesManager::Write(filename_, os);
    }
    return *this;
}

}  // namespace io