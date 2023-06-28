; ModuleID = 'algebraicOUT.bc'
source_filename = "test/test.ll"

define dso_local void @foo(i32 noundef %0) {
  %2 = mul nsw i32 %0, 16
  %3 = mul nsw i32 %2, %0
  %4 = sdiv i32 %3, %0
  %5 = sdiv i32 %3, 128
  %6 = sdiv i32 %4, 54
  %7 = sdiv i32 %3, 1
  %8 = sub nsw i32 %6, 0
  ret void
}
