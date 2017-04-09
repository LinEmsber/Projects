#ifndef GENERIC_H
#define GENERIC_H

#define offsetof(TYPE, MEMBER) ( (size_t) &( (TYPE *)0 )-> MEMBER )

// #define container_of(ptr, type, member) ({                      \
//         const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
//         ((type *) ( (char*)(ptr) - offsetof(type, member)) ); })

#define container_of(ptr, type, member) ({ \
        (type *)( (char *) ptr - offsetof(type,member) );})

#endif
