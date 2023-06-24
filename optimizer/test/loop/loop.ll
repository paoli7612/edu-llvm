define i32 @sum_to_n(i32 %n) {
entry:
  %0 = icmp sgt i32 %n, 0
  br i1 %0, label %loop, label %exit

loop:
  %i.0 = phi i32 [ 0, %entry ], [ %i.next, %loop ]
  %sum.0 = phi i32 [ 0, %entry ], [ %sum.next, %loop ]
  %sum.next = add i32 %i.0, %sum.0
  %i.next = add i32 %i.0, 1
  %exitcond = icmp eq i32 %i.next, %n
  br i1 %exitcond, label %exit, label %loop

exit:
  %sum.exit = phi i32 [0, %entry], [%sum.next, %loop]
  ret i32 %sum.exit
}