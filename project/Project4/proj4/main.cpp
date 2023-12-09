#include "matrix.hpp"
#include "cal.hpp"
#include "util.hpp"

int main(int argc, char **argv) {
    std::ios::sync_with_stdio(0), std::cin.tie(0), std::cout.tie(0);
    if (argc != 4) {
        std::cerr << "ERROR: The number of arguments is unexpected!" << '\n';
    }
    std::ifstream f1(argv[1]);
    std::ifstream f2(argv[2]);
    try {
        check_file(f1);
        check_file(f2);
    } catch (const std::invalid_argument &) {
        return -1;
    }
    size_t m1_row = read_row(f1);
    size_t m1_col = read_col(f1);
    size_t m2_row = read_row(f2);
    size_t m2_col = read_col(f2);

    matrix<float> ma(m1_row, m1_col);
    matrix<float> mb(m2_row, m2_col);
    from_file(ma, m1_row, m1_col, f1);
    from_file(mb, m2_row, m2_col, f2);

//    //测试拷贝函数、=重载、!=重载
//    matrix<float> mc(mb);
//    mc.show();
//    if (mc != ma) mc = ma;
//    mc.show();
//
//    mc.multiply(ma, mb, 1);
//    // mc.multiply(ma, mb, 2);
//    mc.multiply(ma, mb, 3);
//    mc.show();

    return 0;
}