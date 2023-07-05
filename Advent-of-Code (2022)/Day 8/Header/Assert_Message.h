#ifndef ASSERT_MESSAGE_H
#define ASSERT_MESSAGE_H

#include <assert.h>

#define assert_msg(Expression, Message) \
do {                                    \
    const bool e = Expression;          \
    if (!e) {                           \
        printf("\033[0;31m%s\033[0m\n", Message);        \
        assert(e);                      \
    }                                   \
                                        \
} while (0)


#endif