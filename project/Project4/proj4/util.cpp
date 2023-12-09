#include "util.hpp"
#include "matrix.hpp"

void check_file(std::ifstream &f) {
    if (!f.is_open() || !f.good()) {
        std::cerr << "ERROR:" << std::strerror(errno) << '\n';
        throw std::invalid_argument("invalid mode!");
    }
}

size_t read_row(std::ifstream &f) {
    size_t row_cnt = 0;
    std::string tmp;
    while (std::getline(f, tmp, '\n')) ++row_cnt;
    f.clear();
    return row_cnt;
}

size_t read_col(std::ifstream &f) {
    size_t col_cnt = 0;
    std::string l, tmp;
    std::getline(f, l, '\n');
    std::stringstream ssl(l);
    while (ssl >> tmp) ++col_cnt;
    f.clear();
    return col_cnt;
}
