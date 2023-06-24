define void @decrement (i32 %i) {
    entry:
        br label %loop

    loop:
        %i_phi = phi i32 [%i, %entry], [%i_dec, %loop ]
        %cmp = icmp sgt i32 %i_phi, 0
        br i1 %cmp, label %loop, label %exit

    exit:
        ret void
}