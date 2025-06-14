## YAC

| Role | Header |
| - | - |
| Dynamic Array | [yac_dynamic_array.h](/yac_dynamic_array.h) |
| Map (Ordered) | [yac_ordered_map.h](/yac_ordered_map.h) |
| Map (Unordered) | [yac_unordered_map.h](/yac_unordered_map.h) |
| String View | [yac_string_view.h](/yac_string_view.h) |
| String Builder | [yac_string_builder.h](/yac_string_builder.h) |

### Testing
```sh
# yac_dynamic_array.h (/GF = eliminate duplicate strings)

$ cd tests

$ cl.exe /nologo /std:c11 /GF /W4 -wd4709 yac_dynamic_array_test.c && .\yac_dynamic_array_test.exe
```

### Ref
- [tsoding's nob.h](https://github.com/tsoding/nob.h/blob/main/nob.h)
- [saracalihan's da.h](https://github.com/saracalihan/rey/blob/main/src/da.h)
- [belyivadim's cghost.h](https://github.com/belyivadim/cghost/blob/main/cghost.h)
- [ZIG's ArrayList](https://ziglang.org/documentation/master/std/#std.array_list.ArrayList)
- [ZSShen/C-Common-Data-Structures](https://github.com/ZSShen/C-Common-Data-Structures)
