program invest;

var i,j,k:longint;
    n:longint;
    s:string;
    a:array[1..1000000,1..4]of longint;
    pre:array[1..100000]of longint;
procedure setup;
begin
  assign(input,'invest.in');
  reset(input);
  assign(output,'invest.out');
  rewrite(output)
end;
procedure endit;
begin
  close(input);
  close(output)
end;
procedure updata(t:longint);
var i,j,t1,t2:longint;
    b:array[0..4,1..2]of longint;
begin
  while t<>1 do
    begin
      if odd(t) then begin t1:=t-1;t2:=t end
                else begin t1:=t;t2:=t+1 end;
      b[1,1]:=a[t1,1];b[1,2]:=a[t1,2];
      b[2,1]:=a[t1,3];b[2,2]:=a[t1,4];
      b[3,1]:=a[t2,1];b[3,2]:=a[t2,2];
      b[4,1]:=a[t2,3];b[4,2]:=a[t2,4];
      for i:=1 to 3 do
        for j:=i+1 to 4 do
          if (b[i,1]<b[j,1])or((b[i,1]=b[j,1])and(b[i,2]>b[j,2])) then
            begin
              b[0]:=b[i];
              b[i]:=b[j];
              b[j]:=b[0];
            end;
      t:=t div 2;
      a[t,1]:=b[1,1];a[t,2]:=b[1,2];
      a[t,3]:=b[2,1];a[t,4]:=b[2,2];
    end;
end;
begin
  setup;
  readln(n);
  k:=1;
  filldword(a,sizeof(a)div 4,-10000);
  while k<n do k:=k*2;
  for i:=1 to n do
    begin
      readln(pre[i]);
      a[i+k-1,1]:=0;
      a[i+k-1,2]:=i;
      updata(i+k-1);
    end;
  readln(s);
  while s<>'EndOfCurrentCase' do
    begin
      if s='Report' then writeln(a[1,2],' ',a[1,4])
                    else begin
                           val(copy(s,1,pos(' ',s)-1),i);
                           delete(s,1,pos(' ',s));
                           val(copy(s,1,length(s)),j);
                           a[i+k-1,1]:=j-pre[i];pre[i]:=j;
                           updata(i+k-1);
                         end;
      readln(s);
    end;
  endit;
end.

