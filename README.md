## YAC

| Role | Header |
| - | - |
| Dynamic Array | [yac_da.h](/yac_da.h) |
| Map (Ordered) | [yac_map.h](/yac_map.h) |
| String View | [yac_sv.h](/yac_sv.h) |
| String Builder | [yac_sb.h](/yac_sb.h) |

### Testing
```sh
# yac_da.h (/GF = eliminate duplicate strings)

$ cd tests

$ cl.exe /nologo /std:c11 /GF /W4 /WX -wd4709 yac_da_test.c && .\yac_da_test.exe
```

### Ref
- [tsoding's nob.h](https://github.com/tsoding/nob.h/blob/main/nob.h)
- [saracalihan's da.h](https://github.com/saracalihan/rey/blob/main/src/da.h)
- [belyivadim's cghost.h](https://github.com/belyivadim/cghost/blob/main/cghost.h)
- [ZIG's ArrayList](https://ziglang.org/documentation/master/std/#std.array_list.ArrayList)
