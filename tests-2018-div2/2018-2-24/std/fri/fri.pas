program fri(input,output);
var
  a:array[1..1005] of integer;
  ans,n,i,j:integer;
  str:string;
begin
  assign(input,'fri.in');
  assign(output,'fri.out');
  reset(input);
  readln(n);
  fillchar(a,sizeof(a),0);
  for i:=1 to n do
    begin
      readln(str);
      for j:=1 to length(str) do
        if (str[j]>='0') and (str[j]<='9') then inc(a[i],ord(str[j])-ord('0'))
        else inc(a[i],ord(str[j])-ord('A')+10);
    end;
  close(input);
  ans:=0;
  for i:=1 to n do
    for j:=i+1 to n do
      if a[i]=a[j] then inc(ans);
  rewrite(output);
  writeln(ans);
  close(output);
end.