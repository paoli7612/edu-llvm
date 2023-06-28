; ModuleID = 'strengthOUT.bc'
source_filename = "test/test.ll"

define dso_local void @foo(i32 noundef %0) {
  ret void
}
