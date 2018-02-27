program language;

var i,j,k:longint;
    n,m,t1,t2:longint;
    s,s1,s2:string;
    words:array[1..100]of string;
    g:array[1..100,1..100]of longint;
    path:array[1..100,1..100]of string;
procedure setup;
begin
  assign(input,'language.in');
  reset(input);
  assign(output,'language.out');
  rewrite(output);
end;
procedure endit;
begin
  close(input);
  close(output)
end;
function check(a,b:string):boolean;
var i:longint;
begin
  for i:=1 to length(a) do
    if a[i] in ['A'..'Z'] then a[i]:=chr(ord(a[i])-ord('A')+ord('a'));
  for i:=1 to length(a) do
    if b[i] in ['A'..'Z'] then b[i]:=chr(ord(b[i])-ord('A')+ord('a'));
  if a=b then check:=true
         else check:=false
end;
begin
  setup;
  readln(n,m);
  for i:=1 to n do
    readln(words[i]);
  fillchar(g,sizeof(g),0);
  for i:=1 to m do
    begin
      readln(s);
      k:=pos(' ',s);
      s1:=copy(s,1,k-1);
      s2:=copy(s,k+1,length(s)-k);
      for j:=1 to n do
        if check(s1,words[j]) then t1:=j;
      for j:=1 to n do
        if check(s2,words[j]) then t2:=j;
      g[t1,t2]:=-1;
    end;
  for i:=1 to n do
    for j:=1 to n do
      path[i,j]:=chr(ord('0')+i)+chr(ord('0')+j);
  for k:=1 to n do
    for i:=1 to n do
      for j:=1 to n do
        begin
          if (i=j)or(j=k)or(k=i)or(g[i,k]=0)or(g[k,j]=0)then continue;
          if g[i,k]+g[k,j]<g[i,j] then
            begin
              g[i,j]:=g[i,k]+g[k,j];
              path[i,j]:=copy(path[i,k],1,length(path[i,k])-1)+path[k,j];
            end;
        end;
   k:=0;
   for i:=1 to n do
     for j:=1 to n do
       if g[i,j]<k then
         begin
           k:=g[i,j];
           t1:=i;t2:=j;
         end;
    if k=0 then writeln(0)
           else writeln(-k+1);
    for i:=1 to length(path[t1,t2]) do
      begin
        if i<>1 then write(' ');
        write(words[ord(path[t1,t2][i])-ord('0')]);
      end;
    writeln;
  endit;
end.

