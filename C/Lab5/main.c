#include <stdio.h>
#include <assert.h>
#include "receipter.h"

int main(void)
{
    time_t time = 1569472997;

    assert(TRUE == add_item("133k4nk", 5.60));
    assert(TRUE == add_item("569s6gu214Vf1q45C", 626.20));
    assert(TRUE == add_item("JXq4pPNS5p0EUQ", 47.00));
    assert(TRUE == add_item("173s37M435Pq54377X84vm", 39.29));
    assert(TRUE == add_item("9yj0eQ266q7ti9uN6wuJc01U156H52Ye0", 420.40));
    assert(TRUE == add_item("56H52Ye048Cm4", 86.30));
    assert(TRUE == add_item("2P850p7Ba6", 17.10));
    assert(TRUE == add_item("P5y16gUz9X3OsL", 30.00));
    assert(TRUE == add_item("9w44854439W6JnY882FrQ21", 477.00));
    assert(TRUE == add_item("sD3", 93.00));

    assert(TRUE == print_receipt("receipt0.txt", time));

    return 0;
}
