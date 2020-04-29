#pragma once

#include <utility>

#include <zug/compose.hpp>
#include <lager/util.hpp>

namespace lager {
namespace lenses {

/*!
 * `(Part Whole::*) -> Lens<Whole, Part>`
 */
template <typename Member>
auto attr(Member member) {
    return zug::comp([member](auto&& f) {
        return [&, f = LAGER_FWD(f)](auto&& p) {
            return f(LAGER_FWD(p).*member)([&](auto&& x) {
                auto r    = LAGER_FWD(p);
                r.*member = LAGER_FWD(x);
                return r;
            });
        };
    });
}

} // namespace lenses
} // namespace lager