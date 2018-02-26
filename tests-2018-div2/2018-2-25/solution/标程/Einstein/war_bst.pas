Program	tsoi_standard;
{ TSOI War }

Const
inf	='war.in';
ouf	='war.out';
LimitN	=30000;

Var
hp	:array[0..LimitN]of longint;
bst	:array[0..LimitN]of longint;
l,r	:array[0..LimitN]of longint;
count	:array[0..LimitN]of longint;
n,m	:longint;
i,k,x	:longint;
root	:longint;
size	:longint;
free	:longint;
ch	:char;

function	insert(i,x:longint):longint;
begin
	if i=0 then
	begin
		if free=0 then
		begin
			inc(size);
			i:=size;
		end
		else
		begin
			i:=free;
			free:=0;
		end;
		bst[i]:=x;
		l[i]:=0;
		r[i]:=0;
		count[i]:=1;
	end
	else
	if x<bst[i] then
	begin
		inc(count[i]);
		l[i]:=insert(l[i],x);
	end
	else
	begin
		inc(count[i]);
		r[i]:=insert(r[i],x);
	end;
	insert:=i;
end;

function	find_min(i:longint):longint;
begin
	while l[i]<>0 do
		i:=l[i];
	find_min:=bst[i];
end;

function	remove(i,x:longint):longint;
begin
	dec(count[i]);
	if x<bst[i] then
		l[i]:=remove(l[i],x)
	else
	if x>bst[i] then
		r[i]:=remove(r[i],x)
	else
	if (l[i]>0)and(r[i]>0) then
	begin
		bst[i]:=find_min(r[i]);
		r[i]:=remove(r[i],bst[i]);
	end
	else
	begin
		free:=i;
		if l[i]=0 then
			exit(r[i])
		else	exit(l[i]);
	end;
	remove:=i;
end;

function	query(k:longint):longint;
var
i	:longint;
begin
	i:=root;
	while i<>0 do
	begin
		if k>count[r[i]]+1 then
		begin
			dec(k,count[r[i]]+1);
			i:=l[i];
		end
		else
		if k<=count[r[i]] then
			i:=r[i]
		else	exit(bst[i]);
	end;
end;

Begin
	assign(input,inf);
	reset(input);
	assign(output,ouf);
	rewrite(output);
	read(n);
	for i:=1 to n do
	begin
		read(hp[i]);
		root:=insert(root,hp[i]);
	end;
	readln(m);
	for i:=1 to m do
	begin
		read(ch);
		if ch='A' then
		begin
			readln(k,x);
			root:=remove(root,hp[k]);
			dec(hp[k],x);
			if hp[k]>0 then
				root:=insert(root,hp[k])
			else	dec(n);
		end
		else
		if ch='C' then
		begin
			readln(k,x);
			root:=remove(root,hp[k]);
			inc(hp[k],x);
			root:=insert(root,hp[k]);
		end
		else
		begin
			readln(k);
			if k>n then
				writeln(-1)
			else	writeln(query(k));
		end;
	end;
	writeln(n);
	close(input);
	close(output);
End.
