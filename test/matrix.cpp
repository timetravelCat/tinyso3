#include <tinyso3/Matrix.hpp>
#include <catch2/catch_test_macros.hpp>

using namespace tinyso3;

TEST_CASE("Matrix") {
    SECTION("Constructors") {
        const float data_1d[12] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f};
        const float data_2d[3][4] = {{1.0f, 2.0f, 3.0f, 4.0f}, {5.0f, 6.0f, 7.0f, 8.0f}, {9.0f, 10.0f, 11.0f, 12.0f}};

        Matrix<3, 4, float> m1;
        Matrix<3, 4, float> m2(data_1d);
        Matrix<3, 4, float> m3(data_2d);
        Matrix<3, 4, float> m4{m2};
        Matrix<3, 4, float> m5{1};
        Matrix<3, 4, float> m6{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f};

        for(size_t i = 0; i < 3; i++) {
            for(size_t j = 0; j < 4; j++) {
                REQUIRE(m1(i, j) == 0.0f);
                REQUIRE(m2(i, j) == data_1d[i * 4 + j]);
                REQUIRE(m3(i, j) == data_2d[i][j]);
                REQUIRE(m4(i, j) == data_1d[i * 4 + j]);
                REQUIRE(m5(i, j) == 1.0f);
                REQUIRE(m6(i, j) == data_1d[i * 4 + j]);
            }
        }
    }

    SECTION("Assignment") {
        Matrix<3, 4, float> m1;
        Matrix<3, 4, float> m2{1.0f};
        Matrix<3, 4, float> m3;

        m1 = m2;
        m3 = 1.0f;

        for(size_t i = 0; i < 3; i++) {
            for(size_t j = 0; j < 4; j++) {
                REQUIRE(m1(i, j) == 1.0f);
                REQUIRE(m3(i, j) == 1.0f);
            }
        }

        const float data_1[2][3] = {{1.0f, 2.0f, 3.0f}, {4.0f, 5.0f, 6.0f}};
        const float data_2[3][2] = {{1.0f, 2.0f}, {3.0f, 4.0f}, {5.0f, 6.0f}};
        Matrix<2, 3, float> m4{data_1};
        Matrix<3, 2, float> m5{data_2};
        Matrix<4, 5, float> m6;

        m6.setBlock<1, 2>(m4);
        for(size_t i = 0; i < 2; i++) {
            for(size_t j = 0; j < 3; j++) {
                REQUIRE(m6(i + 1, j + 2) == data_1[i][j]);
            }
        }

        m6.setBlock(1, 2, m5);
        for(size_t i = 0; i < 3; i++) {
            for(size_t j = 0; j < 2; j++) {
                REQUIRE(m6(i + 1, j + 2) == data_2[i][j]);
            }
        }

        Matrix<4, 1, float> col{11.0f, 12.0f, 13.0f, 14.0f};
        Matrix<1, 5, float> row{21.0f, 22.0f, 23.0f, 24.0f, 25.0f};

        m6.setCol(1, col);
        m6.setCol<2>(col);
        for(size_t i = 0; i < 4; i++) {
            REQUIRE(m6(i, 1) == col(i, 0));
            REQUIRE(m6(i, 2) == col(i, 0));
        }

        m6.setRow(1, row);
        m6.setRow<2>(row);
        for(size_t i = 0; i < 5; i++) {
            REQUIRE(m6(1, i) == row(0, i));
            REQUIRE(m6(2, i) == row(0, i));
        }
    }

    SECTION("Constants(Static Methods)") {
        Matrix<3, 4, float> zero = Matrix<3, 4, float>::Null();
        Matrix<3, 4, float> identity = Matrix<3, 4, float>::Identity();
        Matrix<3, 4, float> nans = Matrix<3, 4, float>::NaN();

        for(size_t i = 0; i < 3; i++) {
            for(size_t j = 0; j < 4; j++) {
                REQUIRE(zero(i, j) == 0.0f);
                REQUIRE(identity(i, j) == (i == j ? 1.0f : 0.0f));
                REQUIRE(::isnan(nans(i, j)));
            }
        }
    }

    SECTION("Cast") {
        Matrix<3, 4, float> m{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f};
        Matrix<3, 4, int> m1 = m.cast<int>();
        Matrix<3, 4, double> m2 = static_cast<Matrix<3, 4, double>>(m);

        for(size_t i = 0; i < 3; i++) {
            for(size_t j = 0; j < 4; j++) {
                REQUIRE(m1(i, j) == static_cast<int>(m(i, j)));
                REQUIRE(m2(i, j) == static_cast<double>(m(i, j)));
            }
        }
    }

    SECTION("Accessors") {
        float data[3][4] = {{1.0f, 2.0f, 3.0f, 4.0f}, {5.0f, 6.0f, 7.0f, 8.0f}, {9.0f, 10.0f, 11.0f, 12.0f}};
        Matrix<3, 4, float> m{data};

        for(size_t i = 0; i < 3; i++) {
            for(size_t j = 0; j < 4; j++) {
                REQUIRE(m(i, j) == data[i][j]);
                m(i, j) = data[i][j] + 1.0f;
                REQUIRE(m(i, j) == data[i][j] + 1.0f);
                m(i, j) = data[i][j];
            }
        }

        for(size_t i = 0; i < 3; i++) {
            for(size_t j = 0; j < 4; j++) {
                REQUIRE(m.row(i)(0, j) == data[i][j]);
                REQUIRE(m.col(j)(i, 0) == data[i][j]);
            }
        }

        for(size_t i = 0; i < 3; i++) {
            REQUIRE(m.col<0>()(i, 0) == data[i][0]);
            REQUIRE(m.col<1>()(i, 0) == data[i][1]);
            REQUIRE(m.col<2>()(i, 0) == data[i][2]);
            REQUIRE(m.col<3>()(i, 0) == data[i][3]);
        }

        for(size_t j = 0; j < 4; j++) {
            REQUIRE(m.row<0>()(0, j) == data[0][j]);
            REQUIRE(m.row<1>()(0, j) == data[1][j]);
            REQUIRE(m.row<2>()(0, j) == data[2][j]);
        }
    }

    SECTION("Arithmetic operators by scalar") {
        Matrix<3, 4, int> m1{2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24};
        Matrix<3, 4, int> m2 = m1 + 1;
        Matrix<3, 4, int> m3 = m1 - 1;
        Matrix<3, 4, int> m4 = m1 * 2;
        Matrix<3, 4, int> m5 = m1 / 2;

        for(size_t i = 0; i < 3; i++) {
            for(size_t j = 0; j < 4; j++) {
                REQUIRE(m2(i, j) == m1(i, j) + 1);
                REQUIRE(m3(i, j) == m1(i, j) - 1);
                REQUIRE(m4(i, j) == m1(i, j) * 2);
                REQUIRE(m5(i, j) == m1(i, j) / 2);
            }
        }

        m2 -= 1;
        m3 += 1;
        m4 /= 2;
        m5 *= 2;

        for(size_t i = 0; i < 3; i++) {
            for(size_t j = 0; j < 4; j++) {
                REQUIRE(m1(i, j) == m2(i, j));
                REQUIRE(m1(i, j) == m3(i, j));
                REQUIRE(m1(i, j) == m4(i, j));
                REQUIRE(m1(i, j) == m5(i, j));
            }
        }

        Matrix<3, 4, int> m6 = 1 + m1;
        Matrix<3, 4, int> m7 = 1 - m1;
        Matrix<3, 4, int> m8 = 2 * m1;

        for(size_t i = 0; i < 3; i++) {
            for(size_t j = 0; j < 4; j++) {
                REQUIRE(m6(i, j) == 1 + m1(i, j));
                REQUIRE(m7(i, j) == 1 - m1(i, j));
                REQUIRE(m8(i, j) == 2 * m1(i, j));
            }
        }

        Matrix<3, 4, int> m9 = -m1;

        for(size_t i = 0; i < 3; i++) {
            for(size_t j = 0; j < 4; j++) {
                REQUIRE(m9(i, j) == -m1(i, j));
            }
        }
    }

    SECTION("Arithmetic operators by matrix") {
        Matrix<3, 4, int> m1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
        Matrix<3, 4, int> m2{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
        Matrix<3, 4, int> m3 = m1 + m2;
        Matrix<3, 4, int> m4 = m1 - m2;

        for(size_t i = 0; i < 3; i++) {
            for(size_t j = 0; j < 4; j++) {
                REQUIRE(m3(i, j) == m1(i, j) + m2(i, j));
                REQUIRE(m4(i, j) == m1(i, j) - m2(i, j));
            }
        }

        m3 -= m2;
        m4 += m2;

        for(size_t i = 0; i < 3; i++) {
            for(size_t j = 0; j < 4; j++) {
                REQUIRE(m1(i, j) == m3(i, j));
                REQUIRE(m1(i, j) == m4(i, j));
            }
        }

        Matrix<4, 3, int> m5{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
        Matrix<3, 3, int> m6 = m1 * m5;

        for(size_t i = 0; i < 3; i++) {
            for(size_t j = 0; j < 3; j++) {
                int sum = 0;
                for(size_t k = 0; k < 4; k++) {
                    sum += m1(i, k) * m5(k, j);
                }
                REQUIRE(m6(i, j) == sum);
            }
        }
    }

    SECTION("Transpose") {
        Matrix<3, 4, int> m1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
        Matrix<4, 3, int> m2 = m1.transpose();

        for(size_t i = 0; i < 3; i++) {
            for(size_t j = 0; j < 4; j++) {
                REQUIRE(m1(i, j) == m2(j, i));
            }
        }
    }

    SECTION("Slice") {
        Matrix<3, 4, int> m1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

        Matrix<2, 3, int> m2 = m1.slice<1, 1, 2, 3>();
        for(size_t i = 0; i < 2; i++) {
            for(size_t j = 0; j < 3; j++) {
                REQUIRE(m2(i, j) == m1(i + 1, j + 1));
            }
        }

        Matrix<2, 3, int> m3 = m1.slice<2, 3>(1, 1);
        for(size_t i = 0; i < 2; i++) {
            for(size_t j = 0; j < 3; j++) {
                REQUIRE(m3(i, j) == m1(i + 1, j + 1));
            }
        }
    }

    SECTION("Utility functions") {
        Matrix<3, 4, float> m1{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f};
        REQUIRE(m1.isfinite() == true);
        REQUIRE(m1.isnan() == false);

        Matrix<3, 4, float> m2{1.0f, 2.0f, NAN, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f};
        REQUIRE(m2.isfinite() == false);
        REQUIRE(m2.isnan() == false);

        Matrix<3, 4, float> m3{NAN};
        REQUIRE(m3.isfinite() == false);
        REQUIRE(m3.isnan() == true);

        Matrix<3, 4, float> m4{4.0f, 2.0f, 1.0f, 3.0f, 5.0f, 6.0f, 7.0f, 8.0f, 12.0f, 10.0f, 11.0f, 9.0f};
        REQUIRE(m4.min() == 1.0f);
        REQUIRE(m4.max() == 12.0f);

        Matrix<3, 4, float> m5{1.0f, -2.0f, 3.0f, -4.0f, -5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f};
        Matrix<3, 4, float> m6 = m5.abs();
        for(size_t i = 0; i < 3; i++) {
            for(size_t j = 0; j < 4; j++) {
                REQUIRE(m6(i, j) == fabs(m5(i, j)));
            }
        }

        Matrix<3, 4, float> m7{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f};
        Matrix<3, 4, float> m8{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f};
        Matrix<3, 4, float> m9{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f};
        m8.swapRows(1, 2);
        m9.swapRows<1, 2>();

        for(size_t i = 0; i < 4; i++) {
            REQUIRE(m7(1, i) == m8(2, i));
            REQUIRE(m7(2, i) == m8(1, i));
            REQUIRE(m7(1, i) == m9(2, i));
            REQUIRE(m7(2, i) == m9(1, i));
        }

        m8 = m7;
        m9 = m7;
        m8.swapCols(1, 2);
        m9.swapCols<1, 2>();

        for(size_t i = 0; i < 3; i++) {
            REQUIRE(m7(i, 1) == m8(i, 2));
            REQUIRE(m7(i, 2) == m8(i, 1));
            REQUIRE(m7(i, 1) == m9(i, 2));
            REQUIRE(m7(i, 2) == m9(i, 1));
        }
    }

    SECTION("Elementwise Operations") {
        auto square = [](int x) {
            return x * x;
        };
        Matrix<3, 4, int> m1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
        Matrix<3, 4, int> m2 = m1.elementWise(square);

        for(size_t i = 0; i < 3; i++) {
            for(size_t j = 0; j < 4; j++) {
                REQUIRE(m2(i, j) == square(m1(i, j)));
            }
        }

        auto add = [](int x, int y) {
            return x + y;
        };
        Matrix<3, 4, int> m3{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
        Matrix<3, 4, int> m4 = m3.elementWise(m1, add);

        for(size_t i = 0; i < 3; i++) {
            for(size_t j = 0; j < 4; j++) {
                REQUIRE(m4(i, j) == add(m3(i, j), m1(i, j)));
            }
        }
    }
}