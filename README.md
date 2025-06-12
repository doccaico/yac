## YACC

| Role | Header |
| - | - |
| Dynamic Array | [yacc_da.h](/yacc_da.h) |
| String View | [yacc_sv.h](/yacc_sv.h) |
| String Builder | [yacc_sb.h](/yacc_sb.h) |

### Testing
```sh
# yacc_da.h (/GF = eliminate duplicate strings)

$ cd tests

$ cl.exe /nologo /std:c11 /GF /W4 /WX yacc_da_test.c && .\yacc_da_test.exe
```

### Ref
- [tsoding's nob.h](https://github.com/tsoding/nob.h/blob/main/nob.h)
- [saracalihan's da.h](https://github.com/saracalihan/rey/blob/main/src/da.h)
- [belyivadim's cghost.h](https://github.com/belyivadim/cghost/blob/main/cghost.h)
- [ZIG's ArrayList](https://ziglang.org/documentation/master/std/#std.array_list.ArrayList)
