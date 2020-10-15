#include <seahorn/seahorn.h>
#include <aws/common/math.h>
#include "nondet.h"

int main() {
    uint64_t a = nd_uint64_t();
    uint64_t b = nd_uint64_t();
    uint64_t r = nd_uint64_t();
    if (nd_bool()) {
        int rval = aws_add_u64_checked(a, b, &r);
        if (!rval) {
            sassert(r == a + b);
        } else {
            sassert((b > 0) && (a > (UINT64_MAX - b)));
        }
    } else {
        uint32_t *r_32 = (uint32_t*)(&r); // dodgy cast to remove compiler warning
        int rval = aws_add_u32_checked(a, b, r_32);
        if (!rval) {
            sassert(r == a + b);
        } else {
            sassert((b > 0) && (a > (UINT32_MAX - b)));
        }
    }
  return 0;
}
