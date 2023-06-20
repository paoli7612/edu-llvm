; ModuleID = 'multiOUT.bc'
source_filename = "test/test-multi.ll"

define i32 @func(i32 %a) {
entry:
  %add = add i32 %a, 5
  %sub = sub i32 %add, 5
  ret i32 %a
}

define i32 @func3(i32 %a) {
entry:
  %sub = sub i32 %a, 5
  %add = add i32 %sub, 5
  ret i32 %a
}
