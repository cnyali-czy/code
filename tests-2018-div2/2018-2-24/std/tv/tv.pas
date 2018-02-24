Program Tv;
  Const last=1 shl 2;
  Var q:array[1..2,1..1100000]of longint;
      h:array[0..1100000]of boolean;
      a:array[1..20]of longint;
      n,i,j,k,s,m,f,r:longint;
Begin
  assign(input,'tv.in');
  assign(output,'tv.out');
  reset(input);rewrite(output);
  readln(n);s:=0;
  for i:=0 to n-1 do begin
    read(j);
    if j=1 then s:=s or (1 shl i);
  end;
  for i:=1 to n do begin
    read(k);a[i]:=not 0;
    for j:=1 to k do begin
      read(m);dec(m);
      a[i]:=a[i] and not (1 shl m);
    end;
  end;
  fillchar(h,sizeof(h),true);
  h[s]:=false;q[1,1]:=s;
  q[2,1]:=0;f:=1;r:=1;
  repeat
    k:=q[1,r];
    for i:=0 to n-1 do if k and (1 shl i)=0
      then begin
        j:=k and a[i+1];
        j:=j or (1 shl i);
        if j=last then begin
          writeln(q[2,r]+1);
          close(input);
          close(output);
          halt
        end;
        if h[j] then begin
          h[j]:=false;inc(f);
          q[1,f]:=j;
          q[2,f]:=q[2,r]+1
        end;
      end;
    inc(r)
  until r>f;
End.
