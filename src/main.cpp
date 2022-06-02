#include <iostream>

#include <Eigen/Dense>

int main() {
    Eigen::Vector2f v(1.0f, 1.0f);
    std::cout << v.squaredNorm() << std::endl;
    return 0;
}
