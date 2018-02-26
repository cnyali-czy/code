program tsoi2_war;
// Treap
// by Erwin
// Expected Marks:100
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

  size,head     :longint;
  value         :array[1..LimitX] of longint;
  count         :array[1..LimitX] of longint;
  father        :array[1..LimitX] of longint;
  left          :array[1..LimitX] of longint;
  right         :array[1..LimitX] of longint;
  aux           :array[1..LimitX] of longint;
  deleted       :array[1..LimitX] of boolean;

procedure treap_adjust(var head:longint;p:longint);
var f:longint;
begin
  while (father[p]<>-1) and (aux[p]<aux[father[p]]) do
    begin
      f:=father[p];
      if head=f then head:=p;
      if father[f]<>-1 then
        if f=left[father[f]] then
          left[father[f]]:=p
        else
          right[father[f]]:=p;
      father[p]:=father[f];
      father[f]:=p;
      if p=left[f] then
        begin
          if right[p]<>-1 then
            father[right[p]]:=f;
          left[f]:=right[p];
          right[p]:=f;
          inc(count[p],count[f]+ord(not deleted[f]));
        end
      else
        begin
          if left[p]<>-1 then
            father[left[p]]:=f;
          right[f]:=left[p];
          left[p]:=f;
          dec(count[f],count[p]+ord(not deleted[p]));
        end;
    end;
end;

function newnode(v,l,r,f:longint):longint;
begin
  inc(size);
  value[size]:=v;
  left[size]:=l;
  right[size]:=r;
  father[size]:=f;
  aux[size]:=random(65535);
  count[size]:=0;
  newnode:=size;
end;

procedure insert(v,num:longint);
var p,f:longint;
begin
  if size=0 then
    begin
      head:=newnode(v,-1,-1,-1);
      locate[num]:=head;
    end
  else
    begin
      p:=head;
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
      p:=newnode(v,-1,-1,f);
      if v<value[f] then left[f]:=p
                    else right[f]:=p;
      locate[num]:=p;
      treap_adjust(head,p);
    end;
end;

procedure kth(k:longint);
var p:longint;
begin
  p:=head;
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
begin
  deleted[p]:=true;
  while father[p]<>-1 do
    begin
      if p=right[father[p]] then
        dec(count[father[p]]);
      p:=father[p];
    end;
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
      insert(v,i);
    end;
  readln(m);
  for i:=1 to m do
    begin
      read(ch);
      if ch='Q' then
        begin
          readln(x);
          if x>s then writeln(-1)
                 else kth(x);
        end
      else
        begin
          readln(p,x);
          if ch='A' then x:=-x;
          delete(locate[p]);
          if value[locate[p]]+x>0 then
            insert(value[locate[p]]+x,p)
          else
            dec(s);
        end;
    end;
  writeln(s);
  close(input);
  close(output);
end.
