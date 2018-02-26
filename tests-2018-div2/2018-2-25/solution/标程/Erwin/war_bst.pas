program tsoi2_war;
// BST
// by Erwin
// Expected Marks: 90
const
  LimitN=30000;
  LimitM=50000;
  LimitX=LimitN+LimitM;
  fi='war.in';
  fo='war.out';

var
  ch            :char;
  n,m,i,v,x,p,s :longint;
  locate        :array[1..LimitN] of longint;

  size          :longint;
  value         :array[1..LimitX] of longint;
  count         :array[1..LimitX] of longint;
  left          :array[1..LimitX] of longint;
  right         :array[1..LimitX] of longint;
  deleted       :array[1..LimitX] of boolean;

procedure insert(v:longint);
var p,f:longint;
begin
  if size=0 then
    begin
      value[1]:=v;
      left[1]:=-1;
      right[1]:=-1;
      count[1]:=0;
      size:=1;
    end
  else
    begin
      p:=1;
      while p<>-1 do
        begin
          f:=p;
          if v<value[p] then
            p:=left[p]
          else
            begin
              inc(count[p]);
              p:=right[p];
            end;
        end;
      inc(size);
      value[size]:=v;
      left[size]:=-1;
      right[size]:=-1;
      count[size]:=0;
      if v<value[f] then
        left[f]:=size
      else
        right[f]:=size;
    end;
end;

procedure kth(k:longint);
var p:longint;
begin
  p:=1;
  while p<>-1 do
    begin
      if (count[p]=k-1) and (not deleted[p]) then
        begin
          writeln(value[p]);
          exit;
        end;
      if count[p]>=k then
        p:=right[p]
      else
        begin
          dec(k,count[p]+ord(not deleted[p]));
          p:=left[p];
        end;
    end;
end;

procedure delete(p:longint);
var q,v:longint;
begin
  q:=1;
  while q<>p do
    if value[p]<value[q] then
      q:=left[q]
    else
      begin
        dec(count[q]);
        q:=right[q];
      end;
  deleted[p]:=true;
end;

begin
  assign(input,fi);
  reset(input);
  assign(output,fo);
  rewrite(output);
  readln(n); s:=n;
  for i:=1 to n do
    begin
      read(v);
      insert(v);
      locate[i]:=size;
    end;
  readln(m);
  for i:=1 to m do
    begin
      read(ch);
      if ch='Q' then
        begin
          readln(x);
          if x>s then
            writeln(-1)
          else
            kth(x);
        end
      else
        begin
          readln(p,x);
          if ch='A' then x:=-x;
          delete(locate[p]);
          if value[locate[p]]+x>0 then
            insert(value[locate[p]]+x)
          else
            dec(s);
          locate[p]:=size;
        end;
    end;
  writeln(s);
  close(input);
  close(output);
end.
