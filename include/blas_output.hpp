#pragma once

#include <format>

#include "Matrix.hpp"


template<>
struct std::formatter<Vector> {
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

    auto format(const Vector& v, std::format_context& ctx) const {
        auto out = std::format_to(ctx.out(), "[");

        for (std::size_t i = 0; i < v.size(); ++i) {
            out = std::format_to(out, "{}", v[i]);

            if (i + 1 < v.size())
                out = std::format_to(out, ", ");
        }

        return std::format_to(out, "]");
    }
};
template<>
struct std::formatter<Matrix> {
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

    auto format(const Matrix& m, std::format_context& ctx) const {
        auto out = ctx.out();

        for (std::size_t row = 0; row < m.rowsize(); ++row) {
            out = std::format_to(out, "[");

            for (std::size_t col = 0; col < m.colsize(); ++col) {
                out = std::format_to(out, "{}", m(row, col));

                if (col + 1 < m.colsize())
                    out = std::format_to(out, ", ");
            }

            out = std::format_to(out, "]");

            if (row + 1 < m.rowsize())
                out = std::format_to(out, "\n");
        }

        return out;
    }
};

