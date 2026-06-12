#pragma once

#define BIND(a1, a2, a3)                          \
decltype((a2)->a3()) a1()                         \
{                                                 \
    return (a2)->a3();                            \
}                                                 \
void a1(decltype((a2)->a3()) value)               \
{                                                 \
    (a2)->set_##a3(value);                        \
}

#define BINDISLAND(a1, a3)                              \
static decltype(pisland->a3()) a1()                     \
{                                                       \
    return pisland->a3();                               \
}                                                       \
static void a1(decltype(pisland->a3()) value)           \
{                                                       \
    pisland->set_##a3(value);                           \
    penv->a1 = value;                                   \
}                                            

#define BINDISLANDITEM(a1, a2)                                          \
static std::decay_t<decltype(pisland->mutable_items()->at(0))> a1()     \
{                                                                       \
    return (*pisland->mutable_items())[a2];                             \
}                                                                       \
                                                                        \
static void a1(decltype((pisland)->mutable_items()->at(0)) value)       \
{                                                                       \
    (*pisland->mutable_items())[a2] = value;                            \
    penv->a1 = value;                                                   \
}