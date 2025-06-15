## YAC

Only tested on Windows (cl.exe).

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
