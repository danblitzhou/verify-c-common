#include <aws/common/math.h>

int LLVMFuzzerTestOneInput(const uint64_t *data, size_t size)
{
    uint64_t a = data[0];
    uint64_t b = data[1];
    uint64_t r = aws_add_u64_saturating(a, b);
    if ((b > 0) && (a > (UINT32_MAX - b)))
    {
        if (r != UINT64_MAX)
        {
            __builtin_trap();
        }
    }
    else
    {
        if (r != a + b)
        {
            __builtin_trap();
        }
    }
    return 0;
}
