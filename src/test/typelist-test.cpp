#include "rs-core/typelist.hpp"
#include "rs-core/unit-test.hpp"
#include <concepts>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>

using namespace RS::Meta;

namespace {

    // Sort types into void < integers by size < pointers < everything else
    template <typename T1, typename T2>
    struct CompareTypes {
        enum {
            t1_is_void     = std::is_void<T1>::value,
            t1_is_integer  = std::is_integral<T1>::value,
            t1_is_pointer  = std::is_pointer<T1>::value,
            t1_key         = 4 * t1_is_void + 2 * t1_is_integer + t1_is_pointer,
            t2_is_void     = std::is_void<T2>::value,
            t2_is_integer  = std::is_integral<T2>::value,
            t2_is_pointer  = std::is_pointer<T2>::value,
            t2_key         = 4 * t2_is_void + 2 * t2_is_integer + t2_is_pointer,
            value          = t1_key > t2_key || (t1_key == t2_key && sizeof(T1) < sizeof(T2))
        };
    };

    template <typename T1, typename T2> using MakePair = std::pair<T1, T2>;
    template <typename T> using MakePtr = T*;

    template <typename T> struct Pattern;
    template <> struct Pattern<Nil>          { static std::string str() { return "*"; } };
    template <> struct Pattern<int>          { static std::string str() { return "i"; } };
    template <> struct Pattern<void*>        { static std::string str() { return "p"; } };
    template <> struct Pattern<std::string>  { static std::string str() { return "s"; } };
    template <typename T1, typename T2> struct Pattern<std::pair<T1, T2>>
        { static std::string str() { return "(" + Pattern<T1>::str() + Pattern<T2>::str() + ")"; } };

    template <typename T1, typename T2> struct MetaUnify;
    template <typename T> struct MetaUnify<T, T> { using type = T; };
    template <typename T1, typename T2> using Unify = typename MetaUnify<T1, T2>::type;

}

void test_rs_core_typelist_size() {

    using list_i     = Typelist<int>;
    using list_is    = Typelist<int, std::string>;
    using list_isp   = Typelist<int, std::string, void*>;
    using list_isps  = Typelist<int, std::string, void*, std::string>;

    TEST_EQUAL(Nil::count,        0u);
    TEST_EQUAL(list_i::count,     1u);
    TEST_EQUAL(list_is::count,    2u);
    TEST_EQUAL(list_isp::count,   3u);
    TEST_EQUAL(list_isps::count,  4u);

}

void test_rs_core_typelist_conversion() {

    using A = Convert<Typelist<>, std::tuple>;                  TEST((std::same_as<A, std::tuple<>>));
    using B = Convert<Typelist<char>, std::tuple>;              TEST((std::same_as<B, std::tuple<char>>));
    using C = Convert<Typelist<char, int>, std::tuple>;         TEST((std::same_as<C, std::tuple<char, int>>));
    using D = Convert<Typelist<char, int, float>, std::tuple>;  TEST((std::same_as<D, std::tuple<char, int, float>>));
    using Z = Convert<A, Typelist>;                             TEST((std::same_as<Z, Typelist<>>));
    using Y = Convert<B, Typelist>;                             TEST((std::same_as<Y, Typelist<char>>));
    using X = Convert<C, Typelist>;                             TEST((std::same_as<X, Typelist<char, int>>));
    using W = Convert<D, Typelist>;                             TEST((std::same_as<W, Typelist<char, int, float>>));

}

void test_rs_core_typelist_append() {

    using list_i     = Typelist<int>;
    using list_is    = Typelist<int, std::string>;
    using list_isp   = Typelist<int, std::string, void*>;
    using list_isps  = Typelist<int, std::string, void*, std::string>;

    {  using T = Append<Nil, int>;               TEST((std::same_as<T, list_i>));     }
    {  using T = Append<list_i, std::string>;    TEST((std::same_as<T, list_is>));    }
    {  using T = Append<list_is, void*>;         TEST((std::same_as<T, list_isp>));   }
    {  using T = Append<list_isp, std::string>;  TEST((std::same_as<T, list_isps>));  }
    {  using T = Append<Nil, Nil>;               TEST((std::same_as<T, Nil>));        }
    {  using T = Append<list_isp, Nil>;          TEST((std::same_as<T, list_isp>));   }

}

void test_rs_core_typelist_concat() {

    using list_i       = Typelist<int>;
    using list_s       = Typelist<std::string>;
    using list_p       = Typelist<void*>;
    using list_is      = Typelist<int, std::string>;
    using list_sp      = Typelist<std::string, void*>;
    using list_ss      = Typelist<std::string, std::string>;
    using list_isp     = Typelist<int, std::string, void*>;
    using list_spi     = Typelist<std::string, void*, int>;
    using list_issp    = Typelist<int, std::string, std::string, void*>;
    using list_spsp    = Typelist<std::string, void*, std::string, void*>;
    using list_isssp   = Typelist<int, std::string, std::string, std::string, void*>;
    using list_issssp  = Typelist<int, std::string, std::string, std::string, std::string, void*>;

    {  using T = Concat<>;                                               TEST((std::same_as<T, Nil>));          }
    {  using T = Concat<Nil>;                                            TEST((std::same_as<T, Nil>));          }
    {  using T = Concat<Nil, Nil>;                                       TEST((std::same_as<T, Nil>));          }
    {  using T = Concat<Nil, list_i>;                                    TEST((std::same_as<T, list_i>));       }
    {  using T = Concat<Nil, list_is>;                                   TEST((std::same_as<T, list_is>));      }
    {  using T = Concat<list_i, Nil>;                                    TEST((std::same_as<T, list_i>));       }
    {  using T = Concat<list_is, Nil>;                                   TEST((std::same_as<T, list_is>));      }
    {  using T = Concat<list_i, list_s>;                                 TEST((std::same_as<T, list_is>));      }
    {  using T = Concat<list_i, list_sp>;                                TEST((std::same_as<T, list_isp>));     }
    {  using T = Concat<list_sp, list_i>;                                TEST((std::same_as<T, list_spi>));     }
    {  using T = Concat<list_sp, list_sp>;                               TEST((std::same_as<T, list_spsp>));    }
    {  using T = Concat<list_i, list_s, list_p>;                         TEST((std::same_as<T, list_isp>));     }
    {  using T = Concat<list_is, list_ss, list_sp>;                      TEST((std::same_as<T, list_issssp>));  }
    {  using T = Concat<Nil, list_is, Nil, list_ss, Nil, list_sp, Nil>;  TEST((std::same_as<T, list_issssp>));  }
    {  using T = Concat<int>;                                            TEST((std::same_as<T, list_i>));       }
    {  using T = Concat<int, Nil>;                                       TEST((std::same_as<T, list_i>));       }
    {  using T = Concat<Nil, int>;                                       TEST((std::same_as<T, list_i>));       }
    {  using T = Concat<int, list_s>;                                    TEST((std::same_as<T, list_is>));      }
    {  using T = Concat<list_i, std::string>;                            TEST((std::same_as<T, list_is>));      }
    {  using T = Concat<int, list_ss, list_sp>;                          TEST((std::same_as<T, list_isssp>));   }
    {  using T = Concat<list_is, std::string, list_sp>;                  TEST((std::same_as<T, list_isssp>));   }
    {  using T = Concat<list_is, list_ss, void*>;                        TEST((std::same_as<T, list_isssp>));   }
    {  using T = Concat<int, std::string, list_sp>;                      TEST((std::same_as<T, list_issp>));    }
    {  using T = Concat<int, list_ss, void*>;                            TEST((std::same_as<T, list_issp>));    }
    {  using T = Concat<list_is, std::string, void*>;                    TEST((std::same_as<T, list_issp>));    }
    {  using T = Concat<int, std::string, void*>;                        TEST((std::same_as<T, list_isp>));     }

}

void test_rs_core_typelist_insert() {

    using list_i     = Typelist<int>;
    using list_s     = Typelist<std::string>;
    using list_is    = Typelist<int, std::string>;
    using list_ss    = Typelist<std::string, std::string>;
    using list_ips   = Typelist<int, void*, std::string>;
    using list_iips  = Typelist<int, int, void*, std::string>;
    using list_ipps  = Typelist<int, void*, void*, std::string>;
    using list_ipss  = Typelist<int, void*, std::string, std::string>;

    {  using T = Insert<Nil, int, CompareTypes>;               TEST((std::same_as<T, list_i>));     }
    {  using T = Insert<list_s, std::string, CompareTypes>;    TEST((std::same_as<T, list_ss>));    }
    {  using T = Insert<list_s, int, CompareTypes>;            TEST((std::same_as<T, list_is>));    }
    {  using T = Insert<list_i, std::string, CompareTypes>;    TEST((std::same_as<T, list_is>));    }
    {  using T = Insert<list_ips, int, CompareTypes>;          TEST((std::same_as<T, list_iips>));  }
    {  using T = Insert<list_ips, void*, CompareTypes>;        TEST((std::same_as<T, list_ipps>));  }
    {  using T = Insert<list_ips, std::string, CompareTypes>;  TEST((std::same_as<T, list_ipss>));  }

}

void test_rs_core_typelist_insert_at() {

    using list_c     = Typelist<char>;
    using list_i     = Typelist<int>;
    using list_ci    = Typelist<char, int>;
    using list_ic    = Typelist<int, char>;
    using list_is    = Typelist<int, std::string>;
    using list_cis   = Typelist<char, int, std::string>;
    using list_ics   = Typelist<int, char, std::string>;
    using list_isc   = Typelist<int, std::string, char>;
    using list_isp   = Typelist<int, std::string, void*>;
    using list_cisp  = Typelist<char, int, std::string, void*>;
    using list_icsp  = Typelist<int, char, std::string, void*>;
    using list_iscp  = Typelist<int, std::string, char, void*>;
    using list_ispc  = Typelist<int, std::string, void*, char>;

    {  using T = InsertAt<Nil, char, -1>;       TEST((std::same_as<T, list_c>));     }
    {  using T = InsertAt<Nil, char, 0>;        TEST((std::same_as<T, list_c>));     }
    {  using T = InsertAt<Nil, char, 1>;        TEST((std::same_as<T, list_c>));     }
    {  using T = InsertAt<list_i, char, -1>;    TEST((std::same_as<T, list_ci>));    }
    {  using T = InsertAt<list_i, char, 0>;     TEST((std::same_as<T, list_ci>));    }
    {  using T = InsertAt<list_i, char, 1>;     TEST((std::same_as<T, list_ic>));    }
    {  using T = InsertAt<list_i, char, 2>;     TEST((std::same_as<T, list_ic>));    }
    {  using T = InsertAt<list_is, char, -1>;   TEST((std::same_as<T, list_cis>));   }
    {  using T = InsertAt<list_is, char, 0>;    TEST((std::same_as<T, list_cis>));   }
    {  using T = InsertAt<list_is, char, 1>;    TEST((std::same_as<T, list_ics>));   }
    {  using T = InsertAt<list_is, char, 2>;    TEST((std::same_as<T, list_isc>));   }
    {  using T = InsertAt<list_is, char, 3>;    TEST((std::same_as<T, list_isc>));   }
    {  using T = InsertAt<list_isp, char, -1>;  TEST((std::same_as<T, list_cisp>));  }
    {  using T = InsertAt<list_isp, char, 0>;   TEST((std::same_as<T, list_cisp>));  }
    {  using T = InsertAt<list_isp, char, 1>;   TEST((std::same_as<T, list_icsp>));  }
    {  using T = InsertAt<list_isp, char, 2>;   TEST((std::same_as<T, list_iscp>));  }
    {  using T = InsertAt<list_isp, char, 3>;   TEST((std::same_as<T, list_ispc>));  }
    {  using T = InsertAt<list_isp, char, 4>;   TEST((std::same_as<T, list_ispc>));  }

}

void test_rs_core_typelist_prefix() {

    using list_i    = Typelist<int>;
    using list_s    = Typelist<std::string>;
    using list_is   = Typelist<int, std::string>;
    using list_sp   = Typelist<std::string, void*>;
    using list_isp  = Typelist<int, std::string, void*>;

    {  using T = Prefix<int, Nil>;      TEST((std::same_as<T, list_i>));    }
    {  using T = Prefix<int, list_s>;   TEST((std::same_as<T, list_is>));   }
    {  using T = Prefix<int, list_sp>;  TEST((std::same_as<T, list_isp>));  }

}

void test_rs_core_typelist_repeat() {

    using list_s     = Typelist<std::string>;
    using list_sp    = Typelist<std::string, void*>;
    using list_ss    = Typelist<std::string, std::string>;
    using list_sss   = Typelist<std::string, std::string, std::string>;
    using list_sp_1  = Typelist<list_sp>;
    using list_sp_2  = Typelist<list_sp, list_sp>;
    using list_sp_3  = Typelist<list_sp, list_sp, list_sp>;

    {  using T = Repeat<std::string, 0>;  TEST((std::same_as<T, Nil>));        }
    {  using T = Repeat<std::string, 1>;  TEST((std::same_as<T, list_s>));     }
    {  using T = Repeat<std::string, 2>;  TEST((std::same_as<T, list_ss>));    }
    {  using T = Repeat<std::string, 3>;  TEST((std::same_as<T, list_sss>));   }
    {  using T = Repeat<list_sp, 0>;      TEST((std::same_as<T, Nil>));        }
    {  using T = Repeat<list_sp, 1>;      TEST((std::same_as<T, list_sp_1>));  }
    {  using T = Repeat<list_sp, 2>;      TEST((std::same_as<T, list_sp_2>));  }
    {  using T = Repeat<list_sp, 3>;      TEST((std::same_as<T, list_sp_3>));  }

}

void test_rs_core_typelist_repeat_list() {

    using list_s       = Typelist<std::string>;
    using list_sp      = Typelist<std::string, void*>;
    using list_ss      = Typelist<std::string, std::string>;
    using list_sss     = Typelist<std::string, std::string, std::string>;
    using list_spsp    = Typelist<std::string, void*, std::string, void*>;
    using list_spspsp  = Typelist<std::string, void*, std::string, void*, std::string, void*>;

    {  using T = RepeatList<Nil, 0>;      TEST((std::same_as<T, Nil>));          }
    {  using T = RepeatList<Nil, 1>;      TEST((std::same_as<T, Nil>));          }
    {  using T = RepeatList<Nil, 2>;      TEST((std::same_as<T, Nil>));          }
    {  using T = RepeatList<Nil, 3>;      TEST((std::same_as<T, Nil>));          }
    {  using T = RepeatList<list_s, 0>;   TEST((std::same_as<T, Nil>));          }
    {  using T = RepeatList<list_s, 1>;   TEST((std::same_as<T, list_s>));       }
    {  using T = RepeatList<list_s, 2>;   TEST((std::same_as<T, list_ss>));      }
    {  using T = RepeatList<list_s, 3>;   TEST((std::same_as<T, list_sss>));     }
    {  using T = RepeatList<list_sp, 0>;  TEST((std::same_as<T, Nil>));          }
    {  using T = RepeatList<list_sp, 1>;  TEST((std::same_as<T, list_sp>));      }
    {  using T = RepeatList<list_sp, 2>;  TEST((std::same_as<T, list_spsp>));    }
    {  using T = RepeatList<list_sp, 3>;  TEST((std::same_as<T, list_spspsp>));  }

}

void test_rs_core_typelist_resize() {

    using list_c      = Typelist<char>;
    using list_i      = Typelist<int>;
    using list_cc     = Typelist<char, char>;
    using list_ic     = Typelist<int, char>;
    using list_is     = Typelist<int, std::string>;
    using list_icc    = Typelist<int, char, char>;
    using list_isc    = Typelist<int, std::string, char>;
    using list_isp    = Typelist<int, std::string, void*>;
    using list_iscc   = Typelist<int, std::string, char, char>;
    using list_ispc   = Typelist<int, std::string, void*, char>;
    using list_ispcc  = Typelist<int, std::string, void*, char, char>;

    {  using T = Resize<Nil, 0, char>;       TEST((std::same_as<T, Nil>));         }
    {  using T = Resize<Nil, 1, char>;       TEST((std::same_as<T, list_c>));      }
    {  using T = Resize<Nil, 2, char>;       TEST((std::same_as<T, list_cc>));     }
    {  using T = Resize<list_i, 0, char>;    TEST((std::same_as<T, Nil>));         }
    {  using T = Resize<list_i, 1, char>;    TEST((std::same_as<T, list_i>));      }
    {  using T = Resize<list_i, 2, char>;    TEST((std::same_as<T, list_ic>));     }
    {  using T = Resize<list_i, 3, char>;    TEST((std::same_as<T, list_icc>));    }
    {  using T = Resize<list_is, 0, char>;   TEST((std::same_as<T, Nil>));         }
    {  using T = Resize<list_is, 1, char>;   TEST((std::same_as<T, list_i>));      }
    {  using T = Resize<list_is, 2, char>;   TEST((std::same_as<T, list_is>));     }
    {  using T = Resize<list_is, 3, char>;   TEST((std::same_as<T, list_isc>));    }
    {  using T = Resize<list_is, 4, char>;   TEST((std::same_as<T, list_iscc>));   }
    {  using T = Resize<list_isp, 0, char>;  TEST((std::same_as<T, Nil>));         }
    {  using T = Resize<list_isp, 1, char>;  TEST((std::same_as<T, list_i>));      }
    {  using T = Resize<list_isp, 2, char>;  TEST((std::same_as<T, list_is>));     }
    {  using T = Resize<list_isp, 3, char>;  TEST((std::same_as<T, list_isp>));    }
    {  using T = Resize<list_isp, 4, char>;  TEST((std::same_as<T, list_ispc>));   }
    {  using T = Resize<list_isp, 5, char>;  TEST((std::same_as<T, list_ispcc>));  }

}

void test_rs_core_typelist_skip() {

    using list_i    = Typelist<int>;
    using list_s    = Typelist<std::string>;
    using list_p    = Typelist<void*>;
    using list_is   = Typelist<int, std::string>;
    using list_sp   = Typelist<std::string, void*>;
    using list_isp  = Typelist<int, std::string, void*>;

    {  using T = Skip<Nil, 0>;       TEST((std::same_as<T, Nil>));       }
    {  using T = Skip<Nil, 1>;       TEST((std::same_as<T, Nil>));       }
    {  using T = Skip<Nil, 2>;       TEST((std::same_as<T, Nil>));       }
    {  using T = Skip<list_i, 0>;    TEST((std::same_as<T, list_i>));    }
    {  using T = Skip<list_i, 1>;    TEST((std::same_as<T, Nil>));       }
    {  using T = Skip<list_i, 2>;    TEST((std::same_as<T, Nil>));       }
    {  using T = Skip<list_is, 0>;   TEST((std::same_as<T, list_is>));   }
    {  using T = Skip<list_is, 1>;   TEST((std::same_as<T, list_s>));    }
    {  using T = Skip<list_is, 2>;   TEST((std::same_as<T, Nil>));       }
    {  using T = Skip<list_is, 3>;   TEST((std::same_as<T, Nil>));       }
    {  using T = Skip<list_isp, 0>;  TEST((std::same_as<T, list_isp>));  }
    {  using T = Skip<list_isp, 1>;  TEST((std::same_as<T, list_sp>));   }
    {  using T = Skip<list_isp, 2>;  TEST((std::same_as<T, list_p>));    }
    {  using T = Skip<list_isp, 3>;  TEST((std::same_as<T, Nil>));       }
    {  using T = Skip<list_isp, 4>;  TEST((std::same_as<T, Nil>));       }

}

void test_rs_core_typelist_sublist() {

    using list_i    = Typelist<int>;
    using list_s    = Typelist<std::string>;
    using list_p    = Typelist<void*>;
    using list_is   = Typelist<int, std::string>;
    using list_sp   = Typelist<std::string, void*>;
    using list_isp  = Typelist<int, std::string, void*>;

    {  using T = Sublist<Nil, 0, 0>;       TEST((std::same_as<T, Nil>));       }
    {  using T = Sublist<Nil, 0, 1>;       TEST((std::same_as<T, Nil>));       }
    {  using T = Sublist<Nil, 0, 2>;       TEST((std::same_as<T, Nil>));       }
    {  using T = Sublist<Nil, 1, 0>;       TEST((std::same_as<T, Nil>));       }
    {  using T = Sublist<Nil, 1, 1>;       TEST((std::same_as<T, Nil>));       }
    {  using T = Sublist<Nil, 1, 2>;       TEST((std::same_as<T, Nil>));       }
    {  using T = Sublist<Nil, 2, 0>;       TEST((std::same_as<T, Nil>));       }
    {  using T = Sublist<Nil, 2, 1>;       TEST((std::same_as<T, Nil>));       }
    {  using T = Sublist<Nil, 2, 2>;       TEST((std::same_as<T, Nil>));       }
    {  using T = Sublist<list_i, 0, 0>;    TEST((std::same_as<T, Nil>));       }
    {  using T = Sublist<list_i, 0, 1>;    TEST((std::same_as<T, list_i>));    }
    {  using T = Sublist<list_i, 0, 2>;    TEST((std::same_as<T, list_i>));    }
    {  using T = Sublist<list_i, 1, 0>;    TEST((std::same_as<T, Nil>));       }
    {  using T = Sublist<list_i, 1, 1>;    TEST((std::same_as<T, Nil>));       }
    {  using T = Sublist<list_i, 1, 2>;    TEST((std::same_as<T, Nil>));       }
    {  using T = Sublist<list_i, 2, 0>;    TEST((std::same_as<T, Nil>));       }
    {  using T = Sublist<list_i, 2, 1>;    TEST((std::same_as<T, Nil>));       }
    {  using T = Sublist<list_i, 2, 2>;    TEST((std::same_as<T, Nil>));       }
    {  using T = Sublist<list_is, 0, 0>;   TEST((std::same_as<T, Nil>));       }
    {  using T = Sublist<list_is, 0, 1>;   TEST((std::same_as<T, list_i>));    }
    {  using T = Sublist<list_is, 0, 2>;   TEST((std::same_as<T, list_is>));   }
    {  using T = Sublist<list_is, 0, 3>;   TEST((std::same_as<T, list_is>));   }
    {  using T = Sublist<list_is, 1, 0>;   TEST((std::same_as<T, Nil>));       }
    {  using T = Sublist<list_is, 1, 1>;   TEST((std::same_as<T, list_s>));    }
    {  using T = Sublist<list_is, 1, 2>;   TEST((std::same_as<T, list_s>));    }
    {  using T = Sublist<list_is, 1, 3>;   TEST((std::same_as<T, list_s>));    }
    {  using T = Sublist<list_is, 2, 0>;   TEST((std::same_as<T, Nil>));       }
    {  using T = Sublist<list_is, 2, 1>;   TEST((std::same_as<T, Nil>));       }
    {  using T = Sublist<list_is, 2, 2>;   TEST((std::same_as<T, Nil>));       }
    {  using T = Sublist<list_is, 2, 3>;   TEST((std::same_as<T, Nil>));       }
    {  using T = Sublist<list_is, 3, 0>;   TEST((std::same_as<T, Nil>));       }
    {  using T = Sublist<list_is, 3, 1>;   TEST((std::same_as<T, Nil>));       }
    {  using T = Sublist<list_is, 3, 2>;   TEST((std::same_as<T, Nil>));       }
    {  using T = Sublist<list_is, 3, 3>;   TEST((std::same_as<T, Nil>));       }
    {  using T = Sublist<list_isp, 0, 0>;  TEST((std::same_as<T, Nil>));       }
    {  using T = Sublist<list_isp, 0, 1>;  TEST((std::same_as<T, list_i>));    }
    {  using T = Sublist<list_isp, 0, 2>;  TEST((std::same_as<T, list_is>));   }
    {  using T = Sublist<list_isp, 0, 3>;  TEST((std::same_as<T, list_isp>));  }
    {  using T = Sublist<list_isp, 0, 4>;  TEST((std::same_as<T, list_isp>));  }
    {  using T = Sublist<list_isp, 1, 0>;  TEST((std::same_as<T, Nil>));       }
    {  using T = Sublist<list_isp, 1, 1>;  TEST((std::same_as<T, list_s>));    }
    {  using T = Sublist<list_isp, 1, 2>;  TEST((std::same_as<T, list_sp>));   }
    {  using T = Sublist<list_isp, 1, 3>;  TEST((std::same_as<T, list_sp>));   }
    {  using T = Sublist<list_isp, 1, 4>;  TEST((std::same_as<T, list_sp>));   }
    {  using T = Sublist<list_isp, 2, 0>;  TEST((std::same_as<T, Nil>));       }
    {  using T = Sublist<list_isp, 2, 1>;  TEST((std::same_as<T, list_p>));    }
    {  using T = Sublist<list_isp, 2, 2>;  TEST((std::same_as<T, list_p>));    }
    {  using T = Sublist<list_isp, 2, 3>;  TEST((std::same_as<T, list_p>));    }
    {  using T = Sublist<list_isp, 2, 4>;  TEST((std::same_as<T, list_p>));    }
    {  using T = Sublist<list_isp, 3, 0>;  TEST((std::same_as<T, Nil>));       }
    {  using T = Sublist<list_isp, 3, 1>;  TEST((std::same_as<T, Nil>));       }
    {  using T = Sublist<list_isp, 3, 2>;  TEST((std::same_as<T, Nil>));       }
    {  using T = Sublist<list_isp, 3, 3>;  TEST((std::same_as<T, Nil>));       }
    {  using T = Sublist<list_isp, 3, 4>;  TEST((std::same_as<T, Nil>));       }
    {  using T = Sublist<list_isp, 4, 0>;  TEST((std::same_as<T, Nil>));       }
    {  using T = Sublist<list_isp, 4, 1>;  TEST((std::same_as<T, Nil>));       }
    {  using T = Sublist<list_isp, 4, 2>;  TEST((std::same_as<T, Nil>));       }
    {  using T = Sublist<list_isp, 4, 3>;  TEST((std::same_as<T, Nil>));       }
    {  using T = Sublist<list_isp, 4, 4>;  TEST((std::same_as<T, Nil>));       }

}

void test_rs_core_typelist_take() {

    using list_i    = Typelist<int>;
    using list_is   = Typelist<int, std::string>;
    using list_isp  = Typelist<int, std::string, void*>;

    {  using T = Take<Nil, 0>;       TEST((std::same_as<T, Nil>));       }
    {  using T = Take<Nil, 1>;       TEST((std::same_as<T, Nil>));       }
    {  using T = Take<Nil, 2>;       TEST((std::same_as<T, Nil>));       }
    {  using T = Take<list_i, 0>;    TEST((std::same_as<T, Nil>));       }
    {  using T = Take<list_i, 1>;    TEST((std::same_as<T, list_i>));    }
    {  using T = Take<list_i, 2>;    TEST((std::same_as<T, list_i>));    }
    {  using T = Take<list_is, 0>;   TEST((std::same_as<T, Nil>));       }
    {  using T = Take<list_is, 1>;   TEST((std::same_as<T, list_i>));    }
    {  using T = Take<list_is, 2>;   TEST((std::same_as<T, list_is>));   }
    {  using T = Take<list_is, 3>;   TEST((std::same_as<T, list_is>));   }
    {  using T = Take<list_isp, 0>;  TEST((std::same_as<T, Nil>));       }
    {  using T = Take<list_isp, 1>;  TEST((std::same_as<T, list_i>));    }
    {  using T = Take<list_isp, 2>;  TEST((std::same_as<T, list_is>));   }
    {  using T = Take<list_isp, 3>;  TEST((std::same_as<T, list_isp>));  }
    {  using T = Take<list_isp, 4>;  TEST((std::same_as<T, list_isp>));  }

}

void test_rs_core_typelist_at_index() {

    using list_i     = Typelist<int>;
    using list_is    = Typelist<int, std::string>;
    using list_isp   = Typelist<int, std::string, void*>;
    using list_isps  = Typelist<int, std::string, void*, std::string>;

    {  using T = AtIndex<Nil, -1>;        TEST((std::same_as<T, Nil>));          }
    {  using T = AtIndex<Nil, 0>;         TEST((std::same_as<T, Nil>));          }
    {  using T = AtIndex<Nil, 1>;         TEST((std::same_as<T, Nil>));          }
    {  using T = AtIndex<list_i, -1>;     TEST((std::same_as<T, Nil>));          }
    {  using T = AtIndex<list_i, 0>;      TEST((std::same_as<T, int>));          }
    {  using T = AtIndex<list_i, 1>;      TEST((std::same_as<T, Nil>));          }
    {  using T = AtIndex<list_i, 2>;      TEST((std::same_as<T, Nil>));          }
    {  using T = AtIndex<list_is, -1>;    TEST((std::same_as<T, Nil>));          }
    {  using T = AtIndex<list_is, 0>;     TEST((std::same_as<T, int>));          }
    {  using T = AtIndex<list_is, 1>;     TEST((std::same_as<T, std::string>));  }
    {  using T = AtIndex<list_is, 2>;     TEST((std::same_as<T, Nil>));          }
    {  using T = AtIndex<list_is, 3>;     TEST((std::same_as<T, Nil>));          }
    {  using T = AtIndex<list_isp, -1>;   TEST((std::same_as<T, Nil>));          }
    {  using T = AtIndex<list_isp, 0>;    TEST((std::same_as<T, int>));          }
    {  using T = AtIndex<list_isp, 1>;    TEST((std::same_as<T, std::string>));  }
    {  using T = AtIndex<list_isp, 2>;    TEST((std::same_as<T, void*>));        }
    {  using T = AtIndex<list_isp, 3>;    TEST((std::same_as<T, Nil>));          }
    {  using T = AtIndex<list_isp, 4>;    TEST((std::same_as<T, Nil>));          }
    {  using T = AtIndex<list_isps, -1>;  TEST((std::same_as<T, Nil>));          }
    {  using T = AtIndex<list_isps, 0>;   TEST((std::same_as<T, int>));          }
    {  using T = AtIndex<list_isps, 1>;   TEST((std::same_as<T, std::string>));  }
    {  using T = AtIndex<list_isps, 2>;   TEST((std::same_as<T, void*>));        }
    {  using T = AtIndex<list_isps, 3>;   TEST((std::same_as<T, std::string>));  }
    {  using T = AtIndex<list_isps, 4>;   TEST((std::same_as<T, Nil>));          }
    {  using T = AtIndex<list_isps, 5>;   TEST((std::same_as<T, Nil>));          }

}

void test_rs_core_typelist_head() {

    using list_i    = Typelist<int>;
    using list_is   = Typelist<int, std::string>;
    using list_isp  = Typelist<int, std::string, void*>;

    TEST((std::same_as<Head<Nil>,       Nil>));
    TEST((std::same_as<Head<list_i>,    int>));
    TEST((std::same_as<Head<list_is>,   int>));
    TEST((std::same_as<Head<list_isp>,  int>));

}

void test_rs_core_typelist_tail() {

    using list_i    = Typelist<int>;
    using list_s    = Typelist<std::string>;
    using list_is   = Typelist<int, std::string>;
    using list_sp   = Typelist<std::string, void*>;
    using list_isp  = Typelist<int, std::string, void*>;

    TEST((std::same_as<Tail<Nil>,       Nil>));
    TEST((std::same_as<Tail<list_i>,    Nil>));
    TEST((std::same_as<Tail<list_is>,   list_s>));
    TEST((std::same_as<Tail<list_isp>,  list_sp>));

}

void test_rs_core_typelist_most() {

    using list_i    = Typelist<int>;
    using list_is   = Typelist<int, std::string>;
    using list_isp  = Typelist<int, std::string, void*>;

    TEST((std::same_as<Most<Nil>,       Nil>));
    TEST((std::same_as<Most<list_i>,    Nil>));
    TEST((std::same_as<Most<list_is>,   list_i>));
    TEST((std::same_as<Most<list_isp>,  list_is>));

}

void test_rs_core_typelist_last() {

    using list_i    = Typelist<int>;
    using list_is   = Typelist<int, std::string>;
    using list_isp  = Typelist<int, std::string, void*>;

    TEST((std::same_as<Last<Nil>,       Nil>));
    TEST((std::same_as<Last<list_i>,    int>));
    TEST((std::same_as<Last<list_is>,   std::string>));
    TEST((std::same_as<Last<list_isp>,  void*>));

}

void test_rs_core_typelist_max_min() {

    using list_i     = Typelist<int>;
    using list_is    = Typelist<int, std::string>;
    using list_isp   = Typelist<int, std::string, void*>;
    using list_isps  = Typelist<int, std::string, void*, std::string>;

    {  using T = Max<Nil, CompareTypes>;        TEST((std::same_as<T, Nil>));          }
    {  using T = Max<list_i, CompareTypes>;     TEST((std::same_as<T, int>));          }
    {  using T = Max<list_is, CompareTypes>;    TEST((std::same_as<T, std::string>));  }
    {  using T = Max<list_isp, CompareTypes>;   TEST((std::same_as<T, std::string>));  }
    {  using T = Max<list_isps, CompareTypes>;  TEST((std::same_as<T, std::string>));  }
    {  using T = Min<Nil, CompareTypes>;        TEST((std::same_as<T, Nil>));          }
    {  using T = Min<list_i, CompareTypes>;     TEST((std::same_as<T, int>));          }
    {  using T = Min<list_is, CompareTypes>;    TEST((std::same_as<T, int>));          }
    {  using T = Min<list_isp, CompareTypes>;   TEST((std::same_as<T, int>));          }
    {  using T = Min<list_isps, CompareTypes>;  TEST((std::same_as<T, int>));          }

}

void test_rs_core_typelist_fold() {

    using list_i     = Typelist<int>;
    using list_is    = Typelist<int, std::string>;
    using list_isp   = Typelist<int, std::string, void*>;
    using list_isps  = Typelist<int, std::string, void*, std::string>;

    TEST_EQUAL((Pattern<FoldLeft<Nil, MakePair, Nil>>::str()),         "*");
    TEST_EQUAL((Pattern<FoldLeft<list_i, MakePair, Nil>>::str()),      "(*i)");
    TEST_EQUAL((Pattern<FoldLeft<list_is, MakePair, Nil>>::str()),     "((*i)s)");
    TEST_EQUAL((Pattern<FoldLeft<list_isp, MakePair, Nil>>::str()),    "(((*i)s)p)");
    TEST_EQUAL((Pattern<FoldLeft<list_isps, MakePair, Nil>>::str()),   "((((*i)s)p)s)");
    TEST_EQUAL((Pattern<FoldRight<Nil, MakePair, Nil>>::str()),        "*");
    TEST_EQUAL((Pattern<FoldRight<list_i, MakePair, Nil>>::str()),     "(i*)");
    TEST_EQUAL((Pattern<FoldRight<list_is, MakePair, Nil>>::str()),    "(i(s*))");
    TEST_EQUAL((Pattern<FoldRight<list_isp, MakePair, Nil>>::str()),   "(i(s(p*)))");
    TEST_EQUAL((Pattern<FoldRight<list_isps, MakePair, Nil>>::str()),  "(i(s(p(s*))))");
    TEST_EQUAL((Pattern<Reduce<Nil, MakePair>>::str()),                "*");
    TEST_EQUAL((Pattern<Reduce<list_i, MakePair>>::str()),             "i");
    TEST_EQUAL((Pattern<Reduce<list_is, MakePair>>::str()),            "(is)");
    TEST_EQUAL((Pattern<Reduce<list_isp, MakePair>>::str()),           "((is)p)");
    TEST_EQUAL((Pattern<Reduce<list_isps, MakePair>>::str()),          "(((is)p)s)");

}

void test_rs_core_typelist_make_set() {

    using list_i     = Typelist<int>;
    using list_ips   = Typelist<int, void*, std::string>;
    using list_isp   = Typelist<int, std::string, void*>;
    using list_iisp  = Typelist<int, int, std::string, void*>;
    using list_issp  = Typelist<int, std::string, std::string, void*>;
    using list_ispp  = Typelist<int, std::string, void*, void*>;

    {  using T = MakeSet<Nil, CompareTypes>;        TEST((std::same_as<T, Nil>));       }
    {  using T = MakeSet<list_i, CompareTypes>;     TEST((std::same_as<T, list_i>));    }
    {  using T = MakeSet<list_isp, CompareTypes>;   TEST((std::same_as<T, list_ips>));  }
    {  using T = MakeSet<list_iisp, CompareTypes>;  TEST((std::same_as<T, list_ips>));  }
    {  using T = MakeSet<list_issp, CompareTypes>;  TEST((std::same_as<T, list_ips>));  }
    {  using T = MakeSet<list_ispp, CompareTypes>;  TEST((std::same_as<T, list_ips>));  }

}

void test_rs_core_typelist_map() {

    using list_i     = Typelist<int>;
    using list_is    = Typelist<int, std::string>;
    using list_isp   = Typelist<int, std::string, void*>;
    using list_isps  = Typelist<int, std::string, void*, std::string>;
    using ptrs_i     = Typelist<int*>;
    using ptrs_is    = Typelist<int*, std::string*>;
    using ptrs_isp   = Typelist<int*, std::string*, void**>;
    using ptrs_isps  = Typelist<int*, std::string*, void**, std::string*>;

    {  using T = Map<Nil, MakePtr>;        TEST((std::same_as<T, Nil>));        }
    {  using T = Map<list_i, MakePtr>;     TEST((std::same_as<T, ptrs_i>));     }
    {  using T = Map<list_is, MakePtr>;    TEST((std::same_as<T, ptrs_is>));    }
    {  using T = Map<list_isp, MakePtr>;   TEST((std::same_as<T, ptrs_isp>));   }
    {  using T = Map<list_isps, MakePtr>;  TEST((std::same_as<T, ptrs_isps>));  }

}

void test_rs_core_typelist_partial_reduce() {

    using list_i      = Typelist<int>;
    using list_s      = Typelist<std::string>;
    using list_ss     = Typelist<std::string, std::string>;
    using list_isp    = Typelist<int, std::string, void*>;
    using list_iisp   = Typelist<int, int, std::string, void*>;
    using list_ispp   = Typelist<int, std::string, void*, void*>;
    using list_issp   = Typelist<int, std::string, std::string, void*>;
    using list_spsp   = Typelist<std::string, void*, std::string, void*>;
    using list_iiisp  = Typelist<int, int, int, std::string, void*>;
    using list_isppp  = Typelist<int, std::string, void*, void*, void*>;
    using list_isssp  = Typelist<int, std::string, std::string, std::string, void*>;

    {  using T = PartialReduce<Nil, std::is_same, Unify>;         TEST((std::same_as<T, Nil>));        }
    {  using T = PartialReduce<list_i, std::is_same, Unify>;      TEST((std::same_as<T, list_i>));     }
    {  using T = PartialReduce<list_ss, std::is_same, Unify>;     TEST((std::same_as<T, list_s>));     }
    {  using T = PartialReduce<list_isp, std::is_same, Unify>;    TEST((std::same_as<T, list_isp>));   }
    {  using T = PartialReduce<list_iisp, std::is_same, Unify>;   TEST((std::same_as<T, list_isp>));   }
    {  using T = PartialReduce<list_iiisp, std::is_same, Unify>;  TEST((std::same_as<T, list_isp>));   }
    {  using T = PartialReduce<list_issp, std::is_same, Unify>;   TEST((std::same_as<T, list_isp>));   }
    {  using T = PartialReduce<list_isssp, std::is_same, Unify>;  TEST((std::same_as<T, list_isp>));   }
    {  using T = PartialReduce<list_ispp, std::is_same, Unify>;   TEST((std::same_as<T, list_isp>));   }
    {  using T = PartialReduce<list_isppp, std::is_same, Unify>;  TEST((std::same_as<T, list_isp>));   }
    {  using T = PartialReduce<list_spsp, std::is_same, Unify>;   TEST((std::same_as<T, list_spsp>));  }

}

void test_rs_core_typelist_remove() {

    using list_i     = Typelist<int>;
    using list_s     = Typelist<std::string>;
    using list_ip    = Typelist<int, void*>;
    using list_is    = Typelist<int, std::string>;
    using list_ss    = Typelist<std::string, std::string>;
    using list_sps   = Typelist<std::string, void*, std::string>;
    using list_isps  = Typelist<int, std::string, void*, std::string>;

    {  using T = Remove<Nil, int>;                     TEST((std::same_as<T, Nil>));        }
    {  using T = Remove<list_i, int>;                  TEST((std::same_as<T, Nil>));        }
    {  using T = Remove<list_s, int>;                  TEST((std::same_as<T, list_s>));     }
    {  using T = Remove<list_is, int>;                 TEST((std::same_as<T, list_s>));     }
    {  using T = Remove<list_ss, int>;                 TEST((std::same_as<T, list_ss>));    }
    {  using T = Remove<list_ss, std::string>;         TEST((std::same_as<T, Nil>));        }
    {  using T = Remove<list_isps, int>;               TEST((std::same_as<T, list_sps>));   }
    {  using T = Remove<list_isps, std::string>;       TEST((std::same_as<T, list_ip>));    }
    {  using T = Remove<list_isps, float>;             TEST((std::same_as<T, list_isps>));  }
    {  using T = RemoveIf<Nil, std::is_scalar>;        TEST((std::same_as<T, Nil>));        }
    {  using T = RemoveIf<list_i, std::is_scalar>;     TEST((std::same_as<T, Nil>));        }
    {  using T = RemoveIf<list_s, std::is_scalar>;     TEST((std::same_as<T, list_s>));     }
    {  using T = RemoveIf<list_is, std::is_scalar>;    TEST((std::same_as<T, list_s>));     }
    {  using T = RemoveIf<list_ss, std::is_scalar>;    TEST((std::same_as<T, list_ss>));    }
    {  using T = RemoveIf<list_isps, std::is_scalar>;  TEST((std::same_as<T, list_ss>));    }

}

void test_rs_core_typelist_reverse() {

    using list_i     = Typelist<int>;
    using list_is    = Typelist<int, std::string>;
    using list_ps    = Typelist<void*, std::string>;
    using list_si    = Typelist<std::string, int>;
    using list_sp    = Typelist<std::string, void*>;
    using list_isp   = Typelist<int, std::string, void*>;
    using list_psi   = Typelist<void*, std::string, int>;
    using list_isps  = Typelist<int, std::string, void*, std::string>;
    using list_spsi  = Typelist<std::string, void*, std::string, int>;

    TEST((std::same_as<Reverse<Nil>,        Nil>));
    TEST((std::same_as<Reverse<list_i>,     list_i>));
    TEST((std::same_as<Reverse<list_is>,    list_si>));
    TEST((std::same_as<Reverse<list_sp>,    list_ps>));
    TEST((std::same_as<Reverse<list_isp>,   list_psi>));
    TEST((std::same_as<Reverse<list_isps>,  list_spsi>));

}

void test_rs_core_typelist_select() {

    using list_i     = Typelist<int>;
    using list_s     = Typelist<std::string>;
    using list_ip    = Typelist<int, void*>;
    using list_is    = Typelist<int, std::string>;
    using list_ss    = Typelist<std::string, std::string>;
    using list_isps  = Typelist<int, std::string, void*, std::string>;

    {  using T = Select<Nil, std::is_scalar>;        TEST((std::same_as<T, Nil>));      }
    {  using T = Select<list_i, std::is_scalar>;     TEST((std::same_as<T, list_i>));   }
    {  using T = Select<list_s, std::is_scalar>;     TEST((std::same_as<T, Nil>));      }
    {  using T = Select<list_is, std::is_scalar>;    TEST((std::same_as<T, list_i>));   }
    {  using T = Select<list_ss, std::is_scalar>;    TEST((std::same_as<T, Nil>));      }
    {  using T = Select<list_isps, std::is_scalar>;  TEST((std::same_as<T, list_ip>));  }

}

void test_rs_core_typelist_sort() {

    using list_i     = Typelist<int>;
    using list_ips   = Typelist<int, void*, std::string>;
    using list_isp   = Typelist<int, std::string, void*>;
    using list_iips  = Typelist<int, int, void*, std::string>;
    using list_iisp  = Typelist<int, int, std::string, void*>;
    using list_ipps  = Typelist<int, void*, void*, std::string>;
    using list_ipss  = Typelist<int, void*, std::string, std::string>;
    using list_ispp  = Typelist<int, std::string, void*, void*>;
    using list_issp  = Typelist<int, std::string, std::string, void*>;
    using list_pqr   = Typelist<void*, char*, int*>;
    using list_prq   = Typelist<void*, int*, char*>;
    using list_qpr   = Typelist<char*, void*, int*>;
    using list_qrp   = Typelist<char*, int*, void*>;
    using list_rpq   = Typelist<int*, void*, char*>;
    using list_rqp   = Typelist<int*, char*, void*>;

    {  using T = Sort<Nil, CompareTypes>;        TEST((std::same_as<T, Nil>));        }
    {  using T = Sort<list_i, CompareTypes>;     TEST((std::same_as<T, list_i>));     }
    {  using T = Sort<list_isp, CompareTypes>;   TEST((std::same_as<T, list_ips>));   }
    {  using T = Sort<list_iisp, CompareTypes>;  TEST((std::same_as<T, list_iips>));  }
    {  using T = Sort<list_issp, CompareTypes>;  TEST((std::same_as<T, list_ipss>));  }
    {  using T = Sort<list_ispp, CompareTypes>;  TEST((std::same_as<T, list_ipps>));  }
    {  using T = Sort<list_pqr, CompareTypes>;   TEST((std::same_as<T, list_pqr>));   }
    {  using T = Sort<list_prq, CompareTypes>;   TEST((std::same_as<T, list_prq>));   }
    {  using T = Sort<list_qpr, CompareTypes>;   TEST((std::same_as<T, list_qpr>));   }
    {  using T = Sort<list_qrp, CompareTypes>;   TEST((std::same_as<T, list_qrp>));   }
    {  using T = Sort<list_rpq, CompareTypes>;   TEST((std::same_as<T, list_rpq>));   }
    {  using T = Sort<list_rqp, CompareTypes>;   TEST((std::same_as<T, list_rqp>));   }

}

void test_rs_core_typelist_unique() {

    using list_i       = Typelist<int>;
    using list_s       = Typelist<std::string>;
    using list_sp      = Typelist<std::string, void*>;
    using list_ss      = Typelist<std::string, std::string>;
    using list_isp     = Typelist<int, std::string, void*>;
    using list_iisp    = Typelist<int, int, std::string, void*>;
    using list_ispp    = Typelist<int, std::string, void*, void*>;
    using list_issp    = Typelist<int, std::string, std::string, void*>;
    using list_spsp    = Typelist<std::string, void*, std::string, void*>;
    using list_iiisp   = Typelist<int, int, int, std::string, void*>;
    using list_isppp   = Typelist<int, std::string, void*, void*, void*>;
    using list_isssp   = Typelist<int, std::string, std::string, std::string, void*>;
    using list_ispisp  = Typelist<int, std::string, void*, int, std::string, void*>;

    TEST((std::same_as<Unique<Nil>,          Nil>));
    TEST((std::same_as<Unique<list_i>,       list_i>));
    TEST((std::same_as<Unique<list_ss>,      list_s>));
    TEST((std::same_as<Unique<list_isp>,     list_isp>));
    TEST((std::same_as<Unique<list_iisp>,    list_isp>));
    TEST((std::same_as<Unique<list_iiisp>,   list_isp>));
    TEST((std::same_as<Unique<list_issp>,    list_isp>));
    TEST((std::same_as<Unique<list_isssp>,   list_isp>));
    TEST((std::same_as<Unique<list_ispp>,    list_isp>));
    TEST((std::same_as<Unique<list_isppp>,   list_isp>));
    TEST((std::same_as<Unique<list_spsp>,    list_spsp>));
    TEST((std::same_as<Unique<list_ispisp>,  list_ispisp>));

    TEST((std::same_as<FullyUnique<Nil>,          Nil>));
    TEST((std::same_as<FullyUnique<list_i>,       list_i>));
    TEST((std::same_as<FullyUnique<list_ss>,      list_s>));
    TEST((std::same_as<FullyUnique<list_isp>,     list_isp>));
    TEST((std::same_as<FullyUnique<list_iisp>,    list_isp>));
    TEST((std::same_as<FullyUnique<list_iiisp>,   list_isp>));
    TEST((std::same_as<FullyUnique<list_issp>,    list_isp>));
    TEST((std::same_as<FullyUnique<list_isssp>,   list_isp>));
    TEST((std::same_as<FullyUnique<list_ispp>,    list_isp>));
    TEST((std::same_as<FullyUnique<list_isppp>,   list_isp>));
    TEST((std::same_as<FullyUnique<list_spsp>,    list_sp>));
    TEST((std::same_as<FullyUnique<list_ispisp>,  list_isp>));

}

void test_rs_core_typelist_zip() {

    using list_i       = Typelist<int>;
    using list_s       = Typelist<std::string>;
    using list_is      = Typelist<int, std::string>;
    using list_sp      = Typelist<std::string, void*>;
    using list_isp     = Typelist<int, std::string, void*>;
    using list_spi     = Typelist<std::string, void*, int>;
    using zip_i_s      = Typelist<MakePair<int, std::string>>;
    using zip_is_sp    = Typelist<MakePair<int, std::string>, MakePair<std::string, void*>>;
    using zip_isp_spi  = Typelist<MakePair<int, std::string>, MakePair<std::string, void*>, MakePair<void*, int>>;

    {  using T = Zip<Nil, Nil, MakePair>;            TEST((std::same_as<T, Nil>));          }
    {  using T = Zip<list_i, list_s, MakePair>;      TEST((std::same_as<T, zip_i_s>));      }
    {  using T = Zip<list_is, list_sp, MakePair>;    TEST((std::same_as<T, zip_is_sp>));    }
    {  using T = Zip<list_isp, list_spi, MakePair>;  TEST((std::same_as<T, zip_isp_spi>));  }

}

void test_rs_core_typelist_all_any_none_of() {

    using list_ints  = Typelist<short, int, long>;
    using list_strs  = Typelist<std::string, std::wstring>;
    using list_both  = Typelist<short, int, std::string, long>;

    TEST((AllOf<Nil, std::is_scalar>));
    TEST((AllOf<list_ints, std::is_scalar>));
    TEST((! AllOf<list_strs, std::is_scalar>));
    TEST((! AllOf<list_both, std::is_scalar>));
    TEST((! AnyOf<Nil, std::is_scalar>));
    TEST((AnyOf<list_ints, std::is_scalar>));
    TEST((! AnyOf<list_strs, std::is_scalar>));
    TEST((AnyOf<list_both, std::is_scalar>));
    TEST((NoneOf<Nil, std::is_scalar>));
    TEST((! NoneOf<list_ints, std::is_scalar>));
    TEST((NoneOf<list_strs, std::is_scalar>));
    TEST((! NoneOf<list_both, std::is_scalar>));

}

void test_rs_core_typelist_contains() {

    using list_i     = Typelist<int>;
    using list_is    = Typelist<int, std::string>;
    using list_issp  = Typelist<int, std::string, std::string, void*>;

    TEST((! Contains<Nil, int>));
    TEST((Contains<list_i, int>));
    TEST((! Contains<list_i, std::string>));
    TEST((Contains<list_is, int>));
    TEST((Contains<list_is, std::string>));
    TEST((! Contains<list_is, void*>));
    TEST((Contains<list_issp, int>));
    TEST((Contains<list_issp, std::string>));
    TEST((Contains<list_issp, void*>));
    TEST((! Contains<list_issp, char>));

}

void test_rs_core_typelist_count() {

    using list_i     = Typelist<int>;
    using list_is    = Typelist<int, std::string>;
    using list_isp   = Typelist<int, std::string, void*>;
    using list_isps  = Typelist<int, std::string, void*, std::string>;

    TEST_EQUAL((Count<Nil, std::string>),                0);
    TEST_EQUAL((Count<list_i, std::string>),             0);
    TEST_EQUAL((Count<list_is, std::string>),            1);
    TEST_EQUAL((Count<list_isp, std::string>),           1);
    TEST_EQUAL((Count<list_isps, std::string>),          2);
    TEST_EQUAL((CountIf<Nil, std::is_scalar>),           0);
    TEST_EQUAL((CountIf<list_i, std::is_scalar>),        1);
    TEST_EQUAL((CountIf<list_is, std::is_scalar>),       1);
    TEST_EQUAL((CountIf<list_isp, std::is_scalar>),      2);
    TEST_EQUAL((CountIf<list_isps, std::is_scalar>),     2);
    TEST_EQUAL((CountIfNot<Nil, std::is_scalar>),        0);
    TEST_EQUAL((CountIfNot<list_i, std::is_scalar>),     0);
    TEST_EQUAL((CountIfNot<list_is, std::is_scalar>),    1);
    TEST_EQUAL((CountIfNot<list_isp, std::is_scalar>),   1);
    TEST_EQUAL((CountIfNot<list_isps, std::is_scalar>),  2);

}

void test_rs_core_typelist_find() {

    using list_i     = Typelist<int>;
    using list_s     = Typelist<std::string>;
    using list_is    = Typelist<int, std::string>;
    using list_si    = Typelist<std::string, int>;
    using list_sss   = Typelist<std::string, std::string, std::string>;
    using list_iisp  = Typelist<int, int, std::string, void*>;
    using list_issp  = Typelist<int, std::string, std::string, void*>;

    TEST_EQUAL((Find<Nil, int>),                        -1);
    TEST_EQUAL((Find<list_i, int>),                     0);
    TEST_EQUAL((Find<list_i, std::string>),             -1);
    TEST_EQUAL((Find<list_is, int>),                    0);
    TEST_EQUAL((Find<list_is, std::string>),            1);
    TEST_EQUAL((Find<list_is, void*>),                  -1);
    TEST_EQUAL((Find<list_issp, int>),                  0);
    TEST_EQUAL((Find<list_issp, std::string>),          1);
    TEST_EQUAL((Find<list_issp, void*>),                3);
    TEST_EQUAL((Find<list_issp, char>),                 -1);
    TEST_EQUAL((FindIf<Nil, std::is_scalar>),           -1);
    TEST_EQUAL((FindIf<list_i, std::is_scalar>),        0);
    TEST_EQUAL((FindIf<list_s, std::is_scalar>),        -1);
    TEST_EQUAL((FindIf<list_is, std::is_scalar>),       0);
    TEST_EQUAL((FindIf<list_si, std::is_scalar>),       1);
    TEST_EQUAL((FindIf<list_sss, std::is_scalar>),      -1);
    TEST_EQUAL((FindIfNot<Nil, std::is_scalar>),        -1);
    TEST_EQUAL((FindIfNot<list_i, std::is_scalar>),     -1);
    TEST_EQUAL((FindIfNot<list_s, std::is_scalar>),     0);
    TEST_EQUAL((FindIfNot<list_is, std::is_scalar>),    1);
    TEST_EQUAL((FindIfNot<list_si, std::is_scalar>),    0);
    TEST_EQUAL((FindIfNot<list_iisp, std::is_scalar>),  2);

}

void test_rs_core_typelist_is_sorted() {

    using list_i     = Typelist<int>;
    using list_ips   = Typelist<int, void*, std::string>;
    using list_isp   = Typelist<int, std::string, void*>;
    using list_iips  = Typelist<int, int, void*, std::string>;
    using list_iisp  = Typelist<int, int, std::string, void*>;
    using list_ipps  = Typelist<int, void*, void*, std::string>;
    using list_ipss  = Typelist<int, void*, std::string, std::string>;
    using list_ispp  = Typelist<int, std::string, void*, void*>;
    using list_issp  = Typelist<int, std::string, std::string, void*>;
    using list_pqr   = Typelist<void*, char*, int*>;
    using list_prq   = Typelist<void*, int*, char*>;
    using list_qpr   = Typelist<char*, void*, int*>;
    using list_qrp   = Typelist<char*, int*, void*>;
    using list_rpq   = Typelist<int*, void*, char*>;
    using list_rqp   = Typelist<int*, char*, void*>;

    TEST((IsSorted<list_i, CompareTypes>));
    TEST((IsSorted<list_ips, CompareTypes>));
    TEST((! IsSorted<list_isp, CompareTypes>));
    TEST((IsSorted<list_iips, CompareTypes>));
    TEST((! IsSorted<list_iisp, CompareTypes>));
    TEST((IsSorted<list_ipps, CompareTypes>));
    TEST((IsSorted<list_ipss, CompareTypes>));
    TEST((! IsSorted<list_ispp, CompareTypes>));
    TEST((! IsSorted<list_issp, CompareTypes>));
    TEST((IsSorted<list_pqr, CompareTypes>));
    TEST((IsSorted<list_prq, CompareTypes>));
    TEST((IsSorted<list_qpr, CompareTypes>));
    TEST((IsSorted<list_qrp, CompareTypes>));
    TEST((IsSorted<list_rpq, CompareTypes>));
    TEST((IsSorted<list_rqp, CompareTypes>));

}

void test_rs_core_typelist_is_unique() {

    using list_i     = Typelist<int>;
    using list_ii    = Typelist<int, int>;
    using list_is    = Typelist<int, std::string>;
    using list_isp   = Typelist<int, std::string, void*>;
    using list_iis   = Typelist<int, int, std::string>;
    using list_isi   = Typelist<int, std::string, int>;
    using list_sii   = Typelist<std::string, int, int>;
    using list_ipsw  = Typelist<int, void*, std::string, std::wstring>;
    using list_isps  = Typelist<int, std::string, void*, std::string>;
    using list_issp  = Typelist<int, std::string, std::string, void*>;
    using list_sips  = Typelist<std::string, int, void*, std::string>;
    using list_sisp  = Typelist<std::string, int, std::string, void*>;
    using list_ipss  = Typelist<int, void*, std::string, std::string>;
    using list_ssip  = Typelist<std::string, std::string, int, void*>;

    TEST(IsUnique<Nil>);
    TEST(IsUnique<list_i>);
    TEST(! IsUnique<list_ii>);
    TEST(IsUnique<list_is>);
    TEST(IsUnique<list_isp>);
    TEST(! IsUnique<list_iis>);
    TEST(! IsUnique<list_isi>);
    TEST(! IsUnique<list_sii>);
    TEST(IsUnique<list_ipsw>);
    TEST(! IsUnique<list_isps>);
    TEST(! IsUnique<list_issp>);
    TEST(! IsUnique<list_sips>);
    TEST(! IsUnique<list_sisp>);
    TEST(! IsUnique<list_ipss>);
    TEST(! IsUnique<list_ssip>);

}
